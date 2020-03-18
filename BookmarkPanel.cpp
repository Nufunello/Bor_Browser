#include "BookmarkPanel.h"

#include <QUrl>
#include <QResizeEvent>

constexpr int cButton = 2;

BookmarkPanel::BookmarkPanel(QWidget *parent)
    : QWidget(parent)
{
    m_BtnAdd.setParent(this);
    m_BtnOpenBookmarks.setParent(this);

    connect(&m_BtnAdd,           &QPushButton::clicked, this, &BookmarkPanel::AddBookmarkPressed);
    connect(&m_BtnOpenBookmarks, &QPushButton::clicked, this, &BookmarkPanel::OpenBookmarksPressed);
}

void BookmarkPanel::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width() / cButton , height = event->size().height();

    m_BtnAdd.resize(width, height);
    //m_BtnAdd.setPixmap(QPixmap("D:/c++/MentorShip/QT/Bor_Browser_Layouts/icons/UnBookmarked.png").scaled(m_BtnAdd.size()));

    m_BtnOpenBookmarks.resize(width, height);
    //m_BtnOpenBookmarks.setPixmap(QPixmap("D:/c++/MentorShip/QT/Bor_Browser_Layouts/icons/BookmarkList.jpg").scaled(m_BtnOpenBookmarks.size()));

    this->moveButtons();
}

void BookmarkPanel::moveButtons()
{
    m_BtnAdd.move(0, 0);
    m_BtnOpenBookmarks.move(m_BtnAdd.x() + m_BtnAdd.width(), m_BtnAdd.y());
}
