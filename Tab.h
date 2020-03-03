#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QPushButton>

class TabWrapper;

class Tab : public QWidget
{
    Q_OBJECT
public:
    explicit Tab(std::shared_ptr<TabWrapper> parent = nullptr);

signals:

private:
    std::shared_ptr<QPushButton> m_Btn;
};

#endif // TAB_H
