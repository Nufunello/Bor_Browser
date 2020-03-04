#include "UrlWrapper.h"

#include <QResizeEvent>

UrlWrapper::UrlWrapper(QWidget *parent)
    : QWidget(parent)
    , m_Url{nullptr}
{
}

void UrlWrapper::ChangeUrl(std::shared_ptr<Url> url)
{
    if (m_Url != nullptr)
    {
        m_Url->hide();
    }

    m_Url = url;
    m_Url->show();

    m_Url->resize(size());
}

void UrlWrapper::resizeEvent(QResizeEvent *event)
{
    if (m_Url != nullptr)
    {
        m_Url->resize(event->size());
    }
}
