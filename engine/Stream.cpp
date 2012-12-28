
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************
 ** Gestion de stream
 **  Declaracion de la  clase
 **  Clase dedicada a la gestion de los ficheros de sonido
 **
 **
 ****************************************************************************/

#include <math.h>
#include <QDebug>
#include <QTime>
#include "Stream.h"

#include "Fader.h"
#include "StreamMath.h"
#include "StreamFile.h"

//*********************************************************************************************


void CALLBACK StatusProc(const void *buffer, DWORD length, void * /*user*/)
{
    if (buffer && !length)
    {
       qDebug() << buffer; // display connection status
    }


     qDebug() << buffer <<length; // display connection status
}





Stream::Stream(QWidget *parent) :
    QObject(parent)
{




     Timer = new QTimer();
     IsPisador=false;
     IsPisadorIn=false;
     IsPisadorOut=false;
     PisadorSegundos=5;

         Render=10;

         FaderStop= new Fader(this);
        // FaderA= new Fader(this);
        // FaderB= new Fader(this);
          w_Fader=new Fader(this);
        // FaderA->setStream(streamA);
         //FaderB->setStream(streamB);


         w_Pisador = new Pisador(this);
         IsTanda=false;

    connect(Timer, SIGNAL(timeout()), this, SLOT(Update())); // temporizaor horario


}


//*****************************************************
Stream::~Stream(){

  //  delete Timer1;
   // delete Label;
    //delete Vu1;
    //delete Slider;

}



//*************Asignaciond e os objetos ***************

void Stream::SetLabel( QLabel *w_Label){Label =  w_Label;}
void Stream::SetTitulo( QLabel *w_Titulo){LTitulo =  w_Titulo;}

void Stream::SetVumeter( QVUMeter *w_Vumeter){Vumeter = w_Vumeter;}
void Stream::SetSlider( QSlider *w_Slider){
    Slider = w_Slider;
    connect(Slider, SIGNAL(sliderMoved(int)),this, SLOT(slot_Barra(int)));
    //connect(Slider, SIGNAL(valueChanged(int)),this, SLOT(slot_Barra(int)));

}




/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////
////////////////////////   cargamos la musica
//////////////////////////////////////////////////////////////////////////////////////////


void Stream::Load(const QString url)
{

BASS_SetDevice(Dispositivo);    //dispositivo


   IsPisador=false;


/// ******************************** PAUSES *****************

    if(IsPause(streamA)&& IsPause(streamB)){// Ambos en pause
        BASS_ChannelPlay(streamA,false);
        BASS_ChannelPlay(streamB,false);
        Timer->start(Render);
        return;
    }



    if(IsPause(streamA)){   //si pause a
        BASS_ChannelPlay(streamA,false);    //hacemos play
        Timer->start(Render);
        return;
    }


    if(IsPause(streamB)){  //si pause b
        BASS_ChannelPlay(streamB,false);
        Timer->start(Render);
        return;
    }



/// ****************  PLAYS *****************************************


     if(IsPlay(streamA)&& IsPlay(streamB)){  //si suanan los dos




                       if(streamUltimo==streamA){       // ESTAN LOS DOS CUAL ES EL ULTIMO PARA QUITAR EL OTRO
                         // TimerB->stop();
                          BASS_ChannelStop(streamB);
                          BASS_StreamFree(streamB); //lo liberamos

                         }else{
                         // TimerA->stop();
                          BASS_ChannelStop(streamA);
                          BASS_StreamFree(streamA); //lo liberamos

                         }


                       BASS_ChannelStop(streamA);          //a revisar*******************
                       BASS_StreamFree(streamA); //lo liberamos
                       BASS_ChannelStop(streamB);
                       BASS_StreamFree(streamB); //lo liberamos

         }





    if(IsPlay(streamA)){  // si suena a
       Timer->stop();
        streamB = StreamTipo(url);  //############################
        PlayB();

                  if(FundirSolapar){ //si esta la opcion
                      w_Fader->setStream(streamA);
                      w_Fader->setFundir(Fundir);
                      w_Fader->start();
                     }


        return;
    }


    if(IsPlay(streamB)){  // si suena b
       Timer->stop();
       streamA = StreamTipo(url); //#######################################
       PlayA();
                  if(FundirSolapar){
                      w_Fader->setStream(streamB);
                      w_Fader->setFundir(Fundir);
                      w_Fader->start();
                    }



        return;
    }

// ni a ni b***************************************************

    streamA = StreamTipo(url); //#############################################

     PlayA();

}
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////
////////////////////////  hacemos play
//////////////////////////////////////////////////////////////////////////////////////////

 void Stream::PlayA(){Play(streamA);}
 void Stream::PlayB(){Play(streamB);}

  void Stream::Play(HSTREAM cual){

       StreamMath *w_StreamMath = new StreamMath(cual);
       Slider->setMaximum(w_StreamMath->Duracion());

       delete w_StreamMath;

       BASS_ChannelPlay(cual,false);
       Timer->start(Render);

  }




  /////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////
  //////////////////////// stop
  //////////////////////////////////////////////////////////////////////////////////////////
void Stream::StopA(){Stop(streamA);}
void Stream::StopB(){Stop(streamB);}


void Stream::Stop(HSTREAM cual){


     if(!IsPlay(cual)){// si no suena



          Timer->stop();

          BASS_ChannelStop(cual);
          BASS_StreamFree(cual); //lo liberamos
           PuestaCero();
          return;
       }



     Timer->stop();

       if(FundirParar){
          FaderOut(cual);


       } else{
             BASS_ChannelStop(cual);
             BASS_StreamFree(cual); //lo liberamos
       }

     //lo ponemos todo a 0
       PuestaCero();

 }



/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////
////////////////////////   pause
//////////////////////////////////////////////////////////////////////////////////////////

void Stream::PauseA(){Pause(streamA);}
void Stream::PauseB(){Pause(streamB);}

 void Stream::Pause(HSTREAM cual){

     if(IsPlay(cual)){
         BASS_ChannelPause(cual);

          Vumeter->setLeftValue(0);
          Vumeter->setRightValue(0);
          Timer->stop();
       }


 }

//********Si esta en play *************************

bool Stream::IsPlay(HSTREAM cual){

    if(BASS_ChannelIsActive(cual)==BASS_ACTIVE_PLAYING){
        return(true);
    }else{return(false);}


}

//********Si esta en pause *************************

bool Stream::IsPause(HSTREAM cual){

    if(BASS_ChannelIsActive(cual)==BASS_ACTIVE_PAUSED){
        return(true);
    }else{return(false);}


}


//======================================================================
void Stream::Update(){


QTimer::singleShot(30, this, SLOT(ActualizarContadores())); // el consumo de cpu es 0

      if (IsFinal(streamUltimo)){

           if(Timer->isActive ()){
                Timer->stop();
                emit  Finish();
              }
        }



}



/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////
////////////////////////   retorna final
//////////////////////////////////////////////////////////////////////////////////////////

bool Stream::IsFinal(HSTREAM cual){

StreamMath *w_StreamMath = new StreamMath(cual);


  if(IsRadioOnLine){  //es una radio on-line


        if((int)w_StreamMath->Trascurridos()>=TiempoRadioOnLine){
            delete w_StreamMath;
            FaderOut( cual);
            return(true);
           }



           if(w_StreamMath->Trascurridos()==-1){ //fallo conexion
               delete w_StreamMath;
               BASS_StreamFree(cual);
               return(true);
              }


       delete w_StreamMath;
       return(false);
    }



  int tmp;
  int Nivel;





         if((int) w_StreamMath->Duracion()<=Descartar){// si es descartable
              tmp=0;                                        // lo ponemos 0 para descartarlo
            }else{tmp=Solapar;}    // no es asignamos el final

         if(Solapar==0){tmp=0;}         //si solapar=0 corte real

         if(Detector){   // si el detector esta activado/ o no
            Nivel=DetectorNivel;
           }else{
            Nivel=120;    //al maximo como si no hubiese detector
           }


            if(IsTanda){tmp=0;} // si es tanda corte real

              /// detector************************************************************

           if(tmp!=0){   //si solapar es cero no hace falta el detector corte por final real


                   if(w_StreamMath->Contador()<=tmp){ //esta dentro del rango y el detecto activado
                      tmp=0;  // ponemos a cero por si falla el detector o no lo detecta

                      if((int) w_StreamMath->VumetroDe()<=Nivel){
                          delete w_StreamMath;

                          return(true);
                         }


                     }
             }


       delete w_StreamMath;

     /// corte por final real***********************************************************

     if(BASS_ChannelIsActive(cual)!=BASS_ACTIVE_PLAYING){

         return(true);
     }else{return(false);}


}

/////////////////////////////////////////////////////////////////////////////////////////
void Stream::slot_Barra(int pos){


    if(IsPlay(streamUltimo)|| IsPause(streamUltimo)){
    double posx =BASS_ChannelSeconds2Bytes( streamUltimo,  pos);
    BASS_ChannelSetPosition(streamUltimo, posx, BASS_POS_BYTE);
    return;
    }

}

////////////////////////////////////////////////////////////////////////////////////
void Stream::Retroceso(){


   StreamMath *w_StreamMath = new StreamMath(streamUltimo);
   double pos= w_StreamMath ->Trascurridos()-3;
   QWORD posx =BASS_ChannelSeconds2Bytes( streamUltimo,  pos);
   BASS_ChannelSetPosition(streamUltimo, posx, BASS_POS_BYTE);
   delete w_StreamMath;

}

void Stream::Avance(){

    StreamMath *w_StreamMath = new StreamMath(streamUltimo);
    double pos= w_StreamMath ->Trascurridos()+3;
    QWORD posx =BASS_ChannelSeconds2Bytes( streamUltimo,  pos);
    BASS_ChannelSetPosition(streamUltimo, posx, BASS_POS_BYTE);
    delete w_StreamMath;


}

/////////////////////////////////////////////////////////////////////////////////////
void Stream::pisador(){

    if(w_Pisador->isRunning()){return;}

w_Pisador->setStream(streamUltimo);


if(!IsPisador){

    IsPisador=true;
    w_Pisador->setEstado(IsPisador);
    w_Pisador->start();
    return;


   }else{


    IsPisador=false;
    w_Pisador->setEstado(IsPisador);
    w_Pisador->start();
    return;

   }



}

/////////////////////////////////////////////////////////////////////////////////////
void Stream::ActualizarContadores(){


StreamMath *w_StreamMath = new StreamMath(streamUltimo);

if(!IsRadioOnLine){
     Label->setText(w_StreamMath->SegundoToFormato(w_StreamMath->Contador()));
   }else{
     Label->setText(w_StreamMath->SegundoToFormato(TiempoRadioOnLine-w_StreamMath->Trascurridos()));
   }

Vumeter->setLeftValue(w_StreamMath->VumetroDe());
Vumeter->setRightValue(w_StreamMath->VumetroIz());
Slider->setValue((int)w_StreamMath->Trascurridos());



/////// controla los pisadores

  if(IsPisadorIn){           //si hay pisadores
     if((int)w_StreamMath->Trascurridos()==PisadorSegundos){ // intro
        IsPisadorIn=false;
        emit PisadorIn();
        }
    }

  if(IsPisadorOut){

     if((int)w_StreamMath->Duracion()-(int)w_StreamMath->Trascurridos()==Solapar+5){ // Outro
     // if((int)w_StreamMath->Duracion()-(int)w_StreamMath->Trascurridos()==Solapar){ // Outro
        IsPisadorOut=false;
        emit PisadorOut();
        }
     }


delete w_StreamMath;

   if(!Timer->isActive ()){PuestaCero();}  // si esta el timer off apagamos los indicadores, a
                                           //  a velocidades de render de 10 tics  se suelen quedar activos

}


//**********************************************************************

void Stream::PuestaCero(){

    Slider->setValue(0);
    Vumeter->setLeftValue(0);
    Vumeter->setRightValue(0);


    StreamMath w_StreamMath;
    Label->setText(w_StreamMath.SegundoToFormato(0));
    LTitulo->setText("-");


}

//**********************************************************************************

HSTREAM Stream::StreamTipo(const QString url){


//streamUltimo = BASS_StreamCreateURL(url.toLatin1(),0,BASS_STREAM_BLOCK|BASS_STREAM_STATUS|BASS_STREAM_AUTOFREE,StatusProc,0); // open URL

//return(streamUltimo);


    StreamFile *w_StreamFile = new StreamFile(url) ;
    streamUltimo=w_StreamFile->stream;                          //establece el ultimo stream
    LTitulo->setText(w_StreamFile->Titulo);
    IndicadorOnAir=w_StreamFile->Titulo;
    IsRadioOnLine=w_StreamFile->IsRadioOnLine; // para los contadores de tiempo en on-line va hacia arriba
    delete w_StreamFile;
    return(streamUltimo);


}

/////////////////////////////////////////////////////////////////////////////////////
void Stream::FaderOut(HSTREAM cual){
    FaderStop->setStream(cual);
    FaderStop->setFundir(Fundir);
    FaderStop->start();
}




/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////
////////////////////////  configuracion del reproductor
//////////////////////////////////////////////////////////////////////////////////////////

void Stream::Configuracion(const QString Player){


    Prefijo=Player; //establece el prefijo para identificarlo
    QSettings RaditIni("Radit.ini", QSettings::IniFormat);


    Dispositivo=RaditIni.value(Player + "/Dispositivo").toInt();



    Solapar=RaditIni.value(Player + "/Solapar").toInt();
    Descartar=RaditIni.value(Player + "/Descartar").toInt();
    Fundir=RaditIni.value(Player + "/Fundir").toInt();

    Qt::CheckState checkState;


    checkState =  static_cast<Qt::CheckState>(RaditIni.value(Player + "/FundirSolapar", Qt::Unchecked).toInt());
    FundirSolapar=checkState ;

    checkState =  static_cast<Qt::CheckState>(RaditIni.value(Player + "/FundirParar", Qt::Unchecked).toInt());
    FundirParar=checkState ;

    checkState =  static_cast<Qt::CheckState>(RaditIni.value(Player + "/Detector", Qt::Unchecked).toInt());
    Detector=checkState ;

    DetectorNivel=RaditIni.value(Player + "/DetectorNivel").toInt();


    BASS_Init(Dispositivo, 44100, 0, 0, NULL);

    // BASS_SetConfig(BASS_CONFIG_BUFFER, 5000 );
   // BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 10);
   //  BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST,1); // enable playlist processing

     w_Pisador->setPrefijo(Prefijo);

   //  BASS_SetDevice(Dispositivo);    //dispositivo




     //// plugin

   /*  BASS_PluginFree(0);
     QString Path=QCoreApplication::applicationDirPath().toLatin1();

    #ifdef _WIN32
       BASS_PluginLoad(Path.toLatin1() + "/Plugin/bass_aac.dll",0);
       BASS_PluginLoad(Path.toLatin1() + "/Plugin/bassflac.dll",0);
       BASS_PluginLoad(Path.toLatin1() + "/Plugin/basswma.dll",0);
    #endif


    #ifdef Q_OS_UNIX
       BASS_PluginLoad(Path.toLatin1() + "/Plugin/libbass_aac.so",0);
       BASS_PluginLoad(Path.toLatin1() + "/Plugin/libbassflac.so",0);
    #endif*/



}










