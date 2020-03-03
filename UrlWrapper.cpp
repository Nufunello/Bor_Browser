#include "UrlWrapper.h"

#include <QResizeEvent>

UrlWrapper::UrlWrapper(QWidget *parent)
    : QWidget(parent)
    , m_Url{nullptr}
{
}

void UrlWrapper::AddUrl(std::shared_ptr<Url> url)
{
    m_Url = url;
}

void UrlWrapper::resizeEvent(QResizeEvent *event)
{
    if (m_Url != nullptr)
    {
        m_Url->resize(event->size().width(), event->size().height());
    }
}
