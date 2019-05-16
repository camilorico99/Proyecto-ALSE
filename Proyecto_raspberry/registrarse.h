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

    void creartabla_usuario();

    void insertar_usuario();

private slots:
    void on_push_cancelar_clicked();

    void on_push_registrar_clicked();

private:
    Ui::registrarse *ui;
    sqlite3 *db;
};

#endif // REGISTRARSE_H
