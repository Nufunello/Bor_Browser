#include "TabView.h"
#include "TabViewWrapper.h"
#include <iostream>

TabView::TabView(std::shared_ptr<TabViewWrapper> parent)
{
    m_Tab = std::make_shared<Tab>(parent->GetTabWrapper());
    m_Url = std::make_shared<Url>(parent->GetUrlWrapper());
    m_WebView = std::make_shared<WebView>(parent->GetWebViewWrapper());

    QLineEdit::connect(&*m_Url, &Url::UrlChanged, &*m_WebView, &WebView::LoadUrl);

    QLineEdit::connect(&*m_WebView, &WebView::Loading, &*m_Url, &Url::ChangeProgressBar);

    QLineEdit::connect(&*m_WebView, &WebView::PageUpdated, &*m_Tab, &Tab::UpdateTab);
}

std::shared_ptr<Tab> TabView::GetTab()
{
    return m_Tab;
}

std::shared_ptr<Url> TabView::GetUrl()
{
    return m_Url;
}

std::shared_ptr<WebView> TabView::GetWebView()
{
    return m_WebView;
}
