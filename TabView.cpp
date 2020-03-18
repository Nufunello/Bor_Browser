#include "TabView.h"

#include <QLineEdit>

TabView::TabView()
{
    m_Tab  = std::make_shared<Tab>();
    m_View = std::make_shared<View>();
}

std::shared_ptr<Tab> TabView::GetTab()
{
    return m_Tab;
}

std::shared_ptr<View> TabView::GetView()
{
    return m_View;
}
