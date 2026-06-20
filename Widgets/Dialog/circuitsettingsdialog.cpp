#include "circuitsettingsdialog.h"
#include "ui_circuitsettingsdialog.h"

CircuitSettingsDialog::CircuitSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CircuitSettingsDialog)
{
    ui->setupUi(this);
}

CircuitSettingsDialog::~CircuitSettingsDialog()
{
    delete ui;
}
