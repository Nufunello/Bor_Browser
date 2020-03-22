#include "Bookmark.h"

#include <QResizeEvent>

Bookmark::Bookmark(QWidget *parent)
    : QWidget(parent)
{
    m_Href.setParent(this);
    m_Remove.setParent(this);

    m_Remove.setText("x");

    connect(&m_Remove, &QPushButton::clicked, this, &Bookmark::RemovePressed);
    connect(&m_Href,   &QPushButton::clicked, [this](){
        emit this->HrefPressed(m_BookmarkData.Url);
    });
}

BookmarkPage Bookmark::GetBookmarkData()
{
    return m_BookmarkData;
}

void Bookmark::resizeEvent(QResizeEvent *event)
{
    m_Href.  resize(event->size().width() * 0.8, event->size().height());
    m_Remove.resize(event->size().width() * 0.2, event->size().height());

    m_Remove.move(m_Href.x() + m_Href.width(), m_Href.y());
}

void Bookmark::SetInfo(BookmarkPage page)
{
    m_BookmarkData = std::move(page);

    m_Href.setText(m_BookmarkData.Title);
}
