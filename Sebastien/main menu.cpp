#include <iostream>
#include "compte.h"
#include "menu.h"
#include "transaction.h"


using namespace std;

int main(void)
{
    int choix;
    int choix2;
    string tmp_type,c_nom,c_type,ID;
    CompteAbstrait* tmp;
    double montant;
    bool choix_v;
    CompteManager cm;
    TransactionManager& tm = TransactionManager::getInstance();

    cm.Afficher();




    while (1){
        cout<<"-----Menu-----\n"<<"1 - Afficher les comptes\n"<<"2 - Creer un compte\n"<<"3 - Supprimer un compte\n"<<"4 - Crediter un compte\n"<<"5 - debiter un compte\n"<<"6 - Exit\n"<<"7 - efectuer une operation fixe \n";
        cin>>choix;
        cout<<"--------------\n";
        string ID;
        switch(choix)
        {
        case 1:
            cm.Afficher();
            break;
        case 2:
            cout<<"id du dossier ? \n";
            cin>>ID;
            cout<<"nom ? \n";
            cin>>c_nom;
            cout<<"type ? \n";
            cin>>c_type;
            cout<<"virtuel (1 ou 0) ? \n";
            cin>>choix_v;

            if (cm.creer_compte(ID,c_nom,c_type,choix_v)){
                cout<<"Creation réussie\n";
            }
            else{
                cout<<"Erreur creation\n";
            }


            break;
        case 3:
            cout<<"id ? \n";
            cin>>ID;
            if (cm.supprimer_compte(ID)){
                cout<<"suppression réussie\n";
            }
            else{
                cout<<"Erreur\n";
            }

            break;
        case 4:
            cout<<"id ? \n";
            cin>>ID;
            tmp=cm.GetCompte(ID);
            cout<<"montant ? \n";
            cin>>montant;
            tmp->crediter(montant);
            break;
        case 5:
            cout<<"id ? \n";
            cin>>ID;
            tmp=cm.GetCompte(ID);
            cout<<"montant ? \n";
            cin>>montant;
            tmp->debiter(montant);
            break;
        case 6:
            return 0;
            break;
        case 7:
            Date date;
            date.setDate(1,1,1);

            vector<Operation> vec;

            cout<<"Entrez le id de compte source de l'operation: \n";
            cin>>ID;
            tmp=cm.GetCompte(ID);

            Operation op(*tmp,0.0,100.0);
            cout<<"Debit: "<<op.getDebit()<< " Credit: "<<op.getCredit()<<endl;

            vec.push_back(op);

            cout<<"Entrez le id de compte destinataire de l'operation: \n";
            cin>>ID;
            tmp=cm.GetCompte(ID);

            Operation op2(*tmp,100.0, 0.0);

            cout<<"Debit: "<<op.getDebit()<< " Credit: "<<op.getCredit()<<endl;
            vec.push_back(op2);

            tm.ajouterTransaction(date,"1", "Test Transaction", vec);

        }

    }

}
