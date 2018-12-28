#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include <QTime>
//#include <QTableWidgetItem>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_speed(1)
{
	ui->setupUi(this);
	wsServer = new WsServer(7007);	
	connect(wsServer, SIGNAL(newConnection(int)), this, SLOT(setClientCount(int)) );
    connect(wsServer, SIGNAL(newCounter(int)), this, SLOT(showCounter(int)) );
    connect(wsServer, SIGNAL(sendCommand(int, QString)), this, SLOT(showCommand(int, QString))  );
	connect(wsServer, SIGNAL(newDensity(int)), this, SLOT(updateDensity(int)) );

    on_speedDial_valueChanged(ui->speedDial->value()); // set the speed
	on_commandRateSpinBox_valueChanged(ui->commandRateSpinBox->value());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_startButton_clicked()
{
    wsServer->timer.start();
    updateCounter(ui->startFromSpinBox->value());
}

void MainWindow::on_stopButton_clicked()
{
    wsServer->timer.stop();
    updateCounter(ui->startFromSpinBox->value());
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
	ui->startFromSpinBox->setValue(-10);
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
	if (value > 3752) {
		qDebug() << "Stop. Should be over";
		wsServer->timer.stop();
		//on_stopButton_clicked(); // then stop
	}
}

void MainWindow::showCommand(int player, QString commandString)
{
    int testrows= ui->tableWidget->rowCount(), testcolumns = ui->tableWidget->columnCount();

	//qDebug()<< "Command: " << commandString;
    if ( !ui->tableWidget->item(player, 0)) {
       ui->tableWidget->setItem(player,0, new QTableWidgetItem(commandString));
    } else {
        ui->tableWidget->item(player, 0)->setText(commandString);
    }

}

void MainWindow::updateCounter(int value)
{
    wsServer->counter = value;
    showCounter(value);

}

void MainWindow::on_testButton_clicked()
{
	wsServer->sendToAll("command YLD_02");
}

void MainWindow::on_commandRateSpinBox_valueChanged(int arg1)
{
	qDebug()<<"Send now every "<<arg1<<". command.";
	wsServer->setDensity(arg1);
}

void MainWindow::updateDensity(int density)
{
	ui->commandRateSpinBox->setValue(density);
}
