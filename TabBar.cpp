#include "TabBar.h"
#include <QResizeEvent>

constexpr int ADD_BUTTON_WIDTH = 20;

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
    , m_CurrentTab{nullptr}
{
    m_BtnAddTab.setParent(this);
    m_BtnAddTab.setText("+");

    connect(&m_BtnAddTab, &QPushButton::clicked, [this](){
        emit this->AddTabClicked();
    });
}

void TabBar::resizeEvent(QResizeEvent *event)
{
    if (!m_Tabs.empty())
    {
        int avgWidth = event->size().width() / m_Tabs.size();

        int width = std::min(100, avgWidth);
        int height = event->size().height();

        std::for_each(m_Tabs.begin(), m_Tabs.end(), [&](const std::shared_ptr<Tab>& tab){
            tab->resize(width, height);
        });
    }

    m_BtnAddTab.resize(ADD_BUTTON_WIDTH, event->size().height());
}

void TabBar::paintEvent(QPaintEvent *)
{
    int x = this->x(), y =this-> y();

    std::for_each(m_Tabs.begin(), m_Tabs.end(), [&](const std::shared_ptr<Tab>& tab){
        tab->move(x, y);
        x += tab->width();
    });

    m_BtnAddTab.move(x, y);
}

void TabBar::AddTab(std::shared_ptr<Tab> tab)
{
    this->ChangeTab(tab);

    std::weak_ptr<Tab> weakTab = tab;

    connect(&*tab, &Tab::Removed, [this, weakTab](){
        m_Tabs.erase(weakTab.lock());
        if (m_Tabs.empty())
        {
            emit this->IsEmpty();
        }
    });

    m_Tabs.insert(tab);
}

void TabBar::ChangeTab(std::shared_ptr<Tab> tab)
{
    enableCurrentTab();
    m_CurrentTab = std::move(tab);
    disableCurrentTab();
}

void TabBar::enableCurrentTab()
{
    if (m_CurrentTab != nullptr)
    {
        m_CurrentTab->setEnabled(true);
    }
}

void TabBar::disableCurrentTab()
{
    m_CurrentTab->setDisabled(true);
}
