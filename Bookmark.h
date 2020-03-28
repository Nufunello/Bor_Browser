#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "BookmarkPage.h"

#include <QPushButton>
#include <QUrl>
#include <QWidget>

class Bookmark : public QWidget
{
    Q_OBJECT
public:
    explicit Bookmark(QWidget *parent = nullptr);

public:
    BookmarkPage GetBookmarkData();
    void         SetInfo(BookmarkPage);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void HrefPressed(QUrl);
    void RemovePressed();

private:
    QPushButton m_Href;
    QPushButton m_Remove;

private:
    BookmarkPage m_BookmarkData;

};

#endif // BOOKMARK_H
