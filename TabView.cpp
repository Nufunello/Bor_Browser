#include "TabView.h"

int TabView::s_Counter = 0;

TabView::TabView(QObject *parent)
    : QObject(parent)
{
    ++s_Counter;

    m_Tab  = std::make_unique<Tab>();
    m_View = std::make_unique<View>();

    auto pTabRaw = m_Tab.get();
    connect(pTabRaw, &Tab::Selected, this, &TabView::Selected);
    connect(pTabRaw, &Tab::Removed,  this, &TabView::Removed);

    auto pViewRaw = m_View.get();
    connect(pViewRaw->GetWebView(), &WebView::UrlChanged, [tab = &*m_Tab](QWebEnginePage* page){
       tab->UpdateTabInfo(page->title());
    });
    connect(pViewRaw->GetWebView(), &WebView::PageUpdated, [tab = &*m_Tab](QWebEnginePage* page){
        tab->UpdateTabInfo(page->title());
    });
}

TabView::~TabView()
{
    --s_Counter;
}

Tab* TabView::GetTab()
{
    return m_Tab.get();
}

View* TabView::GetView()
{
    return m_View.get();
}
