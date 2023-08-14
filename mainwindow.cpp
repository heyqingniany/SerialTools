#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette backColor = QPalette();
    backColor.setColor(QPalette::Window, "#19232d");

    this->setAutoFillBackground(true);
    this->setPalette(backColor);
    ui->plainTextEdit->setAutoFillBackground(true);
    ui->plainTextEdit->setBackgroundVisible(true);
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->setPalette(backColor);



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

