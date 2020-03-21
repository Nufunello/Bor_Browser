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

public:
    void      SetInfo(VisitedPage);
    QDateTime GetDate();

signals:
    void HrefPressed(QUrl);
    void RemovePressed();

private:
    QLabel      m_LblTime;
    QPushButton m_BtnHref;
    QPushButton m_BtnRemove;

private:
    QUrl      m_Url;
    QDateTime m_Date;

private:
    void moveElements();

};

#endif // VISITEDHISTORY_H
