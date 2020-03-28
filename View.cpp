#include "View.h"

#include <QResizeEvent>

constexpr int NAVIGATION_HEIGHT = 30;

View::View(QWidget *parent)
    : QWidget(parent)
{
    m_Navigation = std::make_unique<Navigation>(this);
    m_WebView    = std::make_unique<WebView>(this);

    auto pWebViewRaw = m_WebView.get();
    connect(pWebViewRaw, &WebView::UrlChanged, &*m_Navigation, &Navigation::UpdateNavigationStatus);

    connect(pWebViewRaw, &WebView::PageUpdated, this, &View::PageLoaded);

    connect(pWebViewRaw, &WebView::Loading, [this](int progress){
        m_Navigation->ChangeLoadProgress(std::move(progress));
    });

    auto navigationPanelPtr = m_Navigation->GetNavigationPanel();
    connect(navigationPanelPtr, &NavigationPanel::GoBackPressed,    pWebViewRaw, &WebView::GoBack);
    connect(navigationPanelPtr, &NavigationPanel::GoForwardPressed, pWebViewRaw, &WebView::GoForward);
    connect(navigationPanelPtr, &NavigationPanel::RefreshPressed,   pWebViewRaw, &WebView::Refresh);

    auto navigationUrlPtr = m_Navigation->GetNavigationUrl();
    connect(navigationUrlPtr, &NavigationUrl::UrlEntered, [this](QUrl url){
        this->m_WebView->LoadUrl(std::move(url));
    });
}

void View::resizeEvent(QResizeEvent *event)
{
    m_Navigation->resize(event->size().width(), NAVIGATION_HEIGHT);
    m_WebView->resize(event->size().width(), event->size().height() - NAVIGATION_HEIGHT);
}

void View::paintEvent(QPaintEvent *)
{
    m_Navigation->move(0, 0);
    m_WebView->move(m_Navigation->x(), m_Navigation->y() + m_Navigation->height());
}

Navigation* View::GetNavigation()
{
    return m_Navigation.get();
}

WebView* View::GetWebView()
{
    return m_WebView.get();
}
