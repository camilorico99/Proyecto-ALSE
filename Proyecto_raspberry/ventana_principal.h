/**
  * @file ventana_principal.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Camilo y Nicolas
  * @title ventana_principal
  */

#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include <QMainWindow>
#include <QtSql>
#include <sqlite3.h>
#include <time.h>
#include <QtCore/QTimer>

namespace Ui {
class Ventana_Principal;
}

class Ventana_Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ventana_Principal(QWidget *parent = 0);
    ~Ventana_Principal();
    enum estado{A,B,C,D};
    estado est;

private slots:

    /**
     * @brief recibo_usuario esta funcion recibe el usuario emitido en la clase Proyecto y ejecuta hay un codigo que nos
     * muestra los datos del usuario que ingreso a la aplicacion en la interfaz grafica, llama la funcion calcular_edad
     * para calcular la edad de la persona que ingreso y poder mostrar este dato en la interfaz
     */
    void recibo_usuario(QString);

    /**
     * @brief calcular_edad esta funcion calcula la edad de una persona si en la base de datos su fecha de nacimiento esta
     * de la siquiente forma (dd-mm-aaaa)
     * @return nos retorna la edad que tiene esta persona en el momento de ingresar a la aplicacion
     */
    int calcular_edad(QString);

    /**
     * @brief maquina_estados esta funcion nos realiza la maquina de estados en la cual cuando oprimimos un boton en el
     * protoboard va cambiar de estado dependiendo en el estado que este y el boton que oprima.
     */
    void maquina_estados();

    //void insertar_interacciones(QString user,QString boton,int estado);

private:

    /**
     * @brief ui definimos un puntero a la interfaz grafica de Ventana_Principal llamado ui
     */
    Ui::Ventana_Principal *ui;

    /**
     * @brief db definimos un puntero a la base de datos llamado db
     */
    sqlite3 *db;

    /**
     * @brief timer definimos un puntero a QTimer llamado timer
     */
    QTimer* timer;
};

#endif // VENTANA_PRINCIPAL_H
