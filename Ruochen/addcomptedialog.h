#ifndef ADDCOMPTEDIALOG_H
#define ADDCOMPTEDIALOG_H

#include <QDialog>

namespace Ui {
class AddCompteDialog;
}

/*!
 *\class AddCompteDialog
 *\brief Cette classe vous permet de gérer la génération d'un compte
 *\details
 */

class AddCompteDialog : public QDialog
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur
         *  Constructeur de la classe AddCompteDialog
         *  \param parent : pointeur vers le QWidget parent
         */

    explicit AddCompteDialog(QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class AddCompteDialog
         */

    ~AddCompteDialog();

    /*!
         *  \brief Accesseur de Id Parent
         *  Méthode permetant d'acceder au Id parent
         *  \return id du parent du type QString
         */
    const QString getFatherId() const{return father_id;}

    /*!
         *  \brief Accesseur de Propriété
         *  Méthode permetant d'acceder au Propriété (Virtuel ou pas) du compte
         *  \return Propriété du compte du type QString
         */
    QString getProp() const{return prop;}

    /*!
         *  \brief Accesseur de Type
         *  Méthode permetant d'acceder au Type (Actif, Passif, Recette, Depense) du compte
         *  \return Type du compte du type QString
         */
    QString getType() const{return type;}

    /*!
         *  \brief Accesseur de Id
         *  Méthode permetant d'acceder au Id du compte
         *  \return id du compte du type QString
         */
    QString getId() const{return id;}

    /*!
         *  \brief Accesseur de Nom
         *  Méthode permetant d'acceder au nom du compte
         *  \return Nom du compte du type QString
         */
    const QString getNom() const{return nom;}

    /*!
         *  \brief Accesseur de Solde
         *  Méthode permetant d'acceder au solde du compte
         *  \return Solde du compte du type QString
         */
    QString getSolde() const{return QString::number(solde);}

    /*!
         *  \brief Setter de id Parent
         *  Méthode permetant de modifier l'id du compte parent
         *  \param id: id du parent du type QString pour remplacer l'actuel
         */
    void setFatherId(QString id){father_id = id;}

    /*!
         *  \brief Setter de Propriété
         *  Méthode permetant de modifier la propriété du compte
         *  \param p: Propriété (Virtuel ou pas) du compte du type QString pour remplacer l'actuel
         */
    void setProp(QString p){prop = p;}

    /*!
         *  \brief Setter de Id
         *  Méthode permetant de modifier l'id du compte
         *  \param id: id du compte du type QString pour remplacer l'actuel
         */
    void setId(QString id) {this->id= id;}

    /*!
         *  \brief Setter de Nom
         *  Méthode permetant de modifier le nom du compte
         *  \param n: nom du compte du type QString pour remplacer l'actuel
         */
    void setNom(QString n){nom = n;}

    /*!
         *  \brief Setter de Solde
         *  Méthode permetant de modifier le solde du compte
         *  \param s: solde du compte du type QString pour remplacer l'actuel
         */
    void setSolde(double s){solde = s;}

    /*!
         *  \brief Setter de Type
         *  Méthode permetant de modifier le type du compte
         *  \param t: type du compte (Actif, Passif, Recette, Depense) du type QString pour remplacer l'actuel
         */
    void setType(QString t){type = t;}

    /*!
         *  \brief Accesseur de UserInterface
         *  Méthode permetant d'accéder à l'interface de la fenêtre "AddCompte"
         *  \return ui (UserInterface) du type Ui::AddCompteDialog
         */
    Ui::AddCompteDialog * getUi(){return ui;}
    void accept();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox2_currentIndexChanged(int index);


private:
    Ui::AddCompteDialog *ui;
    QString father_id;
    QString id;

    QString prop;
    QString type;

    QString nom;
    double solde;

    QString filename;
};

#endif // ADDCOMPTEDIALOG_H
