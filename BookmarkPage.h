#ifndef BOOKMARKPAGE_H
#define BOOKMARKPAGE_H

#include <QUrl>
#include <QWebEnginePage>


struct BookmarkPage
{
    inline BookmarkPage() = default;

    inline BookmarkPage(QUrl url, QString title)
    {
        Url   = std::move(url);
        Title = std::move(title);
    }

    inline BookmarkPage(QWebEnginePage* page)
    {
        Url   = page->url();
        Title = page->title();
    }

    QUrl    Url;
    QString Title;
};

#endif // BOOKMARKPAGE_H
