#ifndef TABVIEWWRAPPER_H
#define TABVIEWWRAPPER_H

#include "TabView.h"

#include "TabWrapper.h"
#include "UrlWrapper.h"
#include "WebViewWrapper.h"

#include <QWidget>

class TabViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit TabViewWrapper(QWidget *parent = nullptr);

public:
    void AddTabView(std::shared_ptr<TabView>);

    std::shared_ptr<TabWrapper> GetTabWrapper();
    std::shared_ptr<UrlWrapper> GetUrlWrapper();
    std::shared_ptr<WebViewWrapper> GetWebViewWrapper();

protected:
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void TabViewSelected(std::weak_ptr<TabView>);

private:
    std::shared_ptr<TabWrapper> m_Tab;
    std::shared_ptr<UrlWrapper> m_Url;
    std::shared_ptr<WebViewWrapper> m_WebView;

private:
    void changeTabView(std::weak_ptr<TabView>);
};

#endif // TABVIEWWRAPPER_H
