#include "TabWrapper.h"

TabWrapper::TabWrapper(QWidget *parent)
    : QWidget(parent)
{   
}

void TabWrapper::AddTab(std::shared_ptr<Tab> tab)
{
    if (m_Tab != nullptr)
    {
        m_Tab->hide();
    }
    m_Tab = tab;
    m_Tab->show();
}
