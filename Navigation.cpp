#include "Navigation.h"

#include <QWebEngineHistory>
#include <QResizeEvent>

constexpr int PANEL_WIDTH = 90;
constexpr int BOOKMARK_WIDTH = 80;

Navigation::Navigation(QWidget *parent)
    : QWidget(parent)
{
    m_Panel    = std::make_unique<NavigationPanel>(this);
    m_Url      = std::make_unique<NavigationUrl>(this);
    m_Bookmark = std::make_unique<BookmarkPanel>(this);

    m_MainLayout.addWidget(&*m_Panel);
    m_MainLayout.addWidget(&*m_Url);
    m_MainLayout.addWidget(&*m_Bookmark);
}

void Navigation::ChangeLoadProgress(int progress)
{
    m_Url->ChangeLoadProgress(std::move(progress));
}

void Navigation::UpdateNavigationStatus(QWebEnginePage *page)
{
    m_Url->ChangeUrl(page->url());

    auto pageHistory = page->history();
    m_Panel->UpdateButtonsStatus(pageHistory->canGoBack(), pageHistory->canGoForward());
}

NavigationPanel* Navigation::GetNavigationPanel()
{
    return m_Panel.get();
}

NavigationUrl* Navigation::GetNavigationUrl()
{
    return m_Url.get();
}

BookmarkPanel* Navigation::GetBookmarkPanel()
{
    return m_Bookmark.get();
}

void Navigation::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width(), height = event->size().height();

    m_Panel->resize(PANEL_WIDTH, height);
    m_Url->resize(width - PANEL_WIDTH - BOOKMARK_WIDTH, height);
    m_Bookmark->resize(BOOKMARK_WIDTH, height);

    moveWidgets(this->pos());
}

void Navigation::moveWidgets(QPoint point)
{
    int y = point.y();

    m_Panel->move(point);
    m_Url->move(m_Panel->x() + PANEL_WIDTH, y);
    m_Bookmark->move(m_Url->x() + m_Url->width(), y);
}
