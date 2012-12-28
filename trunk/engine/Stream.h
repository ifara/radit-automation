
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.raditaudiopro.com)
 **
 ** *************************************************************************
 ** Gestion de stream
 **  Declaracion de la  clase
 **  Clase dedicada a la gestion de los ficheros de sonido
 **
 **
 ****************************************************************************/



#ifndef STREAM_H
#define STREAM_H



#include <QTimer>
#include <QString>
#include <QLabel>
#include <qvumeter.h>
#include <QSlider>
#include "Fader.h"
#include "Pisador.h"
#include "bass.h"




class Stream: public QObject


{

     Q_OBJECT

    private:
    HSTREAM streamA;
    HSTREAM streamB;




    QLabel   *Label;
    QLabel   *LTitulo;
    QVUMeter *Vumeter;
    QSlider  *Slider;
    Fader    *FaderStop;
   // Fader    *FaderA;
   // Fader    *FaderB;
    Fader    *w_Fader;
    void FaderOut(HSTREAM cual);

    Pisador *w_Pisador;







   QTimer *Timer;  // Temporizador para el fader



  // void ActualizarContadores();
 //  void PuestaCero();


    bool IsFinal(HSTREAM cual);  //determina el final de la cancion
    bool IsPlay(HSTREAM cual);  //si  esta en play
    bool IsPause(HSTREAM cual); //si esta en pause


    void PlayA();
    void PlayB();

    void Stop(HSTREAM cual);
    void Play(HSTREAM cual);
    void Pause(HSTREAM cual);

    QString  Prefijo;

    //comfiguraciones

    int Descartar;
    int Fundir;
    bool FundirSolapar;
    bool FundirParar;
    bool Detector;

    int DetectorNivel;

    int Render; // velocidad de actualizacion de los timers



    HSTREAM StreamTipo(const QString url);



//////////////////////////////////////////////////////////////77
    public:

    Stream(QWidget *parent = 0);


   ~Stream();

     HSTREAM streamUltimo;


   int Solapar;
   bool IsTanda;

   void Load(const QString url);
   void StopA();
   void StopB();
   void PauseA();
   void PauseB();
   void Retroceso();
   void Avance();
   void pisador();



 //Entrada de Objetos
   void SetLabel(QLabel *w_Label);
   void SetTitulo(QLabel *w_Titulo);
   void SetVumeter( QVUMeter *w_Vumeter);
   void SetSlider(QSlider *w_Slider);




    void Configuracion(const QString Player);


    bool IsValido; // representa si el strimer es valido
    bool IsPisadorIn;  //controla el pisador IN
    bool IsPisadorOut;  //controla el pisador Out
    bool IsPisador;            //controla si el volumen esta bajo o alto del pisador
    int PisadorSegundos;

    QString  IndicadorOnAir;          //indica el fichero que esta reproduciendo

    void PuestaCero();

    bool IsRadioOnLine;
    float TiempoRadioOnLine;

    int Dispositivo;  //Dispositivo de sonido
 //***********************************************************************************

private slots:


    void slot_Barra(int pos);
    void Update();   //actualiza los tiempos
    void ActualizarContadores();


//**********************************************************************
 signals:
     void Finish();   //sucede cuando termina de reproducir
     void PisadorIn();  //Seucede cuando el pisador IN debe acrivarse
     void PisadorOut();  //Seucede cuando el pisador OUT debe acrivarse
    // void FinishLista();


};


#endif // STREAM_H



















