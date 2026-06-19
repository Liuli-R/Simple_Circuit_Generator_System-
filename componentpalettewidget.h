#ifndef COMPONENTPALETTEWIDGET_H
#define COMPONENTPALETTEWIDGET_H

//核心思路->封装成自定义控件
#include <QWidget>

class QAction;
class QToolButton;

namespace Ui {
class ComponentPaletteWidget;
}

class ComponentPaletteWidget : public QWidget
{
    Q_OBJECT

public:
    ComponentPaletteWidget(QWidget *parent = nullptr);
    ~ComponentPaletteWidget();

signals:
    void bulbRequested();
    void switchRequested();
    void batteryRequested();
    void ammeterRequested();
    void voltmeterRequested();
    void resistorRequested();

private:
    Ui::ComponentPaletteWidget *ui;

    QAction *bulbAction = nullptr;
    QAction *switchAction = nullptr;
    QAction *batteryAction = nullptr;
    QAction *ammeterAction = nullptr;
    QAction *voltmeterAction = nullptr;
    QAction *resistorAction = nullptr;

    void setupHeader();
    void setupComponentActions();
    void setupComponentPanel();
    void setupConnections();

    QToolButton *createComponentButton(QAction *action);
};

#endif // COMPONENTPALETTEWIDGET_H
