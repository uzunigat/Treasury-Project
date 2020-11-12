#ifndef VIEWALLTRANSFERT_H
#define VIEWALLTRANSFERT_H

#include <QDialog>
#include "addtransfertdialog.h"
#include "compte.h"
#include "transaction.h"

namespace Ui {
class ViewAllTransfert;
}

/*!
 *\class ViewAllTransfert
 *\brief Cette classe vous permet de Afficher tous les transactions du TransfertManager
 *\details
 */
class ViewAllTransfert : public QDialog
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur
         *  Constructeur de la classe ViewAllTransfert
         *  \param Item : Pointeur ver un QTreeWidgetItem
         *  \param cm : Pointeur vers le Compte Manager
         *  \param tm: Pointeur vers le Transaction Manager
         *  \param parent : pointeur vers le QWidget parent
         */
    explicit ViewAllTransfert(QTreeWidgetItem* Item, CompteManager* cm, TransactionManager* tm, QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class ViewAllTransfert
         */
    ~ViewAllTransfert();

    /*!
         *  \brief Accesseur de UserInterface
         *  Méthode permetant d'accéder à l'interface de la fenêtre "ViewAllTransfert"
         *  \return ui (UserInterface) du type Ui::ViewAllTransfert
         */
    Ui::ViewAllTransfert* getUi(){return ui;}

    /*!
         *  \brief Accesseur de treeItem
         *  Méthode permetant de retourner un QTreeWidgetItem*
         *  \return QTreeWidgetItem* qui point vers un element de QtreeWidget
         */
    QTreeWidgetItem* getTreeitem()const{return treeitem;}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void transaction_modified();

private:
    Ui::ViewAllTransfert *ui;
    QTreeWidgetItem* treeitem;
    CompteManager* cm;
    TransactionManager* tm;

};

#endif // VIEWALLTRANSFERT_H
