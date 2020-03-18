#include "Tab.h"

#include <QResizeEvent>

Tab::Tab(QWidget *parent)
    : QWidget(parent)
{
    m_BtnToBeSelected = std::make_unique<QPushButton>(this);

    connect(&*m_BtnToBeSelected, &QPushButton::clicked, this, &Tab::Selected);
}

void Tab::UpdateTabInfo(QString title)
{
    m_BtnToBeSelected->setText(title);
}

void Tab::resizeEvent(QResizeEvent *event)
{
    m_BtnToBeSelected->resize(event->size());
}
