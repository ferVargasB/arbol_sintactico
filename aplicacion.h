#ifndef APLICACION_H
#define APLICACION_H

#include <QDialog>
#include <QRegularExpression>
namespace Ui {
class Aplicacion;
}

class Aplicacion : public QDialog
{
    Q_OBJECT

public:
    explicit Aplicacion(QWidget *parent = 0);
    ~Aplicacion();

private slots:
    void on_buttonRealizarAnalisis_clicked();

private:
    Ui::Aplicacion *ui;
    QPixmap *lienzo;
    QString rutaDelCodigoFuente;
    QString codigoFuente;
    QVector <QString>tablaTokens;
    QVector<QString> nodo;
    QVector<QChar> pilaParser;
    QVector<QString> pilaParserDeAtributos;
    QRegularExpression reSuma;

    //Funciones del sistema
    void detenerAplicacion();
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
    void crearAnalisis();
    void analizarPuntoYComa(int indice);
    void analizarOperacion(int indice);
    void analizarOperadorIgual(int indice);
    void analizarLetraC(int indice);
    void analizarLetraB(int indice);
    void analizarLetraA(int indice);
};

#endif // APLICACION_H
