#include "viewalltransfert.h"
#include "ui_viewalltransfert.h"
#include "QDebug"
#include <QMessageBox>
#include "ui_addtransfertdialog.h"

ViewAllTransfert::ViewAllTransfert(QTreeWidgetItem* Item, CompteManager* cm, TransactionManager* tm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAllTransfert)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0,90);
    ui->tableWidget->setColumnWidth(1,70);
    setWindowTitle("TRANSFERTS");
    treeitem = Item;
    this->cm = cm;
    this->tm = tm;
    ui->tableWidget->setColumnHidden(6, true);

}

ViewAllTransfert::~ViewAllTransfert()
{
    delete ui;
}

void ViewAllTransfert::on_pushButton_clicked()
{
    QDialog::accept();
}

void ViewAllTransfert::on_pushButton_2_clicked()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();
    if(!select->hasSelection()){
        QMessageBox::warning(this,"Missing transfert","Please select a transfert!");
        return;
    }

    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();

    int row=ui->tableWidget->row(items.at(0));  //selected row number
    int column = ui->tableWidget->column(items.at(0));//selected column number

    qDebug()<<row<<column;

    if(column!=1){
        QMessageBox::warning(this,"Missing transfert","Please select the reference of the transfert");
        return;
    }

    QString id = ui->tableWidget->item(row,6)->text();
    qDebug()<<"id:"<<id;

    QString ref=items.at(0)->text();
    QString titre=ui->tableWidget->item(row,2)->text();

    AddTransfertDialog* changeTransfertDialog = new AddTransfertDialog(getTreeitem(),this);
    QLineEdit* refEdit = changeTransfertDialog->getUi()->lineEdit_2;
    QLineEdit* titreEdit = changeTransfertDialog->getUi()->lineEdit;
    refEdit->setText(ref);
    titreEdit->setText(titre);


    if(changeTransfertDialog->exec()==QDialog::Accepted){

        qDebug()<<"QDialog::Accepted";

        tm->supprimer_transaction(id.toInt());
        int year = changeTransfertDialog->getUi()->dateEdit->date().year();
        int month = changeTransfertDialog->getUi()->dateEdit->date().month();
        int day = changeTransfertDialog->getUi()->dateEdit->date().day();
        const std::string title = changeTransfertDialog->getUi()->lineEdit->text().toStdString();
        const std::string ref = changeTransfertDialog->getUi()->lineEdit_2->text().toStdString();

        if(tm->verifierReference(ref)){

        Transaction* tran = tm->creerTransaction(year,month,day,ref,title);

        std::vector<Transfert> Tvector = changeTransfertDialog->getTransfertVector();

        for (unsigned int i=0;i<Tvector.size();i++){

            tran->add(Tvector[i].debit,Tvector[i].credit,cm->GetCompte(Tvector[i].id));
        }
        tm->ajouter_transaction(tran);

        emit(transaction_modified());

        }
        else{
            QMessageBox::warning(this,"Warning","Référence répétée");
        }
    }
}
