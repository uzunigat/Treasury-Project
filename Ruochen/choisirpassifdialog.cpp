#include "choisirpassifdialog.h"
#include "ui_choisirpassifdialog.h"
#include "qdebug.h"
ChoisirPassifDialog::ChoisirPassifDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoisirPassifDialog)
{
    ui->setupUi(this);
    setWindowTitle("Choose liability account");
}

ChoisirPassifDialog::~ChoisirPassifDialog()
{
    delete ui;
}

void ChoisirPassifDialog::on_buttonBox_accepted()
{
    qDebug()<<"ChoisirPassifDialog-accepted";
    QDialog::accept();
    emit(accepted(ui->comboBox->currentText()));
}

void ChoisirPassifDialog::on_buttonBox_rejected()
{
    qDebug()<<"ChoisirPassifDialog-canceled";
    QDialog::reject();
}
