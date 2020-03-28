#include "BookmarkPanel.h"

#include <QUrl>
#include <QResizeEvent>

constexpr int cButton = 2;

BookmarkPanel::BookmarkPanel(QWidget *parent)
    : QWidget(parent)
{
    m_BtnAdd.setParent(this);
    m_BtnOpenBookmarks.setParent(this);

    m_BtnAdd.setText("Add");
    m_BtnOpenBookmarks.setText("Show");

    connect(&m_BtnAdd,           &QPushButton::clicked, this, &BookmarkPanel::AddBookmarkPressed);
    connect(&m_BtnOpenBookmarks, &QPushButton::clicked, this, &BookmarkPanel::OpenBookmarksPressed);
}

void BookmarkPanel::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width() / cButton , height = event->size().height();

    m_BtnAdd.resize(width, height);

    m_BtnOpenBookmarks.resize(width, height);
}

void BookmarkPanel::paintEvent(QPaintEvent *)
{
    m_BtnAdd.move(0, 0);
    m_BtnOpenBookmarks.move(m_BtnAdd.x() + m_BtnAdd.width(), m_BtnAdd.y());
}
