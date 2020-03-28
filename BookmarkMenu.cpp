#include "BookmarkMenu.h"

#include <QPaintEvent>
#include <QResizeEvent>

constexpr int BOOKMARK_HEIGHT = 30;

constexpr char CSV_SEPARATOR[] = "||";
constexpr char STORAGE_FILE[] = "bookmarks.csv";

BookmarkMenu::BookmarkMenu(QWidget *parent)
    : QMainWindow(parent)
{
    QFile bookmarksFile(STORAGE_FILE);
    bookmarksFile.open(QIODevice::ReadOnly);

    QTextStream in(&bookmarksFile);
    while (!in.atEnd())
    {
       QString line = in.readLine();
       auto dataList = line.split(CSV_SEPARATOR);

       BookmarkPage page(dataList[0], dataList[1]);
       this->AddBookmark(std::move(page));
    }

    bookmarksFile.close();
}

BookmarkMenu::~BookmarkMenu()
{
    QFile bookmarksFile(STORAGE_FILE);
    bookmarksFile.open(QIODevice::WriteOnly);
    QTextStream writeStream(&bookmarksFile);

    for (const auto& bookmarkPage : m_Bookmarks)
    {
        auto pageData = bookmarkPage->GetBookmarkData();
        writeStream << pageData.Url.toString() << CSV_SEPARATOR << pageData.Title << "\n";
    }

    bookmarksFile.close();
}

void BookmarkMenu::paintEvent(QPaintEvent *)
{
    int x = 0, y = 0;

    for (const auto& bookmark : m_Bookmarks)
    {
        bookmark->move(x, y);
        y += bookmark->height();
    }
}

void BookmarkMenu::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width(), height = BOOKMARK_HEIGHT;

    for (const auto& bookmark : m_Bookmarks)
    {
        bookmark->resize(width, height);
    }
}

void BookmarkMenu::AddBookmark(BookmarkPage page)
{
    auto newBookmark = std::make_unique<Bookmark>(this);

    newBookmark->setParent(this);
    newBookmark->SetInfo(page);
    newBookmark->show();
    newBookmark->resize(this->width(), BOOKMARK_HEIGHT);

    auto raw = newBookmark.get();

    auto itBookmark = m_Bookmarks.emplace(std::move(newBookmark)).first;

    connect(raw, &Bookmark::RemovePressed, [itBookmark, this](){
        m_Bookmarks.erase(itBookmark);
    });

    connect(raw, &Bookmark::HrefPressed, [this](QUrl url){
        emit this->BookmarkSelected(url);
    });
}
