#include "TabView.h"
#include "TabViewWrapper.h"
#include <iostream>

TabView::TabView(TabViewWrapper *parent)
    : QWidget(parent)
{
    m_Tab = std::make_shared<Tab>(parent->GetTabWrapper());
    m_Url = std::make_shared<Url>(parent->GetUrlWrapper());
}

std::shared_ptr<Tab> TabView::GetTab()
{
    return m_Tab;
}

std::shared_ptr<Url> TabView::GetUrl()
{
    return m_Url;
}

TabView::~TabView()
{
    std::cout << "DD";
    std::cout << "DD";
}
