#include <iostream>
#include <string>
#include "transaction.h"
#include "compte.h"

CompteManager cm;

void Operation::effectuer_operation()
{
    CompteAbstrait* compte;
    compte=cm.GetCompte(id_compte);
    compte->crediter(credit);
    compte->debiter(debit);
};



Transaction::Transaction(Date d,std::string r,std::string m):date(d),reference_operation(r),memo(m)
{
    // TEST
    int i=0;
    int j=1;
    while(j)
    {
        std::string tmp_id;
        int tmp_credit;
        int tmp_debit;
        std::cout<<"Veuillez entrer l ID d un compte"<<std::endl;
        std::cin>>tmp_id;
        std::cout<<"Veuillez entrer le credit"<<std::endl;
        std::cin>>tmp_credit;
        std::cout<<"Veuillez entrer le dedit"<<std::endl;
        std::cin>>tmp_debit;
        addCredit(tmp_credit);
        addDedit(tmp_debit);
        Operation tmp(tmp_id,tmp_credit,tmp_debit);
        operation.push_back(tmp);
        i++;
        if(i>2)
        {
            std::cout<<"Voulez vous entrer un autre compte pour la transaction? ( Yes=1 / No=0 )";
            std::cin>>j;
        }
    }
    // FINTEST
}

TransactionManager& TransactionManager::getInstance(){

     if (!handler.instance) handler.instance = new TransactionManager;
     return *handler.instance;

}

void TransactionManager::libererInstance(){

    delete handler.instance;
    handler.instance = nullptr;


}

