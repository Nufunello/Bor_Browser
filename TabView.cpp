#include "TabView.h"

TabView::TabView(QObject *parent)
    : QObject(parent)
{
    m_Tab  = std::make_shared<Tab>();
    m_View = std::make_shared<View>();

    std::weak_ptr<Tab> weakTab   = m_Tab;
    std::weak_ptr<View> weakView = m_View;

    connect(&*m_Tab, &Tab::Selected, this, &TabView::Selected);
    connect(&*m_Tab, &Tab::Removed,  this, &TabView::Removed);

    connect(&*m_View->GetWebView(), &WebView::UrlChanged, [weakTab](QWebEnginePage* page){
       auto tab = weakTab.lock();
       tab->UpdateTabInfo(page->title());
    });

    connect(&*m_View->GetWebView(), &WebView::PageUpdated, [weakTab](QWebEnginePage* page){
        auto tab = weakTab.lock();
        tab->UpdateTabInfo(page->title());
    });
}

std::shared_ptr<Tab> TabView::GetTab()
{
    return m_Tab;
}

std::shared_ptr<View> TabView::GetView()
{
    return m_View;
}
