#ifndef CIRCUITSETTINGSDIALOG_H
#define CIRCUITSETTINGSDIALOG_H

#include <QDialog>
#include <QString>

struct CircuitSettings
{
    double batteryVoltage = 9.0;
    int voltmeterId = -1;
    int targetComponentId = -1;
};//用结构体存储对应消息->作用同昨天的存储计算结果

namespace Ui {
class CircuitSettingsDialog;
}

class CircuitSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CircuitSettingsDialog(QWidget *parent = nullptr);
    ~CircuitSettingsDialog() override;

    void setInitialVoltage(double voltage);
    void addVoltmeterOption(int componentId);
    void addTargetOption(int componentId, const QString &displayText);

    CircuitSettings settings() const;

private:
    void validateAndAccept();
    void setupPicture();//设置旁边看板图片

    Ui::CircuitSettingsDialog *ui = nullptr;
};

#endif // CIRCUITSETTINGSDIALOG_H
