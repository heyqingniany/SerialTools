#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sendButton,SIGNAL(clicked()), this, SLOT(ShowSend()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ShowSend()
{
    QTime timeStamp;
    timeStamp = QTime::currentTime();

    QString timeAddedMessage;
    timeAddedMessage = timeStamp.toString("hh:mm:ss") + ": " + "Message";
    ui->plainTextEdit->appendPlainText(timeAddedMessage);
}

