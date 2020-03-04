#include "Tab.h"
#include <QResizeEvent>

#include "TabWrapper.h"

Tab::Tab(std::shared_ptr<TabWrapper> parent)
    : QWidget(&*parent)
{
    m_Btn = std::make_shared<QPushButton>(this);
    m_Btn->setText("Empty tab");

    connect(&*m_Btn, &QPushButton::clicked, this, &Tab::Selected);
}

void Tab::UpdateTab(QWebEnginePage *page)
{
    m_Btn->setText(page->title());
}

void Tab::resizeEvent(QResizeEvent *event)
{
    m_Btn->resize(event->size().width(), event->size().height());
}

void Tab::SetEnabled()
{
    this->m_Btn->setEnabled(true);
}

void Tab::SetDisabled()
{
    this->m_Btn->setDisabled(true);
}
