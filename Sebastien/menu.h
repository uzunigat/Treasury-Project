#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "compte.h"

#endif // MENU_H_INCLUDED

CompteAbstrait* recherche_compte(CompteVirtuel* dossier,std::string ID){
    return (dossier->GetCompte(ID));
}
