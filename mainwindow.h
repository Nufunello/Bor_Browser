#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TabViews.h"

#include <QMainWindow>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    TabViews    m_TabView;

};
#endif // MAINWINDOW_H
