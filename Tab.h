#ifndef TAB_H
#define TAB_H

#include <QPushButton>
#include <QWidget>

class Tab : public QWidget
{
    Q_OBJECT
public:
    explicit Tab(QWidget *parent = nullptr);

public slots:
    void UpdateTabInfo(QString title);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void Selected();

private:
    std::unique_ptr<QPushButton> m_BtnToBeSelected;

};

#endif // TAB_H
