#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "BookmarkPanel.h"
#include "NavigationPanel.h"
#include "NavigationUrl.h"

#include <QUrl>
#include <QVBoxLayout>
#include <QWebEnginePage>
#include <QWidget>

class Navigation : public QWidget
{
    Q_OBJECT
public:
    explicit Navigation(QWidget *parent = nullptr);

public slots:
    void ChangeLoadProgress(int);
    void UpdateNavigationStatus(QWebEnginePage*);

public:
    std::shared_ptr<NavigationPanel> GetNavigationPanel();
    std::shared_ptr<NavigationUrl>   GetNavigationUrl();
    std::shared_ptr<BookmarkPanel>   GetBookmarkPanel();

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    QHBoxLayout m_MainLayout;

    std::shared_ptr<NavigationPanel> m_Panel;
    std::shared_ptr<NavigationUrl>   m_Url;
    std::shared_ptr<BookmarkPanel>   m_Bookmark;

private:
    void moveWidgets(QPoint point);

};

#endif // NAVIGATION_H
