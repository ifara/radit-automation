/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/




#include <QDebug>


#include "PlayerSetting.h"
#include "bass.h"


PlayerSetting::PlayerSetting(QString Modulo,QDialog *parent )
    :QDialog(parent)
{
   setupUi(this);


   setModal(true);



#ifdef Q_OS_WIN32
 setWindowFlags( Qt::Tool);
#endif

   //evitamos que cambie el formulario
   QSize fixedSize(660,485);
   setMinimumSize(fixedSize);
   setMaximumSize(fixedSize);
   setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
   listWidget->setCurrentRow(0);
   stackedWidget->setCurrentIndex(0);

   this->setWindowTitle(this->windowTitle() + " [ " + Modulo.toLatin1() + " ]");

   connect(BtnSalir,SIGNAL(clicked()),this, SLOT(ClickSalir()));
   w_Modulo=Modulo;

   AddDispositivo();

   Establecer();





}

///////////////////////////////////////////////////

void PlayerSetting::SetPos(QRect scr){
     move( scr.center() - rect().center() );

}

///////////////////////////////////////////////////
void PlayerSetting::AddDispositivo(){

    BASS_DEVICEINFO i;
    QString nombre;

    QString nulo(tr("Sin Sonido")); //añadimos nulo
    this->Dispositivo->addItem(nulo);


#ifdef Q_OS_UNIX

    QString def(tr("Defecto")); //en linux añadimos otro el default
    this->Dispositivo->addItem(def);

#endif


 //****************** añadimos las tarjetas de audio *****************************

    for (int c=1;BASS_GetDeviceInfo(c,&i);c++) { // device 1 = el primer dispositivo
            if (i.flags&BASS_DEVICE_ENABLED) { // enabled, lo añadimos...
                this->Dispositivo->addItem(nombre.fromAscii(i.name));
               }
        }

}


/////////////////////////////////////////////////////////////////////////////////
 void PlayerSetting::Establecer(){

     QSettings RaditIni("Radit.ini", QSettings::IniFormat);



     Dispositivo->setCurrentIndex(RaditIni.value(w_Modulo + "/Dispositivo").toInt());
     Solapar->setValue(RaditIni.value(w_Modulo + "/Solapar").toInt());
     Descartar->setValue(RaditIni.value(w_Modulo + "/Descartar").toInt());
     Fundir->setValue(RaditIni.value(w_Modulo + "/Fundir").toInt());

     Qt::CheckState checkState;


     checkState =  static_cast<Qt::CheckState>(RaditIni.value(w_Modulo + "/FundirSolapar", Qt::Unchecked).toInt());
     FundirSolapar->setCheckState(checkState) ;

     checkState =  static_cast<Qt::CheckState>(RaditIni.value(w_Modulo + "/FundirParar", Qt::Unchecked).toInt());
     FundirParar->setCheckState(checkState) ;

     checkState =  static_cast<Qt::CheckState>(RaditIni.value(w_Modulo + "/Detector", Qt::Unchecked).toInt());
     Detector->setCheckState(checkState) ;

     DetectorNivel->setValue(RaditIni.value(w_Modulo + "/DetectorNivel").toInt());


     //Pisador

      Transicion->setValue(RaditIni.value(w_Modulo + "/Transicion").toInt());
      Locucion->setValue(RaditIni.value(w_Modulo + "/Locucion").toFloat());



 }




///////////////////////////////////////////////////////////////////
void PlayerSetting::ClickSalir(){

    // guardamos la configuracion al salir





   QSettings RaditIni("Radit.ini", QSettings::IniFormat);



  RaditIni.setValue(w_Modulo + "/Dispositivo",this->Dispositivo->currentIndex());
  RaditIni.setValue(w_Modulo + "/Solapar",this->Solapar->value());
  RaditIni.setValue(w_Modulo + "/Descartar",this->Descartar->value());
  RaditIni.setValue(w_Modulo + "/Fundir",this->Fundir->value());

  RaditIni.setValue(w_Modulo + "/FundirSolapar",this->FundirSolapar->checkState());
  RaditIni.setValue(w_Modulo + "/FundirParar",this->FundirParar->checkState());
  RaditIni.setValue(w_Modulo + "/Detector",this->Detector->checkState());
  RaditIni.setValue(w_Modulo + "/DetectorNivel",this->DetectorNivel->value());


  //Pisador
   RaditIni.setValue(w_Modulo + "/Transicion",this->Transicion->value());
   RaditIni.setValue(w_Modulo + "/Locucion",this->Locucion->value());

this->close();
}





