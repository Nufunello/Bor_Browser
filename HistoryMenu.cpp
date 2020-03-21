#include "HistoryMenu.h"

#include <QResizeEvent>

constexpr int VISITED_HISTORY_HEIGHT = 40;

HistoryMenu::HistoryMenu(QWidget *parent)
    : QMainWindow(parent)
{
}

void HistoryMenu::resizeEvent(QResizeEvent *event)
{
    for (const auto& visited : m_Visited)
    {
        visited->resize(event->size().width(), VISITED_HISTORY_HEIGHT);
    }
}

void HistoryMenu::paintEvent(QPaintEvent *)
{
    int x = 0, y = 0;
    for (const auto& visited : m_Visited)
    {
        visited->move(x, y);
        y += VISITED_HISTORY_HEIGHT;
    }
}

void HistoryMenu::AddVisitedPage(VisitedPage page)
{
    auto visitedHistory = std::make_shared<VisitedHistory>(this);
    visitedHistory->SetInfo(page);
    visitedHistory->resize(this->width(), VISITED_HISTORY_HEIGHT);

    std::weak_ptr<VisitedHistory> weakVisited = visitedHistory;

    connect(&*visitedHistory, &VisitedHistory::HrefPressed, this, &HistoryMenu::VisitedHistorySelected);

    connect(&*visitedHistory, &VisitedHistory::RemovePressed, [this, weakVisited](){
        m_Visited.erase(weakVisited.lock());
    });

    m_Visited.insert(visitedHistory);
}
