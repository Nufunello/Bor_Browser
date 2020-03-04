#ifndef URLWRAPPER_H
#define URLWRAPPER_H

#include "Url.h"

#include <QWidget>

class UrlWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit UrlWrapper(QWidget *parent = nullptr);

public:
    void ChangeUrl(std::shared_ptr<Url>);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    std::shared_ptr<Url> m_Url;

};

#endif // URLWRAPPER_H
