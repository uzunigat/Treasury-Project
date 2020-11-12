#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED
#include <iostream>
#include "compte.h"
#include "Date.h"
#include <string>
#include <vector>

class Transaction;




class Operation
{

    protected:

        std::string id_compte;
        double debit;
        double credit;

    public:

        double getCredit() const {return credit;}
        double getDebit() const {return debit;}
        std::string getId() const {return id_compte;}

        Operation(std::string& x,double y,double z):id_compte(x),debit(y),credit(z)
        {
            //std::cout<<"Operation: "<<id_compte<<" Debut."<<std::endl;
        };

        void effectuer_operation();

        ~Operation()
        {
            //std::cout<<"Operation: "<<id_compte<<" Fin."<<std::endl;
        }
};


class Transaction
{
    protected:
        Date date;
        std::string reference_operation;
        std::string memo;
        std::vector<Operation> operation;

        double somme_credits=0;
        double somme_debits=0;
    public:
        Transaction(Date d,std::string r,std::string m);

        Date getDate() const {return date;}
        std::string getMemo() const {return memo;}

        ~Transaction();

        bool verifier_transaction()
        {
            if (somme_credits==somme_debits){return true;}
            else {return false;}
        }

        void addCredit(double x){somme_credits+=x;};

        void addDedit(double x){somme_debits+=x;};
};

class TransactionManager{

    std::vector<Transaction*> transactions;
    std::string filename;

    struct Handler {

         TransactionManager* instance = nullptr;
         ~Handler() { delete instance; instance = nullptr; }
         Handler() = default;
    };

    static Handler handler;
    TransactionManager() = default;

    TransactionManager(const TransactionManager& tm) = delete;
    TransactionManager& operator=(const TransactionManager& tm) = delete;

public:

    static TransactionManager& getInstance();
    static void libererInstance();
    std::vector<Transaction*> getTransactions();
    void load();
    void save();
    bool ajouterTransaction(const Date d, const std::string& r, const std::string& m, std::vector<Operation> vop);
    ~TransactionManager() = default;

};

TransactionManager::Handler TransactionManager::handler = TransactionManager::Handler();


#endif
