#include "BookmarkMenu.h"

#include <QPaintEvent>

constexpr int BOOKMARK_HEIGHT = 30;

BookmarkMenu::BookmarkMenu(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400, 400);
}

void BookmarkMenu::paintEvent(QPaintEvent *)
{
    int x = 0, y = 0;

    std::for_each(m_Bookmarks.begin(), m_Bookmarks.end(), [&](const std::unique_ptr<Bookmark>& bookmark){
        bookmark->move(x, y);
        y += bookmark->height();
    });
}

void BookmarkMenu::AddBookmark(QWebEnginePage* page)
{
    auto newBookmark = std::make_unique<Bookmark>(this);

    newBookmark->setParent(this);
    newBookmark->SetTitle(page->title());
    newBookmark->SetUrl(page->url());
    newBookmark->resize(this->width(), BOOKMARK_HEIGHT);

    connect(&*newBookmark, &Bookmark::RemovePressed, [&](){
        m_Bookmarks.erase(newBookmark);
    });

    m_Bookmarks.insert(std::move(newBookmark));
}
