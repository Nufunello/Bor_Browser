#ifndef TABVIEW_H
#define TABVIEW_H

#include "Tab.h"
#include "View.h"

#include <QVBoxLayout>
#include <QWidget>
#include <memory>

class TabView
{
public:
    TabView();

public:
    std::shared_ptr<Tab>  GetTab();
    std::shared_ptr<View> GetView();

private:
    std::shared_ptr<Tab>  m_Tab;
    std::shared_ptr<View> m_View;

};

#endif // TABVIEW_H
