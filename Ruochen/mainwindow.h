
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QDomElement>
#include <QFile>
#include <QPrinter>
#include <QPainter>


#include "addcomptedialog.h"
#include "choisirpassifdialog.h"
#include "addtransfertdialog.h"
#include "viewalltransfert.h"
#include "rapprochementdialog.h"
#include "saisirrapprochementdialog.h"

#include "compte.h"
#include "transaction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 *\class MainWindow
 *\brief Cette classe est utilisée pour gérer la fenêtre principale du programme
 *\details
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur de la class MainWindow
         *  Constructeur de la class MainWindow
         *  \param parent: Un QWidget* qui pointe vers le QWidget parent
         */
    MainWindow(QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class MainWindow
         */
    ~MainWindow();

    /*!
         *  \brief Accesor a las etiquetas de un archivo de cuentas xml
         *  Méthode pour lire une liste d'étiquettes de compte en extrayant leurs attributs
         *  \param docElem: élement qui contient un objet du type QDomElement& pour connaitre un element du fichier
         *  \param first_time: Attribut qui nous permet de savoir si c'est la prémier foir qu'on appel la méthode
         */
    void listDom(QDomElement& docElem,bool first_time);

    /*!
         *  \brief Ouvrir fichier Comptes.xml
         *  Méthode pour lire un fichier Comptes.xml sous un format spécial
         *  \param filename: path du fichier xml à lire
         *  \param first_load: Attribut qui nous permet de savoir si c'est la prémier foir qu'on appel la méthode
         */
    void openXML(QString fileName,bool first_load);

    /*!
         *  \brief Ouvrir fichier Transactions.xml
         *  Méthode pour lire un fichier Transactions.xml sous un format spécial
         *  \param filename: path du fichier xml à lire
         *  \param first_load: Attribut qui nous permet de savoir si c'est la prémier foir qu'on appel la méthode
         */
    void openXMLTransactions(QString fileName,bool first_load);

    /*!
         *  \brief Ouvrir fenêtre "AddWindow"
         *  Méthode pour ouvrir une nouvelle fenêtre pour saisir les parametres du compte a ajouter
         *  \param father_id: Permet de connaitre l'id du compte parent sélectionné
         *  \param type: Permet de connaître le type de compte sélectionné
         */
    void popAddWindow(QString father_id, QString type);

    /*!
         *  \brief Ouvrir fenêtre "Rapprochement"
         *  Méthode pour ouvrir une nouvelle fenêtre pour saisir les parametres du compte a rapprocher
         *  \param father_id: Permet de connaitre l'id du compte parent sélectionné
         *  \param type: Permet de connaître le type de compte sélectionné
         */
    void popRapprochementWindow(QString id);


    /*!
         *  \brief Ouvrir fenêtre "Saisir Rapprochement"
         *  Méthode pour ouvrir une nouvelle fenêtre pour génerer un rapprochement
         *  \param id: Permet de connaitre l'id du compte sélectionné
         */
    void popSaisirRapprochement(QString id);

    /*!
         *  \brief Ajouter
         *  Méthode pour
         *  \param father_id:
         *  \param type:
         */
    void AddXml() const;

    /*!
         *  \brief Enlever une compte directement du fichier XML
         *  Méthode pour supprimer une Compte directement du fichier XML
         *  \param id: id du compte à supprimer
         */
    void deleteXML(QString id) const;

    /*!
         *  \brief Ajouter un élément à un QTreeWidget
         *  Méthode qui permet d'ajouter un compte, à partir d'un id, nom, prop, type et solde un élement dans un objet du type QTreeWidget
         *   \param father_id: id du compte parent à ajouter
         *   \param id: id du compte à ajouter
         *   \param nom: nom du compte à ajouter
         *   \param prop: propriété (Virtuel ou pas) du compte à ajouter
         *   \param type: type (Actif, Passif, Recette, Depense) du compte à ajouter
         *   \param solde: solde du compte à ajouter
         */
    void addToTree(QString father_id, QString id, QString nom, QString prop, QString type, QString solde=NULL);

    /*!
         *  \brief Enlever un élément à un QTreeWidget
         *  Méthode qui permet d'enlever un compte, à partir d'un id, un élement dans un objet du type QTreeWidget
         *   \param id: id du compte à ajouter
         */
    void deleteFromTree(const QString id);

    /*!
         *  \brief Ouvrir fenetre "PassifWindow"
         *  Méthode pour ouvrir une nouvelle fenêtre pour saisir les parametres du compte a ajouter
         */
    void PopChoisirPassifWindow();

    /*!
         *  \brief Écrire Comptes.xml
         *   Méthode qui permet d'écrire dans un fichier Comptes.xml les balises avec ses attributs sous un format donné
         *   \param filename: path du fichier Comptes.xml
         */
    void writeXmlFile_attributes(const QString& filename);

    /*!
         *  \brief Écrire Transactions.xml
         *   Méthode qui permet d'écrire dans un fichier Transactions.xml les balises avec ses attributs sous un format donné
         *   \param filename: path du fichier Comptes.xml
         */
    void writeXmlFile_subnodes(const QString& filename);

    /*!
         *  \brief Dessiner header du PDF
         *   Méthode qui permet de dessiner dans un objet du type Painter un header pour afficher un pdf
         *   \param painter: Un objet du type Painter sur lequel on va écrire le header du PDF
         */
    void print_header_transactios(QPainter& painter);

    /*!
         *  \brief Dessiner header du PDF pour un rapprochement
         *   Méthode qui permet de dessiner dans un objet du type Painter un header pour afficher un pdf
         *   \param painter: Un objet du type Painter sur lequel on va écrire le header du PDF
         */
    void print_header_rapprochement(QPainter& painter);

    /*!
         *  \brief Écrire opérations dans un PDF
         *   Méthode qui permet d'écrire dans un PDF une liste des opérations à partir d'une transaction
         *   \param printer: Un objet du type Printer
         *   \param painter: Un objet du type Painter sur lequel on va écrire
         *   \param trans: Un objet du type Transaction* qui contient la liste des opérations à afficher
         */
    void operations_PDF(QPrinter& printer, QPainter& painter, Transaction* trans);

    /*!
         *  \brief Écrire rapprochement dans un PDF
         *   Méthode qui permet d'écrire dans un PDF une liste des opérations rapprochés
         *   \param rap: Rapprochement&
         */
    void rapprochement_PDF(Rapprochement* rap);

    /*!
         *  \brief Écrire opérations dans un PDF
         *   Méthode qui permet d'écrire dans un PDF une liste des opérations à partir d'une transaction et un id
         *   \param printer: Un objet du type Printer
         *   \param painter: Un objet du type Painter sur lequel on va écrire
         *   \param trans: Un objet du type Transaction* qui contient la liste des opérations à afficher
         *   \param id: Un objet du type String qui permet de créer un filter pour afficher uniquement les transactions associés à un id du compte
         */
    void operations_PDF(QPrinter& printer, QPainter& painter, Transaction* trans, std::string id);



    void setNom_first(QString n){nom_actif_first = n;}
    const QString getNom_first() const{return nom_actif_first;}

    void setSolde_first(double s){solde_actif_first = s;}
    QString getSolde_first() const{return QString::number(solde_actif_first);}

    void setId_first(QString id) {id_father_first= id;}
    QString getId_first() const{return id_father_first;}

    /*!
         *  \brief Créer une cloture
         *   Méthode qui permet de faire une clôture des comptes
         */
    bool cloture();


private:
    Ui::MainWindow *ui;
    QString filename;
    AddCompteDialog *AddWindow;
    ChoisirPassifDialog *ChoisirPassifWindow;
    AddTransfertDialog* AddTransfertWindow;
    Rapprochementdialog* rapWindow;
    SaisirRapprochementDialog* saiRapWin;

    ViewAllTransfert* viewTransfertWindow;

    CompteManager* cm;
    TransactionManager* tm;

    int count_compte = 1;

    const QString compte_tmp = "Compte_tmp.xml";
    const QString transfert_tmp = "Transfert_tmp.xml";

    int ligne;

    bool create_actif;
    double montant_initial;
    int id_selected;
    bool no_passif = false;

    QString nom_actif_first;
    double solde_actif_first;
    QString id_father_first;

private slots:
    void on_actionNew_triggered();
    void on_actionAdd_account_triggered();
    void on_actionOpen_triggered();
    void Add_accepted();
    void on_actionDelete_Account_triggered();

    void on_actionSave_as_triggered();
    void on_actionClosure_triggered();

    void on_actionRapprochement_triggered();
    void handlePassifAccepted(QString);
    void on_actionAdd_Transation_triggered();
    void on_actionShow_all_transation_triggered();
    void on_actionFor_transferts_triggered();
    void on_actionTransferts_for_one_account_triggered();

    void addWindow_finished(int result);

    void refresh_transaction();
    void on_actionTransferts_par_Rapprochement_triggered();
};





#endif // MAINWINDOW_H
