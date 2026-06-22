#include "guidedialog.h"
#include "ui_guidedialog.h"

#include <QDialogButtonBox>
#include <QFile>
#include <QPixmap>
#include <QString>

GuideDialog::GuideDialog(QWidget *parent): QDialog(parent)
    , ui(new Ui::GuideDialog)
{
    ui->setupUi(this);
    ui->horizontalLayout->setAlignment(ui->guidePictureLabel,Qt::AlignVCenter);

    ui->guideBrowser->setOpenExternalLinks(true);
    //允许打开对应网址连接->当前默认浏览器允许访问
    setupPicture();
    loadGuideContent();

    connect(ui->buttonBox,&QDialogButtonBox::rejected,
    this,&QDialog::reject);
}

GuideDialog::~GuideDialog()
{
    delete ui;
}

void GuideDialog::setupPicture()
{
    QPixmap picture(":/Cpp_Practice_Picture/Guide.png");

    if (picture.isNull())
    {
        ui->guidePictureLabel->setText("说明图片加载失败");
        return;
    }

    ui->guidePictureLabel->setPixmap(picture.scaled(QSize(250, 250),
    Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

void GuideDialog::loadGuideContent()
{
    QFile file(":/docs/guide.md");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        ui->guideBrowser->setPlainText("说明文件加载失败");
        return;
    }

    ui->guideBrowser->setMarkdown(QString::fromUtf8(file.readAll()));
}
