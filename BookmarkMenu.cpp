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

    std::for_each(m_Bookmarks.begin(), m_Bookmarks.end(), [&](const auto& bookmark){
        bookmark->move(x, y);
        y += bookmark->height();
    });
}

void BookmarkMenu::AddBookmark(QWebEnginePage* page)
{
    auto newBookmark = std::make_shared<Bookmark>(this);

    newBookmark->setParent(this);
    newBookmark->SetTitle(page->title());
    newBookmark->SetUrl(page->url());
    newBookmark->resize(this->width(), BOOKMARK_HEIGHT);

    std::weak_ptr<Bookmark> weakBookmark = newBookmark;

    connect(&*newBookmark, &Bookmark::RemovePressed, [weakBookmark, this](){
        m_Bookmarks.erase(weakBookmark.lock());
    });

    connect(&*newBookmark, &Bookmark::RemovePressed, [weakBookmark, this](){
        m_Bookmarks.erase(weakBookmark.lock());
    });

    m_Bookmarks.insert(newBookmark);
}
