#include "TabBar.h"
#include <QResizeEvent>

constexpr int ADD_BUTTON_WIDTH = 20;
constexpr int TAB_MAX_WIDTH = 100;

static inline int GetTabWidth(int width, int cTabs)
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
        int width = GetTabWidth(event->size().width(), m_Tabs.size());
        int height = event->size().height();

        this->resizeTabs(width, height);
    }

    m_BtnAddTab.resize(ADD_BUTTON_WIDTH, event->size().height());
}

void TabBar::paintEvent(QPaintEvent *)
{
    int x = this->x(), y = this-> y();

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

    int tabWidth  = GetTabWidth(this->width(), m_Tabs.size());
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
    auto itNewTab = m_Tabs.erase(std::find(m_Tabs.begin(), m_Tabs.end(), tab));

    if (m_Tabs.empty())
    {
        emit this->IsEmpty();
    }
    else
    {
        if (tab == m_CurrentTab)
        {
            this->changeTab(itNewTab != m_Tabs.end() ? itNewTab : std::prev(itNewTab));
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
    int tabWidth  = GetTabWidth(this->width(), m_Tabs.size());
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
