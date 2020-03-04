#include "WebView.h"
#include "WebViewWrapper.h"

#include <QResizeEvent>

WebView::WebView(std::shared_ptr<WebViewWrapper> parent)
    : QWidget(&*parent)
{
    m_WebView = std::make_shared<QWebEngineView>(this);

    connect(&*m_WebView, &QWebEngineView::loadProgress, this, &WebView::Loading);

    connect(&*m_WebView, &QWebEngineView::loadFinished, this, [&](){
        emit this->PageUpdated(m_WebView->page());
    });
}

void WebView::LoadUrl(QUrl url)
{
    m_WebView->load(url);
}

void WebView::resizeEvent(QResizeEvent *event)
{
    m_WebView->resize(event->size());
}
