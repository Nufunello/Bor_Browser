#include "TabViews.h"

#include <QResizeEvent>

constexpr int TABBAR_HEIGHT = 30;
constexpr int HISTORY_HEIGHT = TABBAR_HEIGHT;
constexpr int HISTORY_WIDTH  = 60;

TabViews::TabViews(QWidget *parent)
    : QWidget(parent)
{
    m_TabBar.setParent(this);
    m_History.setParent(this);

    m_View.setParent(this);

    m_MainLayout.addLayout(&m_TopLayout);
    m_MainLayout.addLayout(&m_VerticalLayout);

    m_TopLayout.addWidget(&m_TabBar);
    m_TopLayout.addWidget(&m_History);

    m_VerticalLayout.addWidget(&m_View);

    m_BookmarkMenu.resize(400, 400);

    addEmptyTab();

    connect(&m_TabBar, &TabBar::AddTabClicked, this, &TabViews::addEmptyTab);
    connect(&m_TabBar, &TabBar::IsEmpty,       this, &TabViews::addEmptyTab);


    connect(&m_View, &ViewWrapper::PageLoaded, [this](QWebEnginePage* page){
        m_History.GetHistoryMenu()->AddVisitedPage(page);
    });

    connect(&m_BookmarkMenu, &BookmarkMenu::BookmarkSelected, [this](QUrl url){
        m_View.GetCurrentView()->GetWebView()->LoadUrl(std::move(url));
    });

    auto historyMenu = m_History.GetHistoryMenu();
    connect(&*historyMenu, &HistoryMenu::VisitedHistorySelected, [this](QUrl url){
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

    m_TabViews.insert(tabView);

    m_TabBar.AddTab(tab);
    m_View.ChangeView(view);

    std::weak_ptr<TabView> weakTabView = tabView;

    connect(&*tabView, &TabView::Removed, [this, weakTabView](){
        auto tabView = weakTabView.lock();
        m_TabBar.RemoveTab(tabView->GetTab());
        m_TabViews.erase(tabView);
    });

    //Tab change connection
    std::weak_ptr<Tab>  weakTab  = tab;
    std::weak_ptr<View> weakView = view;

    connect(&*tabView, &TabView::Selected, [=](){
        m_TabBar.ChangeTab(weakTab.lock());
        m_View.ChangeView(weakView.lock());
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

    m_History.resize(HISTORY_WIDTH, HISTORY_HEIGHT);
    m_TabBar.resize(width - HISTORY_WIDTH, TABBAR_HEIGHT);

    int viewHeight = event->size().height() - m_TabBar.height();
    m_View.resize(width, viewHeight);

    moveWidgets(this->pos());
}

void TabViews::moveEvent(QMoveEvent *event)
{
    moveWidgets(event->pos());
}

void TabViews::addEmptyTab()
{
    AddTabView(std::make_shared<TabView>());
}

void TabViews::moveWidgets(QPoint pos)
{
    m_TabBar.move(pos);
    m_History.move(m_TabBar.x() + m_TabBar.width(), m_TabBar.y());

    m_View.move(pos.x(), m_TabBar.y() + TABBAR_HEIGHT);
}
