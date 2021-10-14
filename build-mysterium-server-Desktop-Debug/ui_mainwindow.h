/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QPushButton *startButton;
    QLabel *clientLabel;
    QPushButton *stopButton;
    QLabel *counterLabel;
    QSpinBox *startFromSpinBox;
    QDial *speedDial;
    QLabel *label_2;
    QLabel *speedLabel;
    QPushButton *testButton;
    QPushButton *seekButton;
    QPushButton *resetButton;
    QLabel *label_4;
    QSpinBox *commandRateSpinBox;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(606, 689);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 441, 263));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        gridLayout->addWidget(startButton, 5, 0, 1, 1);

        clientLabel = new QLabel(layoutWidget);
        clientLabel->setObjectName(QString::fromUtf8("clientLabel"));

        gridLayout->addWidget(clientLabel, 0, 1, 1, 1);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        gridLayout->addWidget(stopButton, 6, 0, 1, 1);

        counterLabel = new QLabel(layoutWidget);
        counterLabel->setObjectName(QString::fromUtf8("counterLabel"));

        gridLayout->addWidget(counterLabel, 1, 1, 1, 1);

        startFromSpinBox = new QSpinBox(layoutWidget);
        startFromSpinBox->setObjectName(QString::fromUtf8("startFromSpinBox"));
        startFromSpinBox->setMinimum(-10);
        startFromSpinBox->setMaximum(5000);
        startFromSpinBox->setValue(-10);

        gridLayout->addWidget(startFromSpinBox, 5, 1, 1, 1);

        speedDial = new QDial(layoutWidget);
        speedDial->setObjectName(QString::fromUtf8("speedDial"));
        speedDial->setMaximum(100);
        speedDial->setSingleStep(1);
        speedDial->setValue(50);

        gridLayout->addWidget(speedDial, 3, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        speedLabel = new QLabel(layoutWidget);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));
        speedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(speedLabel, 3, 2, 1, 1);

        testButton = new QPushButton(layoutWidget);
        testButton->setObjectName(QString::fromUtf8("testButton"));

        gridLayout->addWidget(testButton, 6, 2, 1, 1);

        seekButton = new QPushButton(layoutWidget);
        seekButton->setObjectName(QString::fromUtf8("seekButton"));

        gridLayout->addWidget(seekButton, 6, 1, 1, 1);

        resetButton = new QPushButton(layoutWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        gridLayout->addWidget(resetButton, 5, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        commandRateSpinBox = new QSpinBox(layoutWidget);
        commandRateSpinBox->setObjectName(QString::fromUtf8("commandRateSpinBox"));
        commandRateSpinBox->setMinimum(1);
        commandRateSpinBox->setMaximum(12);

        gridLayout->addWidget(commandRateSpinBox, 4, 1, 1, 1);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 260, 581, 351));
        tableWidget->horizontalHeader()->setDefaultSectionSize(450);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 606, 39));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Mysterium Server", nullptr));
        label->setText(QApplication::translate("MainWindow", "\303\234hendusi:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "L\303\266\303\266k nr:", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "Start (alates)", nullptr));
        clientLabel->setText(QApplication::translate("MainWindow", "0", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        counterLabel->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Kiirus", nullptr));
        speedLabel->setText(QApplication::translate("MainWindow", "1", nullptr));
        testButton->setText(QApplication::translate("MainWindow", "Test", nullptr));
        seekButton->setText(QApplication::translate("MainWindow", "H\303\274ppa", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "Nulli", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Iga N. k\303\244sklus", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "K\303\244sk", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Tarmo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Helena", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Merje", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Levi", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Taavi", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Vambola", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
