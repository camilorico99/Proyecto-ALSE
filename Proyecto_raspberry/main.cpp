#include "proyecto.h"
#include "ventana_principal.h"
#include "ingresar.h"
#include <QApplication>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Proyecto w;
    w.show();

    return a.exec();
}
