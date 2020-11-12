/**
\file compte.cpp
\date 17/06/2020
\version 1
\brief  Fichier de méthodes compte

Ce fichier inclu la définition des différentes méthodes liées aux comptes.


**/




#include <iostream>
#include <string>
#include <iterator>
#include "compte.h"
#include "transaction.h"
#include "QDebug"

using namespace std;

//=======
CompteAbstrait::CompteAbstrait(const std::string& nom,const int& num):m_nom(nom),id(num){}


void CompteAbstrait::Afficher(int n) const
{
cout<<"("<<id<<") "<<m_nom<<" ";
}

CompteAbstrait::~CompteAbstrait()
{

}
//=======
Compte::Compte(const string& nom,const int& num):
CompteAbstrait(nom,num)
{

}

void Compte::Afficher(int n) const
{
    for (int i=0;i<n;i++){cout<<"    ";}
    CompteAbstrait::Afficher();
    cout<<" solde: "<<getSolde()<<" | Pere : "<<getPere()->GetId()<<endl;
}

Compte::~Compte(){}
Actif::~Actif(){}
Passif::~Passif(){}
Recette::~Recette(){}
Depense::~Depense(){}
//=======
CompteVirtuel::CompteVirtuel(const string& nom,const int& num,const string& type):_type(type),CompteAbstrait(nom,num){}

void CompteVirtuel::Afficher(int n) const
{
        //pour chaque �l�ment du vecteur, on l'affiche
        vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
        const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

        for (int i=0;i<n;i++){cout<<"    ";}

        if (getPere() != nullptr){
            cout<<"("<<id<<") ["<<m_nom<<"] solde: "<<this->getSolde()<<" | Pere : "<<getPere()->GetId()<<endl;}
        else{
            cout<<"("<<id<<") ["<<m_nom<<"] solde: "<<this->getSolde()<<"\n";
        }

        for(;itb!=ite;itb++)
        {
            (*itb)->Afficher(n+1);
        };
}


/*!
 * \details La destruction d'un compte virtuel entraine la suppression de ses fils,\n
 * un parcours du vecteur de sous compte est necessaire.
 */
CompteVirtuel::~CompteVirtuel()
{
        //on d�truit chaque �l�ment
        vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
        const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

        for(;itb!=ite;itb++)
        {
            delete (*itb);
        };
}

/*!
 * \details Pour ajouter un fils, le fils doit avoir le même type que son compte père,\n
 * une vérification est donc effectuée, la contrainte n'est pas respecté pour l'ajout d'un fils dans le compte racine.
 */
CompteVirtuel& CompteVirtuel::Add(CompteVirtuel* file)
{
        //cout<<file->getType()<<"=="<<this->getType()<<"\n";
        if (((file->getType()).compare(this->getType())==0) || (this->getType().compare("Racine")==0)){
            file->setPere(this);
            m_listfichier.push_back(file);
            return (*file);
        }
        else{
            throw;
        }

}

/*!
 * \details L'ajout d'un fils se fait par vérification de son type,\n
 *  si le fils est de même type que le dossier, alors il est ajouté au vecteur de compteabstrait du comptevirtuel. lors de l'ajout du fils,\n
 *  le pointeur de père du fils est initialisé et un pointeur vers le fils est ajouté à m_listfichier.
 */
void CompteVirtuel::Add(Compte* file)
{
      if (((file->getType()).compare(this->getType())==0)|| (this->getType().compare("Racine")==0)) {
            file->setPere(this);
            m_listfichier.push_back(file);
        }
        else{
            cout<<"erreur ajout fichier \n";
        }
}


/*!
 * \details Rehderche un compte de manière récursive grâce à l'appel de la fonction GetCompte des sous CompteVirtuel si le compte recherché n'est pas trouvé dans m_listfichier.\n
 * Un cas particulier pour le "compte racine" étant donné que ce compte ne peut pas se trouver dans ses fils.
 */
CompteAbstrait* CompteVirtuel::GetCompte(int num)
{
    if ((num==0)&&(this->GetId() == 0)){
            return this;
    }

    vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
    const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();
    for(;itb!=ite;itb++){
        if ((*itb)->GetId() == num){
            //cout<<"Trouve : "<<(*itb)->GetId()<<"\n";
            return *itb;
        }
        else{
            CompteAbstrait* tmp=(*itb)->GetCompte(num);
            if (tmp != nullptr){
                return tmp;
            }

        }
        //cout<<((*itb)->GetId().compare(num)==0)<<" ";
    }
    return nullptr;

}

/*!
 * \details La fonction supprimer compte parcours l'aborescence d'un CompteVirtuel,\n
 * dès que le compte recherché est trouvé, il est supprimé du vecteur m_listfichier et est supprimé.
 */
bool CompteVirtuel::supprimer_compte(int num)
{
    vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
    const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

    bool test;
    for(;itb!=ite;itb++){
        //cout<<(*itb)->GetId()<<"\n";
        if (((*itb)->GetId())==num){
            cout<<"Trouve : "<<(*itb)->GetId()<<"\n";
            if ((*itb)->is_deletable()){
                delete *itb;
                m_listfichier.erase(itb);
                return true;
            }
            return false;
        }
        else{
            test = (*itb)->supprimer_compte(num);
            if (test == true){
                return true;
            }
        }

    }
    return false;

}

/*!
 * \details Un Comptevirtuel ne possède pas d'attribut solde, son solde est calculé en faisant la somme de celui de ses fils,\n
 * pour chaque fils de type CompteVirtuel, le solde est recalculé de manière récursive.
 */
double CompteVirtuel::getSolde() const {
    double s=0;
    vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
    const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();
    for(;itb!=ite;itb++){
        s+=(*itb)->getSolde();
    }
    return s;
}


//Factory


Compte* Actif::Clone() const
{
    return new Actif(*this);
}

Compte* Passif::Clone() const
{
    return new Passif(*this);
}

Compte* Recette::Clone() const
{
    return new Recette(*this);
}

Compte* Depense::Clone() const
{
    return new Depense(*this);
}

std::map<string,Compte*> FactoryCompte::m_map= std::map<string,Compte*>();

/*!
 * \details Cette méthode enregistre un type de compte à cloner dans le map de notre factory, et enregistre la chaine de caractère le désignant sous forme de clé.
 */
void FactoryCompte::Register(const string& key,Compte* obj)
{
        //si la cl� n'est pas d�j� pr�sente
        if(m_map.find(key)==m_map.end())
        {
            //on ajoute l'objet dans la map
            m_map[key]=obj;
        }

       //on pourrait d�truire obj mais cette t�che ne revient pas � Register
}

/*!
 * \details Duplique un compte à partir de la clé le désignant. et retourne un pointeur vers le compte crée
 */
Compte* FactoryCompte::Create(const std::string& key) const
{
    Compte* tmp=0;
    std::map<string, Compte*>::const_iterator it=m_map.find(key);

    //si l'it�rateur ne vaut pas map.end(), cela signifie que que la cl� � �t� trouv�e
    if(it!=m_map.end())
    {
        tmp=((*it).second)->Clone();
    }

    //on pourrait lancer une exeption si la cl� n'a pas �t� trouv�e

    return tmp;
}




//CompteManager

/*!
 * \details Le constructeur de comptemanager permet d'initialiser la factory en y enregistrant les différents types de compte.
 */
CompteManager::CompteManager(){
    FactoryCompte::Register("Actif",new Actif("",0));
    FactoryCompte::Register("Passif",new Passif("",0));
    FactoryCompte::Register("Recette",new Recette("",0));
    FactoryCompte::Register("Depense",new Depense("",0));
}

/*!
 * \details Appel de la méthode CompteVirtuel::getcompte() depuis le "compte racine".
 */
CompteAbstrait* CompteManager::GetCompte(int id){
    return root.GetCompte(id);
}

/*!
 * \details Effecue une recherche du "compte dossier" dans lequel créer un CompteVirtuel ou Compte,\n
 * si le "compte dossier" est trouvé, une vérification de son type est effectuée grâce à un cast.\n
 * le "Compte" est alors crée par la factory si il est réel.
 */
bool CompteManager::creer_compte(int id_dossier,std::string nom,std::string type,bool virtuel){
    if (id_dossier==0){
        if (virtuel){
            root.Add(new CompteVirtuel(nom,++id_max,type));
            return true;
        }
        else{
            Compte* compte = factory.Create(type);
            compte->id = ++id_max;
            compte->m_nom = nom;
            root.Add(compte);
            return true;
        }
    }

    CompteAbstrait* tmp=root.GetCompte(id_dossier);
    if (tmp==nullptr || (tmp->getType()).compare(type)!=0){
        return false;
    }
    if (dynamic_cast<CompteVirtuel*>(tmp)) {
        if (virtuel){
            tmp->Add(new CompteVirtuel(nom,++id_max,type));
            return true;
        }
        else{
            Compte* compte = factory.Create(type);
            compte->id = ++id_max;
            compte->m_nom = nom;
            tmp->Add(compte);
            return true;
        }
    }
    else{
        qDebug()<<"error2";
        cout<<"impossible de crer le compte\n";
        return false;
    }
}

/*!
 * \details Redéfinition de la fonction afficher du "compte racine" contenu dans notre comptemanager.
 */
void CompteManager::Afficher(){
    root.Afficher();
}


//Opération :


Operation& Compte::add_operation(Operation* operation){
    insert(operation->getTransaction().getDate(),operation);
    //transferer(operation->getMontant());
    return *operation;
}

/*!
 * \details Recherche de l'opération à partir de son id en parcourant le vecteur d'opération d'un compte,\n
 * si l'opération est trouvée, celle-ci est supprimé du vecteur.
 */
bool Compte::supprimer_op(int id){
    for(auto it=begin(); it!=end(); it++){
        if (it.value()->getId() == id){
            erase(it);
            return true;
        }
    }
    return false;

}

/*!
 * \details un CompteVirtuel ne possède pas d'opération, en revanche il peut afficher celle de ses fils.
 */
void CompteVirtuel::Afficher_operation() const {
    vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
    const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();
    for(;itb!=ite;itb++){
        (*itb)->Afficher_operation();
    }
}

/*!
 * \details Appel les méthodes Afficher() de chaque opération d'un compte en parcourant son disctionnaire d'opération.
 */
void Compte::Afficher_operation() const {
    cout<<"Operations du compte "<<this->m_nom<<':'<<endl;
    for(auto it=begin(); it!=end(); it++){
        it.value()->afficher();
    }
    cout<<endl;
}

/*!
 * \details Compte::rapprocher permet de créer un Rapprochement et donne un pointeur vers se rapprochement à toutes les opérations de date inférieur à la date du rapprochement.\n
 * On ne change pas le pointeur Operation::rapprochement si une opération est déjà rapprochée.
 */
void Compte::rapprocher(int y, int m, int d,std::string nom, std::string desc){
    Rapprochement* pt= new Rapprochement(QDate(y,m,d),nom,desc,this,this->solde);
    ListRapprochement.insert(pt->getDate(),pt);
    for (auto it = begin(); it != end(); it++){
        if ((it.value()->getTransaction().getDate() <= pt->getDate()) && (it.value()->getRapprochement() == nullptr)){
            it.value()->setRapprochement(pt);
            //std::cout<<"setrapprochement"<<std::endl;//debug
        }
    }
}


/*!
 * \details Recherche le rapprochement d'un "compte reel" à partir de son id,\n
 *  appel la méthode Afficher() du rapprochement en cas de succès.
 */
void Compte::afficher_rapprochement(int id){

    for (auto it = ListRapprochement.begin(); it != ListRapprochement.end(); it++){
        if (it.value()->getId() == id){
            it.value()->Afficher();
        }
    }
}

/*!
 * \details Parcours le dictionnaire de rapprochement d'un "compte reel", et Affiche chaque rapprochement dans la console grâce à la méthode Rapprochement::Afficher()
 */
void Compte::afficher_rapprochement(){
    for (auto it = ListRapprochement.begin(); it != ListRapprochement.end(); it++){
        it.value()->Afficher();
    }
}

/*!
 * \details Retourne le derner rapprochement d'un compte à partir de la méthode last() du map.
 */
Rapprochement* Compte::Last_Rapprochement(){
    if (ListRapprochement.size()>0)
        return ListRapprochement.last();
    else
        return nullptr;
}

/*!
 * \details verifie si tout les fils du CompteVirtuel sont supprimables, c'est à dire qu'ils n'ont occunes opération liées.
 */
bool CompteVirtuel::is_deletable(){
    if (m_listfichier.size() == 0)
        return true;
    else{
        for(auto it=m_listfichier.begin();it!=m_listfichier.end();it++){
            if (!(*it)->is_deletable())
                return false;
        }
        return true;
    }
}


/*!
 * \details Utilisé pour la remise à zero du solde de tout les comptes, cette méthode s'applique aux "compte réels" qui sont les feuilles de l'arborescence de compte.
 */
void Compte::solde_reset(){
    solde=0;
}

void CompteVirtuel::solde_reset(){
    for (auto it = m_listfichier.begin();it != m_listfichier.end();it++){
        (*it)->solde_reset();
    }
}


void CompteManager::solde_reset()
{
    for (auto it = root.m_listfichier.begin();it != root.m_listfichier.end();it++){
        (*it)->solde_reset();
    }
}
