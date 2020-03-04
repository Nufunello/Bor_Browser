#include "mainwindow.h"
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,800);
    m_TabView = std::make_shared<TabViewWrapper>(this);

    addEmptyTabView();
    addEmptyTabView();
    addEmptyTabView();
    addEmptyTabView();
    addEmptyTabView();
    addEmptyTabView();
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_TabView->resize(event->size());
}

void MainWindow::addEmptyTabView()
{
    auto newTabView = std::make_shared<TabView>(m_TabView);
    m_TabViews.emplace_back(newTabView);
    m_TabView->AddTabView(newTabView);
}

