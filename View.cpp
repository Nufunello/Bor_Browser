#include "View.h"

#include <QResizeEvent>

constexpr int NAVIGATION_HEIGHT = 30;

View::View(QWidget *parent)
    : QWidget(parent)
{
    m_Navigation.setParent(this);

    m_WebView = std::make_shared<WebView>(this);

    connect(&*m_WebView, &WebView::UrlChanged, &m_Navigation, &Navigation::UpdateNavigationStatus);

    connect(&*m_WebView, &WebView::Loading, [this](int progress){
        m_Navigation.ChangeLoadProgress(std::move(progress));
    });

    auto navigationPanelPtr = &*m_Navigation.GetNavigationPanel();
    connect(navigationPanelPtr, &NavigationPanel::GoBackPressed, &*m_WebView, &WebView::GoBack);
    connect(navigationPanelPtr, &NavigationPanel::GoBackPressed, &*m_WebView, &WebView::GoForward);
    connect(navigationPanelPtr, &NavigationPanel::GoBackPressed, &*m_WebView, &WebView::Refresh);

    auto navigationUrlPtr = &*m_Navigation.GetNavigationUrl();
    connect(navigationUrlPtr, &NavigationUrl::UrlEntered, [this](QUrl url){
        this->m_WebView->LoadUrl(std::move(url));
    });

    auto bookmarkPanelPtr = &*m_Navigation.GetBookmarkPanel();
    connect(bookmarkPanelPtr, &BookmarkPanel::AddBookmarkPressed, [this](){
        m_BookmarkMenu.AddBookmark(this->m_WebView->GetCurrentPage());
    });

    connect(bookmarkPanelPtr, &BookmarkPanel::OpenBookmarksPressed, [this](){
        if (m_BookmarkMenu.isHidden())
        {
            m_BookmarkMenu.show();
        }
    });
}

void View::resizeEvent(QResizeEvent *event)
{
    m_Navigation.resize(event->size().width(), NAVIGATION_HEIGHT);
    m_WebView->resize(event->size().width(), event->size().height() - NAVIGATION_HEIGHT);

    moveWidgets();
}

std::shared_ptr<WebView> View::GetWebView()
{
    return m_WebView;
}

void View::moveWidgets()
{
    m_Navigation.move(0, 0);
    m_WebView->move(m_Navigation.x(), m_Navigation.y() + m_Navigation.height());
}