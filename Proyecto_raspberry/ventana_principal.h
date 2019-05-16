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

signals:
    void enviar_estado(int);

    void enviar_user(QString);

private slots:
    void recibo_usuario(QString);

    int calcular_edad(QString);

    QString maquina_estados();

    //void insertar_interacciones(QString user,QString boton,int estado);

private:
    Ui::Ventana_Principal *ui;
    sqlite3 *db;
    QTimer* timer;
};

#endif // VENTANA_PRINCIPAL_H
