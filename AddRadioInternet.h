#ifndef ADDRADIOINTERNET_H
#define ADDRADIOINTERNET_H

#include <QUrl>
#include "engine/StreamFile.h"
#include "ui_FrmAddRadioInternet.h"


class AddRadioInternet : public QDialog, public Ui::FrmAddRadioInternet
 {
     Q_OBJECT

 private:
 HSTREAM cual;
 public:
     explicit AddRadioInternet(QWidget *parent = 0);
     virtual ~AddRadioInternet();
     QString Url;
     QString Duracion;
     QString Nombre;
     int Dispositivo;

public slots:
     void ClickAceptar();


private slots:
 void ClickPlay();
 void ClickStop();
 void ClickCancelar();
signals:



 };



#endif // ADDRADIOINTERNET_H
