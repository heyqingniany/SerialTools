#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>
#include <QSettings>

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QIODevice>

#include "tmylabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->toolBox->setEnabled(false);
//    ui->tabWidget->setEnabled(false);

    //显示串口列表
    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
        ui->comboCom_Port->addItem(portInfo.portName()+":"+portInfo.description());
    ui->actCom_Open->setEnabled(ui->comboCom_Port->count()>0);   //如果有串口,则使能按键

    connect(&comPort,&QIODevice::readyRead, this, &MainWindow::do_com_readyRead);
    //添加标准波特率
    ui->comboCom_Baud->clear();
    foreach (qint32 baud, QSerialPortInfo::standardBaudRates()) {
        ui->comboCom_Baud->addItem(QString::number(baud));
    }
    ui->comboCom_Baud->setCurrentText("115200"); //默认使用115200

    QApplication::setOrganizationName("WWB-Qt");  // 设置应用程序参数,用于注册表
    QApplication::setApplicationName("my first serial try");
    loadFromReg();             // 从注册表载入数据





    connect(ui->sendButton,SIGNAL(clicked()), this, SLOT(ShowSend()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadFromReg()
{
    QSettings setting;
    bool saved = setting.value("saved", false).toBool();
    if(!saved)
        return;

    // 查找frame_cmdA中的QLineEdit对象,载入注册表里的数据
    QList<QLineEdit*> editList= ui->frame_CmdA->findChildren<QLineEdit*>();
}

void MainWindow::on_actCom_Open_triggered()
{//"打开串口"按钮
    if(comPort.isOpen())
    {
        QMessageBox::warning(this,"错误","打开串口时出现错误");
        return;
    }
    QList<QSerialPortInfo> comList = QSerialPortInfo::availablePorts();
    QSerialPortInfo portInfo = comList.at(ui->comboCom_Port->currentIndex());
    comPort.setPort(portInfo);                 // 设置使用哪个串口
    //comPort.setPortName(portInfo.portName());      // 也可以设置串口名称

    //设置串口通信参数
    QString str= ui->comboCom_Baud->currentText();
    comPort.setBaudRate(str.toInt());         //设置波特率
    int value= ui->comboCom_DataBit->currentText().toInt();
    comPort.setDataBits(QSerialPort::DataBits(value));     // 数据位,默认为8位

    value = 1+ui->comboCom_StopBit->currentIndex();
    comPort.setStopBits(QSerialPort::StopBits(value)); // 停止位,默认为1位
    if(ui->comboCom_Parity->currentIndex()==0)
        value= 0;
    else
        value= 1+ui->comboCom_Parity->currentIndex();
    comPort.setParity(QSerialPort::Parity(value));   // 校验位

    if(comPort.open(QIODeviceBase::ReadWrite))
    {
        QMessageBox::information(this,"提示信息","串口已经被成功打开");
    }



}

void MainWindow::onactCom_Close_triggered()
{
    //"关闭串口"按钮
    if(comPort.isOpen())
    {
        comPort.close();
    }

}
void MainWindow::do_com_readyRead()
{
        QByteArray all= comPort.readAll();
        QString str(all);
        ui->textCOM->appendPlainText(str);
}

void MainWindow::dolabel_clicked()
{
    TMyLabel *lab= static_cast<TMyLabel*>(sender());  //获取信号发射者
    QLineEdit *edit=static_cast<QLineEdit*>(lab->buddy());  //获取伙伴组件
    QString cmd= edit->text().trimmed();     //指令字符串
    if(ui->chkBox_NewLine2->isChecked())       //添加回车换行符
        cmd = cmd+"\r\n";                    //通过串口发送字符串
    uartSend(cmd);
}

void MainWindow::uartSend(QString cmd)
{
    ui->textCOM->appendPlainText(cmd);
    const char *stdCmd= cmd.toLocal8Bit().data();       //转换为char*类型字符串
    comPort.write(stdCmd);
}





void MainWindow::delayMs(int ms)
{//延时数据的单位: ms
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed()<ms)
        QApplication::processEvents();  //运行此程序,使得应用程序能够处理事件,程序界面不至于被固定住.

}

















