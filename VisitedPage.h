#ifndef VISITEDPAGE_H
#define VISITEDPAGE_H

#include <QWebEnginePage>

struct VisitedPage
{
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
