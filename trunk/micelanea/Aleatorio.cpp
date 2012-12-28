
/****************************************************************************
 **
 ** Copyright (C) 2010 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.raditaudiopro.com)
 **
 ** *************************************************************************
 **  Aleatorio:
 **
 **  Implementa el sistema aleatorio

 **   Funciones

      - Aleatorio(const QString url) Constuptor, recibe un path que representa un directorio c:/musica

 **   - QString FicheroPath: Retorna un path que representa un fichero aleatorio de la carpeta
        pasada al construptor

      -  int NumeroAleatorio(int range_starts, int range_ends): retorna un entero que representa un numero aleatorio
         recibe dos enteros que representan el intervalo de numeros a sacar

 **
 ****************************************************************************/





#include <QDebug>
#include <QModelIndex>
#include <QTime>
#include <QFileInfo>
#include "Aleatorio.h"




Aleatorio::Aleatorio(const QString url, QLabel *w_Label){



    Path=url;



   QFile fexiste( url + "/index.dat" );   //comprobamos si hay fichero indice
   if(!fexiste.exists()){     //si no existe  creamos el indice

       this->CrearIndice(url);
       fexiste.close();
    }






    QFile file( url + "/index.dat");             //leemos el fichero indice que contiene los paht+file
   file.open( QIODevice::ReadOnly );

      QDataStream stream( &file );
      stream.setVersion( QDataStream::Qt_4_2 );

      stream >> results;            //lo cargamos en qlist para hacer la lista


      file.close();

  TotalFicheros=results.count();






}

//***************************************************

Aleatorio::~Aleatorio(){


}

//*******************************************************
// retorna el path de un fichero aleatorio
//*********************************************************
QString Aleatorio::FicheroPath(){



    int Cual;
    Cual=NumeroAleatorio(0,TotalFicheros-1);



      while (!Repetido(Cual)){
            Cual=NumeroAleatorio(0,TotalFicheros-1);
       }

 Todos();                //comprueba que si estan todos reproducidos
Cancion=results[Cual]; //Para los titulos

    return(results[Cual]);



}


//**************************************************************
//*  seleciona un numero aleatorio
//***************************************************************
int Aleatorio::NumeroAleatorio(int range_starts, int range_ends)
{



        if (range_starts > range_ends)
        {
                range_starts = range_starts ^ range_ends;
                range_ends = range_ends ^ range_starts;
                range_starts = range_starts ^ range_ends;
        }

        if (range_starts == range_ends){

                return range_starts;
            }




        return qrand() % (range_ends - range_starts + 1) + range_starts;
}


//************************************************************************************
// determina si el numero aleatorio esta repetido para evitar repeticiones
//*************************************************************************************
bool Aleatorio::Repetido(int numero){



    QFile file(Path + "/radit.txt");
         if (!file.open(QIODevice::WriteOnly| QIODevice::ReadOnly| QIODevice::Text))
             return(true);


         QTextStream out(&file);

         while (!out.atEnd()) {
                  QString line = out.readLine();
                  if(numero==line.toInt()){return(false);} // esta repetido

                }


         out << numero;
         out << "\n";
         return(true);


}

//***************************************************************
// si estan todos reproducios pone a 0 el indice
//***************************************************************
 void Aleatorio::Todos(){

    int TotalReproducidos=0;

    QFile file(Path + "/radit.txt");
         file.open(QIODevice::WriteOnly| QIODevice::ReadOnly| QIODevice::Text);


         QTextStream out(&file);
         QString line;
         while (!out.atEnd()) {
              line = out.readLine();
                 ++TotalReproducidos;

               }


         if(TotalFicheros<=TotalReproducidos){   // si el total de ficheros es menos o igual que el indice borra indice
             file.remove();

             Nuevo(line.toInt());   // marca el ultimo en el indice evita repetir el ultimo


          }




}


 //***************************************************************
 // Marca el ultimo reproducido en el indice evita que el ultimo sea el primero
 //***************************************************************
  void Aleatorio::Nuevo(int ultimo){
      QFile file(Path + "/radit.txt");
           file.open(QIODevice::WriteOnly| QIODevice::ReadOnly| QIODevice::Text);


           QTextStream out(&file);

           out << ultimo;
           out << "\n";


  }



//////////////////////////////////////////////////////////////////////////////////

  void Aleatorio::CrearIndice(const QString url){


      QFile fexiste( url + "/index.dat" );
        if(fexiste.exists())
          return;
        fexiste.close();





      QList<QString> list;

      QStringList filters;
      filters << "*.mp3" << "*.mp2" << "*.mp1" << "*.ogg" << "*.wav" << "*.aif" <<"*.wma"  <<"*.flac";
      QDirIterator it(url,filters, QDir::Files|QDir::NoSymLinks, QDirIterator::Subdirectories);


       while (it.hasNext()) {
              QString qstr = it.next();
              list << qstr ;

              }



       QFile file( url + "/index.dat" );
         if( !file.open( QIODevice::WriteOnly ) )
           return;

         QDataStream stream( &file );
         stream.setVersion( QDataStream::Qt_4_2 );

         stream << list;

         file.close();

  }

/////////////////////////////////////////////////////////////////////////////////
