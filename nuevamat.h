#ifndef NUEVAMAT_H
#define NUEVAMAT_H

#include <QMainWindow>
#include "ConjuntoMat.h"
#include <QDialog>


namespace Ui {
class NuevaMat;
}

class NuevaMat : public QDialog
{
    Q_OBJECT

public:
    explicit NuevaMat(QWidget *parent = 0);
    ~NuevaMat();
    //void setPrincipal(MainWindow *w);
    void mostrarInsMat();
    void mostrarInsAula();

private slots:
    void on_boton_ingresar_clicked();

private:
    Ui::NuevaMat *ui;
    ConjuntoMat materias;
    //MainWindow *principal;
};

#endif // NUEVAMAT_H
