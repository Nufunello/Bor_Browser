#ifndef TABWRAPPER_H
#define TABWRAPPER_H

#include "Tab.h"
#include <QWidget>

class TabWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit TabWrapper(QWidget *parent = nullptr);

public:
    void AddTab(std::shared_ptr<Tab>);

signals:

private:
    std::shared_ptr<Tab> m_Tab;

};

#endif // TABWRAPPER_H
