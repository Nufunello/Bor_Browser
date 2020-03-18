#include "Tab.h"

#include <QResizeEvent>

constexpr float MAIN_BUTTON_WIDTH_KOEF   = {0.8f};
constexpr float REMOVE_BUTTON_WIDTH_KOEF = {0.2f};

Tab::Tab(QWidget *parent)
    : QWidget(parent)
{
    m_BtnToBeSelected.setParent(this);
    m_BtnToRemove.setParent(this);

    m_BtnToRemove.setText("x");

    connect(&m_BtnToBeSelected, &QPushButton::clicked, this, &Tab::Selected);
    connect(&m_BtnToRemove,     &QPushButton::clicked, this, &Tab::Removed);
}

void Tab::UpdateTabInfo(QString title)
{
    m_BtnToBeSelected.setText(title);
}

void Tab::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width(), height = event->size().height();

    m_BtnToBeSelected.resize(width, height);
    m_BtnToRemove.    resize(width * REMOVE_BUTTON_WIDTH_KOEF, height);

    this->moveButtons();
}

void Tab::moveButtons()
{
    m_BtnToBeSelected.move(0, 0);
    m_BtnToRemove.    move(m_BtnToBeSelected.x() + m_BtnToBeSelected.width() * MAIN_BUTTON_WIDTH_KOEF, m_BtnToBeSelected.y());
}
