#include "addtransfertdialog.h"
#include "ui_addtransfertdialog.h"
#include "QDebug"
#include "QMessageBox"
#include <vector>

AddTransfertDialog::AddTransfertDialog(QTreeWidgetItem* Item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransfertDialog)
{
    qDebug()<<"ctor Addtransfert!";
    qDebug()<<"treeItem:"<<Item;
    ui->setupUi(this);
    ui->treeWidget->addTopLevelItem(Item);
    ui->treeWidget->setColumnWidth(0, 170);
    ui->treeWidget->setColumnWidth(1, 40);
    ui->dateEdit->setDate(QDate::currentDate());
    setWindowTitle("Add Transfert");
//    ui->treeWidget->hideColumn(1);

}

AddTransfertDialog::~AddTransfertDialog()
{
    delete ui;
}

void AddTransfertDialog::on_pushButton_clicked()
{
    QList<QTreeWidgetItem*> item_list = ui->treeWidget->selectedItems();
    QTreeWidgetItem* selectedItem ;
    if(!item_list.empty())
        selectedItem = item_list.at(0);
    else{
        QMessageBox::warning(this,"Warning","Please select a account!");
        return;
    }
    int count = ui->tableWidget->rowCount();

    if(!item_list.empty()){
        QString name = selectedItem->text(0);
        QString id = selectedItem->text(1);
        if(selectedItem->text(3)=="Virtuel"||selectedItem->text(3)==""){           //only allows to add new account under a virtual account
            QMessageBox::warning(this,"Warning","Can not use virtual accounts!");
            return;
        }

        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,3)->text()==id){
                QMessageBox::warning(this,"Warning","This account has already been added!");
                return;
            }
        }

        qDebug()<<"add id: "<<selectedItem->text(1)<<"to table";

        ui->tableWidget->insertRow(count);

        QTableWidgetItem* itemName = new QTableWidgetItem(name);
        itemName->setFlags(itemName->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(count, 0, itemName);
        QTableWidgetItem* itemId = new QTableWidgetItem(id);
        itemId->setFlags(itemId->flags() ^ Qt::ItemIsEditable);
        ui->tableWidget->setItem(count, 3, itemId);

        auto dv = new QDoubleValidator(0.0, 5.0, 2);    //with 2 decimals of precision
        QLineEdit *edit1 = new QLineEdit(ui->tableWidget);
        QLineEdit *edit2 = new QLineEdit(ui->tableWidget);
        edit1->setFrame(false);
        edit2->setFrame(false);
        edit1->setValidator(dv);
        edit2->setValidator(dv);
        ui->tableWidget->setCellWidget(count, 1, edit1);
        ui->tableWidget->setCellWidget(count, 2, edit2);
    }
    else{
        QMessageBox::warning(this,"Missing account","Please select an account!");
    }
}





void AddTransfertDialog::accept(){
    if(ui->tableWidget->rowCount()<2){
        QMessageBox::warning(this,"Invalid Transfert","Please add at least 2 accounts!");
        return;
    }
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this,"Invalid Transfert","Please enter a title!");
        return;
    }
    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this,"Invalid Transfert","Please enter a Reference!");
        return;
    }
    T.clear();
    QTableWidget* table = ui->tableWidget;
    for (int i=0;i<ui->tableWidget->rowCount();i++){
        QLineEdit* edit1 = qobject_cast<QLineEdit*>(table->cellWidget(i,1));
        QLineEdit* edit2 = qobject_cast<QLineEdit*>(table->cellWidget(i,2));

        int id = table->item(i,3)->text().toInt();
        double debit =  edit1->text().isEmpty()? 0:edit1->text().toDouble();
        double credit =  edit2->text().isEmpty()? 0:edit2->text().toDouble();

        if(debit==0&&credit==0){
            QMessageBox::warning(this,"Invalid Transfert","There is a redundant account!");
            return;
        }
        T.push_back({id,debit,credit});
        qDebug()<<"id:"<<T[i].id<<" debit:"<<T[i].debit<< "credit:"<<T[i].credit;
    }
    double totalDebit=0;
    double totalCredit=0;
    for (auto t : T){
        totalDebit += t.debit;
        totalCredit += t.credit;
    }
    qDebug()<<"total debit"<<totalDebit;
    qDebug()<<"total credit"<<totalCredit;
    if(totalDebit!=totalCredit){
        QMessageBox::warning(this,"Invalid Transfert","Total debit not equal to total credit!");
        return;
    }
    QDialog::accept();
}


void AddTransfertDialog::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item)
{
    if(item->text(3)=="Reel"){
        on_pushButton_clicked();
    }
}



void AddTransfertDialog::on_pushButton_2_clicked()
{

   if(!ui->tableWidget->selectedItems().empty()){

       QList<QTableWidgetItem*> list = ui->tableWidget->selectedItems();

       QTableWidgetItem* item = list.at(0);

       ui->tableWidget->removeRow(item->row());


    }

    else{

        QMessageBox::warning(this,"Warning","aucun compte sélectionné");


    }


}
