#ifndef RAPPROCHEMENTDIALOG_H
#define RAPPROCHEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class Rapprochementdialog;
}


/*!
 *\class Rapprochementdialog
 *\brief Cette classe est utilisée pour génerer un rapprochement des comptes
 *\details
 */
class Rapprochementdialog : public QDialog
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur de la class Rapprochementdialog
         *  Constructeur de la class Rapprochementdialog
         *  \param parent: Un QWidget* qui pointe vers le QWidget parent
         */
    explicit Rapprochementdialog(QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class Rapprochementdialog
         */
    ~Rapprochementdialog();

    /*!
         *  \brief Accesseur de UserInterface
         *  Méthode permetant d'accéder à l'interface de la fenêtre "Rapprochementdialog"
         *  \return ui (UserInterface) du type Ui::Rapprochementdialog
         */
    Ui::Rapprochementdialog * getUi(){return ui;}
    void accept();

private slots:



private:
    Ui::Rapprochementdialog *ui;
};

#endif // RAPPROCHEMENTDIALOG_H
