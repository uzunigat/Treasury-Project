#ifndef ADDTRANSFERTDIALOG_H
#define ADDTRANSFERTDIALOG_H

#include <QDialog>
#include <QTreeWidget>


struct Transfert{
    int id;
    double debit;
    double credit;
};

namespace Ui {
class AddTransfertDialog;
}

/*!
 *\class AddTransfertDialog
 *\brief Cette classe vous permet de Ajouter des Transactions à travers d'une interface graphique
 *\details
 */
class AddTransfertDialog : public QDialog
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur de la class AddTransfertDialog
         *  Constructeur de la class AddTransfertDialog
         *  \param tree: Un QTreeWidgetItem* ce qui permet d'afficher les comptes dans cette fenêtre
         *  \param parent: Un QWidget* qui pointe vers le QWidget parent
         */
    explicit AddTransfertDialog(QTreeWidgetItem* tree, QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class AddTransfertDialog
         */
    ~AddTransfertDialog();
    void accept();

    /*!
         *  \brief Accesseur de UserInterface
         *  Méthode permetant d'accéder à l'interface de la fenêtre "AddTransfert"
         *  \return ui (UserInterface) du type Ui::AddTransfertDialog
         */
    Ui::AddTransfertDialog* getUi(){return ui;}

    /*!
         *  \brief Accesseur du vecteur Transferts
         *  Méthode permetant d'accéder au vecteur des transferts
         *  \return Vector<transfert>
         */
    std::vector<Transfert> getTransfertVector(){return T;}

private slots:
    void on_pushButton_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item);

    void on_pushButton_2_clicked();

private:
    Ui::AddTransfertDialog *ui;
    std::vector<Transfert> T;

};


#endif // ADDTRANSFERTDIALOG_H
