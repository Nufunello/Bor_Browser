#ifndef VISITEDPAGE_H
#define VISITEDPAGE_H

#include <QWebEnginePage>

struct VisitedPage
{
    inline VisitedPage() = default;

    inline VisitedPage(QUrl url, QString title, QDateTime date)
    {
        Url   = std::move(url);
        Title = std::move(title);
        Date  = std::move(date);
    }

    inline VisitedPage(QWebEnginePage* page)
    {
        Url   = page->url();
        Title = page->title();
        Date  = QDateTime::currentDateTime();
    }

    QUrl      Url;
    QString   Title;
    QDateTime Date;

};

#endif // VISITEDPAGE_H
