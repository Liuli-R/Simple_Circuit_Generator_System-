#ifndef CIRCUITSETTINGSDIALOG_H
#define CIRCUITSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class CircuitSettingsDialog;
}

class CircuitSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CircuitSettingsDialog(QWidget *parent = nullptr);
    ~CircuitSettingsDialog() override;

private:
    Ui::CircuitSettingsDialog *ui;
};

#endif // CIRCUITSETTINGSDIALOG_H
