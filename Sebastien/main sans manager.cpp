#include <iostream>
#include "compte.h"
#include "menu.h"
using namespace std;

int main(void)
{
    int choix;
    int choix2;
    string tmp_type,c_nom,c_type;
    CompteAbstrait* tmp;
    double montant;

    CompteVirtuel root("Compte racine","RA1","Racine");
    root.Add(new CompteVirtuel("Actifs","A1","Actif")).Add(new CompteVirtuel("seb","A11","Actif")).Add(new Actif("Livret A","A111"));
    root.Add(new CompteVirtuel("Passifs","P1","Passif")).Add(new CompteVirtuel("seb","P11","Passif")).Add(new Passif("Capitaux propres","P111"));
    root.Add(new CompteVirtuel("Depenses","D1","Depense")).Add(new CompteVirtuel("seb","D11","Depense")).Add(new Depense("Achat de matériel","D111"));
    root.Add(new CompteVirtuel("Recettes","R1","Recette")).Add(new CompteVirtuel("seb","R11","Recette")).Add(new Recette("Cotisations","R111"));

    root.Afficher();

    while (1){
        cout<<"-----Menu-----\n"<<"1 - Afficher les comptes\n"<<"2 - Creer un compte\n"<<"3 - Supprimer un compte\n"<<"4 - Crediter un compte\n"<<"5 - debiter un compte\n"<<"6 - Exit\n";
        cin>>choix;
        cout<<"--------------\n";
        string ID;
        switch(choix)
        {
        case 1:
            root.Afficher();
            break;
        case 2:
            cout<<"id du dossier ? \n";
            cin>>ID;
            tmp=recherche_compte(&root,ID);

            if (tmp != nullptr){
                cout<<tmp->GetId()<<"\n";
            }
            else{
                cout<<"Aucun resultat"<<"\n";
            }

            if (dynamic_cast<CompteVirtuel*>(tmp)) {
                std::cout << "Type CompteVirtuel" << std::endl;
                tmp_type = tmp->getType();

                cout<<"nom ?\n";
                cin>>c_nom;
                cout<<"1 - Compte Virtuel\n"<<"2 - Compte reel\n";
                cin>>choix2;

                switch(choix2)
                {
                    case 1:
                        if (tmp_type.compare("Racine")==0){
                            cout<<"Type du compte ?";
                            cin>>c_type;
                            tmp->Add(new CompteVirtuel(c_nom,"RDM",c_type));
                        }
                        else{
                            tmp->Add(new CompteVirtuel(c_nom,"RDM",tmp_type));
                        }

                        break;
                    case 2:
                        if (tmp_type.compare("Racine")==0){
                            cout<<"Impossible de creer un compte à la racine\n";
                        }
                        if (tmp_type.compare("Actif")==0){
                            tmp->Add(new Actif(c_nom,"RDM"));
                        }
                        else if (tmp_type.compare("Passif")==0){
                            tmp->Add(new Passif(c_nom,"RDM"));
                        }
                        else if (tmp_type.compare("Recette")==0){
                            tmp->Add(new Recette(c_nom,"RDM"));
                        }
                        else if (tmp_type.compare("Depense")==0){
                            tmp->Add(new Depense(c_nom,"RDM"));
                        }
                        break;
                }

            }
            else{
                cout<<"Action impossible\n";
            }

            break;
        case 3:
            cout<<"id ? \n";
            cin>>ID;
            root.supprimer_compte(ID);
            break;
        case 4:
            cout<<"id ? \n";
            cin>>ID;
            tmp=recherche_compte(&root,ID);
            cout<<"montant ? \n";
            cin>>montant;
            tmp->crediter(montant);
            break;
        case 5:
            cout<<"id ? \n";
            cin>>ID;
            tmp=recherche_compte(&root,ID);
            cout<<"montant ? \n";
            cin>>montant;
            tmp->debiter(montant);
            break;
        case 6:
            return 0;
            break;
        }

    }

}
