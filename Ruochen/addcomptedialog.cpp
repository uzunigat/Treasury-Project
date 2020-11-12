#include "addcomptedialog.h"
#include "ui_addcomptedialog.h"
#include "qdebug.h"
#include "QMessageBox"

AddCompteDialog::AddCompteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCompteDialog)
{
    ui->setupUi(this);
    ui->lineEditB->hide();
    ui->soldel->hide();
    ui->lineEditB->setEnabled(false);
    auto dv = new QDoubleValidator(0.0, 5.0, 2);    //with 2 decimals of precision
    ui->lineEditB->setValidator(dv);
    setWindowTitle("Add Account");
}

AddCompteDialog::~AddCompteDialog()
{
    delete ui;
}


void AddCompteDialog::on_comboBox_currentIndexChanged(int index)
{
    if(index==1&&(ui->comboBox2->currentIndex()==0||ui->comboBox2->currentIndex()==1)){
        ui->lineEditB->setEnabled(true);
        ui->lineEditB->show();
        ui->soldel->show();
    }

    else{
        ui->lineEditB->setEnabled(false);
        ui->lineEditB->hide();
        ui->soldel->hide();
        ui->lineEditB->setText(NULL);
    }
}

void AddCompteDialog::on_comboBox2_currentIndexChanged(int index)
{
    if((index==0||index==1)&&ui->comboBox->currentIndex()==1){
        ui->lineEditB->setEnabled(true);
        ui->soldel->show();
        ui->lineEditB->show();
    }
    else{
        ui->lineEditB->setEnabled(false);
        ui->lineEditB->hide();
        ui->soldel->hide();
        ui->lineEditB->setText(NULL);
    }
}

void AddCompteDialog::accept(){
    if(ui->lineEditA->text().isEmpty()){
        QMessageBox::warning(this,"Missing name","Please enter a name for the account!");
        return;
    }
    if(ui->lineEditB->text().isEmpty()&&ui->comboBox->currentIndex()==1&&ui->comboBox2->currentIndex()==0){
        QMessageBox::warning(this,"Missing solde","Please enter the solde for the account!");
        return;
    }
    else{
        QDialog::accept();
    }
}




