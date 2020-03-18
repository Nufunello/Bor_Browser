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
    std::shared_ptr<WebView> GetWebView();

signals:

private:
    QVBoxLayout m_MainLayout;

    Navigation                   m_Navigation;
    BookmarkMenu                 m_BookmarkMenu;

    std::shared_ptr<WebView>     m_WebView;

private:
    void moveWidgets();

};

#endif // VIEW_H
