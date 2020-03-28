#ifndef TABVIEWWRAPPER_H
#define TABVIEWWRAPPER_H

#include "HistoryPanel.h"
#include "TabBar.h"
#include "TabView.h"
#include "ViewWrapper.h"

#include <unordered_set>

#include <QWidget>

class TabViews : public QWidget
{
    Q_OBJECT
public:
    explicit TabViews(QWidget *parent = nullptr);
    ~TabViews();

public:
    void AddTabView(std::unique_ptr<TabView>);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

signals:

private:
    QVBoxLayout   m_MainLayout;

    QHBoxLayout   m_TopLayout;
    QVBoxLayout   m_VerticalLayout;

    TabBar        m_TabBar;
    HistoryPanel  m_History;

    ViewWrapper   m_View;
    BookmarkMenu  m_BookmarkMenu;

private:
    std::unordered_set<std::unique_ptr<TabView>>  m_TabViews;

private:
    void addEmptyTab();
    void moveWidgets(QPoint);

};

#endif // TABVIEWWRAPPER_H
