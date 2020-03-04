#include "WebViewWrapper.h"

#include <QResizeEvent>

WebViewWrapper::WebViewWrapper(QWidget *parent)
    : QWidget(parent)
    , m_WebView{nullptr}
{
}

void WebViewWrapper::resizeEvent(QResizeEvent *event)
{
    if (m_WebView != nullptr)
    {
        m_WebView->resize(event->size());
    }
}

void WebViewWrapper::ChangeWebView(std::shared_ptr<WebView> webView)
{
    if (m_WebView != nullptr)
    {
        m_WebView->hide();
    }

    m_WebView = webView;
    m_WebView->show();

    m_WebView->resize(size());
}
