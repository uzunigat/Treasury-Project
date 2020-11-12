#include <iostream>
#include "compte.h"
#include "transaction.h"
using namespace std;

int main(int argc, char *argv[])
{
    int choix,ID,J,M,A;
    int menu=1;
    string tmp_type,c_nom,c_type,nom,date,desc;
    CompteAbstrait* tmp;
    double debit,credit,montant;
    bool choix_v,op;
    CompteManager cm;
    TransactionManager tm;
    Operation* operation;

    cm.creer_compte(0,"Actif","Actif",1);//1
    cm.creer_compte(0,"Passif","Passif",1);//2
    cm.creer_compte(0,"Recette","Recette",1);//3
    cm.creer_compte(0,"Depense","Depense",1);//4

    cm.creer_compte(1,"Actif","Actif",0);//5
    cm.creer_compte(2,"Passif","Passif",0);//6
    cm.creer_compte(3,"Recette","Recette",0);//7
    cm.creer_compte(4,"Depense","Depense",0);//8

    cm.creer_compte(0,"Passif","Passif",0);//9



    Transaction* t = tm.creerTransaction(2020,10,10,"R1","Sub");
    t->add(0,100,cm.GetCompte(7));
    t->add(100,0,cm.GetCompte(5));
    tm.ajouter_transaction(t);

    t = tm.creerTransaction(2020,11,10,"R1","Sub");
    t->add(0,100,cm.GetCompte(7));
    t->add(100,0,cm.GetCompte(5));
    tm.ajouter_transaction(t);

    t = tm.creerTransaction(2020,11,11,"R1","Sub");
    t->add(0,100,cm.GetCompte(7));
    t->add(100,0,cm.GetCompte(5));
    tm.ajouter_transaction(t);

    t = tm.creerTransaction(2020,9,10,"R1","Sub");
    t->add(100,0,cm.GetCompte(7));
    t->add(0,100,cm.GetCompte(8));
    cout<<"nb operation test: "<<t->getSize()<<endl;
    tm.ajouter_transaction(t);

    tmp = cm.GetCompte(5);
    tmp->rapprocher(2021,10,10,"rapprochement","test");
    tmp->afficher_rapprochement();

    cm.Afficher();



    while (1){
        switch(menu)
        {
        case 1: //Menu comptes
            cout<<"-----Menu-----\n"<<"1 - Afficher les comptes\n"<<"2 - Creer un compte\n"<<"3 - Supprimer un compte\n"<<"4 - Crediter un compte\n"<<"5 - debiter un compte\n"<<"6 - solde reset\n"<<"7 - Menu Transfert\n"<<"8 - Exit\n";
            cin>>choix;
            cout<<"--------------\n";

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
                tm.recalculer_solde(cm);
                break;

            case 7:
                menu=2;
                break;

            case 8:
                return 0;
                break;
            }
        break;


        case 2: //Menu transferts
            cout<<"-----Menu-----\n"<<"1 - Afficher les transfert\n"<<"2 - Creer transfert\n"<<"3 - Modifier transaction\n"<<"4 - Supprimer transaction\n"<<"5 - liste opérations\n"<<"6 - Rapprocher\n"<<"7 - Afficher rapprochement\n"<<"8 - Menu Compte\n"<<"9 - Exit\n";
            cin>>choix;
            cout<<"--------------\n";
            switch(choix)
            {
            case 1:
                tm.afficher();
                break;

            case 2:
                cout<<"nom ? \n";
                cin>>nom;
                cout<<"Date \n";
                cout<<"J :";
                cin>>J;
                cout<<"M :";
                cin>>M;
                cout<<"A :";
                cin>>A;
                t = tm.creerTransaction(A,M,J,"R",nom);
                op=1;
                cout<<"Operation : \n";

                while(op==1){
                    cout<<"Compte (id)? : \n";
                    cin>>ID;
                    cout<<"Credit ? : \n";
                    cin>>credit;
                    cout<<"Debit ? : \n";
                    cin>>debit;

                    try {
                       t->add(credit,debit,cm.GetCompte(ID));
                    } catch (...) {
                        cerr<<"Operation non valide\n";
                    }

                    cout<<"Continuer 1 arreter 0 \n";
                    cin>>op;
                }
                tm.ajouter_transaction(t);
                break;

            case 3:
                cout<<"id transaction ?\n";
                cin>>ID;
                t = tm.retirer_transaction(ID);
                if (t==nullptr) {cout<<"Transaction inexistante\n";break;}
                t->afficher();
                cout<<"opération ?\n";
                cin>>ID;
                operation = t->recherche_op(ID);
                operation->afficher();
                cout<<"credit ?\n";
                cin>>credit;
                operation->setCredit(credit);
                cout<<"debit ?\n";
                cin>>debit;
                operation->setDebit(debit);

                break;

            case 4:
                cout<<"id transaction ?\n";
                cin>>ID;
                tm.supprimer_transaction(ID);
                break;

            case 5:
                cout<<"id compte ?\n";
                cin>>ID;
                cm.GetCompte(ID)->Afficher_operation();
                break;

            case 6:
                cout<<"id compte ?\n";
                cin>>ID;
                cout<<"Date \n";
                cout<<"J :"<<endl;
                cin>>J;
                cout<<"M :"<<endl;
                cin>>M;
                cout<<"A :"<<endl;
                cin>>A;
                cout<<"nom :"<<endl;
                cin>>nom;
                cout<<"desc :"<<endl;
                cin>>desc;
                tmp = cm.GetCompte(ID);
                tmp->rapprocher(A,M,J,nom,desc);
                tmp->afficher_rapprochement(0);
                break;

            case 7:
                cout<<"id compte ?\n";
                cin>>ID;
                cm.GetCompte(ID)->afficher_rapprochement();

            case 8:
                menu=1;
                break;

            case 9:
                return 0;
                break;
            }

        break;
        }
    }
}

