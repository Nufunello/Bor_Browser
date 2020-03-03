#ifndef TABVIEW_H
#define TABVIEW_H

#include <Tab.h>
#include <Url.h>

#include <QWidget>

class TabViewWrapper;

class TabView : public QWidget
{
    Q_OBJECT
public:
    explicit TabView(TabViewWrapper *parent = nullptr);

public:
    std::shared_ptr<Tab> GetTab();
    std::shared_ptr<Url> GetUrl();

    ~TabView();
signals:

private:
    std::shared_ptr<Tab> m_Tab;
    std::shared_ptr<Url> m_Url;

};

#endif // TABVIEW_H
