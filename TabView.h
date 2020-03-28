#ifndef TABVIEW_H
#define TABVIEW_H

#include "Tab.h"

#include <QObject>

class TabView : public QObject
{
    Q_OBJECT
public:
    explicit TabView(QObject *parent = nullptr);
    ~TabView();

public:
    Tab*  GetTab();
    View* GetView();

signals:
    void Selected();
    void Removed();

private:
    std::unique_ptr<Tab>  m_Tab;
    std::unique_ptr<View> m_View;

public:
    static int s_Counter;

};

#endif // TABVIEW_H
