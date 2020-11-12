/********************************************************************************
** Form generated from reading UI file 'addtransfertdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTRANSFERTDIALOG_H
#define UI_ADDTRANSFERTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>

QT_BEGIN_NAMESPACE

class Ui_AddTransfertDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QListView *listView;

    void setupUi(QDialog *AddTransfertDialog)
    {
        if (AddTransfertDialog->objectName().isEmpty())
            AddTransfertDialog->setObjectName(QString::fromUtf8("AddTransfertDialog"));
        AddTransfertDialog->resize(640, 480);
        buttonBox = new QDialogButtonBox(AddTransfertDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 440, 621, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(AddTransfertDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(420, 50, 121, 16));
        label_2 = new QLabel(AddTransfertDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 50, 131, 16));
        listView = new QListView(AddTransfertDialog);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(70, 80, 256, 192));

        retranslateUi(AddTransfertDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddTransfertDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddTransfertDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddTransfertDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTransfertDialog)
    {
        AddTransfertDialog->setWindowTitle(QCoreApplication::translate("AddTransfertDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddTransfertDialog", "Compte \303\240 cr\303\251diter", nullptr));
        label_2->setText(QCoreApplication::translate("AddTransfertDialog", "Compte \303\240 d\303\251biter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTransfertDialog: public Ui_AddTransfertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTRANSFERTDIALOG_H
