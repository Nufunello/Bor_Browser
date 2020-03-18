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
    m_CurrentView = std::move(view);
    openCurrentView();
}

void ViewWrapper::AddView(std::shared_ptr<View> view)
{
    m_Views.emplace_back(view);
    this->ChangeView(std::move(view));
}

std::shared_ptr<View> ViewWrapper::GetCurrentView()
{
    return m_CurrentView;
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
