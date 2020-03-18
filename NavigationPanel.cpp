#include "NavigationPanel.h"

constexpr size_t cButtons = 3;

#include <QResizeEvent>

NavigationPanel::NavigationPanel(QWidget *parent)
    : QWidget(parent)
{
    m_BtnBack.setParent(this);
    m_BtnForward.setParent(this);
    m_BtnRefresh.setParent(this);

    m_BtnBack.setText("<-");
    m_BtnForward.setText("->");
    m_BtnRefresh.setText("0");

    this->UpdateButtonsStatus(false, false);

    connect(&m_BtnBack,    &QPushButton::pressed, this, &NavigationPanel::GoBackPressed);
    connect(&m_BtnForward, &QPushButton::pressed, this, &NavigationPanel::GoForwardPressed);
    connect(&m_BtnRefresh, &QPushButton::pressed, this, &NavigationPanel::RefreshPressed);
}

void NavigationPanel::UpdateButtonsStatus(bool canGoBack, bool canGoForward)
{
    m_BtnBack.setEnabled(canGoBack);
    m_BtnForward.setEnabled(canGoForward);
}

void NavigationPanel::resizeEvent(QResizeEvent *event)
{
    int avgWidth = event->size().width() / cButtons;
    int height = event->size().height();

    m_BtnBack.resize(avgWidth, height);
    m_BtnForward.resize(avgWidth, height);
    m_BtnRefresh.resize(avgWidth, height);

    this->moveButtons();
}

void NavigationPanel::moveButtons()
{
    m_BtnBack.move(0, 0);
    m_BtnForward.move(m_BtnBack.x() + m_BtnBack.width(), m_BtnBack.y());
    m_BtnRefresh.move(m_BtnForward.x() + m_BtnForward.width(), m_BtnForward.y());
}
