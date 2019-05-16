#include "registrarse.h"
#include "ui_registrarse.h"
#include "proyecto.h"
#include <QMessageBox>

registrarse::registrarse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registrarse)
{
    ui->setupUi(this);

    ui->txt_password1->setEchoMode(QLineEdit::Password);
    ui->txt_password2->setEchoMode(QLineEdit::Password);

    string path = "db_proyecto.db" ;
    int rc;

    rc = sqlite3_open(path.c_str(), &db);

    if(rc == SQLITE_OK){
    qDebug()<<"Se ha conectado a la base de datos.";}
    else{
    qDebug()<<"Error, no se ha abierto la base de datos.";}

    creartabla_usuario();
}

registrarse::~registrarse()
{
    delete ui;

}

void registrarse::creartabla_usuario(){
    string consulta;
    char *zErrMsg = 0;
    int rc;

    consulta.append( "CREATE TABLE IF NOT EXISTS usuarios(user_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                 "user_name TEXT NOT NULL UNIQUE,contrasena TEXT NOT NULL, nombre TEXT NOT NULL,apellido TEXT NOT NULL"
                 ",documento_id TEXT NOT NULL UNIQUE,fecha_nacimiento TEXT NOT NULL);");
    rc = sqlite3_exec(db, consulta.c_str(), 0, 0, &zErrMsg);
    consulta.clear();
    consulta.append("CREATE TABLE IF NOT EXISTS registros(fecha TEXT NOT NULL, usuario TEXT NOT NULL, boton TEXT NOT NULL, estado TEXT NOT NULL);");
    rc = sqlite3_exec(db, consulta.c_str(), 0, 0, &zErrMsg);

    if(rc == SQLITE_OK){
        qDebug()<<"Se ha creado o se ha abierto correctamente la base de datos.";}
    else{
        qDebug()<<zErrMsg;
    }
}

void registrarse::insertar_usuario(){
    QString user_name,password, nombre, apellido, fecha_nacimiento, documento_id, password1;
    string consulta, verificar;
    char *zErrMsg = 0;
    int rc;
    user_name = ui->txt_new_usuario->text();
    password = ui->txt_password1->text();
    password1 = ui->txt_password2->text();
    nombre = ui->txt_nombre->text();
    apellido = ui->txt_apellido->text();
    documento_id= ui->txt_documento->text();
    fecha_nacimiento= ui->fecha_nacimiento->text();

    consulta.append("INSERT INTO usuarios(user_name,contrasena,nombre,apellido,documento_id,fecha_nacimiento)"
                    "VALUES('"+user_name.toStdString()+"','"+password.toStdString()+"','"+nombre.toStdString()+"',"
                    "'"+apellido.toStdString()+"','"+documento_id.toStdString()+"','"+fecha_nacimiento.toStdString()+"');");

    verificar.append("SELECT * FROM usuarios");

    if(nombre!=NULL){
        if(apellido!=NULL){
            if(documento_id!=NULL){
                if(user_name!=NULL){
                    if(password!=NULL){
                        if(password1!=NULL){
                            if(password==password1){
                                rc =sqlite3_exec(db,consulta.c_str(),0,0, &zErrMsg);
                                if(rc == SQLITE_OK){
                                    QMessageBox::information(this,"Correcto","El usuario se ha creado correctamente.");
                                    qDebug()<<"Se ha introducido correctamente.";
                                    Proyecto*registrarse = new Proyecto;
                                    registrarse->show();
                                    close();}
                                else{
                                    qDebug()<< "no ingreso";
                                    rc =sqlite3_exec(db,verificar.c_str(),0,0, &zErrMsg);
                                    if(rc == SQLITE_OK){
                                        fprintf(stdout, "Operation done successfully\n");
                                        //if(stdout==user_name){
                                            qDebug()<<"Usuario repetido.";
                                            QMessageBox::information(this,"Error","El usuario ya existe, cambielo.");}
                                        //if(insertar.value(4)==documento_id){
                                            qDebug()<<"documento repetido.";
                                            QMessageBox::information(this,"Error","El documento ya existe, cambielo.");
                                    }}
                            else{
                                qDebug()<<"Error, no se ha introducido contraseñas no coinciden.";
                                QMessageBox::information(this, "Error", "Las contraseñas no coinciden.");}}
                        else{
                            QMessageBox::information(this, "Error", "Repita contraseña esta vacio, ingrese datos.");}}
                    else{
                        QMessageBox::information(this, "Error", "Contraseña esta vacio, ingrese datos.");}}
                else{
                    QMessageBox::information(this, "Error", "Usuario esta vacio, ingrese datos.");}}
            else{
                QMessageBox::information(this, "Error", "Documento de identidad esta vacio, ingrese datos.");}}
        else{
            QMessageBox::information(this, "Error", "Apellido esta vacio, ingrese datos.");}}
    else{
        QMessageBox::information(this, "Error", "Nombre esta vacio, ingrese datos.");}
}
void registrarse::on_push_registrar_clicked(){

    insertar_usuario();
}

void registrarse::on_push_cancelar_clicked(){
    Proyecto*registrarse = new Proyecto;
    registrarse->show();
    close();
}
