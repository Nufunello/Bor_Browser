#ifndef URL_H
#define URL_H

#include <QWidget>
#include <QLineEdit>
#include <QUrl>
#include <QProgressBar>

class UrlWrapper;

class Url : public QWidget
{
    Q_OBJECT
public:
    explicit Url(std::shared_ptr<UrlWrapper> parent = nullptr);

public slots:
    void ChangeProgressBar(int progress);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;

signals:
    void UrlChanged(QUrl);

private:
    std::shared_ptr<QLineEdit> m_Url;
    std::shared_ptr<QProgressBar> m_ProgressBar;
};

#endif // URL_H
