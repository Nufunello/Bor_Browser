#ifndef TABVIEW_H
#define TABVIEW_H

#include "Tab.h"

#include <QObject>

class TabView : public QObject
{
    Q_OBJECT
public:
    explicit TabView(QObject *parent = nullptr);

public:
    std::shared_ptr<Tab>  GetTab();
    std::shared_ptr<View> GetView();

signals:
    void Selected();
    void Removed();

private:
    std::shared_ptr<Tab>  m_Tab;
    std::shared_ptr<View> m_View;

};

#endif // TABVIEW_H
