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

    connect(&m_TabBar, &TabBar::IsEmpty,       this, &TabViews::addEmptyTab);
    connect(&m_TabBar, &TabBar::AddTabClicked, this, &TabViews::addEmptyTab);

    connect(&m_BookmarkMenu, &BookmarkMenu::BookmarkSelected, [this](QUrl url){
        m_View.GetCurrentView()->GetWebView()->LoadUrl(std::move(url));
    });
}

void TabViews::AddTabView(std::shared_ptr<TabView> tabView)
{
    auto tab  = tabView->GetTab();
    auto view = tabView->GetView();

    tab->setParent(&m_TabBar);
    view->setParent(&m_View);

    tab->show();
    view->show();

    std::weak_ptr<Tab> weakTab = tab;
    std::weak_ptr<View> weakView = view;

    m_TabBar.AddTab(tab);
    m_View.AddView(view);

    //Tab change connection
    connect(&*tab, &Tab::Selected, [=](){
        m_TabBar.ChangeTab(weakTab.lock());
        m_View.ChangeView(weakView.lock());
    });
    //

    //WebView connections
    connect(&*view->GetWebView(), &WebView::UrlChanged, [weakTab](QWebEnginePage* page){
        weakTab.lock()->UpdateTabInfo(page->title());
    });

    connect(&*view->GetWebView(), &WebView::PageUpdated, [weakTab](QWebEnginePage* page){
        weakTab.lock()->UpdateTabInfo(page->title());
    });
    //

    //Bookmarks connections
    auto bookmarkPanelPtr = &*m_View.GetCurrentView()->GetNavigation()->GetBookmarkPanel();
    connect(bookmarkPanelPtr, &BookmarkPanel::AddBookmarkPressed, [this](){
        m_BookmarkMenu.AddBookmark(&*m_View.GetCurrentView()->GetWebView()->GetCurrentPage());
    });

    connect(bookmarkPanelPtr, &BookmarkPanel::OpenBookmarksPressed, &m_BookmarkMenu, &BookmarkMenu::show);
    //
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
    AddTabView(std::make_shared<TabView>());
}
