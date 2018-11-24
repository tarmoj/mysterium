#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include <QTime>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_speed(1)
{
	ui->setupUi(this);
	wsServer = new WsServer(7007);	
	connect(wsServer, SIGNAL(newConnection(int)), this, SLOT(setClientCount(int)) );
    connect(wsServer, SIGNAL(newCounter(int)), this, SLOT(showCounter(int)) );
    on_speedDial_valueChanged(ui->speedDial->value()); // set the speed
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_startButton_clicked()
{
    wsServer->resetEventCounters();
    wsServer->timer.start();
    updateCounter(ui->startFromSpinBox->value());
}

void MainWindow::on_stopButton_clicked()
{
    wsServer->timer.stop();
    updateCounter(ui->startFromSpinBox->value());
    wsServer->resetEventCounters();
}

void MainWindow::on_seekButton_clicked()
{
   updateCounter(ui->startFromSpinBox->value());
}

void MainWindow::setClientCount(int count)
{
	ui->clientLabel->setText(QString::number(count));
}

void MainWindow::on_resetButton_clicked()
{
    ui->startFromSpinBox->setValue(0);
}

void MainWindow::on_speedDial_valueChanged(int value)
{
    m_speed =  0.5 + ui->speedDial->value()/100.0; // to 0.5 .. 1.5
    ui->speedLabel->setText(QString::number(m_speed));
    wsServer->timer.setInterval(1000/m_speed);
}

void MainWindow::showCounter(int value)
{
    ui->counterLabel->setText(QString::number(value));
}

void MainWindow::updateCounter(int value)
{
    wsServer->counter = value;
    showCounter(value);

}
