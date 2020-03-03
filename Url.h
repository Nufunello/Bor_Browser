#ifndef URL_H
#define URL_H

#include <QWidget>
#include <QLineEdit>

class UrlWrapper;

class Url : public QWidget
{
    Q_OBJECT
public:
    explicit Url(std::shared_ptr<UrlWrapper> parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
signals:

private:
    std::shared_ptr<QLineEdit> m_Url;
};

#endif // URL_H
