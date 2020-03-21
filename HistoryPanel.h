#ifndef HISTORYPANEL_H
#define HISTORYPANEL_H

#include "HistoryMenu.h"

#include <QPushButton>
#include <QWidget>

class HistoryPanel : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryPanel(QWidget *parent = nullptr);

public:
    std::shared_ptr<HistoryMenu> GetHistoryMenu();

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    QPushButton                  m_BtnOpenHistoryMenu;
    std::shared_ptr<HistoryMenu> m_Menu;

};

#endif // HISTORYPANEL_H
