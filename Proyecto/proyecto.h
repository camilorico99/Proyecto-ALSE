#ifndef PROYECTO_H
#define PROYECTO_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <ventana_principal.h>
#include <sqlite3.h>
#include <string>

using namespace std;

namespace Ui {
class Proyecto;
}

class Proyecto : public QMainWindow
{
    Q_OBJECT

public:
    explicit Proyecto(QWidget *parent = 0);
    ~Proyecto();

    void verificar_usuario();

signals:
    void enviar_usuario(QString);

private slots:
    void on_link_registrarse_clicked();

    void on_push_ingresar_clicked();

    void on_radioButton_clicked(bool checked);

private:
    Ui::Proyecto *ui;
    sqlite3 *db;
    Ventana_Principal *ventana;
};

#endif // PROYECTO_H
