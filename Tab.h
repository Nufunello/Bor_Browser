#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QPushButton>
#include <QWebEnginePage>

class TabWrapper;

class Tab : public QWidget
{
    Q_OBJECT
public:
    explicit Tab(std::shared_ptr<TabWrapper> parent = nullptr);

public slots:
    void UpdateTab(QWebEnginePage* page);

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    void SetDisabled();
    void SetEnabled();

signals:
    void Selected();

private:
    std::shared_ptr<QPushButton> m_Btn;
};

#endif // TAB_H
