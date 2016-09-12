#include "aplicacion.h"
#include "ui_aplicacion.h"
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QMessageBox>
#include <QTime>
#include <QRegularExpression>

Aplicacion::Aplicacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aplicacion)
{
    ui->setupUi(this);
    nodo.resize(3);
    reSuma.setPattern("^\\w\\\\+\\w");
    lienzo = new QPixmap(ui->labelLienzo->width(),ui->labelLienzo->height());
    limpiarLienzo();
    codigoFuente = "";
    rutaDelCodigoFuente = "/Users/fernandovargas/Desktop/codigoFuenteArbolSemantico.txt";
    leerElCodigoFuente();
    establecerParser();
    descomponerCodigoFuenteEnTokens();
}

Aplicacion::~Aplicacion()
{
    delete ui;
}

void Aplicacion::detenerAplicacion()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Aplicacion::leerElCodigoFuente()
{
    QFile file(rutaDelCodigoFuente); //objeto file con la direccion de nuestro archivo
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //comprobamos si existe
           return;

    QTextStream entrada(&file); //poder leer el contenido del archivo
    while (!entrada.atEnd()) { //devuelve false hasta terminar el archivo
        codigoFuente += entrada.readLine(); //leer cada linea y concatenar
    }
}

void Aplicacion::establecerParser()
{
    int indice{codigoFuente.size() - 2};
    while(codigoFuente[indice] != ';'){
        if(codigoFuente[indice] == 'b'){
            pilaParser.push_front(codigoFuente[indice]);
            indice--;
        }
        else if(codigoFuente[indice] == 'a'){
            pilaParser.push_front(codigoFuente[indice]);
            indice--;
        }
        else if(codigoFuente[indice] == 'c'){
            pilaParser.push_front(codigoFuente[indice]);
            indice--;
        }
        else
            indice--;
    }
    establecerPilaDeAtributos(indice);
}

void Aplicacion::establecerPilaDeAtributos(int indice)
{
    while(indice != 0){
        if(codigoFuente[indice].isDigit()){
            pilaParserDeAtributos.push_back("int");
            indice--;
        }
        else
            indice--;
    }
    pilaParserDeAtributos.push_front("int");
}

void Aplicacion::limpiarLienzo()
{
    lienzo->fill(Qt::white);
    ui->labelLienzo->setPixmap(*lienzo);
}

void Aplicacion::dibujarArbol()
{
    limpiarLienzo();
    QPainter p(lienzo);
    p.setPen(Qt::black);
    p.drawEllipse(300,50,40,40);
    p.drawEllipse(200,150,40,40);
    p.drawEllipse(400,150,40,40);
    p.drawText(315,75,nodo[1]);
    p.drawText(415,175,nodo[0]);
    p.drawText(215,175,nodo[2]);
    p.drawLine(300,80,233,157);
    p.drawLine(338,80,407,157);
    ui->labelLienzo->setPixmap(*lienzo);
    detenerAplicacion();
}

void Aplicacion::descomponerCodigoFuenteEnTokens()
{
    QString token = "";
    int indice = codigoFuente.size() - 1;
    while(indice != 0){
        if(codigoFuente[indice].isSpace()){
            tablaTokens.push_back(token);
            token = "";
            indice--;
        }
        else if(codigoFuente[indice] == ';'){
            tablaTokens.push_back(token);
            tablaTokens.push_back(";");
            token = "";
            indice--;
        }
        else{
            token.push_front(codigoFuente[indice]);
            indice--;
        }
    }
   token.push_front(codigoFuente[indice]);
   tablaTokens.push_back(token);

   for(int i = 0; i < tablaTokens.size(); i++){
       if (tablaTokens[i] == ""){
           tablaTokens.remove(i);
       }
   }
}

void Aplicacion::crearAnalisis()
{
    for(int i = 0; i < tablaTokens.size(); i++){
        if(tablaTokens[i] == ";"){
            analizarPuntoYComa(i);
        }
        else if (tablaTokens[i] == "a+b"){
            analizarOperacion(i);
        }
        else if(tablaTokens[i] == "="){
            analizarOperadorIgual(i);
        }
        else if(tablaTokens[i] == "c"){
            analizarLetraC(i);
        }
    }
}

void Aplicacion::analizarPuntoYComa(int indice)
{
    nodo[0] = "null";
    nodo[1] = tablaTokens[indice];
    nodo[2] = "a|i";
    QMessageBox::information(this,"","El analisis del punto y coma es correcto");
    dibujarArbol();
}

void Aplicacion::analizarOperacion(int indice)
{
    nodo[0] = "operando";
    nodo[1] = tablaTokens[indice];
    nodo[2] = "operando";
    QMessageBox::information(this,"","El analisis de la operacion es correcto");
    dibujarArbol();
}

void Aplicacion::analizarOperadorIgual(int indice)
{
    QRegularExpression reCualquierLetra("\\w");
    QRegularExpression reCualquierIns("\\w\\+\\w");
    QRegularExpression reCualquierNum("\\d");
    QRegularExpressionMatch coincidenciaLadoIzq = reCualquierLetra.match(tablaTokens[indice+1]);
    QRegularExpressionMatch coincidenciaLadoDere = reCualquierIns.match(tablaTokens[indice-1]);
    QRegularExpressionMatch coincidenciaLadoDere2 = reCualquierNum.match(tablaTokens[indice-1]);
    if(coincidenciaLadoIzq.hasMatch() && coincidenciaLadoDere.hasMatch()){
        QMessageBox::information(this,"","Analisis correcto");
        nodo[0] = "varibale";
        nodo[1] = "=";
        nodo[2] = "a";
        dibujarArbol();
    }
    else if(coincidenciaLadoIzq.hasMatch() && coincidenciaLadoDere2.hasMatch()){
        nodo[0] = "variable";
        nodo[1] = "=";
        nodo[2] = "a";
        QMessageBox::information(this,"","Analisis correcto");
        dibujarArbol();
    }
}

void Aplicacion::analizarLetraC(int indice)
{
    if(tablaTokens[indice+1] == ";" && tablaTokens[indice-1] == "="){
        nodo[0] = "variable";
        nodo[2] = "=";
        nodo[1] = "instruccion";
        dibujarArbol();
        QMessageBox::information(this,"","Analisis correcto");
    }
    else if(tablaTokens[indice-1] == ";" && tablaTokens[indice+1] == "int"){
        nodo[0] = "int";
        nodo[2] = "variable";
        nodo[1] = "valor";
        dibujarArbol();
        QMessageBox::information(this,"","Analisis correcto");
    }
}

void Aplicacion::on_buttonRealizarAnalisis_clicked()
{
    crearAnalisis();
}
