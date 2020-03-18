#include "TabViews.h"

#include <QResizeEvent>

constexpr int TABBAR_HEIGHT = 30;

TabViews::TabViews(QWidget *parent)
    : QWidget(parent)
{
    m_TabBar.setParent(this);
    m_View.setParent(this);

    m_MainLayout.addWidget(&m_TabBar);
    m_MainLayout.addWidget(&m_View);

    addEmptyTab();
    addEmptyTab();

    connect(&m_TabBar, &TabBar::AddTabClicked, this, &TabViews::addEmptyTab);
}

void TabViews::AddTabView(std::shared_ptr<TabView> tabView)
{
    auto tab  = tabView->GetTab();
    auto view = tabView->GetView();

    tab->setParent(&m_TabBar);
    view->setParent(&m_View);

    std::weak_ptr<View> weakView = view;

    m_TabBar.AddTab(tab);
    m_View.ChangeView(view);

    connect(&*tab, &Tab::Selected, [=](){
        m_View.ChangeView(weakView.lock());
    });

    connect(&*view->GetWebView(), &WebView::UrlChanged, [tab](QWebEnginePage* page){
        tab->UpdateTabInfo(page->title());
    });

    connect(&*view->GetWebView(), &WebView::PageUpdated, [tab](QWebEnginePage* page){
        tab->UpdateTabInfo(page->title());
    });
}

void TabViews::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();

    m_TabBar.resize(width, TABBAR_HEIGHT);

    int viewHeight = event->size().height() - m_TabBar.height();
    m_View.resize(width, viewHeight);
}

void TabViews::moveEvent(QMoveEvent *event)
{
    m_TabBar.move(event->pos());
    m_View.move(event->pos().x(), m_TabBar.y() + TABBAR_HEIGHT);
}

void TabViews::addEmptyTab()
{
    m_TabViews.emplace_back(std::make_shared<TabView>());
    AddTabView(*m_TabViews.rbegin());
}
