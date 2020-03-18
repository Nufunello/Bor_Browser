#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
#include <QWidget>

class WebView : public QWidget
{
    Q_OBJECT
public:
    explicit WebView(QWidget *parent = nullptr);

public:
    QWebEnginePage* GetCurrentPage();

public slots:
    void LoadUrl(QUrl);
    void GoBack();
    void GoForward();
    void Refresh();

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void Loading(int);
    void PageUpdated(QWebEnginePage*);
    void UrlChanged(QWebEnginePage*);

private:
    QWebEngineView m_WebView;

};

#endif // WEBVIEW_H
