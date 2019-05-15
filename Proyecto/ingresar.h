#ifndef INGRESAR_H
#define INGRESAR_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <ventana_principal.h>
#include <sqlite3.h>

namespace Ui {
class Ingresar;
}

class Ingresar : public QDialog
{
    Q_OBJECT

public:
    explicit Ingresar(QWidget *parent = 0);
    ~Ingresar();

     void verificar_usuario();

private slots:


    void on_push_ingresar_clicked();

    void on_link_registrarse_clicked();

    void on_radioButton_clicked(bool checked);

private:
    Ui::Ingresar *ui;
    sqlite3 *db;
    Ventana_Principal *ventana;

static int recuperar(void *data, int argc, char **argv, char **azColName);
};

#endif // INGRESAR_H
