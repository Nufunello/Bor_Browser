#ifndef NAVIGATIONURL_H
#define NAVIGATIONURL_H

#include <QLineEdit>
#include <QUrl>
#include <QProgressBar>
#include <QWidget>

class NavigationUrl : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationUrl(QWidget *parent = nullptr);

public slots:
    void ChangeLoadProgress(int);
    void ChangeUrl(QUrl);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void UrlEntered(QUrl);

private:
    QLineEdit    m_UrlInput;
    QProgressBar m_LoadProgress;

};

#endif // NAVIGATIONURL_H
