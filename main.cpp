#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    QDebug() << "\n"
             <<"Port"<<serialPortInfos.;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SerialTools_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
