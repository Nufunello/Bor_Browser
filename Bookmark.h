#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QPushButton>
#include <QUrl>
#include <QWidget>

class Bookmark : public QWidget
{
    Q_OBJECT
public:
    explicit Bookmark(QWidget *parent = nullptr);

public:
    QUrl GetUrl();

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void SetTitle(QString);
    void SetUrl(QUrl);

signals:
    void HrefPressed(QUrl);
    void RemovePressed();

private:
    QPushButton m_Href;
    QPushButton m_Remove;

private:
    QUrl m_Url;

};

#endif // BOOKMARK_H
