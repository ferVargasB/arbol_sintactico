#ifndef APLICACION_H
#define APLICACION_H

#include <QDialog>

namespace Ui {
class Aplicacion;
}

class Aplicacion : public QDialog
{
    Q_OBJECT

public:
    explicit Aplicacion(QWidget *parent = 0);
    ~Aplicacion();

private:
    Ui::Aplicacion *ui;
    QPixmap *lienzo;
    QString rutaDelCodigoFuente;
    QString codigoFuente;
    QVector <QString>tablaTokens;
    QVector<QString> nodo;
    QVector<QChar> pilaParser;
    QVector<QString> pilaParserDeAtributos;

    //Funcion para obtener el codigo fuente
    void leerElCodigoFuente();
    //Funciones para crear la pila de parser
    void establecerParser();
    void establecerPilaDeAtributos(int indice);

    //Funciones relacionadas con dibujar los arboles
    void limpiarLienzo();
    void dibujarArbol();

    //Funciones relacionadas con el análisis de las reglas
    void descomponerCodigoFuenteEnTokens();
};

#endif // APLICACION_H
