#ifndef TABBAR_H
#define TABBAR_H

#include "Tab.h"

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

public:
    void AddTab(std::shared_ptr<Tab>);

signals:
    void AddTabClicked();

private:
    QHBoxLayout m_HorizontalLayout;

    std::vector<std::shared_ptr<Tab>> m_Tabs;
    QPushButton                       m_BtnAddTab;

};

#endif // TABBAR_H
