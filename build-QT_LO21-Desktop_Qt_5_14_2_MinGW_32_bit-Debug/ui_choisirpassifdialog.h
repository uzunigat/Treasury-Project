/********************************************************************************
** Form generated from reading UI file 'choisirpassifdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOISIRPASSIFDIALOG_H
#define UI_CHOISIRPASSIFDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChoisirPassifDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QDialog *ChoisirPassifDialog)
    {
        if (ChoisirPassifDialog->objectName().isEmpty())
            ChoisirPassifDialog->setObjectName(QString::fromUtf8("ChoisirPassifDialog"));
        ChoisirPassifDialog->resize(320, 240);
        buttonBox = new QDialogButtonBox(ChoisirPassifDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(90, 180, 211, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(ChoisirPassifDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 50, 161, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);


        retranslateUi(ChoisirPassifDialog);

        QMetaObject::connectSlotsByName(ChoisirPassifDialog);
    } // setupUi

    void retranslateUi(QDialog *ChoisirPassifDialog)
    {
        ChoisirPassifDialog->setWindowTitle(QCoreApplication::translate("ChoisirPassifDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ChoisirPassifDialog", "Choisir le compte passif : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChoisirPassifDialog: public Ui_ChoisirPassifDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOISIRPASSIFDIALOG_H
