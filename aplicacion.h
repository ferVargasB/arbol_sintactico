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
    QString rutaDelCodigoFuente;
    QString codigoFuente;
    QVector<QString> nodo;
    QVector<QChar> pilaParser;
    QVector<QString> pilaParserDeAtributos;

    //Funcion para obtener el codigo fuente
    void leerElCodigoFuente();
    //Funciones para crear la pila de parser
    void establecerParser();
};

#endif // APLICACION_H
