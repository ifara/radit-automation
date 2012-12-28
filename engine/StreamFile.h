
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/




/**
   La clase StreamFile determina el tipo de archivo que
   se va a  reproducir wav, mp3,ogg,flac wma carpeta etc y proporcionar un Stream.

 */






#ifndef STREAMFILE_H
#define STREAMFILE_H


#include <QFileInfo>
#include <QString>

#include "bass.h"
//#include "bassflac.h"
//#include "bass_aac.h"


//#ifdef _WIN32 // _WIN32
//#include "basswma.h"

//#endif






class StreamFile {

private:
   void EstableceStream(const QString url);
   void OnLine(const QString url);


public:
    StreamFile();
    StreamFile(const QString url);

    /** Establece la url para el stream*/
     void SetUrl(const QString url);

     /**  el stream*/
    HSTREAM stream;

     /**  Nombre de la cancion, es el nombre del fichero sin la extensión*/
    QString Titulo;

    bool setTitulo;              //decide si establece el titulo
    bool IsRadioOnLine;
    virtual ~StreamFile(){;}




};












#endif // STREAMFILE_H
