/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.raditaudiopro.com)
 **
 ** *************************************************************************/




/** @brief Esta clase da soporte a la información Tag.
*
*
*    Devuelve la información de los ficheros de audio.
*/





#ifndef TAGINFO_H
#define TAGINFO_H

#include <QString>

#include "fileref.h"
#include "tag.h"

//#include "tbytevector.h"
//#include "taglib_export.h"




class TagInfo
{

   private:
    TagLib::FileRef tagFile;
    QString TagTiempo(int duracion );





   protected:

    public:

   TagInfo(const QString file);
   TagInfo();

   /** Establece el fichero */
   void setFile(const QString file);

   /** Devuelve la informacion del Artista */
   QString Artista();
   QString Titulo();
   QString Album();
   QString Duracion();
   QString Genero();


};




#endif // TAGINFO_H
