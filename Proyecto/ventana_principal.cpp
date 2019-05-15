#include "ventana_principal.h"
#include "ui_ventana_principal.h"
#include "proyecto.h"


Ventana_Principal::Ventana_Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana_Principal){
    ui->setupUi(this);
    string path = "db_proyecto.db" ;
    int rc;

    rc = sqlite3_open(path.c_str(), &db);

    if(rc == SQLITE_OK){
    qDebug()<<"Se ha conectado a la base de datos.";}
    else{
    qDebug()<<"Error, no se ha abierto la base de datos.";}
}

Ventana_Principal::~Ventana_Principal(){
    delete ui;
}

void Ventana_Principal::recibo_usuario(QString user_name){
    string consulta;
    int rc;
    sqlite3_stmt *pStmt;
    consulta = "SELECT * FROM usuarios WHERE user_name = '"+user_name.toStdString()+"'";
    rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &pStmt, NULL);
    if (rc == SQLITE_OK){
        while(SQLITE_ROW == sqlite3_step(pStmt)){
            ui->label_usuario->setText((char*)sqlite3_column_text(pStmt,1));
            ui->label_nombre->setText((char*)sqlite3_column_text(pStmt,3));
            ui->label_apellido->setText((char*)sqlite3_column_text(pStmt,4));
            ui->label_doc_identidad->setText((char*)sqlite3_column_text(pStmt,5));
            ui->label_fechaNacimiento->setText((char*)sqlite3_column_text(pStmt,6));
            ui->label_edad->setText(QString::number(calcular_edad(user_name)));
        }
    }
}

int Ventana_Principal::calcular_edad(QString user){
    QString nacimiento;
    string consulta;
    int rc;
    sqlite3_stmt *pStmt;
    consulta = "SELECT fecha_nacimiento FROM usuarios WHERE user_name = '"+user.toStdString()+"'";
    rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &pStmt, NULL);
    if (rc == SQLITE_OK){
        while(SQLITE_ROW == sqlite3_step(pStmt)){
            nacimiento = (char*)sqlite3_column_text(pStmt,0);}}
    QString dia,mes,anno;
    int day,month, year;
    dia=nacimiento[0], dia.append(nacimiento[1]), mes=nacimiento[3], mes.append(nacimiento[4]);
    anno=nacimiento[6], anno.append(nacimiento[7]), anno.append(nacimiento[8]),anno.append(nacimiento[9]);
    day=dia.toInt(), month=mes.toInt(), year=anno.toInt();
    time_t now =time(0);
    tm * time =localtime(&now);
    int edad;
    if (month<(time->tm_mon+1)){
        edad=time->tm_year+1900-year;}
    if (month>(time->tm_mon+1)){
        edad=time->tm_year+1900-year-1;}
    if(month==(time->tm_mon+1)){
        if(day>(time->tm_mday)){
            edad=time->tm_year+1900-year-1;}
        else{
            edad=time->tm_year+1900-year;}}
    return edad;}

