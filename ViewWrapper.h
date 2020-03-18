#ifndef VIEWWRAPPER_H
#define VIEWWRAPPER_H

#include "View.h"

#include <QWidget>

class ViewWrapper : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWrapper(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

public:
    void ChangeView(std::shared_ptr<View>);
    void AddView(std::shared_ptr<View>);

signals:

private:
    std::shared_ptr<View> m_CurrentView;
    std::vector<std::shared_ptr<View>> m_Views;

private:
    void closeCurrentView();
    void openCurrentView();

};

#endif // VIEWWRAPPER_H
