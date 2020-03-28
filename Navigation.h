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
    NavigationPanel* GetNavigationPanel();
    NavigationUrl*   GetNavigationUrl();
    BookmarkPanel*   GetBookmarkPanel();

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    QHBoxLayout m_MainLayout;

    std::unique_ptr<NavigationPanel> m_Panel;
    std::unique_ptr<NavigationUrl>   m_Url;
    std::unique_ptr<BookmarkPanel>   m_Bookmark;

private:
    void moveWidgets(QPoint point);

};

#endif // NAVIGATION_H
