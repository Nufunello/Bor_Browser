#include "VisitedHistory.h"

#include <QResizeEvent>

constexpr float TIME_LABEL_WIDTH_KOEF      = 0.15f;
constexpr float HREF_BUTTON_WIDTH_KOEF     = 0.7f;
constexpr float REMOVE_BUTTON_WIDTH_KOEF   = 0.1f;

VisitedHistory::VisitedHistory(QWidget *parent)
    : QWidget(parent)
{
    m_LblTime.setParent(this);
    m_BtnHref.setParent(this);
    m_BtnRemove.setParent(this);

    m_BtnRemove.setText("x");

    connect(&m_BtnRemove, &QPushButton::clicked, this, &VisitedHistory::RemovePressed);
    connect(&m_BtnHref,   &QPushButton::clicked, [this](){
        emit this->HrefPressed(m_Url);
    });
}

void VisitedHistory::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width(), height = event->size().height();

    m_LblTime.resize(width * TIME_LABEL_WIDTH_KOEF, height);
    m_BtnHref.resize(width * HREF_BUTTON_WIDTH_KOEF, height);
    m_BtnRemove.resize(width * REMOVE_BUTTON_WIDTH_KOEF, height);

    moveElements();
}

void VisitedHistory::SetInfo(VisitedPage page)
{
    m_Url = page.Url;
    m_Date = page.Date;

    m_LblTime.setText(m_Date.time().toString());
    m_BtnHref.setText(page.Title + "\n" + page.Url.toString());
}

QDateTime VisitedHistory::GetDate()
{
    return m_Date;
}

void VisitedHistory::moveElements()
{
    m_LblTime.move(5, 0);
    m_BtnHref.move(m_LblTime.x() + m_LblTime.width(), m_LblTime.y());
    m_BtnRemove.move(m_BtnHref.x() + m_BtnHref.width(), m_BtnHref.y());
}
