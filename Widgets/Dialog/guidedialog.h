#ifndef GUIDEDIALOG_H
#define GUIDEDIALOG_H

#include <QDialog>

namespace Ui {
class GuideDialog;
}

class GuideDialog : public QDialog
{
    Q_OBJECT

public:
    GuideDialog(QWidget *parent = nullptr);
    ~GuideDialog() override;

private:
    void setupPicture();
    void loadGuideContent();//加载说明内容文本

    Ui::GuideDialog *ui = nullptr;
};

#endif
