#ifndef HISTORYMENU_H
#define HISTORYMENU_H

#include "VisitedHistory.h"
#include "VisitedPage.h"

#include <set>

#include <QPushButton>
#include <QMainWindow>

struct VisitedHistoryCompare
{
    bool operator()(const std::shared_ptr<VisitedHistory>& lhs, const std::shared_ptr<VisitedHistory>& rhs) const
    {
        return lhs->GetPageData().Date > rhs->GetPageData().Date;
    }
};

class HistoryMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit HistoryMenu(QWidget *parent = nullptr);
    ~HistoryMenu();

protected:
    void resizeEvent(QResizeEvent*) override;
    void paintEvent(QPaintEvent*) override;

public slots:
    void AddVisitedPage(VisitedPage page);

signals:
    void VisitedHistorySelected(QUrl);

private:
    std::set<std::shared_ptr<VisitedHistory>, VisitedHistoryCompare> m_Visited;

};

#endif // HISTORYMENU_H
