#include "ViewWrapper.h"

#include <QResizeEvent>

ViewWrapper::ViewWrapper(QWidget *parent)
    : QWidget(parent)
    , m_CurrentView{nullptr}
{
}

void ViewWrapper::resizeEvent(QResizeEvent *event)
{
    if (m_CurrentView != nullptr)
    {
        m_CurrentView->resize(event->size());
    }
}

void ViewWrapper::ChangeView(std::shared_ptr<View> view)
{
    closeCurrentView();
    m_CurrentView = view;
    openCurrentView();
}

std::shared_ptr<View> ViewWrapper::GetCurrentView()
{
    return m_CurrentView;
}

void ViewWrapper::closeCurrentView()
{
    if (m_CurrentView != nullptr)
    {
        m_CurrentView->hide();
        QObject::disconnect(m_CurrentPageLoadedConnection);
    }
}

void ViewWrapper::openCurrentView()
{
    if (m_CurrentView != nullptr)
    {
        m_CurrentPageLoadedConnection = connect(&*m_CurrentView, &View::PageLoaded, this, &ViewWrapper::PageLoaded);

        m_CurrentView->resize(this->size());
        m_CurrentView->show();
    }
}
