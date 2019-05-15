#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include <QMainWindow>
#include <QtSql>
#include <sqlite3.h>
#include <time.h>

namespace Ui {
class Ventana_Principal;
}

class Ventana_Principal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ventana_Principal(QWidget *parent = 0);
    ~Ventana_Principal();

private slots:
    void recibo_usuario(QString);

    int calcular_edad(QString);
private:
    Ui::Ventana_Principal *ui;
    sqlite3 *db;
};

#endif // VENTANA_PRINCIPAL_H
