#ifndef TABVIEWWRAPPER_H
#define TABVIEWWRAPPER_H

#include "TabView.h"

#include <TabWrapper.h>
#include <UrlWrapper.h>

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

protected:
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    std::shared_ptr<TabWrapper> m_Tab;
    std::shared_ptr<UrlWrapper> m_Url;

};

#endif // TABVIEWWRAPPER_H
