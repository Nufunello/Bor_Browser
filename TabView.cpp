#include "TabView.h"

int TabView::s_Counter = 0;

TabView::TabView(QObject *parent)
    : QObject(parent)
{
    ++s_Counter;
    m_Tab  = std::make_unique<Tab>();
    m_View = std::make_unique<View>();

    connect(&*m_Tab, &Tab::Selected, this, &TabView::Selected);
    connect(&*m_Tab, &Tab::Removed,  this, &TabView::Removed);

    connect(&*m_View->GetWebView(), &WebView::UrlChanged, [tab = &*m_Tab](QWebEnginePage* page){
       tab->UpdateTabInfo(page->title());
    });

    connect(&*m_View->GetWebView(), &WebView::PageUpdated, [tab = &*m_Tab](QWebEnginePage* page){
        tab->UpdateTabInfo(page->title());
    });
}

TabView::~TabView()
{
    --s_Counter;
}

Tab* TabView::GetTab()
{
    return &*m_Tab;
}

View* TabView::GetView()
{
    return &*m_View;
}
