#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wsserver.h"
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_startButton_clicked();

	void on_stopButton_clicked();

	void on_seekButton_clicked();
	void setClientCount(int count);

	void on_resetButton_clicked();

    void on_speedDial_valueChanged(int value);

    void showCounter(int value);

    void showCommand(int player, QString commandString);

	void on_testButton_clicked();

    //void on_commandRateSpinBox_valueChanged(int arg1);

    // void updateDensity(int density);

    void on_sendButton_clicked();

private:
	Ui::MainWindow *ui;
	WsServer * wsServer;
    double m_speed;
    void updateCounter(int value);

};

#endif // MAINWINDOW_H
