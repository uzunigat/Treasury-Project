#ifndef CHOISIRPASSIFDIALOG_H
#define CHOISIRPASSIFDIALOG_H

#include <QDialog>

namespace Ui {
class ChoisirPassifDialog;
}

/*!
 *\class ChoisirPassifDialog
 *\brief Cette classe vous permet de Afficher une interface graphique quand on a besoin d'une compte passif
 *\details
 */
class ChoisirPassifDialog : public QDialog
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur de la class ChoisirPassifDialog
         *  Constructeur de la class ChoisirPassifDialog
         *  \param parent: Un QWidget* qui pointe vers le QWidget parent
         */
    explicit ChoisirPassifDialog(QWidget *parent = nullptr);

    /*!
         *  \brief Destructeur
         *  Destructeur de la class ChoisirPassifDialog
         */
    ~ChoisirPassifDialog();

    /*!
         *  \brief Accesseur de UserInterface
         *  Méthode permetant d'accéder à l'interface de la fenêtre "ChoisirPassifDialog"
         *  \return ui (UserInterface) du type Ui::ChoisisPassifDialog
         */
    Ui::ChoisirPassifDialog* getUi(){return ui;}

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void accepted(QString);

private:
    Ui::ChoisirPassifDialog *ui;
};

#endif // CHOISIRPASSIFDIALOG_H
