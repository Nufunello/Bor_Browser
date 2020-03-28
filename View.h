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
    void paintEvent(QPaintEvent *event) override;

public:
    Navigation* GetNavigation();
    WebView*    GetWebView();

signals:
    void PageLoaded(QWebEnginePage*);

private:
    QVBoxLayout m_MainLayout;

    std::unique_ptr<Navigation> m_Navigation;
    std::unique_ptr<WebView>    m_WebView;

};

#endif // VIEW_H
