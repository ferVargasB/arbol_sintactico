#include "aplicacion.h"
#include "ui_aplicacion.h"
#include <QFile>
#include <QTextStream>

Aplicacion::Aplicacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aplicacion)
{
    ui->setupUi(this);
    lienzo = new QPixmap(ui->labelLienzo->width(),ui->labelLienzo->height());
    lienzo->fill(Qt::white);
    ui->labelLienzo->setPixmap(*lienzo);
    codigoFuente = "";
    rutaDelCodigoFuente = "/Users/fernandovargas/Desktop/codigoFuenteArbolSemantico.txt";
    leerElCodigoFuente();
    establecerParser();
}

Aplicacion::~Aplicacion()
{
    delete ui;
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
