#include "proyecto.h"
#include "ui_proyecto.h"
#include "registrarse.h"
#include "ventana_principal.h"
#include <QMessageBox>
#include <string>
#include <sstream>
#include <wiringPi.h>

Proyecto::Proyecto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Proyecto){
    ui->setupUi(this);

    string path = "db_proyecto.db" ;
    int rc;

    rc = sqlite3_open(path.c_str(), &db);

    if(rc == SQLITE_OK){
    qDebug()<<"Se ha conectado a la base de datos.";}
    else{
    qDebug()<<"Error, no se ha abierto la base de datos.";}

    ui->txt_password->setEchoMode(QLineEdit::Password);
}

Proyecto::~Proyecto(){
    delete ui;
}

void Proyecto::verificar_usuario(){

    QString user_name, password, contrasena;
    string comprobar,comprobar1;
    char *zErrMsg = 0;
    int rc;
    user_name = ui->txt_usuario->text();
    password = ui->txt_password->text();
    comprobar = "SELECT contrasena FROM usuarios WHERE user_name=='"+user_name.toStdString()+"'";
    comprobar1 = "SELECT contrasena FROM usuarios WHERE user_name!='"+user_name.toStdString()+"'";
    sqlite3_stmt *pStmt;
    rc = sqlite3_prepare_v2(db, comprobar.c_str(), -1, &pStmt, NULL);
    if (rc == SQLITE_OK){
        while(SQLITE_ROW == sqlite3_step(pStmt)){
            contrasena = (char*)sqlite3_column_text(pStmt,0);
            if(contrasena == password){
                QMessageBox::information(this,"Correcto","El usuario se ha autenticado correctamente.");
                ventana = new Ventana_Principal();
                ventana->show();
                connect(this,SIGNAL(enviar_usuario(QString)),ventana,SLOT(recibo_usuario(QString)));
                emit enviar_usuario(user_name);
                close();
                return;}
            else{
                QMessageBox::information(this,"Error","La contraseña no concide con el usuario.");
                return;}}}
    else {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);}
    rc = sqlite3_prepare_v2(db, comprobar1.c_str(), -1, &pStmt, NULL);
    if (rc == SQLITE_OK){
        qDebug()<<"Usuario no existe.";
        QMessageBox::information(this,"Error","El usuario no existe.");}}

void Proyecto::on_link_registrarse_clicked(){
    registrarse*Proyecto = new registrarse();
    Proyecto->show();
    close();
}

void Proyecto::on_push_ingresar_clicked(){
    verificar_usuario();
}


void Proyecto::on_radioButton_clicked(bool checked){
    if(checked==false){
        ui->txt_password->setEchoMode(QLineEdit::Password);}
    if(checked==true){
        ui->txt_password->setEchoMode(QLineEdit::Normal);
    }
}
