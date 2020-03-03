#include "TabViewWrapper.h"
#include <QMoveEvent>
#include <QResizeEvent>

TabViewWrapper::TabViewWrapper(QWidget *parent)
    : QWidget(parent)
    , m_Tab{nullptr}
    , m_Url{nullptr}
{
    m_Tab = std::make_shared<TabWrapper>(this);
    m_Url = std::make_shared<UrlWrapper>(this);
    //m_Url.move(m_Tab.x(), m_Tab.y() + m_Tab.height());
    //m_Url.AddUrl(std::make_shared<Url>(&m_Url));
}

void TabViewWrapper::AddTabView(std::shared_ptr<TabView> tabView)
{
    m_Tab->AddTab(tabView->GetTab());
    m_Url->AddUrl(tabView->GetUrl());
}

std::shared_ptr<TabWrapper> TabViewWrapper::GetTabWrapper()
{
    return m_Tab;
}

std::shared_ptr<UrlWrapper> TabViewWrapper::GetUrlWrapper()
{
    return m_Url;
}

void TabViewWrapper::moveEvent(QMoveEvent *event)
{
    m_Tab->move(event->pos());
    m_Url->move(m_Tab->x(), m_Tab->y() + m_Tab->height());
}

void TabViewWrapper::resizeEvent(QResizeEvent *event)
{
    m_Tab->resize(event->size().width(), 30);
    m_Url->resize(event->size().width(), 30);
}
