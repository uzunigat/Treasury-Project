#include <iostream>
#include <string>
#include "transaction.h"
#include "compte.h"

TransactionManager* TransactionManager::instance=nullptr;

bool TransactionManager::ajouterTransaction(const Date d, const std::string& r, const std::string& m, std::vector<Operation> vop){

    if(reference_valide(r)){
        Transaction trans(d, r, m, vop);
        transactions.push_back(trans);

        for (std::vector<Operation>::iterator it = vop.begin(); it != vop.end(); ++it) {

            if ((*it).getDebit() > 0)
                (*it).getCompte().debiter((*it).getDebit());
            else
                (*it).getCompte().crediter((*it).getCredit());

        }

        return true;
    }

    else

        return false;

}

bool Operation::Check(){


    if (debit == 0 && credit == 0){

            return false;

    }else{

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

            return true;

        }

  }

}

Transaction TransactionManager::chercherTransaction(const std::string& _ref) const{

    for (std::vector<Transaction>::const_iterator it = transactions.begin(); it != transactions.end(); ++it){

        if((*it).getReference() == _ref) return *it;

    }

}

bool TransactionManager::reference_valide(const std::string _ref) const{

    for (std::vector<Transaction>::const_iterator it = transactions.begin(); it != transactions.end(); ++it){

        if((*it).getReference() == _ref) return false;

    }

    return true;

}




