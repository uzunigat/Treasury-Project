#ifndef COMPTE_H_INCLUDED
#define COMPTE_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <map>
class CompteVirtuel;
class Compte;
class CompteManager;


//un fichier de base
/*!
 *\class CompteAbstrait
 *\brief C'est le fichier de base de tous les comptes créés
 *\details ...
 */
class CompteAbstrait
{
        friend CompteManager;
        static const int m_taille;

        protected:
        std::string m_nom;
        std::string id;

        public:
        CompteAbstrait* Pere=nullptr;
        std::string GetId() const {return id;}
        virtual int GetTaille() const;
        virtual std::string getType() const {throw;}
        virtual void Afficher(int n=0) const ;
        virtual CompteAbstrait* GetCompte(std::string num){return nullptr;}
        //fonction Add
        virtual CompteVirtuel& Add(CompteVirtuel* file){throw;}
        virtual void Add(Compte* file){throw;}

        //transferts:
        virtual double crediter(double credit){return 0;}
        virtual double debiter(double debit) {return 0;}
        virtual double transferer(double transfert) {return 0;}

        virtual bool supprimer_compte(std::string num){}
        virtual ~CompteAbstrait() =0;
        CompteAbstrait(const std::string& nom,const std::string& num);
};

//un fichier terminal
/*!
 *\class Compte
 *\brief C'est la version terminal d'un compte
 *\details ...
 */
class Compte : public CompteAbstrait
{
protected:
    double solde = 0;

public:
    virtual Compte* Clone() const =0 ;
    void Afficher(int n=0) const ;
    //transferts
    virtual double crediter(double credit){return solde += credit;}
    virtual double debiter(double debit){return solde -= debit;}
    virtual double transferer(double transfert) {return solde += transfert;}
    virtual std::string getType() const =0;
    Compte(const std::string& nom,const std::string& num);
    ~Compte();
};

//un conteneur
/*!
 *\class CompteVirtuel
 *\brief Elle nous servira de conteneur de comptes
 *\details Un virtuel est un compte qui n’est destiné qu’à regrouper des sous-compte sans enregistrer d’opération
 */
class CompteVirtuel : public CompteAbstrait
{
        protected:
        std::vector<CompteAbstrait*> m_listfichier;
        std::string _type;
        public:

        std::string getType() const {return _type;}

        void Afficher(int n=0) const;
        int GetTaille() const;

        CompteVirtuel& Add(CompteVirtuel* file);
        CompteAbstrait* GetCompte(std::string num);
        bool supprimer_compte(std::string num);

        void Add(Compte* file);
        CompteVirtuel(const std::string& nom,const std::string& num,const std::string& type);
        ~CompteVirtuel();

};

/*!
 *\class Actif
 *\brief Elle caractérise un compte comme étant un "Actif"
 *\details L’actif d’une association est composé d’éléments qu’elle possède ayant une valeur économique positive.
 */
class Actif: public Compte
{
public:
    Compte* Clone() const ;//Factory
    Actif(const std::string& nom,const std::string& num): Compte(nom,num){};
    std::string getType() const {return "Actif";}
    ~Actif();
};

/*!
 *\class Passif
 *\brief Elle caractérise un compte comme étant un "Passif"
 *\details Le passif d’une association est tout ce qu’elle doit à ses tiers.
 */
class Passif: public Compte
{
public:
    Compte* Clone() const ;//Factory
    double crediter(double credit){return solde -= credit;}
    double debiter(double debit) {return solde += debit;}
    double transferer(double transfert) {return solde +=  (-1) * transfert;}
    Passif(const std::string& nom,const std::string& num): Compte(nom,num){};
    std::string getType() const {return "Passif";}
    ~Passif();
};

/*!
 *\class Recette
 *\brief Elle caractérise une opération comme étant une "Recette"
 *\details Les recettes (produits) sont des ressources pour l’association.
 */
class Recette: public Compte
{
public:
    Compte* Clone() const ;//Factory
    Recette(const std::string& nom,const std::string& num): Compte(nom,num){};
    std::string getType() const {return "Recette";}
    ~Recette();
};

/*!
 *\class Depense
 *\brief Elle caractérise une opération comme étant une "Dépense"
 *\details Les dépenses sont considérés comme des emplois (achats de biens et de prestations, les charges liées aux personnels, les impôts, etc).
 */
class Depense: public Compte
{
public:
    Compte* Clone() const ;//Factory
    double crediter(double credit){return solde -= credit;}
    double debiter(double debit) {return solde += debit;}
    double transferer(double transfert) {return solde +=  (-1) * transfert;}
    Depense(const std::string& nom,const std::string& num): Compte(nom,num){};
    std::string getType() const {return "Depense";}
    ~Depense();
};

//Factory

/*!
 *\class FactoryCompte
 *\brief Elle gère la création de comptes
 *\details ...
 */
class FactoryCompte
{
public:
       static std::map<std::string,Compte*> m_map;

public:
        //Fonction qui associe cl <=> prototype
        static void Register(const std::string& key,Compte* obj);

        //Celle qui va crer les objets
        Compte* Create(const std::string& key) const;
};


//===========================

/*!
 *\class CompteManager
 *\brief Elle s'occupe de tout ce qui est en relation avec la gestion des comptes
 *\details ...
 */
class CompteManager {
	CompteVirtuel root=CompteVirtuel("Compte Racine","0","Racine");
	FactoryCompte factory;
	unsigned int id_max=0;
	std::string filename = "tmpComptes.xml";
public:
    void Afficher();
    CompteAbstrait* GetCompte(std::string id);
    bool creer_compte(std::string& id_dossier,std::string& nom,std::string& type,bool virtuel);
    bool supprimer_compte(std::string id){return root.supprimer_compte(id);}
	CompteManager();
	//void load(const string& f);
	//void save() const;
};


#endif
