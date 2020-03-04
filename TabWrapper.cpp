#include "TabWrapper.h"
#include <QResizeEvent>

TabWrapper::TabWrapper(QWidget *parent)
    : QWidget(parent)
    , m_CurrentTab{nullptr}
{   
}

void TabWrapper::AddTab(std::shared_ptr<Tab> tab)
{
    m_Tabs.emplace_back(tab);
    this->ChangeTab(tab);
}

void TabWrapper::ChangeTab(std::shared_ptr<Tab> tab)
{
    this->setCurrentTabEnabled();
    m_CurrentTab = tab;
    this->setCurrentTabDisabled();
}

void TabWrapper::paintEvent(QPaintEvent *)
{
    int x = this->x();
    int y = this->y();

    std::for_each(m_Tabs.begin(), m_Tabs.end(), [&](std::shared_ptr<Tab> tab){
        tab->move(x, y);
        x += tab->width();
    });
}

void TabWrapper::resizeEvent(QResizeEvent *event)
{
    int wrapWidth = width();

    int width = (m_Tabs.size() != 0) ?  wrapWidth / m_Tabs.size() : 100;
    int height = event->size().height();

    std::for_each(m_Tabs.begin(), m_Tabs.end(), [width, height](std::shared_ptr<Tab> tab){
        tab->resize(width, height);
    });
}

void TabWrapper::setCurrentTabDisabled()
{
    if (m_CurrentTab != nullptr)
    {
        m_CurrentTab->SetDisabled();
    }
}

void TabWrapper::setCurrentTabEnabled()
{
    if (m_CurrentTab != nullptr)
    {
        m_CurrentTab->SetEnabled();
    }
}
