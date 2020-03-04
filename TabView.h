#ifndef TABVIEW_H
#define TABVIEW_H

#include "Tab.h"
#include "Url.h"
#include "WebView.h"

#include <QWidget>

class TabViewWrapper;

class TabView
{
public:
    explicit TabView(std::shared_ptr<TabViewWrapper> parent = nullptr);

public:
    std::shared_ptr<Tab> GetTab();
    std::shared_ptr<Url> GetUrl();
    std::shared_ptr<WebView> GetWebView();

private:
    std::shared_ptr<Tab> m_Tab;
    std::shared_ptr<Url> m_Url;
    std::shared_ptr<WebView> m_WebView;

};

#endif // TABVIEW_H
