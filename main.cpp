#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtLanguageTranslator;
    qtLanguageTranslator.load(QString("QtLanguage_") + QString("en_US"));
    qApp->installTranslator(&qtLanguageTranslator);

    MainWindow w;
    w.show();
    return a.exec();
}
