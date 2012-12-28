#ifndef CUNAS_H
#define CUNAS_H

#include "ui_FrmCunas.h"
#include <QTableWidget>
#include <QString>
#include <QSqlDatabase>
#include "micelanea/CunaButton.h"

class Cunas : public QDialog, public Ui::FrmCunas
 {
     Q_OBJECT

 private:
    QSqlDatabase db;
    void CrearBase();   //crea la base de datos para las cuñas
    void Llenar(); // crea los registros de la base


 public:
     explicit Cunas(QWidget *parent = 0);
     virtual ~Cunas(){;}


 private slots:
 void ShowEditorCunas();
 void clickBoton();
 void Final(QPushButton *boton);
 void BotonColor(QPushButton *boton, bool verde);
 void ShowNombre();


};




#endif // CUNAS_H
