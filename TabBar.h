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
    void AddTab(Tab*);
    void ChangeTab(Tab*);
    void RemoveTab(Tab*);

signals:
    void AddTabClicked();
    void IsEmpty();

private:
    Tab*              m_CurrentTab;

    std::vector<Tab*> m_Tabs;
    QPushButton       m_BtnAddTab;

private:
    void enableCurrentTab();
    void disableCurrentTab();
    void resizeTabs();
    void resizeTabs(int height, int width);

    void changeTab(const std::vector<Tab*>::iterator& it);

};

#endif // TABBAR_H
