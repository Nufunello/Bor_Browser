#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_TabView{this}
    , btn{this}
{
    resize(800,800);

    m_TabView.AddTabView(std::make_shared<TabView>(&m_TabView));

    btn.move(500,0);
    connect(&btn, &QPushButton::clicked, this, &MainWindow::add);

    m_TabView.resize(size());

}

MainWindow::~MainWindow()
{
}

