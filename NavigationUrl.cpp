#include "NavigationUrl.h"

#include <QResizeEvent>

constexpr int PADDING = 1;

static inline int isNotLoadingAnymore(int progress){
    return progress == 0 || progress == 100;
}

static QUrl formatUrlStr(QString url)
{
    return QUrl(url.startsWith("http") ? url : ("https://" + url));
}

NavigationUrl::NavigationUrl(QWidget *parent)
    : QWidget(parent)
{
    m_UrlInput.setParent(this);
    m_LoadProgress.setParent(this);

    m_LoadProgress.hide();

    connect(&m_UrlInput, &QLineEdit::returnPressed, [this](){
        emit UrlEntered(formatUrlStr(m_UrlInput.text()));
    });
}

void NavigationUrl::ChangeLoadProgress(int progress)
{
    if (isNotLoadingAnymore(progress))
    {
        m_LoadProgress.hide();
    }
    else
    {
        if (m_LoadProgress.isHidden())
        {
            m_LoadProgress.show();
        }

        m_LoadProgress.setValue(progress);
    }
}

void NavigationUrl::ChangeUrl(QUrl url)
{
    m_UrlInput.setText(url.toString());
}

void NavigationUrl::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width(), height = event->size().height() - 2 * PADDING;

    m_UrlInput.resize(width, height);
    m_LoadProgress.resize(width, height);
}

void NavigationUrl::paintEvent(QPaintEvent *)
{
    m_UrlInput.move(0, PADDING);
    m_LoadProgress.move(0, PADDING);
}
