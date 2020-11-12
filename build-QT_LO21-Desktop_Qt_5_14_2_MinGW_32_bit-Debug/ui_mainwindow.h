/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_as;
    QAction *actionAdd_account;
    QAction *actionDelete_Account;
    QAction *actionOpen_preset_File;
    QAction *actionAdd_Transation;
    QWidget *centralwidget;
    QTreeWidget *treeWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionAdd_account = new QAction(MainWindow);
        actionAdd_account->setObjectName(QString::fromUtf8("actionAdd_account"));
        actionDelete_Account = new QAction(MainWindow);
        actionDelete_Account->setObjectName(QString::fromUtf8("actionDelete_Account"));
        actionOpen_preset_File = new QAction(MainWindow);
        actionOpen_preset_File->setObjectName(QString::fromUtf8("actionOpen_preset_File"));
        actionAdd_Transation = new QAction(MainWindow);
        actionAdd_Transation->setObjectName(QString::fromUtf8("actionAdd_Transation"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(0, 10, 741, 331));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionOpen_preset_File);
        menuEdit->addAction(actionAdd_account);
        menuEdit->addAction(actionDelete_Account);
        menuEdit->addAction(actionAdd_Transation);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionOpen_preset_File);
        toolBar->addAction(actionSave_as);
        toolBar->addAction(actionAdd_account);
        toolBar->addAction(actionDelete_Account);
        toolBar->addAction(actionAdd_Transation);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New Window...", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open...", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as...", nullptr));
        actionAdd_account->setText(QCoreApplication::translate("MainWindow", "Add account...", nullptr));
        actionDelete_Account->setText(QCoreApplication::translate("MainWindow", "Delete account", nullptr));
        actionOpen_preset_File->setText(QCoreApplication::translate("MainWindow", "Open preset File", nullptr));
        actionAdd_Transation->setText(QCoreApplication::translate("MainWindow", "Add Transation", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("MainWindow", "Type", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "Property", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Solde", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "ID", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Nom du compte", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
