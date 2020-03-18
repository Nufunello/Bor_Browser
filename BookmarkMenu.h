#ifndef BOOKMARKMENU_H
#define BOOKMARKMENU_H

#include "Bookmark.h"

#include <set>

#include <QMainWindow>
#include <QWebEnginePage>
#include <QWidget>

struct BookmarkCompare
{
    bool operator()(const std::shared_ptr<Bookmark>& lhs, const std::shared_ptr<Bookmark>& rhs) const
    {
        return lhs->GetUrl() < rhs->GetUrl();
    }
};

class BookmarkMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit BookmarkMenu(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;

public:
    void AddBookmark(QWebEnginePage*);

signals:
    void BookmarkSelected(QUrl);

private:
    std::set<std::shared_ptr<Bookmark>, BookmarkCompare> m_Bookmarks;

};

#endif // BOOKMARKMENU_H
