#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QString>
#include <QStringList>

namespace {
QString loadApplicationStyleSheet()
{
    const QStringList stylePaths = {
        ":/styles/base.qss",
        ":/styles/actions.qss",
        ":/styles/palette.qss",
        ":/styles/dock.qss",
        ":/styles/dialog.qss",
        ":/styles/guide.qss",
        ":/styles/scrollbar.qss"
    };

    QString styleSheet;
    for (const QString &path : stylePaths)
    {
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            styleSheet += QString::fromUtf8(file.readAll());
            styleSheet += '\n';
        }
    }
    return styleSheet;
}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(loadApplicationStyleSheet());

    MainWindow w;
    w.show();
    return QApplication::exec();
}
