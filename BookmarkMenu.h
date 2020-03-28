#ifndef BOOKMARKMENU_H
#define BOOKMARKMENU_H

#include "Bookmark.h"
#include "BookmarkPage.h"

#include <set>

#include <QMainWindow>
#include <QWebEnginePage>
#include <QWidget>

struct BookmarkCompare
{
    bool operator()(const std::unique_ptr<Bookmark>& lhs, const std::unique_ptr<Bookmark>& rhs) const
    {
        return lhs->GetBookmarkData().Url < rhs->GetBookmarkData().Url;
    }
};

class BookmarkMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit BookmarkMenu(QWidget *parent = nullptr);
    ~BookmarkMenu();

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;

public:
    void AddBookmark(BookmarkPage);

signals:
    void BookmarkSelected(QUrl);

private:
    std::set<std::unique_ptr<Bookmark>, BookmarkCompare> m_Bookmarks;

};

#endif // BOOKMARKMENU_H
