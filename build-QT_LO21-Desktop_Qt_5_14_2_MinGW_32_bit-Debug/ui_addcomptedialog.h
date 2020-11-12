/********************************************************************************
** Form generated from reading UI file 'addcomptedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOMPTEDIALOG_H
#define UI_ADDCOMPTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddCompteDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *typel;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox2;
    QLabel *noml;
    QLineEdit *lineEditA;
    QLabel *soldel;
    QLineEdit *lineEditB;

    void setupUi(QDialog *AddCompteDialog)
    {
        if (AddCompteDialog->objectName().isEmpty())
            AddCompteDialog->setObjectName(QString::fromUtf8("AddCompteDialog"));
        AddCompteDialog->resize(404, 272);
        buttonBox = new QDialogButtonBox(AddCompteDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(220, 200, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(AddCompteDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 181, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        typel = new QLabel(verticalLayoutWidget);
        typel->setObjectName(QString::fromUtf8("typel"));

        verticalLayout->addWidget(typel);

        comboBox = new QComboBox(verticalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        comboBox2 = new QComboBox(verticalLayoutWidget);
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->setObjectName(QString::fromUtf8("comboBox2"));

        verticalLayout->addWidget(comboBox2);

        noml = new QLabel(verticalLayoutWidget);
        noml->setObjectName(QString::fromUtf8("noml"));

        verticalLayout->addWidget(noml);

        lineEditA = new QLineEdit(verticalLayoutWidget);
        lineEditA->setObjectName(QString::fromUtf8("lineEditA"));

        verticalLayout->addWidget(lineEditA);

        soldel = new QLabel(verticalLayoutWidget);
        soldel->setObjectName(QString::fromUtf8("soldel"));

        verticalLayout->addWidget(soldel);

        lineEditB = new QLineEdit(verticalLayoutWidget);
        lineEditB->setObjectName(QString::fromUtf8("lineEditB"));

        verticalLayout->addWidget(lineEditB);


        retranslateUi(AddCompteDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddCompteDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddCompteDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddCompteDialog);
    } // setupUi

    void retranslateUi(QDialog *AddCompteDialog)
    {
        AddCompteDialog->setWindowTitle(QCoreApplication::translate("AddCompteDialog", "Dialog", nullptr));
        typel->setText(QCoreApplication::translate("AddCompteDialog", "Virtuel ou r\303\251el", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("AddCompteDialog", "Virtuel", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("AddCompteDialog", "R\303\251el", nullptr));

        label->setText(QCoreApplication::translate("AddCompteDialog", "Type du compte", nullptr));
        comboBox2->setItemText(0, QCoreApplication::translate("AddCompteDialog", "Actif", nullptr));
        comboBox2->setItemText(1, QCoreApplication::translate("AddCompteDialog", "Passif", nullptr));
        comboBox2->setItemText(2, QCoreApplication::translate("AddCompteDialog", "Depense", nullptr));
        comboBox2->setItemText(3, QCoreApplication::translate("AddCompteDialog", "Recette", nullptr));

        noml->setText(QCoreApplication::translate("AddCompteDialog", "Nom", nullptr));
        soldel->setText(QCoreApplication::translate("AddCompteDialog", "Solde", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCompteDialog: public Ui_AddCompteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOMPTEDIALOG_H
