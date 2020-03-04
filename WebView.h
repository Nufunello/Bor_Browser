#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>

class WebViewWrapper;

class WebView : public QWidget
{
    Q_OBJECT
public:
    explicit WebView(std::shared_ptr<WebViewWrapper> parent = nullptr);

public slots:
    void LoadUrl(QUrl);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void PageUpdated(QWebEnginePage*);
    void Loading(int progress);

private:
    std::shared_ptr<QWebEngineView> m_WebView;

};

#endif // WEBVIEW_H
