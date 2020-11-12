#include "saisirrapprochementdialog.h"
#include "ui_saisirrapprochementdialog.h"

SaisirRapprochementDialog::SaisirRapprochementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaisirRapprochementDialog)
{
    ui->setupUi(this);

}

SaisirRapprochementDialog::~SaisirRapprochementDialog()
{
    delete ui;
}

void SaisirRapprochementDialog::accept(){

    QDialog::accept();



}
