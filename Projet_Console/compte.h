/**
\file compte.h
\date 17/06/2020
\version 1
\brief  Fichier de classe compte

Ce fichier inclu les différentes classes liées aux comptes.


**/


#ifndef COMPTE_H_INCLUDED
#define COMPTE_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QMultiMap>
#include <QDate>
#include <QDebug>
class Operation;
class CompteVirtuel;
class Compte;
class CompteManager;
class Rapprochement;

//un fichier de base
/*!
 *\class CompteAbstrait
 *\brief Classe abstraite permettant d'implémenter les comptes réels et virtuels
 *\details Cette classe à été implémenté pour le design pattern composite,\n
 * il s'agit de l'interface de Compte et CompteVirtuel
 */
class CompteAbstrait
{
        friend CompteManager;

    protected:
        /*!
             *  \brief Nom du compte, commun à tout les types de compte
             */
        std::string m_nom;

        /*!
             *  \brief identifiant du compte
             */
        int id;

        /*!
             *  \brief pointeur vers le père du compte initialisé à nullptr
             */
        CompteAbstrait* Pere=nullptr;

    public:
        /*!
             * \brief Getter de l'identifiant du compte
             * \return retourne l'identifiant du compte
             */
        int GetId() const {return id;}

        /*!
             * \brief Getter du nom de compte
             * \return retourne le nom du compte
             */
        std::string getNom() const {return m_nom;}

        /*!
             * \brief définition virtuelle du getter de type, utile pour comptes de tout types
             */
        virtual std::string getType() const {throw;}

        /*!
             * \brief définition virtuelle du getter de solde
             */
        virtual double getSolde() const {throw;}

        /*!
             * \brief définition virtuelle de la fonction Afficher, qui permet d'afficher tout type de compte
             */
        virtual void Afficher(int n=0) const ;

        /*!
             * \brief définition virtuelle de la fonction Afficher_opération\n
             * \details Permet d'afficher toute les opérations des Compte dans un CompteVirtuel
             */
        virtual void Afficher_operation() const{}

        /*!
             * \brief définition virtuelle de la fonction GetCompte\n
             * \details Permet d'utiliser la fonction GetCompte d'un CompteVirtuel sans avoir à le caster
             */
        virtual CompteAbstrait* GetCompte(int num){return nullptr;}

        //fonction Add
        /*!
             * \brief intitialiser le père d'un compte\n
             */
        void setPere(CompteAbstrait* compte){Pere = compte;}

        /*!
             * \return retourne le père du compte
             */
        CompteAbstrait* getPere() const {return Pere;}

        /*!
             * \brief définition virtuelle de la fonction Add
             */
        virtual CompteVirtuel& Add(CompteVirtuel* file){throw;}

        /*!
             * \brief définition virtuelle de la fonction Add
             */
        virtual void Add(Compte* file){throw;}

        //transferts:
        virtual double crediter(double credit){return 0;}
        virtual double debiter(double debit) {return 0;}
        virtual double transferer(double transfert) {return 0;}
        virtual void rapprocher(int y, int m, int d,std::string nom, std::string desc){}
        virtual void afficher_rapprochement(int id){}
        virtual void afficher_rapprochement(){}
        QDate Last_Rapprochement(){}

        virtual bool supprimer_compte(int num){return 0;}
        virtual bool is_deletable()= 0;
        virtual void solde_reset()=0;
        virtual ~CompteAbstrait() =0;
        CompteAbstrait(const std::string& nom,const int& num);
};

//un fichier terminal
/*!
 *\class Compte
 *\brief compte réel
 *\details compte pouvant participer à des transactions et ayant un solde propre
 */
class Compte : public CompteAbstrait, private QMultiMap<QDate, Operation*>
{

protected:
    using Operations = QMultiMap<QDate, Operation*>;

    /*!
         *  \brief solde défini et initialisé à 0
         */
    double solde = 0;

    /*!
         *  \brief dictionnaire des rapprochement pouvant contenir plusieurs fois la même clé
         */
    QMultiMap<QDate, Rapprochement*> ListRapprochement;
    friend CompteManager;

public:
    /*!
         *  \brief Permet de rapprocher un compte
         *  \param y : Année de création
         *  \param m: Mois de création
         *  \param d : Jour de création
         *  \param nom: nom du rapprochement
         *  \param desc: decription du rapprochement
         */
    void rapprocher(int y, int m, int d,std::string nom, std::string desc);

    /*!
         *  \brief Ajouter une opération
         *  \details Permet d'ajouter une opération au map d'opération d'un compte
         * \param operation: pointeur vers l'opération à ajouter
         */
    Operation& add_operation(Operation* operation);

    /*!
         *  \brief Cloner un compte
         *  \details définiton virtuelle de la fonction Clone, implémentée pour le design pattern factory
         */
    virtual Compte* Clone() const =0 ;

    /*!
         *  \brief Permet d'afficher un compte dans la console
         *  \param n : niveau dans l'aborescence du compte
         */
    void Afficher(int n=0) const ;

    /*!
         *  \brief Permet d'afficher les opérations d'un compte dans la console
         */
    void Afficher_operation() const ;

    /*!
         *  \brief Permet d'afficher un rapprochement d'un compte dans la console
         *  \param id : id du rapprochement à afficher
         */
    void afficher_rapprochement(int id);

    /*!
         *  \brief Permet d'afficher tout les rapprochements d'un compte dans la console
         */
    void afficher_rapprochement();

    /*!
         *  \brief Permet d'afficher le dernier rpprochement d'un compte dans la console
         */
    Rapprochement* Last_Rapprochement();
    //transferts
    /*!
         *  \brief Permet de créditer un compte
         *  \param credit : montant à créditer
         *  \return Retourne le solde actualisé du compte
         */
    virtual double crediter(double credit){return solde += credit;}

    /*!
         *  \brief Permet de débiter un compte
         *  \param debit : montant à débiter
         *  \return Retourne le solde actualisé du compte
         */
    virtual double debiter(double debit){return solde -= debit;}

    /*!
         *  \brief Permet d'éffectuer de faire une opération directement sur le solde d'un compte
         *  \param transfert : montant à transférer
         *  \return Retourne le solde actualisé du compte
         */
    virtual double transferer(double transfert) {return solde += transfert;}

    /*!
         *  \brief Méthode virtuelle afin de determiner le type des objet hérités
         */
    virtual std::string getType() const =0;

    /*!
         *  \brief Permet de retourner le solde d'un compte
         *  \param transfert : montant à transférer
         *  \return Retourne le solde actualisé du compte
         */
    double getSolde()const {return solde;}

    /*!
         *  \brief Permet de supprimer une opération
         *  \param id : identifiant
         *  \return true en cas de succès false sinon
         */
    bool supprimer_op(int id);

    /*!
         *  \brief Constructeur
         *  \details Constructeur de la classe Compte
         *  \param nom : nom du compte
         *  \param num : id du compte
         */
    Compte(const std::string& nom,const int& num);

    /*!
         *  \brief Permet de savoir si le compte est supprimable
         *  \return return true si le compte n'a pas d'opération associée.
         */
    bool is_deletable(){return size()==0;}

    /*!
         *  \brief Remete à zero le solde d'un compte et supprime ses opérations
         */
    void solde_reset();

    /*!
         *  \brief Destucteur Par défaut de la classe Compte
         */
    ~Compte();

    /*!
         *  \brief Passage en public de la méthode begin de QMultiMap
         */
    using Operations::begin;

    /*!
         *  \brief Passage en public de la méthode end de QMultiMap
         */
    using Operations::end;
};


//un conteneur
/*!
 *\class CompteVirtuel
 *\brief Dossier de Compte
 *\details Un Comptevirtuel est un compte qui n’est destiné qu’à regrouper des sous-compte sans enregistrer d’opération
 */
class CompteVirtuel : public CompteAbstrait
{
     protected:
        /*!
             *  \brief Vecteur contenant la liste des fils du compte
             */
        std::vector<CompteAbstrait*> m_listfichier;

        /*!
             *  \brief Tpe du compte en chaine de caractère
             */
        std::string _type;
        friend CompteManager;

     public:
        /*!
             *  \brief Permet de connaitre le type du compte
             *  \param _type : type du compte en chaine de caractère
             */
        std::string getType() const {return _type;}

        /*!
             *  \brief Permet d'afficher un CompteVirtuel dans la console
             *  \param n : niveau du compte dans l'arborescence
             */
        void Afficher(int n=0) const;

        /*!
             *  \brief Permet d'afficher les opération des sous comptes.
             */
        void Afficher_operation() const ;

        /*!
             *  \brief Permet de connaitre la somme du solde des sous compte d'un CompteVirtuel
             *  \return retourne la valeur du solde calculé
             */
        double getSolde() const;

        /*!
             *  \brief Permet d'ajouter un sous CompteVirtuel
             *  \param file : pointeur vers le sous compte
             *  \return Retourne un pointeur vers le fils ajouté
             */
        CompteVirtuel& Add(CompteVirtuel* file);

        /*!
             *  \brief Permet de rechercher un compte parmis les fils d'un CompteVirtuel
             *  \param num : identifiant du sous compte
             */
        CompteAbstrait* GetCompte(int num);

        /*!
             *  \brief Permet d'ajouter un sous Compte
             *  \param file : pointeur vers le sous compte
             */
        void Add(Compte* file);

        /*!
             *  \brief Permet supprimer un compte à partir de son identifiant
             *  \param num : identifiant du compte
             *  \return retourne true en cas de succès false sinon
             */
        bool supprimer_compte(int num);

        /*!
             *  \brief vérifie si les sous comptes n'ont pas d'opérations et donc si ce dossier est supprimable
             *  \return Retourne true si tout les fils non aucunes opération liée
             */
        bool is_deletable();

        /*!
             *  \brief Remet le solde de tout les comptes fils à 0\n
             * \details fonction récursive qui appelle les fonctions solde_reset de ses fils
             */
        void solde_reset();


        /*!
             *  \brief Constructeur
             *  \details Constructeur de la classe CompteVirtuel
             *  \param nom : nom du compte
             *  \param num : id du compte
             */
        CompteVirtuel(const std::string& nom,const int& num,const std::string& type);

        /*!
             *  \brief Destructeur\n
             *  \details Desttructeur par default
             */
        ~CompteVirtuel();

};

/*!
 *\class Actif
 *\brief Compte de type "Actif"
 *\details L’actif d’une association est composé d’éléments qu’elle possède ayant une valeur économique positive.
 */
class Actif: public Compte
{
public:
    /*!
         *  \brief Cloner compte\n
         *  \details fonction necessaire au fonctionnement de la factory, elle permet la duplication de compte Actif
         */
    Compte* Clone() const ;//Factory

    /*!
         *  \brief Crediter un compte\n
         *  \details Crédite le montant choisi au compte
         *  \param credit : montant à créditer
         *  \return retourne le solde mis à jour
         */
    double crediter(double credit){return solde -= credit;}

    /*!
         *  \brief Debiter un compte\n
         *  \details Débite le montant choisi au compte
         *  \param debit : montant à créditer
         *  \return retourne le solde mis à jour
         */
    double debiter(double debit) {return solde += debit;}

    /*!
         *  \brief Opération directe sur le solde du compte\n
         *  \param transfert : montant à transferer
         *  \return retourne le solde mis à jour
         */
    double transferer(double transfert) {return solde +=  (-1) * transfert;}

    /*!
         *  \brief Constructeur\n
         *  \details Constructeur de la classe Actif
         *  \param nom : nom du compte
         *  \param num : identifiant du compte
         */
    Actif(const std::string& nom,const int& num): Compte(nom,num){};

    /*!
         *  \brief Getter de type\n
         *  \details Permet de récupérer le type du compte en chaine de caractère
         *  \return retourne le type du compte
         */
    std::string getType() const {return "Actif";}

    /*!
         *  \brief Destructeur\n
         *  \details destructeur par défaut de la classe Actif
         */
    ~Actif();
};

/*!
 *\class Passif
 *\brief Compte de type "Passif"
 *\details Le passif d’une association est tout ce qu’elle doit à ses tiers.
 */
class Passif: public Compte
{
public:
    /*!
         *  \brief Cloner compte\n
         *  \details fonction necessaire au fonctionnement de la factory, elle permet la duplication de compte Actif
         */
    Compte* Clone() const ;//Factory

    /*!
         *  \brief Constructeur\n
         *  \details Constructeur de la classe Passif
         *  \param nom : nom du compte
         *  \param num : identifiant du compte
         */
    Passif(const std::string& nom,const int& num): Compte(nom,num){};

    /*!
         *  \brief Getter de type\n
         *  \details Permet de récupérer le type du compte en chaine de caractère
         *  \return retourne le type du compte
         */
    std::string getType() const {return "Passif";}

    /*!
         *  \brief Destructeur\n
         *  \details destructeur par défaut de la classe Actif
         */
    ~Passif();
};

/*!
 *\class Recette
 *\brief Compte de type "Recette"
 *\details Les recettes (produits) sont des ressources pour l’association.
 */
class Recette: public Compte
{
public:
    /*!
         *  \brief Cloner compte\n
         *  \details fonction necessaire au fonctionnement de la factory, elle permet la duplication de compte Actif
         */
    Compte* Clone() const ;//Factory

    /*!
         *  \brief Constructeur\n
         *  \details Constructeur de la classe Recette
         *  \param nom : nom du compte
         *  \param num : identifiant du compte
         */
    Recette(const std::string& nom,const int& num): Compte(nom,num){};

    /*!
         *  \brief Getter de type\n
         *  \details Permet de récupérer le type du compte en chaine de caractère
         *  \return retourne le type du compte
         */
    std::string getType() const {return "Recette";}

    /*!
         *  \brief Destructeur\n
         *  destructeur par défaut de la classe Recette
         */
    ~Recette();
};

/*!
 *\class Depense
 *\brief Compte de type "Dépense"
 *\details Les dépenses sont considérés comme des emplois (achats de biens et de prestations, les charges liées aux personnels, les impôts, etc).
 */
class Depense: public Compte
{
public:

    /*!
         *  \brief Cloner compte\n
         *  \details fonction necessaire au fonctionnement de la factory, elle permet la duplication de compte Actif
         */
    Compte* Clone() const ;//Factory

    /*!
         *  \brief Crediter un compte\n
         *  \details Crédite le montant choisi au compte
         *  \param credit : montant à créditer
         *  \return retourne le solde mis à jour
         */
    double crediter(double credit){return solde -= credit;}

    /*!
         *  \brief Debiter un compte\n
         *  \details Débite le montant choisi au compte
         *  \param debit : montant à créditer
         *  \return retourne le solde mis à jour
         */
    double debiter(double debit) {return solde += debit;}

    /*!
         *  \brief Opération directe sur le solde du compte\n
         *  \param transfert : montant à transferer
         *  \return retourne le solde mis à jour
         */
    double transferer(double transfert) {return solde +=  (-1) * transfert;}

    /*!
         *  \brief Constructeur\n
         *  \details Constructeur de la classe Depense
         *  \param nom : nom du compte
         *  \param num : identifiant du compte
         */
    Depense(const std::string& nom,const int& num): Compte(nom,num){};

    /*!
         *  \brief Getter de type\n
         *  \details Permet de récupérer le type du compte en chaine de caractère
         *  \return retourne le type du compte
         */
    std::string getType() const {return "Depense";}

    /*!
         *  \brief Destructeur\n
         *  destructeur par défaut de la classe Recette
         */
    ~Depense();
};

//Factory

/*!
 *\class FactoryCompte
 *\brief Générateur de "compte réel"
 *\details La factory est utile à la création de compte de type différents simplement grâce à leurs nom en chaine de caractère
 */
class FactoryCompte
{
public:
       static std::map<std::string,Compte*> m_map;

public:
        //Fonction qui associe cl� <=> prototype
       /*!
            *  \brief Enregistrer mot clef\n
            *  \details cette fonction permet d'enregister l'orthographe à utiliser associé à un type de compte dans la factory
            *  \param key : mot clé désignant le compte comme son type par exemple
            *  \param obj : objet compte à dupliquer
            */
        static void Register(const std::string& key,Compte* obj);

        //Celle qui va cr�er les objets
        /*!
             *  \brief Permet de générer un compte\n
             *  \details Cette méthode génére un compte à partir du mot clé utilisé en consultant le dictionnaire d'objets enregistrés
             *  \param key : mot clé désignant le compte à dupliquer
             */
        Compte* Create(const std::string& key) const;
};


//===========================

/*!
 *\class CompteManager
 *\brief Classe qui s'occupe de la gestion des comptes
 *\details Cette fonction gère entièrement les comptes à gérer par le logiciel et contient la racine de notre arborescence
 */
class CompteManager {

    /*!
         *  \brief Definition et initialisation du compte racine\n
         */
    CompteVirtuel root=CompteVirtuel("Compte Racine",0,"Racine");

    /*!
         *  \brief définition de la factory de compte \n
         */
    FactoryCompte factory;

    /*!
         *  \brief Compteur d'identifiant
         */
    unsigned int id_max=0;
    std::string filename = "tmpComptes.xml";
public:
    /*!
         *  \brief Permet d'afficher l'arbre des comptes dans la console\n
         */
    void Afficher();

    /*!
         *  \brief Permet de chercher un compte dans l'arborescence à partir de son identifiant
         *  \return retourne un pointeur vers le compte trouvé, nullptr sinon
         */
    CompteAbstrait* GetCompte(int id);

    /*!
         *  \brief Permet de creer un compte dans un dossier
         *  \param id_dossier : id du CompteVirtuel dans lequel créer un compte
         *  \param nom : nom du compte à créer
         *  \param type : type du compte, utilisation de la factory pour créer le compte à partir de son nom
         *  \param virtuel : booleen permettant de choisir si le compte est virtuel (true) ou réel (false)
         *  \return retourne true en cas de succès, else sinon
         */
    bool creer_compte(int id_dossier,std::string nom,std::string type,bool virtuel);

    /*!
         *  \brief Permet de supprimer un compte dans l'arborescence à partir de son identifiant
         *  \return retourne true en cas de succès, else sinon
         */
    bool supprimer_compte(int id){return root.supprimer_compte(id);}

    /*!
         *  \brief Getter de l'id à
         *
         *
         *
         *
         *
         * er au prochain compte crée
         *  \return retourne true en cas de succès, else sinon
         */
    unsigned int getIdMax() const {return id_max;}

    /*!
         *  \brief Permet de remettre à zero le solde de tout les compte dans l'arborescence
         */
    void solde_reset();

    /*!
         *  \brief Constructeur par défaut de la classe CompteManager
         */
    CompteManager();
};


#endif
