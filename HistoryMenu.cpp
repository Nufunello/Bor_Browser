#include "HistoryMenu.h"

#include <QResizeEvent>

constexpr int VISITED_HISTORY_HEIGHT = 40;

constexpr char CSV_SEPARATOR[] = "||";
constexpr char STORAGE_FILE[] = "history.csv";

HistoryMenu::HistoryMenu(QWidget *parent)
    : QMainWindow(parent)
{
    QFile historyFile(STORAGE_FILE);
    historyFile.open(QIODevice::ReadOnly);

    QTextStream in(&historyFile);
    while (!in.atEnd())
    {
       QString line = in.readLine();
       auto dataList = line.split(CSV_SEPARATOR);

       VisitedPage page(dataList[0], dataList[1], QDateTime::fromString(dataList[2]));
       this->AddVisitedPage(std::move(page));
    }
    historyFile.close();
}

HistoryMenu::~HistoryMenu()
{
    QFile historyFile(STORAGE_FILE);
    historyFile.open(QIODevice::WriteOnly);
    QTextStream writeStream(&historyFile);

    for (const auto& visitedPage : m_Visited)
    {
        auto pageData = visitedPage->GetPageData();
        writeStream << pageData.Url.toString() << CSV_SEPARATOR << std::move(pageData.Title) << CSV_SEPARATOR << pageData.Date.toString() << "\n";
    }

    historyFile.close();
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
    visitedHistory->show();
    visitedHistory->resize(this->width(), VISITED_HISTORY_HEIGHT);

    std::weak_ptr<VisitedHistory> weakVisited = visitedHistory;

    connect(&*visitedHistory, &VisitedHistory::HrefPressed, [this](QUrl url){
        emit this->VisitedHistorySelected(std::move(url));
        this->hide();
    });

    connect(&*visitedHistory, &VisitedHistory::RemovePressed, [this, weakVisited](){
        m_Visited.erase(weakVisited.lock());
    });

    m_Visited.insert(visitedHistory);

}
