#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QToolButton>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setupScene();
    void setupComponentActions();
    QToolButton *createComponentButton(QAction *action);
    void setupComponentPanel();
    void setupRunButton();
    void setupHeader();
    void setupConnections();
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene=nullptr;
    QAction *bulbAction=nullptr;
    QAction *switchAction=nullptr;
    QAction *batteryAction=nullptr;
    QAction *ammeterAction=nullptr;
    QAction *voltmeterAction=nullptr;
    QAction *resistorAction=nullptr;
    QAction *runAction=nullptr;
    QList<QAction *> componentActions;
};
#endif // MAINWINDOW_H
