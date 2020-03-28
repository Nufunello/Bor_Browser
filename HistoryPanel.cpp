#include "HistoryPanel.h"

#include <QResizeEvent>

HistoryPanel::HistoryPanel(QWidget *parent)
    : QWidget(parent)
{
    m_BtnOpenHistoryMenu.setParent(this);
    m_BtnOpenHistoryMenu.setText("History");

    m_Menu = std::make_unique<HistoryMenu>(this);
    m_Menu->resize(400, 800);

    connect(&m_BtnOpenHistoryMenu, &QPushButton::clicked, &*m_Menu, &HistoryMenu::show);
}

HistoryMenu* HistoryPanel::GetHistoryMenu()
{
    return m_Menu.get();
}

void HistoryPanel::resizeEvent(QResizeEvent *event)
{
    m_BtnOpenHistoryMenu.resize(event->size());
}
