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
    void ChangeTab(std::shared_ptr<Tab>);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    std::vector<std::shared_ptr<Tab>> m_Tabs;
    std::shared_ptr<Tab> m_CurrentTab;

private:
    void setCurrentTabDisabled();
    void setCurrentTabEnabled();

};

#endif // TABWRAPPER_H
