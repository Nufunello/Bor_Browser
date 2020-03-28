#ifndef TAB_H
#define TAB_H

#include "View.h"

#include <QPushButton>
#include <QWidget>

class Tab : public QWidget
{
    Q_OBJECT
public:
    explicit Tab(QWidget *parent = nullptr);

public slots:
    void UpdateTabInfo(QString title);
    void SetEnabled();
    void SetDisabled();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void Selected();
    void Removed();

private:
    QPushButton m_BtnToBeSelected;
    QPushButton m_BtnToRemove;

};

#endif // TAB_H
