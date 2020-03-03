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

private:
    TabViewWrapper m_TabView;
    QPushButton btn;

private:
    inline void add(){
        m_TabView.AddTabView(std::make_shared<TabView>(&m_TabView));
    }

};
#endif // MAINWINDOW_H
