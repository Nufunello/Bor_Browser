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

void ViewWrapper::closeCurrentView()
{
    if (m_CurrentView != nullptr)
        m_CurrentView->hide();
}

void ViewWrapper::openCurrentView()
{
    m_CurrentView->resize(this->size());
    m_CurrentView->show();
}
