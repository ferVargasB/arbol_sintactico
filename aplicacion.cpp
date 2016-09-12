#include "aplicacion.h"
#include "ui_aplicacion.h"
#include <QFile>
#include <QTextStream>

Aplicacion::Aplicacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aplicacion)
{
    ui->setupUi(this);
    codigoFuente = "";
    rutaDelCodigoFuente = "/Users/fernandovargas/Desktop/codigoFuenteArbolSemantico.txt";
    leerElCodigoFuente();
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
