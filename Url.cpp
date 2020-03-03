#include "Url.h"
#include "UrlWrapper.h"

#include <QResizeEvent>

Url::Url(std::shared_ptr<UrlWrapper> parent)
    : QWidget(&*parent)
{
    m_Url = std::make_shared<QLineEdit>(this);
}

void Url::resizeEvent(QResizeEvent *event)
{
    m_Url->resize(event->size());
}
