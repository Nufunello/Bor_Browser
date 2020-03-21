#ifndef TABBAR_H
#define TABBAR_H

#include "Tab.h"

#include <set>

#include <QVBoxLayout>
#include <QWidget>

class TabBar : public QWidget
{
    Q_OBJECT
public:
    explicit TabBar(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

public slots:
    void AddTab(std::shared_ptr<Tab>);
    void ChangeTab(std::shared_ptr<Tab>);
    void RemoveTab(std::shared_ptr<Tab>);

signals:
    void AddTabClicked();
    void IsEmpty();

private:
    QHBoxLayout                       m_HorizontalLayout;

    std::shared_ptr<Tab>              m_CurrentTab;

    std::vector<std::shared_ptr<Tab>> m_Tabs;
    QPushButton                       m_BtnAddTab;

private:
    void enableCurrentTab();
    void disableCurrentTab();
    void resizeTabs();
    void resizeTabs(int height, int width);

};

#endif // TABBAR_H
