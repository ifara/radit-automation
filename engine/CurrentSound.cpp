/**
 * CurrentSound
 * -----------------------------------------
 *
 * - This class creates new file with information of the current song.
 * - file: CurrentSound.txt  folder: CurrentSound
 * - Out: title, artist, album,gender
 * - if don't have tag information , a out filename
 *
 * @author
 */
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

#include "CurrentSound.h"
#include "TagInfo.h"

CurrentSound::CurrentSound(){}

CurrentSound::CurrentSound(const QString url)
{
    CrearFichero(url);
}

void CurrentSound::SetCurrent(const QString url)
{
    CrearFichero(url);
}

void CurrentSound::CrearFichero(const QString url)
{
   QString Path=QCoreApplication::applicationDirPath().toLatin1();
   QFile file(Path.toLatin1() + "/CurrentSound/CurrentSound.txt");
   file.open(QIODevice::WriteOnly| QIODevice::Text);
   QTextStream out(&file);

   TagInfo *w_TagInfo = new TagInfo(QDir::toNativeSeparators(url));
   QFileInfo File(url);

   if(w_TagInfo->Titulo()!="")
        out << w_TagInfo->Titulo();
   else
        out << File.completeBaseName();

   out << "\n";
   out << w_TagInfo->Artista();
   out << "\n";
   out << w_TagInfo->Album();
   out << "\n";
   out << w_TagInfo->Genero();
   out << "\n";

   delete w_TagInfo;
}
