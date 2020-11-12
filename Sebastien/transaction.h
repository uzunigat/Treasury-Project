#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED
#include <iostream>
#include "compte.h"
#include "timinig.h"
#include <string>
#include <vector>
#include "compte.h"


class Transaction;

using namespace TIME;
/*!
 *\class Operation
 *\brief Elle représente les triplets utilisés dans la classe Transaction 
 *\details Cette classe va nous permettre de stocker les informations relatives aux comptes prenants dans une transaction, notamment le débit, le crédit ainsi que le compte respectif auquel s'appliquera l'opération dans le contexte de la transaction
 */
class Operation
{
    private:

        CompteAbstrait& compte;
        double debit;
        double credit;

    public:

        double getCredit() const {return credit;}
        double getDebit() const {return debit;}
        CompteAbstrait& getCompte() const {return compte;}

        Operation(CompteAbstrait& _compte,double _debit,double _credit):compte(_compte),debit(_debit),credit(_credit){ if(Check()) std::cout<< "Bien crée\n"; else std::cout<<"Mal crée\n";};

        bool Check();

};

/*!
 *\class Transaction
 *\brief Elle sert à modéliser une transaction
 *\details Cette classe prend en paramètre la date, la référence, une memo et le vecteur d'opérations dont consiste la transaction
 */
class Transaction
{
    private:
        Date date;
        std::string reference_operation;
        std::string memo;
        std::vector<Operation> operations;

    public:

        Transaction(Date _date,std::string _reference_operation,std::string _memo, std::vector<Operation> _operations): date(_date), reference_operation(_reference_operation), memo(_memo), operations(_operations){};

        Date getDate() const {return date;}

        std::string getMemo() const {return memo;}

        std::string getReference() const {return reference_operation;}

        std::vector<Operation> getOperations() const {return operations;}

        int getTaille(){return operations.size();}
};

/*!
 *\class TransactionManager
 *\brief Elle gère tout ce qui est en relation avec les transactions
 *\details Cette classe s'occupe du stockage, de la création ainsi que la vérification des transactions saisies par l'utilisateur
 */
class TransactionManager{

    static TransactionManager* instance;
    std::vector<Transaction> transactions;
    std::string filename;

public:

    TransactionManager()=default;

    static TransactionManager& getInstance(){

            if(!instance) instance = new TransactionManager;

            return *instance;

    };

    static bool libererInstance(){

         if(instance) {

            delete instance;
            return true;

    }

    return false;

    };

    std::vector<Transaction> getTransactions()const {return transactions;};
    bool ajouterTransaction(const Date d, const std::string& r, const std::string& m, std::vector<Operation> vop);
    Transaction chercherTransaction(const std::string& _ref) const;
    bool reference_valide(const std::string _ref) const;

};

#endif
