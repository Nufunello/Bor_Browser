#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include "View.h"

#include <QWidget>

class ViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWrapper(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    void ChangeView(View*);

    View* GetCurrentView();

signals:
    void PageLoaded(QWebEnginePage*);

private:
    View*                   m_CurrentView;
    QMetaObject::Connection m_CurrentPageLoadedConnection;

private:
    void closeCurrentView();
    void openCurrentView();

};

#endif // VIEWWRAPPER_H
