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
};

#endif // APLICACION_H
