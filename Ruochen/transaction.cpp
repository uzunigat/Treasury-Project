/**
\file transaction.cpp
\date 17/06/2020
\version 1
\brief  Fichier de méthodes transaction

Ce fichier inclu la définition des différentes méthodes liées aux transactions.

**/



#include <iostream>
#include <string>
#include "transaction.h"
#include "compte.h"
#include "QDebug"


/*!
 * \details Vérifie toutes les condiions necessaire à la validiter d'une opération.
 */
bool Operation::Check(){
    if (debit == 0 && credit == 0){
            return false;
    }

    else{
        if (debit < 0) {
            credit = credit - debit;
            debit = 0;
        }

        if (credit < 0) {
            debit = debit - credit;
            credit = 0;
        }

        if (debit>0 && credit>0) {
            double min;
            if(debit < credit) min = debit;
            else min = credit;

            debit = debit - min;
            credit = credit - min;
        }
        return true;
  }
}

/*!
 * \details Créer une transaction par l'intermédiaire du TransactionManager sans l'enregistrer dans la liste des transactions.
 */
Transaction* TransactionManager::creerTransaction(int y, int m, int d, const std::string& ref, const std::string& memo){
    Transaction* t = new Transaction(id_max++,y,m,d, ref, memo);
    return t;
}

/*!
 * \details Ajoute une opération au vecteur d'opération contenu dans une transaction.\n
 * Verification de la validité de l'opération avec la méthode Operation::Check() et si le compte concerné est bien réel.
 */
Operation& Transaction::add(double debit, double credit, CompteAbstrait* compte, QString intitule){
    Compte* pt=dynamic_cast<Compte*>(compte);
    if (pt == nullptr){
        qDebug()<<"Erreur compte virtuel";
        throw("Erreur compte virtuel");
    }

    Operation* operation = new Operation(id_op++,debit,credit,pt,this,intitule);

    if (operation->Check()){
        pt->add_operation(operation);
        push_back(operation);
        return *operation;
    }
    else{
        qDebug()<<"Operation non valide";
        throw("Operation non valide");
    }

}

/*!
 * \details verifie si de l'argent ne se créer pas lors d'une transaction, donc on vérifie que la somme du montant des opérations est nulle.
 */
bool Transaction::Check() const{
    int somme=0;

    for(auto it=begin(); it!=end(); it++)
       somme+= - (*it)->getDebit() + (*it)->getCredit();

    if(somme==0){
        return true;
    }
    else{
        return false;
    }

}

/*!
 * \details Ajouter transaction permet de sauvegarde une transaction dans le transactionmanager l'ajoutant à son dictionnaire.\n
 * Cette méthode applique la transaction aux comptes concernés en créditant ou débitant leurs solde.
 */
bool TransactionManager::ajouter_transaction(Transaction *transaction){
    if (transaction->Check()){
        for(auto it=transaction->begin();it!=transaction->end();it++){
            (*it)->getCompte().debiter((*it)->getDebit());
            (*it)->getCompte().crediter((*it)->getCredit());
        }
        insert(transaction->getDate(), transaction);
        return true;
    }
    else {
        std::cout<<"Transaction invalide"<<std::endl;
        delete transaction;
        return false;
    }
}

/*!
 * \details cette methode permet l'ajout d'une transaction directement au dictionnaire de transaction sans appliquer la transaction.
 */
bool TransactionManager::ajouter_transaction2(Transaction* transaction){

    insert(transaction->getDate(), transaction);
    return true;

}

/*!
 * \details Affiche la valeur des variable d'une opération dans la console
 */
void Operation::afficher(){
    std::cout<<"\t"<<id<<" Intitule: "<<intitule.toStdString()<<" Compte: "<<compte->getNom()<<" debit: "<<debit<<" credit: "<<credit<<' '<<transaction->getDate().toString().toStdString()<<std::endl;
}

/*!
 * \details Affiche les informations concernant une transaction, ainsi que ses opération en appelant la méthode Afficher() des opérations contenues dans son vecteur.
 */
void Transaction::afficher(){
    std::cout<<id<<' '<<reference<<' '<<date.toString().toStdString()<<' '<<memo<<' '<<std::endl;
    for(auto it=begin(); it!=end();++it){
        (*it)->afficher();
    }
    std::cout<<std::endl;
}

/*!
 * \details Appel la méthode afficher() de chaque transaction contenues dans le dictionaire de transaction.
 */
void TransactionManager::afficher() const{
    std::cout << "\nTransaction Manager :\n"<<std::endl;
    for(auto it=begin(); it!=end();++it){
        it.value()->afficher();
    }
}

/*!
 * \details effectue une recherche par id d'une opération, met à jour le solde des comptes après annulation et supprime l'opération du vecteur.
 */
bool Transaction::supprimer_op(int id){
    for(auto it=begin(); it!=end(); it++){
        if ((*it)->id == id){
            auto pt = (*it);
            erase(it);
            pt->getCompte().crediter(pt->getDebit());
            pt->getCompte().debiter(pt->getCredit());
            delete pt;
            return true;
        }
    }
    return false;
}

/*!
 * \details Supprime l'opération dans le dictionnaire du compte associé à l'appel du destructeur.
 */
Operation::~Operation(){
    compte->supprimer_op(this->id);
}

/*!
 * \details effectue une recherche par id d'une transaction et la supprime en annulant ses opération et en la supprimant du dictionnaire.
 */
bool TransactionManager::supprimer_transaction(int id){
    for(auto it=begin(); it!=end();++it){
        if (it.value()->getId()==id){
            auto pt = it.value();
            erase(it);
            for (auto it_op = pt->begin();it_op != pt->end();it_op++){
                (*it_op)->getCompte().crediter((*it_op)->getDebit());
                (*it_op)->getCompte().debiter((*it_op)->getCredit());
            }
            delete pt;
            return true;
        }
    }
    return false;
}

/*!
 * \details La suppression d'une transaction entraine la suppression de ses opérations.\n
 * l'appel du destructeur d'opération permet de supprimer les opérations stockées aussi dans les comptes concernés.
 */
Transaction::~Transaction(){
    auto it=begin();
    while(it!=end()){
        auto pt = (*it);
        it = erase(it);
        delete pt;
    }
}


Transaction* TransactionManager::retirer_transaction(int id){
    for(auto it=begin(); it!=end();++it){
        if(it.value()->getId()==id){
            Transaction* pt=it.value();
            erase(it);
            for(auto i = pt->begin();i != pt->end(); i++){
                Compte& compte = (*i)->getCompte();
                compte.crediter((*i)->getDebit());
                compte.debiter((*i)->getCredit());
            }
            return pt;
        }
    }
    return nullptr;
}


Transaction *TransactionManager::recherche_transaction(int id){
    for(auto it=begin(); it!=end();++it){
        if(it.value()->getId()==id){
            return it.value();;
        }
    }
    return nullptr;
}

/*!
 * \details Algorithme de recherche par id d'une opération dans une transaction.
 */
Operation* Transaction::recherche_op(int id){

    for(auto it=begin(); it!=end(); it++){
        if ((*it)->id == id){
            return (*it);
        }
    }
    return nullptr;
}

int Rapprochement::id_max=0;

/*!
 * \details Affiche l'ensemble des opérations concernant un rapprochement dans un compte,\n
 * si le pointeur de rapprochement dans une opération est le même que le reapprochement à afficher, alors on affiche l'opération.
 */
void Rapprochement::Afficher(){ //affiche un raprochement
    std::cout<<id<<' '<<date.toString().toStdString()<<' '<<nom<<' '<<desc<<' '<<compte->getNom()<<std::endl;
    for (auto it=compte->begin();it!=compte->end();it++){
        if (it.value()->getRapprochement()!=nullptr && it.value()->getRapprochement()->getId() == id){
            it.value()->afficher();
        }
    }
}

/*!
 * \details Vérifie si une transaction est gelée en vérifiant si au moins une opération contient un pointeur de rapprochement.
 */
bool Transaction::is_frozen(){  //Vérifie si la transaction est rapprochée
    for(auto it = begin();it!=end();it++){
        if ((*it)->is_frozen()){    //Vérifie si une opération est rapprochée
            return true;
        }
    }
    return false;
}


bool TransactionManager::verifierReference(const std::string ref){
    for(auto it_trans = begin(); it_trans!= end(); ++it_trans){
        if(it_trans.value()->getReference() == ref)
            return false;
    }
    return true;
}

/*!
 * \brief TransactionManager::recalculer_solde
 * \details Remet à zero le solde de tout les comptes grâce à CompteManager::solde_reset
 * puis parcours le dictionnaire de transaction et réapplique les crédit et débit de chaque opération à chaque compte
 */
void TransactionManager::recalculer_solde(CompteManager& cm){
    cm.solde_reset();
    for(auto it=begin();it!=end();it++){
        for(auto it_op = it.value()->begin();it_op != it.value()->end();it_op++){
            (*it_op)->getCompte().crediter((*it_op)->getCredit());
            (*it_op)->getCompte().debiter((*it_op)->getDebit());
        }
    }
}

