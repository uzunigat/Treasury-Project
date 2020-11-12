#include "rapprochementdialog.h"
#include "ui_rapprochementdialog.h"
#include <QMessageBox>

#include <QDebug>

Rapprochementdialog::Rapprochementdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rapprochementdialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

Rapprochementdialog::~Rapprochementdialog()
{
    delete ui;
}




void Rapprochementdialog::accept(){
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"Warning","Please enter a description");
        return;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this,"Warning","Please enter a name");
        return;
    }
    QDialog::accept();
}
