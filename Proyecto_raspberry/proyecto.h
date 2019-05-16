/**
  * @file proyecto.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Camilo y Nicolas
  * @title proyecto
  */

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

    /**
     * @brief verificar_usuario nos verifica si el usuario ingresado esta en la base de datos y si la contraseña
     *  coincide con el usuario ingresado, si la verificacion es correcta nos cerrara esta ventana y nos abrira la ventana
     *  principal, dentro de esta funcion esta el emit de el usuario que enviaremos.
     */
    void verificar_usuario();

signals:

    /**
     * @brief enviar_usuario esta funcion nos envia el usuario ingresado en esta ventana el cual recibiremeos en una funcion
     * de la ventana principal llamada recibo_usuario.
     */
    void enviar_usuario(QString);

private slots:

    /**
     * @brief on_link_registrarse_clicked nos abre la interfaz para registrarnos en la base de datos
     */
    void on_link_registrarse_clicked();

    /**
     * @brief on_push_ingresar_clicked aca llamaremos la funcion verificar_usuario()
     */
    void on_push_ingresar_clicked();

    /**
     * @brief on_radioButton_clicked este boton nos mostrara la contraseña si esta oprimido o la dejara en asteriscos si no
     * esta oprimido
     * @param checked si esta checkeado mostrara contraseña si no se eran asteriscos
     */
    void on_radioButton_clicked(bool checked);

private:
    /**
     * @brief ui definimos un puntero a la interfaz grafica de Proyecto llamado ui
     */
    Ui::Proyecto *ui;

    /**
     * @brief db definimos un puntero a la base de datos sqlite3 llamado db
     */
    sqlite3 *db;

    /**
     * @brief ventana definimos un puntero a la clase Ventana_Principal llamado ventana
     */
    Ventana_Principal *ventana;
};

#endif // PROYECTO_H
