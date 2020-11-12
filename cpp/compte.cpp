#include <iostream>
#include <string>
#include <iterator>

#include "compte.h"

using namespace std;

const int CompteAbstrait::m_taille=1;
//=======
CompteAbstrait::CompteAbstrait(const std::string& nom,const std::string& num):
m_nom(nom),id(num){}

int CompteAbstrait::GetTaille() const
{
    return m_taille;
}

void CompteAbstrait::Afficher(int n) const
{
cout<<"("<<id<<") "<<m_nom<<" ";
}

CompteAbstrait::~CompteAbstrait()
{

}
//=======
Compte::Compte(const string& nom,const std::string& num):
CompteAbstrait(nom,num)
{

}
void Compte::Afficher(int n) const
{
    for (int i=0;i<n;i++){cout<<"    ";}
    CompteAbstrait::Afficher();
    cout<<" ("<<solde<<" euros)"<<endl;
}

Compte::~Compte(){}
Actif::~Actif(){}
Passif::~Passif(){}
Recette::~Recette(){}
Depense::~Depense(){}
//=======
CompteVirtuel::CompteVirtuel(const string& nom,const string& num,const string& type):_type(type),CompteAbstrait(nom,num)
{

}

void CompteVirtuel::Afficher(int n) const
{
        //pour chaque lment du vecteur, on l'affiche
        vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
        const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

        for (int i=0;i<n;i++){cout<<"    ";}
        cout<<"("<<id<<") ["<<m_nom<<"]\n";
        for(;itb!=ite;itb++)
        {
            (*itb)->Afficher(n+1);
        };
}

int CompteVirtuel::GetTaille() const
{
        //on fait la somme de la taille de chaque lment
        int somtaille=0;

        vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
        const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

        for(;itb!=ite;itb++)
        {
        somtaille+=(*itb)->GetTaille();
        }

        return somtaille;
}

CompteVirtuel::~CompteVirtuel()
{
        //on dtruit chaque lment
        vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
        const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

        for(;itb!=ite;itb++)
        {
            delete (*itb);
        };
}

CompteVirtuel& CompteVirtuel::Add(CompteVirtuel* file)
{
        //cout<<file->getType()<<"=="<<this->getType()<<"\n";
        if (((file->getType()).compare(this->getType())==0) || (this->getType().compare("Racine")==0)){
            m_listfichier.push_back(file);
            return (*file);
        }
        else{
            throw;
        }

}

void CompteVirtuel::Add(Compte* file)
{
      if ((file->getType()).compare(this->getType())==0) {
            m_listfichier.push_back(file);
        }
        else{
            cout<<"erreur ajout fichier \n";
        }
}


CompteAbstrait* CompteVirtuel::GetCompte(std::string num)
{
    vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
    const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();
    for(;itb!=ite;itb++){
        if ((*itb)->GetId().compare(num)==0){
            cout<<"Trouve : "<<(*itb)->GetId()<<"\n";
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

bool CompteVirtuel::supprimer_compte(std::string num)
{
    vector<CompteAbstrait*>::const_iterator itb=m_listfichier.begin();
    const vector<CompteAbstrait*>::const_iterator ite=m_listfichier.end();

    bool test;
    for(;itb!=ite;itb++){
        //cout<<(*itb)->GetId()<<"\n";
        if ((*itb)->GetId().compare(num)==0){
            cout<<"Trouve : "<<(*itb)->GetId()<<"\n";
            delete *itb;
            m_listfichier.erase(itb);
            return true;
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

void FactoryCompte::Register(const string& key,Compte* obj)
{
        //si la cl n'est pas dj prsente
        if(m_map.find(key)==m_map.end())
        {
            //on ajoute l'objet dans la map
            m_map[key]=obj;
        }

       //on pourrait dtruire obj mais cette tche ne revient pas  Register
}

Compte* FactoryCompte::Create(const std::string& key) const
{
    Compte* tmp=0;
    std::map<string, Compte*>::const_iterator it=m_map.find(key);

    //si l'itrateur ne vaut pas map.end(), cela signifie que que la cl  t trouve
    if(it!=m_map.end())
    {
        tmp=((*it).second)->Clone();
    }

    //on pourrait lancer une exeption si la cl n'a pas t trouve

    return tmp;
}




//CompteManager

CompteManager::CompteManager(){
    FactoryCompte::Register("Actif",new Actif("",""));
    FactoryCompte::Register("Passif",new Passif("",""));
    FactoryCompte::Register("Recette",new Recette("",""));
    FactoryCompte::Register("Depense",new Depense("",""));
}

CompteAbstrait* CompteManager::GetCompte(std::string id){
    return root.GetCompte(id);
}

bool CompteManager::creer_compte(std::string& id_dossier,std::string& nom,std::string& type,bool virtuel){
    if (id_dossier.compare("0")==0){
        if (virtuel==true){
            root.Add(new CompteVirtuel(nom,to_string(++id_max),type));
            return true;
        }
    }
    CompteAbstrait* tmp=root.GetCompte(id_dossier);
    if (tmp==nullptr || (tmp->getType()).compare(type)!=0){
        return false;
    }
    if (dynamic_cast<CompteVirtuel*>(tmp)) {
        if (virtuel){
            tmp->Add(new CompteVirtuel(nom,to_string(++id_max),type));
            return true;
        }
        else{
            Compte* compte = factory.Create(type);
            compte->id = to_string(++id_max);
            compte->m_nom = nom;
            tmp->Add(compte);
            return true;

        }
    }
    else{
        cout<<"impossible de crer le compte\n";
        return false;
    }


}

void CompteManager::Afficher(){
    root.Afficher();
}


