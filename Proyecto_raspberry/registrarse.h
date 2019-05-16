/**
  * @file registrarse.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Camilo y Nicolas
  * @title registrarse
  */

#ifndef REGISTRARSE_H
#define REGISTRARSE_H

#include <QWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <sqlite3.h>
#include <string>

using namespace std;

namespace Ui {
class registrarse;
}

class registrarse : public QWidget
{
    Q_OBJECT

public:
    explicit registrarse(QWidget *parent = 0);
    ~registrarse();

    /**
     * @brief insertar_usuario registra los datos de los usuarios en la base de datos
     */
    void insertar_usuario();

private slots:

    /**
     * @brief on_push_cancelar_clicked cancela el registro de un nuevo usuario y nos devuelve a la interfaz Proyecto
     */
    void on_push_cancelar_clicked();

    /**
     * @brief on_push_registrar_clicked llama la funcion insertar_usuario y si los datos son correctos para registrarlos
     * los registra y nos devuelve a la interfaz Proyecto
     */
    void on_push_registrar_clicked();

private:

    /**
     * @brief creartabla_usuario crea la tabla usuario y la tabla regitros en la base de datos
     */
    void creartabla_usuario();

    /**
     * @brief ui definimos un puntero a la interfaz grafica de registrarse llamado ui
     */
    Ui::registrarse *ui;

    /**
     * @brief db definimos un puntero a la base de datos llamado db
     */
    sqlite3 *db;
};

#endif // REGISTRARSE_H
