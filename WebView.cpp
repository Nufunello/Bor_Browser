#include "WebView.h"

#include <QResizeEvent>

WebView::WebView(QWidget *parent)
    : QWidget(parent)
{
    m_WebView.setParent(this);

    connect(&m_WebView, &QWebEngineView::loadProgress, this, &WebView::Loading);

    connect(&m_WebView, &QWebEngineView::loadProgress, [this](int progress){
        if (progress == 100)
        {
            emit this->PageUpdated(m_WebView.page());
        }
    });

    connect(&m_WebView, &QWebEngineView::urlChanged, [this](){
        emit this->UrlChanged(m_WebView.page());
    });
}

QWebEnginePage *WebView::GetCurrentPage()
{
    return m_WebView.page();
}

void WebView::LoadUrl(QUrl url)
{
    m_WebView.load(url);
}

void WebView::GoBack()
{
    m_WebView.back();
}

void WebView::GoForward()
{
    m_WebView.forward();
}

void WebView::Refresh()
{
    m_WebView.reload();
}

void WebView::resizeEvent(QResizeEvent *event)
{
    m_WebView.resize(event->size());
}
