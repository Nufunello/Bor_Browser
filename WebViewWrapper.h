#ifndef WEBVIEWWRAPPER_H
#define WEBVIEWWRAPPER_H

#include "WebView.h"

#include <QWidget>

class WebViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit WebViewWrapper(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    void ChangeWebView(std::shared_ptr<WebView>);

signals:

private:
    std::shared_ptr<WebView> m_WebView;

};

#endif // WEBVIEWWRAPPER_H
