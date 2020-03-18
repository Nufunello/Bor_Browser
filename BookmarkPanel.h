#ifndef BOOKMARKPANEL_H
#define BOOKMARKPANEL_H

#include "BookmarkMenu.h"

#include <QLabel>
#include <QWidget>

class BookmarkPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BookmarkPanel(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void AddBookmarkPressed();
    void OpenBookmarksPressed();

private:
    QPushButton m_BtnAdd;
    QPushButton m_BtnOpenBookmarks;

private:
    void moveButtons();

};

#endif // BOOKMARKPANEL_H
