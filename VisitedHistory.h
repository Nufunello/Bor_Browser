#ifndef VISITEDHISTORY_H
#define VISITEDHISTORY_H

#include "VisitedPage.h"

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class VisitedHistory : public QWidget
{
    Q_OBJECT
public:
    explicit VisitedHistory(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

public:
    void        SetInfo(VisitedPage);
    VisitedPage GetPageData();

signals:
    void HrefPressed(QUrl);
    void RemovePressed();

private:
    QLabel      m_LblTime;
    QPushButton m_BtnHref;
    QPushButton m_BtnRemove;

private:
    VisitedPage m_PageData;

private:
    void moveElements();

};

#endif // VISITEDHISTORY_H
