#ifndef TOPACTIONWIDGET_H
#define TOPACTIONWIDGET_H

#include <QWidget>

class QAction;

namespace Ui {
class TopActionWidget;
}

class TopActionWidget : public QWidget
{
    Q_OBJECT

public:
    TopActionWidget(QWidget *parent = nullptr);
    ~TopActionWidget();

    void setRunAction(QAction *action);
    void setClearAction(QAction *action);

private:
    Ui::TopActionWidget *ui;
};

#endif // TOPACTIONWIDGET_H
