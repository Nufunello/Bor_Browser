#include "TabViewWrapper.h"
#include <QCoreApplication>
#include <QMoveEvent>
#include <QResizeEvent>
#include <memory>

TabViewWrapper::TabViewWrapper(QWidget *parent)
    : QWidget(parent)
    , m_Tab{nullptr}
    , m_Url{nullptr}
{
    m_Tab = std::make_shared<TabWrapper>(this);
    m_Url = std::make_shared<UrlWrapper>(this);
    m_WebView = std::make_shared<WebViewWrapper>(this);

    connect(this, &TabViewWrapper::TabViewSelected, this, &TabViewWrapper::changeTabView);
}

void TabViewWrapper::AddTabView(std::shared_ptr<TabView> tabView)
{
    auto tab = tabView->GetTab();
    m_Tab->AddTab(tab);
    m_Url->ChangeUrl(tabView->GetUrl());
    m_WebView->ChangeWebView(tabView->GetWebView());

    std::weak_ptr<TabView> weakTabView = tabView;

    connect(&*tab, &Tab::Selected, this, [=](){
        emit this->TabViewSelected(weakTabView);
    });
}

std::shared_ptr<TabWrapper> TabViewWrapper::GetTabWrapper()
{
    return m_Tab;
}

std::shared_ptr<UrlWrapper> TabViewWrapper::GetUrlWrapper()
{
    return m_Url;
}

std::shared_ptr<WebViewWrapper> TabViewWrapper::GetWebViewWrapper()
{
    return m_WebView;
}

void TabViewWrapper::moveEvent(QMoveEvent *event)
{
    m_Tab->move(event->pos());
    m_Url->move(m_Tab->x(), m_Tab->y() + m_Tab->height());
    m_WebView->move(m_Url->x(), m_Url->y() + m_Url->height());
}

void TabViewWrapper::resizeEvent(QResizeEvent *event)
{
    m_Tab->resize(event->size().width(), 30);
    m_Url->resize(event->size().width(), 30);
    m_WebView->resize(event->size().width(), event->size().height() - m_Tab->height() - m_Url->height());
}

void TabViewWrapper::changeTabView(std::weak_ptr<TabView> tabView)
{
    m_Tab->ChangeTab(tabView.lock()->GetTab());
    m_Url->ChangeUrl(tabView.lock()->GetUrl());
    m_WebView->ChangeWebView(tabView.lock()->GetWebView());

    this->adjustSize();
}
