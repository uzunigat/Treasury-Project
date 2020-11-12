#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_addcomptedialog.h"
#include "ui_choisirpassifdialog.h"
#include "ui_addtransfertdialog.h"
#include "ui_viewalltransfert.h"
#include "addcomptedialog.h"
#include "rapprochementdialog.h"
#include "addtransfertdialog.h"
#include "ui_rapprochementdialog.h"
#include "saisirrapprochementdialog.h"
\
#include "ui_saisirrapprochementdialog.h"

#include <QTreeWidgetItem>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <vector>


//test//

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    // **************************YOU CAN CHANGE THE PATH HERE*******************************
    filename = "/Users/apple/Documents/GitHub/lo21-projet-tr-sorerie/Ruochen/Comptes.xml";
    // *************************************************************************************
    ui->setupUi(this);
    ui->treeWidget->setColumnWidth(0, 250);
    ui->treeWidget->setColumnWidth(1, 50);
    ui->treeWidget->setColumnWidth(2, 100);
    ui->treeWidget->setColumnWidth(3, 70);
    cm = new CompteManager();
    tm = new TransactionManager();
    writeXmlFile_attributes(compte_tmp);
    openXML(compte_tmp,false);


}


MainWindow::~MainWindow()
{
    int ret;

    if(cm->getIdMax()!=0){
        QMessageBox msgBox;
        msgBox.setText("Le document a été modifié.");
        msgBox.setInformativeText("Voulez-vous enregistrer les changements ?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
    }
    else{
        ret = QMessageBox::Discard;
    }

    switch (ret) {
        case QMessageBox::Save:

        if(cm->getIdMax()!=0){
            QString filename_comptes = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du fichier COMPTES avec l'extension.xml");
            qDebug()<<filename_comptes;
            writeXmlFile_attributes(filename_comptes);

            if(tm->begin()!=tm->end()){
                QString filename_transactions = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du fichier TRANSFERTS avec l'extension.xml");
                writeXmlFile_subnodes(filename_transactions);
            }

            else{

                QMessageBox::warning(this,"Warning","Pas des transactions dans le projet");

            }

            delete ui;
            delete cm;
            delete tm;
        }

        break;

        case QMessageBox::Discard:

        delete ui;
        delete cm;
        delete tm;

        break;

        case QMessageBox::Cancel:


        break;

         default:


        break;


    }

}


void MainWindow::on_actionNew_triggered()
{
    MainWindow* w = new MainWindow();
    w->show();
}

void MainWindow::on_actionAdd_account_triggered()
{
    if(!ui->treeWidget->selectedItems().empty()){
        QTreeWidgetItem* selectedItem = ui->treeWidget->selectedItems().at(0);
        QString id = selectedItem->text(1);
        QString type = selectedItem->text(4);

        if(selectedItem->text(3)=="Virtuel"||selectedItem->text(3).isEmpty()){           //only allows to add new account under a virtual account
            popAddWindow(id,type);
        }
        else{
            QMessageBox::warning(this,"Warning","Can not create accounts based on real account!");
        }
    }
    else{
        QMessageBox::warning(this,"Missing account","Please select a virtual account first!");
    }
}

void MainWindow::on_actionOpen_triggered()
{
    cm = new CompteManager;
    tm = new TransactionManager;

    int ret;

    if(cm->getIdMax()!=0){
        QMessageBox msgBox;
        msgBox.setText("Le document a été modifié.");
        msgBox.setInformativeText("Voulez-vous enregistrer les changements ?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
    }
    else{
        ret = QMessageBox::Discard;
    }

    switch (ret) {
    case QMessageBox::Save:

        if(cm->getIdMax()!=0){
            QString filename_comptes = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du fichier COMPTES avec l'extension.xml");
            qDebug()<<filename_comptes;
            writeXmlFile_attributes(filename_comptes);

            if(tm->begin()!=tm->end()){
                QString filename_transactions = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du fichier TRANSFERTS avec l'extension.xml");
                writeXmlFile_subnodes(filename_transactions);
            }

            else{

                QMessageBox::warning(this,"Warning","Pas des transactions dans le projet");

            }
        }

        cm = new CompteManager;
        filename = QFileDialog::getOpenFileName(this,"Open the file COMPTES.xml","./",tr("XML(*.xml);;  All files (*.*)"));

        if(!filename.isEmpty())
        {
            openXML( filename,true );
        }
        filename = QFileDialog::getOpenFileName(this,"Open the file TRANSACTIONS.xml","./",tr("XML(*.xml);;  All files (*.*)"));

        if(!filename.isEmpty())
        {
            openXMLTransactions(filename,true );
        }

        cm->Afficher();
        tm->afficher();

        break;
    case QMessageBox::Discard:

        cm = new CompteManager;
        filename = QFileDialog::getOpenFileName(this,"Open the file COMPTES.xml","./",tr("XML(*.xml);;  All files (*.*)"));

        if(!filename.isEmpty())
        {
            openXML( filename,true );
        }
        filename = QFileDialog::getOpenFileName(this,"Open the file TRANSACTIONS.xml","./",tr("XML(*.xml);;  All files (*.*)"));

        if(!filename.isEmpty())
        {
            openXMLTransactions(filename,true );
        }

        cm->Afficher();
        tm->afficher();

        break;
    case QMessageBox::Cancel:
        qDebug()<<"Cancel";
        break;
    default:
        // ne doit pas se produire
        break;
    }

}



void MainWindow::on_actionDelete_Account_triggered()
{
    qDebug()<<"clicked!!!";
    if(!ui->treeWidget->selectedItems().empty()){
        QTreeWidgetItem* selected = ui->treeWidget->selectedItems().at(0);
        QString id = selected->text(1);
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("QMessageBox::question()"),"Are you sure to delete this account?",QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes){
            qDebug()<<"delete accepted!!";
            if(!cm->supprimer_compte(id.toInt())){
                QMessageBox::critical(this,"Can't delete account","This account has a transaction!");
                return;
            }

            cm->Afficher();
            writeXmlFile_attributes(compte_tmp);
            openXML(compte_tmp,false);
        }
        else if (reply == QMessageBox::No){
            qDebug()<<"no";
        }
        else{
            qDebug()<<"else";
        }
    }
    else{
        QMessageBox::warning(this,"Missing account","Please select a account which you want to delete!");
    }
}

void MainWindow::handlePassifAccepted(QString passif_id){
    qDebug()<<"handlePassifAccepted";

    bool vir = (AddWindow->getProp()=="Virtuel") ? true : false;
    int parent = AddWindow->getFatherId().toInt();
    std::string nomString = AddWindow->getNom().toLocal8Bit().constData();
    std::string typeString = AddWindow->getType().toLocal8Bit().constData();

    if(!cm->creer_compte(parent, nomString, typeString, vir)){
        qDebug()<<"erreur when adding account: "<<QString::fromStdString(nomString);
    }
    QDate current = QDate::currentDate();
    Transaction* t = tm->creerTransaction(current.year(),current.month(),current.day(),"I"+std::to_string(tm->getidmax()),"Solde initial");

    if(create_actif){
        qDebug()<<"handlePassifAccepted2";
        montant_initial = AddWindow->getSolde().toDouble();
        t->add(0,montant_initial,cm->GetCompte(passif_id.toInt()));
        t->add(montant_initial,0,cm->GetCompte(cm->getIdMax()));
    }else{
        t->add(montant_initial,0,cm->GetCompte(passif_id.toInt()));
        t->add(0,montant_initial,cm->GetCompte(cm->getIdMax()));
    }
    tm->ajouter_transaction(t);
    cm->Afficher();
    writeXmlFile_attributes(compte_tmp);
    openXML(compte_tmp,false);

    qDebug()<<"compte passif id is:"<<passif_id;
}

void MainWindow::openXML(QString fileName,bool first_load)
{
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        qDebug()<<"file opened";
        QDomDocument dom("Comptes");
        if (dom.setContent(&file))      //成功读取文件
        {
            qDebug()<<"file loaded";
            ui->treeWidget->clear();
            QDomElement docElem = dom.documentElement();
            listDom(docElem,first_load);
        }
        else{
            qDebug()<<"can't load file! Maybe there is a syntax error in the xml files";
        }
    }
    else{
        qDebug()<<"Can't open file!";
    }
    file.close();
}

void MainWindow::openXMLTransactions(QString fileName, bool first_load){

    qDebug()<<"Ouverture de fichier Transactions";

    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {

        qDebug()<<"File Transactions Open";

        QDomDocument dom("Transactions");

        if(dom.setContent(&file)){

            QDomElement docElem = dom.documentElement();
            QDomNodeList transactions = docElem.elementsByTagName("Transaction");

            for(int i = 0;i < transactions.count();i++){

                QDomElement element = transactions.at(i).toElement();
                if( !element.isNull() ){

                    QTreeWidgetItem *item;
                    item = new QTreeWidgetItem();

                    QString intitule = element.attribute("Intitule");
                    QString reference = element.attribute("Reference");
                    QString day = element.attribute("Day");
                    QString month = element.attribute("Month");
                    QString year = element.attribute("Year");

                    Transaction* trans = tm->creerTransaction(year.toInt(), month.toInt(), day.toInt(), reference.toStdString(), intitule.toStdString());
                    qDebug()<<trans->getDate();
                    QDomNodeList operations = docElem.elementsByTagName("Operation");

                    for(int i = 0;i < operations.count();i++){
                        QDomElement element2 = operations.at(i).toElement();
                        QTreeWidgetItem *item;
                        item = new QTreeWidgetItem();

                        QString compte = element2.attribute("Compte");
                        QString debit = element2.attribute("Debit");
                        QString credit = element2.attribute("Credit");
                        QString reference_compte = element2.attribute("Reference");

                        qDebug()<<"Compte: "<< compte.toInt() << "debit: "<< debit.toDouble() << "credit: "<< credit.toDouble();

                        if (reference.compare(reference_compte)==0)
                            trans->add(debit.toDouble(), credit.toDouble(), cm->GetCompte(compte.toInt()));

                    }

                    tm->ajouter_transaction2(trans);

                }

            }

        }

        else{

            qDebug()<<"can't load file! Maybe there is a syntax error in the xml files";
        }

    }

    else{


        qDebug()<<"Can't open the file";
    }



}

void MainWindow::listDom(QDomElement& docElem, bool first_time)
{
    QDomNodeList comptes = docElem.elementsByTagName("compte");
    for(int i = 0;i < comptes.count();i++){
        QDomElement element = comptes.at(i).toElement();
        if( !element.isNull() ){
            QTreeWidgetItem *item;
            item = new QTreeWidgetItem();
            QString nom = element.attribute("nom");
            QString id = element.attribute("id");
            QString prop = element.attribute("prop");
            QString type = element.attribute("type");

            QString solde = element.attribute("solde");
            QString parent = element.attribute("parent");


            if(parent==NULL){
                item = new QTreeWidgetItem(ui->treeWidget);
                item->setText(0,nom);
                item->setText(1,id);
                ui->treeWidget->addTopLevelItem(item);
            }
            else{
                addToTree(parent, id,nom, prop,type, solde);

                if(first_time){
                    //Connection avec code de Séb
                    bool vir = (prop.compare("Virtuel")) ? false : true;

                    std::string nomString = nom.toLocal8Bit().constData();
                    std::string typeString = type.toLocal8Bit().constData();
                    if(!cm->creer_compte(parent.toInt(), nomString, typeString, vir)){
                        qDebug()<<"erreur when loading account: "<<QString::fromStdString(nomString);
                    }

                    if(!vir){

                        if(QString::compare(type, "Actif", Qt::CaseInsensitive) == 0 || QString::compare(type, "Depense", Qt::CaseInsensitive) == 0 )
                            cm->GetCompte(id.toInt())->debiter(solde.toDouble());

                        else
                            cm->GetCompte(id.toInt())->crediter(solde.toDouble());
                    }
                }
            }
        }
    }
}


void MainWindow::popAddWindow(QString f_id, QString type){

    /*--------------------------------------------------------------------------
      ouvrir une nouvelle fenetre pour saisir les parametres du compte a ajouter
    -----------------------------------------------------------------------------*/

    AddWindow = new AddCompteDialog(this);


    connect(AddWindow,SIGNAL(finished(int)),this,SLOT(addWindow_finished(int)));

    qDebug()<<type;
    if(no_passif){
        AddWindow->getUi()->comboBox->setCurrentIndex(1);
        AddWindow->getUi()->comboBox->setDisabled(true);
        AddWindow->getUi()->comboBox2->setCurrentIndex(1);
        AddWindow->getUi()->comboBox2->setDisabled(true);
        AddWindow->getUi()->lineEditB->setDisabled(true);
    }
    else{
        if(type!=NULL){
            for(int i = 0; i< AddWindow->getUi()->comboBox2->count();i++){
                AddWindow->getUi()->comboBox2->setDisabled(true);
            }
        }
        if(type=="Actif"){
            AddWindow->getUi()->comboBox2->setCurrentIndex(0);
        }
        else if(type=="Passif"){
            AddWindow->getUi()->comboBox2->setCurrentIndex(1);
            AddWindow->getUi()->lineEditB->setDisabled(true);
        }
        else if(type=="Depense"){
            AddWindow->getUi()->comboBox2->setCurrentIndex(2);
            AddWindow->getUi()->lineEditB->setDisabled(true);
        }
        else if(type=="Recette"){
            AddWindow->getUi()->comboBox2->setCurrentIndex(3);
            AddWindow->getUi()->lineEditB->setDisabled(true);
        }
    }

    AddWindow->setFatherId(f_id);

    if(AddWindow->exec() == QDialog::Accepted){
        Add_accepted();
    }
}

void MainWindow::popRapprochementWindow(QString id){

    rapWindow = new Rapprochementdialog(this);
    CompteAbstrait* compte = cm->GetCompte(id.toInt());


    if(rapWindow->exec()==QDialog::Accepted){

        rapWindow->getUi()->dateEdit->setDate( QDate::currentDate());
        int year = rapWindow->getUi()->dateEdit->date().year();
        int month = rapWindow->getUi()->dateEdit->date().month();
        int day = rapWindow->getUi()->dateEdit->date().day();


        QString desc = rapWindow->getUi()->lineEdit->text();
        QString nom = rapWindow->getUi()->lineEdit_2->text();

        compte->rapprocher(year, month, day, nom.toStdString(), desc.toStdString());

        QMessageBox::warning(this, "Rapprochement", "Rapprochement crée");

    }


}

void MainWindow::popSaisirRapprochement(QString id){

    saiRapWin = new SaisirRapprochementDialog(this);
    QString item;

    Compte* tmp = dynamic_cast<Compte*>(cm->GetCompte(id.toInt()));
    QMultiMap<QDate, Rapprochement*>::iterator it_begin = tmp->getListRapprochement().begin();
    QMultiMap<QDate, Rapprochement*>::iterator it_end = tmp->getListRapprochement().end();

    for(QMultiMap<QDate, Rapprochement*>::iterator it = it_begin; it!=it_end; it++){

        item = (*it)->getDate().toString();
        qDebug()<<item;
        saiRapWin->getUi()->comboBox->addItem(item);

    }

    if(saiRapWin->exec()==QDialog::Accepted){

            QVariant item = saiRapWin->getUi()->comboBox->itemData(saiRapWin->getUi()->comboBox->currentIndex());
            qDebug()<<item.toString(); //Ici j'ai recupere l'item du comboBox

            //Appel à la fonction génerer pdf d'un rapprochement


        }





}


void MainWindow::Add_accepted(){
    if(AddWindow->getUi()->comboBox->currentIndex()==0){
        AddWindow->setProp("Virtuel");

    }
    else if(AddWindow->getUi()->comboBox->currentIndex()==1){
        AddWindow->setProp("Reel");
    }

    AddWindow->setType(AddWindow->getUi()->comboBox2->currentText());
    AddWindow->setNom(AddWindow->getUi()->lineEditA->text());
    AddWindow->setSolde(AddWindow->getUi()->lineEditB->text().toDouble());

    qDebug()<<"Type:"<<AddWindow->getType();

    //will be the second time here
    if(no_passif){
        //add two accounts and transferts
        std::string nom_passif = AddWindow->getNom().toLocal8Bit().constData();
        std::string type_passif = AddWindow->getUi()->comboBox2->currentText().toLocal8Bit().constData();

        QList<QTreeWidgetItem*> clist = ui->treeWidget->findItems("Passif", Qt::MatchExactly|Qt::MatchRecursive, 0);

        if(!cm->creer_compte(0, nom_passif, type_passif, false)){
            qDebug()<<"erreur when adding passif: "<<QString::fromStdString(nom_passif);
        }

        int id_father_actif = getId_first().toInt();
        std::string nom_actif = getNom_first().toLocal8Bit().constData();
        qDebug()<<"nom_first::"<<getNom_first();

        qDebug()<<"id_father:"<<id_father_actif;
        if(!cm->creer_compte(id_father_actif,nom_actif,"Actif",false)){
            qDebug()<<"erreur when adding active: "<<QString::fromStdString(nom_actif);
        }

        QDate current = QDate::currentDate();
        Transaction* t = tm->creerTransaction(current.year(),current.month(),current.day(),"I"+std::to_string(count_compte++),"Solde initial");

        montant_initial = getSolde_first().toDouble();
        qDebug()<<montant_initial;

        t->add(0,montant_initial,cm->GetCompte(cm->getIdMax()-1));
        t->add(montant_initial,0,cm->GetCompte(cm->getIdMax()));

        qDebug()<<"here3";

        tm->ajouter_transaction(t);

        writeXmlFile_attributes(compte_tmp);

        openXML(compte_tmp,false);
        no_passif = false;
    }
    else{
        //Si il veut creer un compte reel actif
        if(AddWindow->getType()=="Actif"&&AddWindow->getProp()=="Reel"){
            create_actif = true;
            PopChoisirPassifWindow();

        }
        //Si il veut creer un compte reel passif avec montant initial
        else if(AddWindow->getProp()=="Reel"&&AddWindow->getType()=="Passif"&&AddWindow->getUi()->lineEditB->text()!=NULL){
            qDebug()<<AddWindow->getUi()->lineEditB;
            create_actif = false;
            PopChoisirPassifWindow();
        }
        else{
            bool vir = (AddWindow->getProp()=="Virtuel") ? true : false;
            int parent_id = AddWindow->getFatherId().toInt();
            std::string nomString = AddWindow->getNom().toLocal8Bit().constData();
            std::string typeString = AddWindow->getUi()->comboBox2->currentText().toLocal8Bit().constData();

            cm->creer_compte(parent_id, nomString, typeString, vir);
            AddWindow->setId(QString::number(cm->getIdMax()));


            addToTree(AddWindow->getFatherId(),AddWindow->getId(),AddWindow->getNom(),AddWindow->getProp(),AddWindow->getType(),AddWindow->getSolde());    //add new account to QTreeWidget
            cm->Afficher();
        }
    }
}



void MainWindow::addToTree(QString father_id, QString id, QString nom, QString prop, QString type, QString solde){

    QList<QTreeWidgetItem*> clist = ui->treeWidget->findItems(father_id, Qt::MatchExactly|Qt::MatchRecursive, 1);
    qDebug()<<clist.count();
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,nom);
    item->setText(1,id);
    if(prop=="Reel"){item->setText(2,solde);}
    item->setText(3,prop);
    item->setText(4,type);

    clist[0]->addChild(item);
}

void MainWindow::deleteXML(QString id) const{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)){
        qDebug()<<"can't open!";
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        qDebug()<<"can't read file!";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList node;


    node = doc.elementsByTagName("compte");
    for(int i=0;i<node.count();i++){
        if(node.at(i).toElement().attribute("id")==id){
            qDebug()<<"node:"<<node.at(i).toElement().attribute("id");
            node.at(i).parentNode().removeChild(node.at(i));
        }
    }

    if(!file.open(QFile::WriteOnly|QFile::Truncate)){
        qDebug()<<"can't open file";
        return;
    }
    //out to the file
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //indent 4 cases
    file.close();
}

void MainWindow::deleteFromTree(const QString id){
    QList<QTreeWidgetItem*> clist = ui->treeWidget->findItems(id, Qt::MatchExactly|Qt::MatchRecursive, 1);
    delete clist.constFirst();
}

void MainWindow::PopChoisirPassifWindow(){
    ChoisirPassifWindow = new ChoisirPassifDialog(this);
    connect(ChoisirPassifWindow,SIGNAL(accepted(QString)),this,SLOT(handlePassifAccepted(QString)));

    QList<QTreeWidgetItem*> clist = ui->treeWidget->findItems("Passif", Qt::MatchExactly|Qt::MatchRecursive, 4);

    QStandardItemModel *model = new QStandardItemModel(this);

    int Nbrow = 0;
    for (auto item : clist){
        if(item->text(3)=="Reel"){
            QStandardItem* colID = new QStandardItem(item->text(1));
            QStandardItem* colNom = new QStandardItem(item->text(0));
            model->setItem(Nbrow, 0, colID);
            model->setItem(Nbrow, 1, colNom);
            Nbrow++;
        }
    }

    QTreeView* treeView = new QTreeView(this);
    ChoisirPassifWindow->getUi()->comboBox->setModel(model);
    ChoisirPassifWindow->getUi()->comboBox->setView(treeView);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView->setColumnWidth ( 0, 50 );
    treeView->setAllColumnsShowFocus(true);
    treeView->setRootIsDecorated(false);
    treeView->setAutoScroll(false);
    treeView->header()->hide();

    if(ChoisirPassifWindow->getUi()->comboBox->count()==0){
        QMessageBox::warning(this,"Warning","Pas de compte passif encore, veuillez creer un");
        //        create_actif = false;
        no_passif = true;
        setNom_first(AddWindow->getUi()->lineEditA->text());
        qDebug()<<"nom first:"<<getNom_first();
        setSolde_first(AddWindow->getUi()->lineEditB->text().toDouble());
        setId_first(AddWindow->getFatherId());
        popAddWindow(0,"Passif");
    }
    else{
        no_passif = false;
        ChoisirPassifWindow->exec();
    }
}

void MainWindow::on_actionSave_as_triggered(){

    if(cm->getIdMax()!=0){
        QString filename_comptes = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du fichier COMPTES avec l'extension.xml");
        qDebug()<<filename_comptes;
        writeXmlFile_attributes(filename_comptes);

        if(tm->begin()!=tm->end()){
            QString filename_transactions = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du fichier TRANSFERTS avec l'extension.xml");
            writeXmlFile_subnodes(filename_transactions);
        }

        else{

            QMessageBox::warning(this,"Warning","Pas des transactions dans le projet");

        }
    }
}

void MainWindow::on_actionAdd_Transation_triggered()
{

    qDebug()<<"Here";
    //s'il y a pas de compte dans le treewidget encore -> warning

    if(ui->treeWidget->itemAt(0,0)==NULL){
        QMessageBox::warning(this,"Warning","Pas de compte passif encore, veuillez creer un");
    }
    else{
        AddTransfertWindow = new AddTransfertDialog(ui->treeWidget->topLevelItem(0)->clone(),this);
        AddTransfertWindow->setWindowTitle("Add a Transfert");
        //connect(AddTransfertWindow->getUi()->pushButton_2,SIGNAL(released()),this,SLOT(delCompte()));


        if(AddTransfertWindow->exec()==QDialog::Accepted){
            //add a transation


            qDebug()<<"QDialog::Accepted";
            int year = AddTransfertWindow->getUi()->dateEdit->date().year();
            int month = AddTransfertWindow->getUi()->dateEdit->date().month();
            int day = AddTransfertWindow->getUi()->dateEdit->date().day();
            const std::string title = AddTransfertWindow->getUi()->lineEdit->text().toStdString();
            const std::string ref = AddTransfertWindow->getUi()->lineEdit_2->text().toStdString();

            if(tm->verifierReference(ref)){

                Transaction* tran = tm->creerTransaction(year,month,day,ref,title);

                std::vector<Transfert> Tvector = AddTransfertWindow->getTransfertVector();

                for (unsigned int i=0;i<Tvector.size();i++){

                    tran->add(Tvector[i].debit,Tvector[i].credit,cm->GetCompte(Tvector[i].id));
                }
                tm->ajouter_transaction(tran);

                //            writeXmlFile_subnodes("transferts_temp.xml");
                writeXmlFile_attributes(compte_tmp);
                openXML(compte_tmp,false );

            }

            else{

                QMessageBox::warning(this,"Warning","Référence répétée");


            }


        }
    }

    if(tm->getidmax()!=0)
        tm->afficher();

    if(cm->getIdMax()!=0)
        cm->Afficher();


}

void MainWindow::writeXmlFile_attributes(const QString& filename)
{
    /*----------------------------------------------------------
     * Création de l'élément document et du tag principal 'Comptes' qui va
     * regrouper les différents comptes à exporter
     *----------------------------------------------------------*/
    QDomDocument doc;
    QDomElement root = doc.createElement("Comptes");
    doc.appendChild(root);

    // on va itérer sur tous les comptes à exporter
    QDomElement cptElement = doc.createElement("compte");

    cptElement.setAttribute("nom", "Compte Racine");
    cptElement.setAttribute("id", "0");
    cptElement.setAttribute("prop", "Virtuel");

    root.appendChild(cptElement);

    if(cm->getIdMax()>=1){
        for (unsigned int i = 1; i <= cm->getIdMax(); i++)
        {


            CompteAbstrait* cpt = cm->GetCompte(i);
            if(cpt==nullptr){
                continue;
            }

            Compte* cpt_reel = dynamic_cast<Compte*>(cpt);

            // on crée un élément global pour le compte : le nom donné ici à
            // l'élément correspond au nom du tag dans la balise
            QDomElement cptElement = doc.createElement("compte");


            // on ajoute simplement les attributs sur l'élément avec la méthode
            // setAttribute
            // on remarquera que l'ordre d'ajout des attributs n'est pas
            // nécessairement le même que l'ordre des lignes qui suivent


            cptElement.setAttribute("nom", QString::fromStdString(cpt->getNom().c_str()));

            cptElement.setAttribute("id", QString::number(cpt->GetId()));



            if(dynamic_cast<CompteVirtuel*>(cpt)){

                cptElement.setAttribute("prop", "Virtuel");

            }

            else{

                cptElement.setAttribute("prop", "Reel");
                cptElement.setAttribute("solde", QString::number(cpt_reel->getSolde()));
            }

            cptElement.setAttribute("parent", QString::number(cpt->getPere()->GetId()));

            cptElement.setAttribute("type", QString::fromStdString(cpt->getType()));


            // on ajoute le compte à l'élément principal


            root.appendChild(cptElement);

        }

    }

    qDebug()<<"fin de lecture";

    // ouverture du fichier en écriture
    QFile outfile(filename);

    if (!outfile.open(QIODevice::WriteOnly)){

        qDebug()<<"file error";
        return;
    }

    // création d'un flux pour gérer la sortie
    QTextStream stream(&outfile);

    // export du document
    stream << doc.toString();

    // fermeture du fichier
    outfile.close();
}

void MainWindow::writeXmlFile_subnodes(const QString& filename)
{
    /*----------------------------------------------------------
     * Création de l'élément document et du tag principal 'Comptes' qui va
     * regrouper les différents comptes à exporter
     *----------------------------------------------------------*/
    QDomDocument doc;
    QDomElement root = doc.createElement("Transactions");
    doc.appendChild(root);

    // on va itérer sur tous les comptes à exporter
    for (auto it_trans = tm->begin(); it_trans!= tm->end(); ++it_trans)
    {
        Transaction* trans = it_trans.value();

        // on crée un élément global pour le compte : le nom donné ici à
        // l'élément correspond au nom du tag dans la balise
        QDomElement transElement = doc.createElement("Transaction");
        transElement.setAttribute("Intitule", QString::fromStdString(trans->getMemo()));
        transElement.setAttribute("Reference", QString::fromStdString(trans->getReference()));
        transElement.setAttribute("Year", QString::number(trans->getDate().year()));
        transElement.setAttribute("Month", QString::number(trans->getDate().month()));
        transElement.setAttribute("Day", QString::number(trans->getDate().day()));

        for(auto it_operations=trans->begin(); it_operations!=trans->end(); ++it_operations){

            QDomElement opeElem = doc.createElement("Operation");
            opeElem.setAttribute("Compte", QString::number(((*it_operations)->getCompte().GetId())));
            opeElem.setAttribute("Debit", QString::number((*it_operations)->getDebit()));
            opeElem.setAttribute("Credit", QString::number((*it_operations)->getCredit()));
            opeElem.setAttribute("Reference", QString::fromStdString((*it_operations)->getTransaction().getReference()));

            if((*it_operations)->getRapprochement()!=nullptr)
            opeElem.setAttribute("Rapprochement", QString::number((*it_operations)->getRapprochement()->getId()));

            transElement.appendChild(opeElem);

        }


        // on ajoute le compte à l'élément principal
        root.appendChild(transElement);
    }

    // ouverture du fichier en écriture
    QFile outfile(filename);

    if (!outfile.open(QIODevice::WriteOnly))
        return;

    // création d'un flux pour gérer la sortie
    QTextStream stream(&outfile);

    // export du document
    stream << doc.toString();

    // fermeture du fichier
    outfile.close();
}


void MainWindow::on_actionShow_all_transation_triggered()
{
    tm->afficher();

    bool frozen;

    viewTransfertWindow = new ViewAllTransfert(ui->treeWidget->topLevelItem(0)->clone(),cm,tm,this);
    QTableWidget* table = viewTransfertWindow->getUi()->tableWidget;
    table->verticalHeader()->hide();
    table->setSelectionBehavior( QAbstractItemView::SelectItems );
    table->setSelectionMode( QAbstractItemView::SingleSelection );

    connect(viewTransfertWindow,SIGNAL(transaction_modified()),this,SLOT(refresh_transaction()));



    int nb_row = 0;
    for (int count = 0; count<tm->getidmax();count++){


        Transaction* t = tm->recherche_transaction(count);


        if(t==NULL){
            continue;
        }

        if(t->is_frozen()) frozen = true;
        else frozen = false;

        int nb_row_tmp = nb_row;
        bool startline = true;
        table->insertRow(nb_row);

        QString date = t->getDate().toString("dd/MM/yyyy");
        QString reference = QString::fromStdString(t->getReference());
        QString title = QString::fromStdString(t->getMemo());
        QTableWidgetItem* itemDate = new QTableWidgetItem(date);
        itemDate->setFlags(itemDate->flags() ^ Qt::ItemIsEditable);
        table->setItem(nb_row, 0, itemDate);
        QTableWidgetItem* itemRef = new QTableWidgetItem(reference);
        if(frozen)
            itemRef->setBackgroundColor(Qt::red);

        itemRef->setFlags(itemRef->flags() ^ Qt::ItemIsEditable);
        table->setItem(nb_row, 1, itemRef);
        QTableWidgetItem* itemTitre = new QTableWidgetItem(title);
        itemTitre->setFlags(itemTitre->flags() ^ Qt::ItemIsEditable);
        table->setItem(nb_row, 2, itemTitre);
        QString ID = QString::number(t->getId());
        qDebug()<<ID;
        QTableWidgetItem* itemID = new QTableWidgetItem(ID);
        itemID->setFlags(itemID->flags() ^ Qt::ItemIsEditable);
        table->setItem(nb_row, 6, itemID);


        for (auto it=t->begin();it!=t->end();it++){
            if(!startline){table->insertRow(nb_row);}
            qDebug()<<QString::fromStdString((*it)->getCompte().getNom());
            QTableWidgetItem* itemCompte = new QTableWidgetItem(QString::fromStdString((*it)->getCompte().getNom()));
            itemCompte->setFlags(itemCompte->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* itemDebit = new QTableWidgetItem(QString::number((*it)->getDebit()));
            itemDebit->setFlags(itemDebit->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem* itemCredit = new QTableWidgetItem(QString::number((*it)->getCredit()));
            itemCredit->setFlags(itemCredit->flags() ^ Qt::ItemIsEditable);
            table->setItem(nb_row, 3, itemCompte);
            table->setItem(nb_row, 4, itemDebit);
            table->setItem(nb_row, 5, itemCredit);
            startline=false;
            nb_row++;
        }
        qDebug()<<nb_row_tmp<<nb_row;
        table->setSpan(nb_row_tmp, 0, nb_row-nb_row_tmp, 1);
        table->setSpan(nb_row_tmp, 1, nb_row-nb_row_tmp, 1);
        table->setSpan(nb_row_tmp, 2, nb_row-nb_row_tmp, 1);


    }

    viewTransfertWindow->show();
}

void MainWindow::refresh_transaction(){

    writeXmlFile_attributes(compte_tmp);

    openXML(compte_tmp,false);
    viewTransfertWindow->close();
    on_actionShow_all_transation_triggered();
}

void MainWindow::on_actionFor_transferts_triggered()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du rapport des transactions en format .pdf");

    QFont _font;
    QPrinter::PageSize size = QPrinter::A4;

    ligne = 120;

    int date_x=100, ref_x=200, titre_x=300;


    int line_x1=100, line_x2=900, line_y1=0, line_y2=0;

    QPrinter printer;

    printer.setPaperSize(size);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    QPainter painter;


    if(!painter.begin(&printer)){
        qDebug()<<filename;
        qDebug()<<"Erreur d'ouverture de PDF!!!";
        return;
    }

    else {

        _font.setBold(true);
        _font.setFamily("Arial");
        painter.setFont(_font);
        painter.drawText(400,50, "RAPPORT DES TRANSACTIONS");

        _font.setFamily("Times New Roman");
        _font.setBold(false);
        painter.setFont(_font);

        print_header_transactios(painter);

        QLine line;
        QPoint P1;
        QPoint P2;

        P1.setX(line_x1);
        P2.setX(line_x2);

        for(auto it_trans = tm->begin(); it_trans!= tm->end(); ++it_trans){

            Transaction* trans =  it_trans.value();

            painter.drawText(date_x,ligne,(QString::number(trans->getDate().day())+"/"+QString::number(trans->getDate().month())+"/"+QString::number(trans->getDate().year()) ));
            painter.drawText(ref_x,ligne, QString::fromStdString(trans->getReference()));
            painter.drawText(titre_x,ligne, QString::fromStdString(trans->getMemo()));

            operations_PDF(printer, painter, trans);

            line_y1 = ligne - 18 ; line_y2 = ligne - 18;
            P1.setY(line_y1);
            P2.setY(line_y2);

            line.setP1(P1); line.setP2(P2);
            painter.drawLine(line);

        }

        painter.end();
    }

}

void MainWindow::print_header_transactios(QPainter& painter){

    int date_x=100, ref_x=200, titre_x=300, comptes_x= 500, debit_x=700, credit_x=800;
    int header=100;

    QRect rectangle_date(date_x-10, header-15, ref_x-date_x, 20);
    QRect rectangle_ref(ref_x-10, header-15, titre_x-ref_x, 20);
    QRect rectangle_titre(titre_x-10, header-15, comptes_x-titre_x, 20);
    QRect rectangle_comptes(comptes_x-10, header-15, debit_x-comptes_x, 20);
    QRect rectangle_debit(debit_x-10, header-15, credit_x-debit_x, 20);
    QRect rectangle_credit(credit_x-10, header-15, 900-credit_x, 20);

    painter.drawText(date_x,header, "DATE");
    painter.drawText(ref_x,header, "REFERENCE");
    painter.drawText(titre_x,header, "TITRE");
    painter.drawText(comptes_x,header, "COMPTES");
    painter.drawText(debit_x,header, "DEBIT");
    painter.drawText(credit_x,header, "CREDIT");

    painter.drawRect(rectangle_date);
    painter.drawRect(rectangle_ref);
    painter.drawRect(rectangle_titre);
    painter.drawRect(rectangle_comptes);
    painter.drawRect(rectangle_debit);
    painter.drawRect(rectangle_credit);


}


void MainWindow::operations_PDF(QPrinter& printer, QPainter& painter, Transaction* trans){

    int saute = 22;

    int comptes_x= 500, debit_x=700, credit_x=800;

    for(auto it_operations=trans->begin(); it_operations!=trans->end(); ++it_operations){

        painter.drawText(comptes_x,ligne, QString::fromStdString((*it_operations)->getCompte().getNom()));
        painter.drawText(debit_x,ligne, QString::number((*it_operations)->getDebit()));
        painter.drawText(credit_x,ligne, QString::number((*it_operations)->getCredit()));
        ligne += saute;

        if(ligne>=1242){

            printer.newPage();

            print_header_transactios(painter);

            ligne=120;

        }
    }
}

void MainWindow::operations_PDF(QPrinter& printer, QPainter& painter, Transaction* trans, std::string id){

    int saute = 22;

    int date_x=100, ref_x=200, titre_x=300, comptes_x= 500, debit_x=700, credit_x=800;
    int header=100;

    QRect rectangle_date(date_x-10, header-15, ref_x-date_x, 20);
    QRect rectangle_ref(ref_x-10, header-15, titre_x-ref_x, 20);
    QRect rectangle_titre(titre_x-10, header-15, comptes_x-titre_x, 20);
    QRect rectangle_comptes(comptes_x-10, header-15, debit_x-comptes_x, 20);
    QRect rectangle_debit(debit_x-10, header-15, credit_x-debit_x, 20);
    QRect rectangle_credit(credit_x-10, header-15, 900-credit_x, 20);

    for(auto it_operations=trans->begin(); it_operations!=trans->end(); ++it_operations){

        if(std::to_string((*it_operations)->getCompte().GetId()) == id){

            painter.drawText(comptes_x,ligne, QString::fromStdString((*it_operations)->getCompte().getNom()));
            painter.drawText(debit_x,ligne, QString::number((*it_operations)->getDebit()));
            painter.drawText(credit_x,ligne, QString::number((*it_operations)->getCredit()));
            ligne += saute;

            if(ligne>=1242){

                printer.newPage();

                print_header_transactios(painter);

                ligne=120;

            }

        }
    }

}


void MainWindow::on_actionTransferts_for_one_account_triggered()
{
    if(ui->treeWidget->selectedItems().empty()){
        QMessageBox::warning(this,"Missing account","Please select a account to generate PDF!");
        return;
    }


    QTreeWidgetItem* selected = ui->treeWidget->selectedItems().at(0);
    QString id = selected->text(1);
    qDebug()<<"selected account id:"<<id;
    if(selected->text(3)=="Virtuel"||selected->text(3)==""){
        QMessageBox::warning(this,"Warning","To generate PDF, please choose a real account");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du rapport des transactions en format .pdf");

    QFont _font;
    QPrinter::PageSize size = QPrinter::A4;


    ligne = 120;

    int date_x=100, ref_x=200, titre_x=300;


    int line_x1=100, line_x2=900, line_y1=0, line_y2=0;

    QPrinter printer;

    printer.setPaperSize(size);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    printer.setOrientation(QPrinter::Portrait);

    QPainter painter;


    if(!painter.begin(&printer)){
        qDebug()<<filename;
        qDebug()<<"Erreur d'ouverture de PDF!!!";
        return;
    }

    else {

        _font.setBold(true);
        _font.setFamily("Arial");
        painter.setFont(_font);
        painter.drawText(400,50, "RAPPORT DES TRANSACTIONS");

        _font.setFamily("Times New Roman");
        _font.setBold(false);
        painter.setFont(_font);

        print_header_transactios(painter);

        QLine line;
        QPoint P1;
        QPoint P2;

        P1.setX(line_x1);
        P2.setX(line_x2);

        for(auto it_trans = tm->begin(); it_trans!= tm->end(); ++it_trans){

            Transaction* trans =  it_trans.value();

            painter.drawText(date_x,ligne,(QString::number(trans->getDate().day())+"/"+QString::number(trans->getDate().month())+"/"+QString::number(trans->getDate().year()) ));
            painter.drawText(ref_x,ligne, QString::fromStdString(trans->getReference()));
            painter.drawText(titre_x,ligne, QString::fromStdString(trans->getMemo()));

            operations_PDF(printer, painter, trans, id.toLocal8Bit().constData());

            line_y1 = ligne - 18 ; line_y2 = ligne - 18;
            P1.setY(line_y1);
            P2.setY(line_y2);

            line.setP1(P1); line.setP2(P2);
            painter.drawLine(line);

        }

        painter.end();
    }
}

void MainWindow::addWindow_finished(int result){
    qDebug()<<"result :"<<result;
    //si on clicke sur "Cancel" ou ferme la fenetre
    if(result == 0){
        no_passif = false;
    }
}

bool MainWindow::cloture(){

    int year = QDate::currentDate().year();
    int month = QDate::currentDate().month();
    int day = QDate::currentDate().day();

    cm->creer_compte(0, "Resultat", "Passif", false);

    double creditResultat = 0;
    double debitResultat = 0;

    QVector<CompteAbstrait*> Recettes;
    QVector<CompteAbstrait*> Depenses;

    CompteAbstrait* tmp;

    for(unsigned int i= 1; i<cm->getIdMax(); i++){

        tmp = cm->GetCompte(i);

        if(dynamic_cast<Recette*>(tmp)){

            if(tmp->getSolde()!=0){
                Recettes.push_back(tmp);
                creditResultat += tmp->getSolde();
            }

        }


        if(dynamic_cast<Depense*>(tmp)){

            if(tmp->getSolde()!=0){
                Depenses.push_back(tmp);
                debitResultat += tmp->getSolde();
            }

        }

    }

    qDebug()<<"Somme credit: "<<creditResultat<<" Somme Debit: "<< debitResultat;
    qDebug()<<"size debit: "<<Depenses.size()<<" Size recettes: "<< Recettes.size();


    if((Depenses.size()==0 && Recettes.size() ==0) || (creditResultat == 0 && debitResultat ==0)) return false;

    Transaction* trans_recettes = tm->creerTransaction(year,month,day,"CL2020R", "Cloture 2020");
    Transaction* trans_depenses = tm->creerTransaction(year, month, day,"CL2020D", "Cloture 2020");
    Transaction* trans_final = tm->creerTransaction(year, month, day,"CONS2020", "Cloture 2020");


    if(Recettes.size()>0){

        trans_recettes->add(0,creditResultat, cm->GetCompte(cm->getIdMax()));

        for(QVector<CompteAbstrait*>::iterator it = Recettes.begin(); it != Recettes.end(); ++it){

            trans_recettes->add((*it)->getSolde(), 0, (*it));

        }

        tm->ajouter_transaction(trans_recettes);

    }

    if(Depenses.size()>0){

        trans_depenses->add(debitResultat, 0, cm->GetCompte(cm->getIdMax()));

        for(QVector<CompteAbstrait*>::iterator it = Depenses.begin(); it != Depenses.end(); ++it){

            trans_depenses->add(0, (*it)->getSolde() ,(*it));

        }

        tm->ajouter_transaction(trans_depenses);

    }

    if(creditResultat > debitResultat){

        cm->creer_compte(0, "Excedent", "Passif", false);
        tmp = cm->GetCompte(cm->getIdMax()-1);
        trans_final->add(tmp->getSolde(),0,tmp);
        trans_final->add(0, tmp->getSolde(), cm->GetCompte(cm->getIdMax()));
        tm->ajouter_transaction(trans_final);

    }

    else if(creditResultat < debitResultat){

        cm->creer_compte(0, "Deficit", "Passif", false);
        tmp = cm->GetCompte(cm->getIdMax()-1);
        trans_final->add(0, tmp->getSolde() ,tmp);
        trans_final->add(tmp->getSolde(), 0 , cm->GetCompte(cm->getIdMax()));
        tm->ajouter_transaction(trans_final);

    }

    return true;

}


void MainWindow::on_actionClosure_triggered(){

    if(cloture()){
        writeXmlFile_attributes(compte_tmp);
        openXML(compte_tmp,false);
        QMessageBox::warning(this,"Cloture","Clôture fait");
    }

    else{

        QMessageBox::warning(this,"Warning","On ne peut pas faire la clôture!");

    }

}

void MainWindow::on_actionRapprochement_triggered(){



    if(!ui->treeWidget->selectedItems().empty()){

        QTreeWidgetItem* selectedItem = ui->treeWidget->selectedItems().at(0);
        QString id = selectedItem->text(1);

        if(selectedItem->text(3)=="Reel"||selectedItem->text(3).isEmpty()){           //only allows to add new account under a virtual account
            popRapprochementWindow(id);

        }
        else{
            QMessageBox::warning(this,"Warning","Can not create accounts based on Virtual account!");
        }

    }

    else{

        QMessageBox::warning(this,"Warning","Tu dois sélectionner une compte réel");

    }



}





void MainWindow::on_actionTransferts_par_Rapprochement_triggered()
{

    if(!ui->treeWidget->selectedItems().empty()){

        QTreeWidgetItem* selectedItem = ui->treeWidget->selectedItems().at(0);
        QString id = selectedItem->text(1);

        if(selectedItem->text(3)=="Reel"||selectedItem->text(3).isEmpty()){           //only allows to add new account under a virtual account

            if(dynamic_cast<Compte*> (cm->GetCompte(id.toInt()))->getListRapprochement().size() != 0)
            popSaisirRapprochement(id);

            else

                QMessageBox::warning(this,"Warning","Ce compte n'a pas des rapprochements!");

        }
        else{
            QMessageBox::warning(this,"Warning","Can not create accounts based on Virtual account!");
        }

    }

    else{

        QMessageBox::warning(this,"Warning","Tu dois sélectionner une compte réel");

    }




}

void MainWindow::rapprochement_PDF(Rapprochement* rap){

    QString filename = QFileDialog::getSaveFileName(nullptr, "Entrez le nom du rapport des transactions en format .pdf");

    QFont _font;
    QPrinter::PageSize size = QPrinter::A4;

    ligne = 120;

    int saute = 22;
    int date_x=70, ref_x=170, titre_x=270, comptes_x= 470, debit_x=670, credit_x=770, solde_x = 820;
    int line_x1=70, line_x2=900, line_y1=0, line_y2=0;

    QPrinter printer;

    printer.setPaperSize(size);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    printer.setOrientation(QPrinter::Portrait);

    QPainter painter;


    if(!painter.begin(&printer)){
        qDebug()<<filename;
        qDebug()<<"Erreur d'ouverture de PDF!!!";
        return;
    }

    else {

        _font.setBold(true);
        _font.setFamily("Arial");
        painter.setFont(_font);
        painter.drawText(50,50, "RAPPORT DES TRANSACTIONS"+ QString::fromStdString(rap->getNom()) + " " + QString::fromStdString(rap->getDesc()));

        _font.setFamily("Times New Roman");
        _font.setBold(false);
        painter.setFont(_font);

        print_header_rapprochement(painter);

        QLine line;
        QPoint P1;
        QPoint P2;

        P1.setX(line_x1);
        P2.setX(line_x2);

        for(auto it_operations = rap->getCompte()->begin(); it_operations != rap->getCompte()->end(); ++it_operations){

            if((*it_operations)->getRapprochement()==rap){

                painter.drawText(date_x,ligne, QString::number((*it_operations)->getTransaction().getDate().day()) + "/" +QString::number((*it_operations)->getTransaction().getDate().month()) + "/" + QString::number((*it_operations)->getTransaction().getDate().year()));
                painter.drawText(ref_x,ligne, QString::fromStdString((*it_operations)->getTransaction().getReference()));
                painter.drawText(titre_x,ligne, QString::fromStdString((*it_operations)->getTransaction().getMemo()));
                painter.drawText(comptes_x,ligne, QString::fromStdString((*it_operations)->getCompte().getNom()));
                painter.drawText(debit_x,ligne, QString::number((*it_operations)->getDebit()));
                painter.drawText(credit_x,ligne, QString::number((*it_operations)->getCredit()));
                painter.drawText(solde_x, ligne, QString::number((*it_operations)->getRapprochement()->getSolde()));
                ligne += saute;

                if(ligne>=1242){

                    printer.newPage();

                    print_header_transactios(painter);

                    ligne=120;

                }

                line_y1 = ligne - 18 ; line_y2 = ligne - 18;
                P1.setY(line_y1);
                P2.setY(line_y2);

                line.setP1(P1); line.setP2(P2);
                painter.drawLine(line);
            }

    }



}

}

void MainWindow::print_header_rapprochement(QPainter& painter){


    int date_x=70, ref_x=170, titre_x=270, comptes_x= 470, debit_x=670, credit_x=770, solde_x = 820;
    int header=100;

    QRect rectangle_date(date_x-10, header-15, ref_x-date_x, 20);
    QRect rectangle_ref(ref_x-10, header-15, titre_x-ref_x, 20);
    QRect rectangle_titre(titre_x-10, header-15, comptes_x-titre_x, 20);
    QRect rectangle_comptes(comptes_x-10, header-15, debit_x-comptes_x, 20);
    QRect rectangle_debit(debit_x-10, header-15, credit_x-debit_x, 20);
    QRect rectangle_credit(credit_x-10, header-15, solde_x-credit_x, 20);
    QRect rectangle_solde(solde_x-10, header-15, 900-solde_x, 20);

    painter.drawText(date_x,header, "DATE");
    painter.drawText(ref_x,header, "REFERENCE");
    painter.drawText(titre_x,header, "TITRE");
    painter.drawText(comptes_x,header, "COMPTES");
    painter.drawText(debit_x,header, "DEBIT");
    painter.drawText(credit_x,header, "CREDIT");
    painter.drawText(credit_x,header, "SOLDE");

    painter.drawRect(rectangle_date);
    painter.drawRect(rectangle_ref);
    painter.drawRect(rectangle_titre);
    painter.drawRect(rectangle_comptes);
    painter.drawRect(rectangle_debit);
    painter.drawRect(rectangle_credit);
    painter.drawRect(rectangle_solde);


}
