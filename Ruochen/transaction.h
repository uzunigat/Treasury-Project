/**
\file transaction.h
\date 17/06/2020
\version 1
\brief  Fichier de classe transaction

Ce fichier inclu les différentes classes liées aux transactions.


**/


#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <QDate>
#include <QMultiMap>

class Transaction;
class Compte;
class CompteAbstrait;
class Rapprochement;
class CompteManager;

/*!
 *\class Operation
 *\brief Conteneur d'informations sur une opération concernant un "Compte réel"
 *\details Cette classe va nous permettre de stocker les informations relatives aux comptes prenants dans une transaction, notamment le débit, le crédit ainsi que le compte respectif auquel s'appliquera l'opération dans le contexte de la transaction
 */
class Operation
{
    private:
        int id;
        double debit,credit;
        Compte* compte;
        Transaction* transaction;
        QString intitule;

        /*!
         * \brief Pointeur de Rapprochement différent de nullptr quand opération est rapprochée
         */
        Rapprochement* rapprochement=nullptr;

        /*!
         * \details seule une transaction possède le droit de créer une opération.
         */
        friend class Transaction;
        /*!
             *  \brief Constructeur
             *  \details Constructeur de la classe Opération
             *  \param id : identifiant opération (clé locale à une transaction)
             *  \param debit : montant à débiter
             * \param credit : montant à créditer
             * \param C : pointeur du compte réel sur lequel est appliquée l'opération
             * \param T : pointeur vers la transaction à laquelle appartient l'opération
             * \param intitule : description de l'opération
             */
        Operation(int id,double debit,double credit,Compte* C,Transaction* T,QString intitule=""):id(id),debit(debit),credit(credit),compte(C),transaction(T),intitule(intitule){};

        /*!
             * \brief destruction du constructeur de recopie, une opération ne peut exister que par le biais une transaction
             */
        Operation(const Operation&) = delete;

    public:

        /*!
             *  \brief Vérifier la validité
             *  Méthode qui permet de vérifier la validité d'une opération en respectant les régles
             *  \return True si l'opération est valide, False sinon
             */
        bool Check();

        /*!
             *  \brief Getter crédit
             *  Méthode qui retourne le credit de l'opération
             *  \return retourne le crédit de l'opération du type double
             */
        double getCredit() const {return credit;}

        /*!
             *  \brief Getter Debit
             *  Méthode qui retourne le debit de l'opération
             *  \return retourne le debit de l'opération du type double
             */
        double getDebit() const {return debit;}

        /*!
             *  \brief Getter Raprochement
             *  Méthode qui retourne le raprochement de l'opération
             *  \return retourne le raprochement du type Raprochement*
             */
        Rapprochement* getRapprochement() const {return rapprochement;}

        /*!
             *  \brief Setter Credit
             *  Méthode qui permet de saisir le credit d'une opération
             *  \param cr: crédit à mettre dans l'opération
             */
        void setCredit(double cr){credit=cr;}

        /*!
             *  \brief Setter Debit
             *  Méthode qui permet de saisir le debit d'une opération
             *  \param db: debit à mettre dans l'opération
             */
        void setDebit(double db){debit=db;}

        /*!
             *  \brief Setter Rapprochement
             *  Méthode qui permet de saisir le Rapprochement d'une opération
             *  \param rp: Raprochement à mettre dans l'opération du type Rapprochement*
             */
        void setRapprochement(Rapprochement* rp){rapprochement=rp;}

        /*!
             *  \brief Getter id
             *  Méthode qui permet de retourner l'id d'une opération
             *  \return retourne l'id d'une opération
             */
        int getId() const {return id;}

        /*!
             *  \brief Getter compte
             *  Méthode qui permet de retourner le compte auquel une opération est associée
             *  \return retourne l'id d'une opération
             */
        Compte& getCompte() const {return *compte;}

        /*!
             *  \brief Getter transaction
             *  Méthode qui permet de retourner le Transaction auquel une opération est associée
             *  \return retourne l'id d'une opération
             */
        Transaction& getTransaction() const {return *transaction;}

        /*!
             *  \brief is_frozen
             *  Méthode qui permet de retourner True si une opération est gelée et False sinon
             *  \return True si l'opération est gelée et False sinon
             */
        bool is_frozen(){return rapprochement!=nullptr;}

        /*!
             *  \brief Afficher une opération
             *  Méthode qui permet d'afficher une opération
             */
        void afficher();

        /*!
             *  \brief Destructeur
             *  Destructeur de la class Opération
             */
        ~Operation();
};

/*!
 *\class Transaction
 *\brief Conteneur d'opérations et d'informations
 *\details Cette classe prend en paramètre la date, la référence, une memo et le vecteur d'opérations dont consiste la transaction
 */
class Transaction: private std::vector<Operation*>
{
    private:
        /*!
         * \brief identifiant de la transaction
         */
        int id;

        /*!
         * \brief Compteur d'id à sassigner aux opérations générées
         */
        int id_op=0;

        /*!
         * \brief Date de la transaction
         */
        QDate date;

        /*!
         * \brief reference de la transaction
         */
        std::string reference;

        /*!
         * \brief note à ajouter sur la transaction
         */
        std::string memo;

        /*!
         * \brief définition du nom du vecteur d'opération
         */
        using operations = std::vector<Operation*> ;

    public:

        /*!
             *  \brief Constructeur
             *  Constructeur de la classe Transaction
             *  \param idmax : idMax du Transaction
             *  \param y : Année de création
             *  \param m: Mois de création
             *  \param d : Jour de création
             *  \param ref: Reference de la Transaction
             *  \param _memo: Intitule de la Transaction
             */
        Transaction(int idmax, int y, int m, int d,std::string ref,std::string _memo):id(idmax),date(y,m,d),reference(ref),memo(_memo){}

        /*!
             *  \brief Ajouter opération
             *  Permet d'ajouter une opérations dans une transaction
             *  \param debit : debit de l'opération
             *  \param credit : credit de l'opération
             *  \param compte: Compte associé à l'opération
             *  \param intitule : intitule de l'opération
             *  \return l'opération crée du type Operation&
             */
        Operation& add(double debit,double credit, CompteAbstrait* compte, QString intitule="");

        /*!
             *  \brief Getter id
             *  Méthode qui permet de retourner l'id d'une transaction
             *  \return retourne l'id d'une opération
             */
        int getId(){return id;}

        /*!
             *  \brief Getter Reference
             *  Méthode qui permet de retourner la reference d'une transaction
             *  \return retourne la reference du transaction
             */
        const std::string& getReference() const {return reference;}

        /*!
             *  \brief Getter Date
             *  Méthode qui permet de retourner la date d'une transaction
             *  \return retourne la date d'une transaciton du type QDate
             */
        QDate getDate() const {return date;}

        /*!
             *  \brief Getter memo
             *  Méthode qui permet de retourner le memo d'une transaction
             *  \return retourne le memo d'une transaciton du type string
             */
        std::string getMemo() const {return memo;}

        /*!
             *  \brief Vérifier la validité
             *  Méthode qui permet de vérifier la validité d'une transaction
             *  \return True si la somme des débits de chaque opération est égal au somme de credits des tous les opérations, False sinon
             */
        bool Check() const;

        /*!
             *  \brief Afficher une transaction
             *  Méthode qui permet d'afficher une transaction
             */
        void afficher();

        /*!
             *  \brief Supprimer une opération
             *  Méthode qui permet de supprimer une opération
             *  \param id: id de l'opération à supprimer
             *  \return True s'il a réussi à supprimer l'opération False sinon
             */
        bool supprimer_op(int id);

        /*!
             *  \brief Chercher une opération
             *  Méthode qui permet de chercher une opération
             *  \param id: id de l'opération à rechercher
             *  \return Operation du type Operation*
             */
        Operation* recherche_op(int id);

        /*!
             *  \brief Destructeur
             *  Destructeur de la class Transaction
             */
        ~Transaction();

        /*!
             *  \brief Retourne le nombre des opération
             *  Méthode qui permet de retourner la taille du transaction
             *  \return taille de la transaction du type int
             */
        int getSize(){return size();}

        /*!
             *  \brief Retourne si la transaction est gelée
             *  Méthode qui permet de savoir si une transaction en gelée
             *  \return True si un des opérations est gelée, False sinon
             */
        bool is_frozen();



        using operations::begin;
        using operations::end;
};

/*!
 *\class TransactionManager
 *\brief Gestionnaire de transactions
 *\details Cette classe s'occupe du stockage, de la création ainsi que la vérification des transactions saisies par l'utilisateur
 */
class TransactionManager : private QMultiMap<QDate, Transaction*>{


    std::string filename;
    int id_max=0;

    /*!
     * \brief Multimap de transaction de clé date, permet de trier les éléments par date
     */
    using ListeTransaction = QMultiMap<QDate, Transaction*>;

public:

    /*!
         *  \brief Constructeur
         *  Constructeur de la classe TransactionManager
         */
    TransactionManager()=default;

    /*!
         *  \brief Creer une Transaction
         *  Méthode qui permet de creer une Transactio
         *  \param y : Année de création
         *  \param m: Mois de création
         *  \param d : Jour de création
         *  \param ref: Reference de la Transaction
         *  \param _memo: Intitule de la Transaction
         *  \return Retourne la Transaction géneré vide du type Transaction*
         */
    Transaction* creerTransaction(int y, int m, int d, const std::string& ref, const std::string& memo);

    /*!
         *  \brief Ajoute une transaction au Transfert Manager
         *  Méthode qui permet d'ajouter une transaction au TransfertManager en créditant et débitant chaque compte
         *  \param transaction: Transaction à ajouter
         *  \return Retourne True si la transaction est bien ajouté et False sinon
         */
    bool ajouter_transaction(Transaction* transaction);

    /*!
         *  \brief Ajoute une transaction au Transfert Manager
         *  Méthode qui permet d'ajouter une transaction au TransfertManager sans créditer ni débiter les comptes associés
         *  \param transaction: Transaction à ajouter
         *  \return Retourne True si la transaction est bien ajouté et False sinon
         */
    bool ajouter_transaction2(Transaction* transaction);

    /*!
         *  \brief Afficher tous les transactions
         *  Méthode qui permet d'afficher tous les transactions
         */
    void afficher() const;

    /*!
         *  \brief Supprimer une transaction
         *  Méthode qui permet de supprimer une transaction
         *  \param id: id du transaction à supprimer
         *  \return True si la Transaction est bien suprimé, False sinon
         */
    bool supprimer_transaction(int id);

    /*!
         *  \brief Retirer une transaction
         *  Méthode qui enlève une transaction du transaction manager et annule ses opération sans la supprimer (renvoi un pointeur de transaction)
         *  \param id: id du transaction à retirer
         *  \return Transaction*
         */
    Transaction* retirer_transaction(int id);

    /*!
         *  \brief Rechercher une transaction
         *  Méthode qui cherche une transaction à partir de l'id du transaction
         *  \param id: id du transaction à rechercher
         *  \return Transaction*
         */
    Transaction* recherche_transaction(int id);

    /*!
         *  \brief Verification de reference
         *  Méthode qui cherche dans la liste des transactions si une réference est valide ou pas
         *  \param ref: reference à valider dans la liste des transactions
         *  \return True si la réference n'est pas répeté, False sinon
         */
    bool verifierReference(const std::string ref);

    /*!
         *  \brief Recalculer le solde des Transactions
         *
         *  \param cm: reference à valider dans la liste des transactions
         */
    void recalculer_solde(CompteManager& cm);

    /*!
         *  \brief Getter d'idMax du TransfertManager
         *  Méthode qui retourne l'idMax des transaction (La taille des transactions)
         *  \return Taille des transactions du type int
         */
    int getidmax(){return id_max;}

    //redéclaration en public des méthodes de Qmultimap
    using ListeTransaction::begin;
    using ListeTransaction::end;

};

/*!
 *\class Rapprochement
 *\brief Le rapprochement d'un Compte consiste à figer des transactions passées.
 *\details Cette classe permet de comparer les opérations saisies dans le logiciel avec les opérations effectuées
réellement sur le compte bancaire
 */
class Rapprochement {
    /*!
     * \brief identifiant d'un rapprochement
     */
    int id;

    /*!
     * \brief date du rapprochement
     */
    QDate date;

    /*!
     * \brief nom du rapprochement
     */
    std::string nom;

    /*!
     * \brief description du rapprochement
     */
    std::string desc;

    /*!
     * \brief pointeur vers le compte rapproché
     */
    Compte* compte;

    /*!
     * \brief solde sauvegardé au moment du rapprochement
     */
    double solde;

    //passage en privé des construceurs destructeurs et opérateur d'affectation
    Rapprochement()=default;
    Rapprochement(const Rapprochement&) = delete;
    Rapprochement& operator=(const Rapprochement& tm) = delete;
public:
    static int id_max;

    /*!
         *  \brief Constructor de la class Rapprochement
         *  Méthode qui permet de créer un rapprochement
         *  \param date : Date de la création du rapprochement
         *  \param nom: Nom du rapprochement
         *  \param desc : Description du rapprochement
         *  \param compte: Compte a rapprocher
         *  \param solde: Solde du rapprochement
         */
    Rapprochement(QDate date,std::string nom, std::string desc, Compte* compte, double solde):id(id_max++),date(date),nom(nom),desc(desc),compte(compte),solde(solde){}

    /*!
         *  \brief Afficher une Rapprochement
         *  Méthode qui permet d'afficher un raprochement
         */
    void Afficher();

    /*!
         *  \brief Getter date
         *  Méthode qui permet de retourner la date du rapprochement
         */
    QDate getDate(){return date;}

    /*!
         *  \brief Getter Nom
         *  Méthode qui permet de retourner le nom du rapprochement
         */
    std::string getNom(){return nom;}

    /*!
         *  \brief Getter Description
         *  Méthode qui permet de retourner la description du rapprochement
         */
    std::string getDesc(){return desc;}

    /*!
         *  \brief Setter Solde
         *  Méthode qui permet de saisir le solde du rapprochement
         */
    void setSolde(double s){solde=s;}

    /*!
         *  \brief Getter id
         *  Méthode qui permet de retourner l'a description'id du rapprochement
         */
    int getId(){return id;}

    /*!
         *  \brief Getter compte
         *  Méthode qui permet de retourner la compte associé au rapprochement
         */
    Compte* getCompte() const {return  compte;}

    /*!
         *  \brief Getter solde
         *  Méthode qui permet de retourner le solde associé au rapprochement
         */
    double getSolde() const {return solde;}

};







#endif
