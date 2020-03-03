#include "Tab.h"
#include <QShowEvent>

#include "TabWrapper.h"

Tab::Tab(std::shared_ptr<TabWrapper> parent)
    : QWidget(&*parent)
{
    static int i = 0;
    m_Btn = std::make_shared<QPushButton>(this);
    m_Btn->setText(QString::number(i++));
}
