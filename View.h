#ifndef VIEW_H
#define VIEW_H

#include "Navigation.h"
#include "WebView.h"

#include <QVBoxLayout>
#include <QWidget>

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    std::shared_ptr<Navigation> GetNavigation();
    std::shared_ptr<WebView>    GetWebView();

signals:
    void PageLoaded(QWebEnginePage*);

private:
    QVBoxLayout m_MainLayout;

    std::shared_ptr<Navigation> m_Navigation;
    std::shared_ptr<WebView>    m_WebView;

private:
    void moveWidgets();

};

#endif // VIEW_H
