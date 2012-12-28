
/****************************************************************************
 **
 ** Copyright (C) 2012 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/







#include <QDebug>
#include "AddRadioInternet.h"



AddRadioInternet::AddRadioInternet( QWidget*parent )
    :QDialog(parent)
{
setupUi(this);


setModal(true);



#ifdef Q_OS_WIN32
setWindowFlags( Qt::Tool);
#endif

//evitamos que cambie el formulario
QSize fixedSize(this->width(),this->height());
setMinimumSize(fixedSize);
setMaximumSize(fixedSize);
setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);



        connect(BtnCancelar,SIGNAL(clicked()),this, SLOT(ClickCancelar())); //Cancelar
        connect(BtnAceptar,SIGNAL(clicked()),this, SLOT(ClickAceptar())); //Cancelar
        connect(BtnPlay,SIGNAL(clicked()),this, SLOT(ClickPlay())); //Cancelar
        connect(BtnStop,SIGNAL(clicked()),this, SLOT(ClickStop())); //Cancelar


}

///////////////////////////////////////////////////
 AddRadioInternet::~AddRadioInternet(){

    BASS_StreamFree(cual);

 }



void AddRadioInternet::ClickAceptar(){

           BASS_StreamFree(cual);

           Url=EditUrl->text().toLatin1();
           Duracion = TimeDuracion->text().toLatin1();
           Nombre=EditNombre->text().toLatin1();

           if(Url.isEmpty() || Nombre.isEmpty()){
              return;

           }


           this->close();

}


//////////////////////////////////////////////
void AddRadioInternet::ClickPlay(){

   BASS_SetDevice(Dispositivo);    //dispositivo
   BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST,1); // enable playlist processing
   BASS_StreamFree(cual);
   StreamFile *w_StreamFile= new StreamFile(EditUrl->text().toLatin1());


    cual=w_StreamFile->stream;
    delete w_StreamFile;

     BASS_ChannelPlay(cual,false);



 }

///////////////////////////////
void AddRadioInternet::ClickStop(){

      BASS_ChannelStop(cual);

}


void AddRadioInternet::ClickCancelar(){

      BASS_ChannelStop(cual);
       BASS_StreamFree(cual);
       this->close();


}

