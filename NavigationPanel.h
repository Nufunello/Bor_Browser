#ifndef NAVIGATIONPANEL_H
#define NAVIGATIONPANEL_H

#include <QPushButton>
#include <QWidget>

class NavigationPanel : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationPanel(QWidget *parent = nullptr);

public slots:
    void UpdateButtonsStatus(bool canGoBack, bool canGoForward);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void GoBackPressed();
    void GoForwardPressed();
    void RefreshPressed();

private:
    QPushButton m_BtnBack;
    QPushButton m_BtnForward;
    QPushButton m_BtnRefresh;
};

#endif // NAVIGATIONPANEL_H
