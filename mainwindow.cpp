#include "mainwindow.h"

#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_TabView{this}
{
    resize(800, 800);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_TabView.resize(event->size());
}

