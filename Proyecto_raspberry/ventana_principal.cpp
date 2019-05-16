#include "ventana_principal.h"
#include "ui_ventana_principal.h"
#include "proyecto.h"
#include <wiringPi.h>


Ventana_Principal::Ventana_Principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana_Principal){
    ui->setupUi(this);
    wiringPiSetup();

    string path = "db_proyecto.db" ;
    int rc;

    rc = sqlite3_open(path.c_str(), &db);

    if(rc == SQLITE_OK){
    qDebug()<<"Se ha conectado a la base de datos.";}
    else{
    qDebug()<<"Error, no se ha abierto la base de datos.";}
    timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer,SIGNAL(timeout()), this, SLOT(maquina_estados()));
    timer->start();
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

//void Ventana_Principal::insertar_interacciones(QString user, QString boton, int estado){
  //  string insertar;
    //char *zErrMsg = 0;
    //int rc;
    //time_t now =time(0);
    //tm * time =localtime(&now);
    //QString fecha;
    //fecha.append("as");
    //qDebug()<< time->tm_mon ;
    //insertar.append("INSERT INTO registros(fecha,usuario,boton,estado)"
      //              "VALUES('"+fecha+"','"+user+"','"+boton+"','"+estado+"');");

    //rc = sqlite3_exec(db, insertar.c_str(), 0, 0, &zErrMsg);
//}

QString Ventana_Principal::maquina_estados(){
    estado est;
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    if (est!=A,est!=B,est!=C,est!=D){
        est=A;}
    bool btn1, btn2, btn3;
    btn1 = btn2 = btn3 = true;
        qDebug()<< est ;
        btn1 = digitalRead(0);
        btn2 = digitalRead(1);
        btn3 = digitalRead(2);
        if( btn1 ){
            qDebug()<< "boton 1";
            if(est == A ){
               est = B;}
            else if(est == B){
               est = A;}
            }
        if( btn2 ){
            qDebug()<< "boton 2";
            if(est==B ){
                est = C;}
            else if(est == C){
                est = B;}
            else if(est == D){
                est = B;}}
        if( btn3 ){
            qDebug()<< "boton 3" ;
            if(est == C ){
                est = D;}
        }
        string as;
        as = to_string(est);
        ui->label_estado->setText(as.c_str());
    switch(est){
    case A:
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        delay(2000);
        break;
    case B:
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        delay(1000);
        digitalWrite(3,HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5,HIGH);
        delay(1000);
        break;
    case C:
        digitalWrite(3,HIGH);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        delay(660);
        digitalWrite(3,LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5,LOW);
        delay(660);
        digitalWrite(3,LOW);
        digitalWrite(4, LOW);
        digitalWrite(5,HIGH);
        delay(660);
        break;
    case D:
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        delay(1000);
        digitalWrite(3,LOW);
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        delay(1000);
        digitalWrite(3,HIGH);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        delay(1000);
        break;
        return;
    }}





