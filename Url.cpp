#include "Url.h"
#include "UrlWrapper.h"

#include <QResizeEvent>

static QString formatUrlText(const QString& str)
{
    if (str.startsWith("http://") || str.startsWith("https://"))
    {
        return str;
    }
    else
    {
        return "https://" + str;
    }
}

Url::Url(std::shared_ptr<UrlWrapper> parent)
    : QWidget(&*parent)
{
    m_Url         = std::make_shared<QLineEdit>(this);
    m_ProgressBar = std::make_shared<QProgressBar>(this);

    m_ProgressBar->hide();

    connect(&*m_Url, &QLineEdit::returnPressed, this, [&](){
        auto enteredUrl = formatUrlText(m_Url->text());
        emit this->UrlChanged(QUrl(enteredUrl));
    });
}

void Url::ChangeProgressBar(int progress)
{
    if (progress == 0 || progress == 100)
    {
        m_ProgressBar->hide();
    }
    else
    {
        if (m_ProgressBar->isHidden())
        {
            m_ProgressBar->show();
        }

        m_ProgressBar->setValue(progress);
    }

}

void Url::resizeEvent(QResizeEvent *event)
{
    m_Url->resize(event->size());
    m_ProgressBar->resize(event->size());
}
void Url::enterEvent(QEvent *)
{
    //on click
}
