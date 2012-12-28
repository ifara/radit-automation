/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.raditaudiopro.com)
 **
 ** *************************************************************************
 **  Genera un fade out
 **
 **
 **
 **
 ****************************************************************************/




#include <QDebug>

#include "Fader.h"

Fader::Fader(QObject *parent):
             QThread(parent)

{
}



Fader::Fader(HSTREAM Stream, int Fundir, QObject *parent):
    QThread(parent)

{

 stream=Stream;
 Tiempo=Fundir*1000;


}


void Fader::run(){

           BASS_ChannelSlideAttribute(stream, BASS_ATTRIB_VOL, -1, Tiempo);
           this->msleep(Tiempo);
           BASS_ChannelStop(stream);
           BASS_StreamFree(stream); //lo liberamos

          // this->terminate();


}

void Fader::setStream(HSTREAM Stream){stream=Stream;}
void Fader::setFundir(int Fundir){Tiempo=Fundir*1000;}





