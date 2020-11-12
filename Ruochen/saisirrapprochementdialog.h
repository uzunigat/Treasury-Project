#ifndef SAISIRRAPPROCHEMENTDIALOG_H
#define SAISIRRAPPROCHEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class SaisirRapprochementDialog;
}

/*!
 *\class SaisirRapprochementDialog
 *\brief Cette classe est utilisée pour saisir un rapprochement et aprés génerer un pdf
 *\details
 */
class SaisirRapprochementDialog : public QDialog
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur de la class SaisirRapprochementdialog
         *  Constructeur de la class SaisirRapprochementdialog
         *  \param parent: Un QWidget* qui pointe vers le QWidget parent
         */
    explicit SaisirRapprochementDialog(QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class SaisirRapprochementDialog
         */
    ~SaisirRapprochementDialog();

    /*!
         *  \brief Accesseur de UserInterface
         *  Méthode permetant d'accéder à l'interface de la fenêtre "SaisirRapprochementdialog"
         *  \return ui (UserInterface) du type Ui::SaisirRapprochementdialog
         */
     Ui::SaisirRapprochementDialog* getUi(){return ui;}
     void accept();

private:
    Ui::SaisirRapprochementDialog *ui;
};

#endif // SAISIRRAPPROCHEMENTDIALOG_H
