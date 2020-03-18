#ifndef TABVIEWWRAPPER_H
#define TABVIEWWRAPPER_H

#include "TabBar.h"
#include "TabView.h"
#include "ViewWrapper.h"

#include <QWidget>

class TabViews : public QWidget
{
    Q_OBJECT
public:
    explicit TabViews(QWidget *parent = nullptr);

public:
    void AddTabView(std::shared_ptr<TabView>);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

signals:

private:
    QVBoxLayout   m_MainLayout;

    TabBar        m_TabBar;
    ViewWrapper   m_View;
    BookmarkMenu  m_BookmarkMenu;

private:
    void addEmptyTab();

};

#endif // TABVIEWWRAPPER_H
