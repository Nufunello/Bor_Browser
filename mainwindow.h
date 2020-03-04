#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TabViewWrapper.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    std::shared_ptr<TabViewWrapper> m_TabView;
    std::vector<std::shared_ptr<TabView>> m_TabViews;

private:
    void addEmptyTabView();

};
#endif // MAINWINDOW_H
