/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/




/**
   Esta clase da soporte al sistema matemático especificos para los ficheros de audio.


 */











#ifndef STREAMMATH_H
#define STREAMMATH_H

#include <QString>

#include "bass.h"



class StreamMath
{

private:
    HSTREAM stream;

    double ToDb(double valor);

public:


    StreamMath(HSTREAM stream);
    StreamMath();

    virtual ~StreamMath(){;}

 /** Establece el stream*/
    void SetStream(HSTREAM stream);


    /** Retorna la duracion en segundos*/
      double Duracion();

    /** Retorna el tiempo trascurrido en segundos */
      double Trascurridos();


    /** Retorna la duracion menos el trascurrido en segundos*/
      double Contador();

    /** Combierte segundos a formato "hh:mm:ss:zzz */
      QString SegundoToFormato();
      QString SegundoToFormato(QString Formato);
      QString SegundoToFormato(float Segundos,QString Formato="hh:mm:ss:zzz");


     /** Retorna el nivel de DB(decibelios) del canal derecho */
     double VumetroDe();
     /** Retorna el nivel de DB(decibelios) del canal Izquierdo */
     double VumetroIz();

     double FormatoToSegundos(QString Formato);


};

#endif // STREAMMATH_H














