#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

private:
    QSerialPort comPort;                               // 串口对象
    void uartSend(QString cmd);                        // 向串口发送字符串数据
    void delayMs(int ms);                              // 毫秒级延时
    void loadFromReg();                                // 从注册表载入界面数据
    void saveToReg();                                  // 保存到注册表
    void closeEvent(QCloseEvent *event);

private slots:
    void do_com_readyRead();                            // 串口有数据可读
    void do_label_clicked();                                // 与label的click()信号关联







};
#endif // MAINWINDOW_H
