#include "TabBar.h"
#include <QResizeEvent>

constexpr int ADD_BUTTON_WIDTH = 20;
constexpr int TAB_MAX_WIDTH = 100;

static inline int getTabWidth(int width, int cTabs)
{
    int avgWidth = (width - ADD_BUTTON_WIDTH) / cTabs;
    return std::min(TAB_MAX_WIDTH, avgWidth);
}

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
    , m_CurrentTab{nullptr}
{
    m_BtnAddTab.setParent(this);
    m_BtnAddTab.setText("+");

    connect(&m_BtnAddTab, &QPushButton::clicked, this, &TabBar::AddTabClicked);
}

void TabBar::resizeEvent(QResizeEvent *event)
{
    if (!m_Tabs.empty())
    {
        int width = getTabWidth(event->size().width(), m_Tabs.size());
        int height = event->size().height();

        this->resizeTabs(width, height);
    }

    m_BtnAddTab.resize(ADD_BUTTON_WIDTH, event->size().height());
}

void TabBar::paintEvent(QPaintEvent *)
{
    int x = 0, y = 0;

    for (Tab* const tab : m_Tabs)
    {
        tab->move(x, y);
        x += tab->width();
    }

    m_BtnAddTab.move(x, y);
}

void TabBar::AddTab(Tab* tab)
{
    this->ChangeTab(tab);

    m_Tabs.emplace_back(tab);

    int tabWidth  = getTabWidth(this->width(), m_Tabs.size());
    int tabHeight = this->height();

    //if calculated tab width is less than const value
    //so with new one it need all tabs to resize
    if (tabWidth < TAB_MAX_WIDTH)
    {
        this->resizeTabs(tabWidth, tabHeight);
    }
    else
    {
        tab->resize(tabWidth, tabHeight);
    }
}

void TabBar::ChangeTab(Tab* tab)
{
    enableCurrentTab();
    m_CurrentTab = std::move(tab);
    disableCurrentTab();
}

void TabBar::RemoveTab(Tab* tab)
{
    auto itNextTab = m_Tabs.erase(std::find(m_Tabs.begin(), m_Tabs.end(), tab));

    if (m_Tabs.empty())
    {
        emit this->IsEmpty();
    }
    else
    {
        if (tab == m_CurrentTab)
        {
            this->changeTab(itNextTab != m_Tabs.end() ? itNextTab : std::prev(itNextTab));
        }
        this->resizeTabs();
    }
}

void TabBar::enableCurrentTab()
{
    if (m_CurrentTab != nullptr)
    {
        m_CurrentTab->SetEnabled();
    }
}

void TabBar::disableCurrentTab()
{
    m_CurrentTab->SetDisabled();
}

void TabBar::resizeTabs()
{
    int tabWidth  = getTabWidth(this->width(), m_Tabs.size());
    int tabHeight = this->height();

    this->resizeTabs(tabWidth, tabHeight);
}

void TabBar::resizeTabs(int width, int height)
{
    for (Tab* const tab : m_Tabs)
    {
        tab->resize(width, height);
    }
}

void TabBar::changeTab(const std::vector<Tab*>::iterator &it)
{
    auto& newTab = *it;

    this->ChangeTab(newTab);
    newTab->Selected();
}
