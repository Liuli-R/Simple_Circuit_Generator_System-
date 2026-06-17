#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.css");
    //读取资源样式文件，加载美化资源
    if (file.open(QFile::ReadOnly))//判断是否能以只读方式打开文件
    {
        a.setStyleSheet(QString::fromUtf8(file.readAll()));
        //作用于全局，设计全局的样式格式设计
        //内部参数为阅读整体文件内容
    }
    MainWindow w;
    w.show();
    return QApplication::exec();
}
