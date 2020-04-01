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
    connect(historyMenu, &HistoryMenu::VisitedHistorySelected, [this](QUrl url){
        m_View.GetCurrentView()->GetWebView()->LoadUrl(std::move(url));
    });
}

TabViews::~TabViews()
{
    m_TabViews.clear();
    qDebug() << "TabViews undeleted:" << TabView::s_Counter;
}

void TabViews::AddTabView(std::unique_ptr<TabView> tabView)
{
    auto pTabViewRaw = tabView.get();

    auto tab  = pTabViewRaw->GetTab();
    auto view = pTabViewRaw->GetView();

    tab->setParent(&m_TabBar);
    view->setParent(&m_View);

    tab->show();
    view->show();

    m_TabBar.AddTab(tab);
    m_View.ChangeView(view);

    connect(pTabViewRaw, &TabView::Selected, [this, tab, view](){
        m_TabBar.ChangeTab(tab);
        m_View.ChangeView(view);
    });
    connect(pTabViewRaw, &TabView::Removed, [this, pTabViewRaw](){
        m_TabBar.RemoveTab(pTabViewRaw->GetTab());
    });

    auto itTabView = m_TabViews.emplace(std::move(tabView)).first;
    connect(pTabViewRaw, &TabView::Removed, [this, itTabView]() {
        m_TabViews.erase(itTabView);
    });

    auto pCurrentViewRaw = m_View.GetCurrentView();
    auto bookmarkPanelPtr = pCurrentViewRaw->GetNavigation()->GetBookmarkPanel();
    connect(bookmarkPanelPtr, &BookmarkPanel::OpenBookmarksPressed, &m_BookmarkMenu, &BookmarkMenu::show);

    connect(bookmarkPanelPtr, &BookmarkPanel::AddBookmarkPressed, [this, pCurrentViewRaw](){
        m_BookmarkMenu.AddBookmark(pCurrentViewRaw->GetWebView()->GetCurrentPage());
    });
}

void TabViews::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();

    m_History.resize(HISTORY_WIDTH, HISTORY_HEIGHT);
    m_TabBar.resize(width - HISTORY_WIDTH, TABBAR_HEIGHT);

    int viewHeight = event->size().height() - m_TabBar.height();
    m_View.resize(width, viewHeight);
}

void TabViews::paintEvent(QPaintEvent *)
{
    auto pos = this->pos();

    m_TabBar.move(pos);
    m_History.move(m_TabBar.x() + m_TabBar.width(), m_TabBar.y());

    m_View.move(pos.x(), m_TabBar.y() + TABBAR_HEIGHT);
}

void TabViews::addEmptyTab()
{
    AddTabView(std::make_unique<TabView>());
}
