/**
 * Hth
 * -----------------------------------------
 *
 * - This class uses to play time, temperature and humidity.
 *
 * @author Victor Algaba
 */
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>
#include <stdlib.h>
#include "Hth.h"
#include "StreamMath.h"

Hth::Hth(QObject *parent):
    QObject(parent)
{
    Timer = new QTimer();
    connect(Timer, SIGNAL(timeout()), this, SLOT(Update())); // temporizaor horario
    IsHFinal=false;//Ha reproducido la hora
    IsMFinal=false;

    IsHora=false;
    IsTemperatura=false;
    IsHumedad=false;
    Path=QCoreApplication::applicationDirPath().toLatin1();

    LeerClima();
}

Hth::~Hth()
{
    BASS_StreamFree(stream); //lo liberamos
}

void Hth::StartHora()
{
    BASS_SetDevice(Dispositivo);    //dispositivo

    IsHora=true;
    emit Iniciar();

    QDateTime dateTime = QDateTime::currentDateTime();// obtenemos la hora
    QTime playTime=dateTime.time(); // para descomponer la hora

    QString Hora , Minutos; //Path;
    //Path=QCoreApplication::applicationDirPath().toLatin1();

    Hora= "HRS" + playTime.toString("hh")+ QString(".mp3").toLower();  //obtenemos fichero de hora
    Minutos ="MIN" + playTime.toString("mm")+ QString(".mp3").toLower();  //obtenemos fichero de minutos

    //hora en punto
    if (playTime.minute()==0)
    {
        Hora= "HRS" + playTime.toString("hh")+ "_O" + QString(".mp3").toLower(); //obtenemos fichero hora en punto añadiendo _O
        IsMFinal=true; //evita decir minutos
    }

    if(!IsHFinal)//si no se ha reprodcido la hora
    {
        IsHFinal=true;
        stream=BASS_StreamCreateFile(FALSE, Path.toLatin1() + "/Hth/Time/"+ Hora.toLatin1(), 0, 0, 0);
        BASS_ChannelPlay(stream,false);
        Timer->start(30);
        return;
    }

    if(!IsMFinal)// si no se ha reproducido los minutos
    {
        IsMFinal=true;
        BASS_StreamFree(stream); //lo liberamos
        stream=BASS_StreamCreateFile(FALSE, Path.toLatin1() + "/Hth/Time/" + Minutos.toLatin1(), 0, 0, 0);
        BASS_ChannelPlay(stream,false);
        Timer->start(30);
        return;
    }


    emit Finish(); //si es hora en punto
}

/**
 * Locution temperature
 * @brief Hth::StartTemp
 * @return void
 */
void Hth::StartTemp()//locuta la temperatura
{
    BASS_SetDevice(Dispositivo);    //dispositivo
    LeerClima();  //Actaulizamos los datos

    QFileInfo File(Path.toLatin1() + "/Hth/Temp/TMP" + Temperatura.toLatin1() + ".mp3");

    IsTemperatura=true;
    BASS_StreamFree(stream);//lo liberamos
    stream=BASS_StreamCreateFile(FALSE, File.absoluteFilePath().toLatin1(), 0, 0, 0);
    BASS_ChannelPlay(stream,false);
    Timer->start(30);
}

/**
 * Locution Humidity
 * @brief Hth::StartHumedad
 * @return void
 */
void Hth::StartHumedad()
{
    BASS_SetDevice(Dispositivo);    //dispositivo
    LeerClima();

    QFileInfo File(Path.toLatin1() + "/Hth/Hume/HUM" + Humedad.toLatin1() + ".mp3");

    IsTemperatura=true;
    BASS_StreamFree(stream); //lo liberamos
    stream=BASS_StreamCreateFile(FALSE, File.absoluteFilePath().toLatin1(), 0, 0, 0);
    BASS_ChannelPlay(stream,false);
    Timer->start(30);
}

/**
 * This function processes the time
 * @brief Hth::Update
 * @return void
 */
void Hth::Update()
{
    if (IsFinal(stream))//checks if hstream is the end
    {
        Timer->stop();

        if(IsHora)// es hora
        {
            if(IsMFinal)// primero comprobamos los minutos, si es el final de los minutos
            {
                emit Finish();         // Se reproducieros las hora y mandamos la señal de final
                IsHora=false;
                return;
            }

            if(IsHFinal)
            {
                StartHora();
                return;
            }

          }

        emit Finish();         // es temperatura/humedad
     }
}

/**
 * This function checks if is the end of pre listening
 * @brief Hth::IsFinal
 * @param cual Hstream
 * @return true or false
 */
bool Hth::IsFinal(HSTREAM cual)
{
    if(BASS_ChannelIsActive(cual)!=BASS_ACTIVE_PLAYING)
        return(true);
    else
        return(false);
}

/**
 * This fucntion get the configuration of radit
 * @brief Hth::Configuracion
 * @param Player
 * @return void
 */
void Hth::Configuracion(const QString Player)
{
    QSettings RaditIni("Radit.ini", QSettings::IniFormat);
    Dispositivo=RaditIni.value(Player + "/Dispositivo").toInt();
    IsHFinal=false;//Ha reproducido la hora
    IsMFinal=false;
}

/**
 * This function read temperature and humidity
 * @brief Hth::LeerClima
 * @return void
 */
void Hth:: LeerClima()
{
    QFile file(Path.toLatin1() + "/Currenweather/currenweather.txt");//select file

    if (!file.open( QIODevice::ReadOnly| QIODevice::Text))
        return;

    int tempo;
    bool MenosCero=false;

    QTextStream out(&file);
    QString line=out.readLine();

    Temperatura=line.left(2);

    tempo=Temperatura.toInt();

    if(tempo<0)
    {
        tempo=abs(tempo);
        MenosCero=true;
    }

    Temperatura=Temperatura.setNum(tempo);

    if(tempo<10)
    {
        Temperatura= "0" + Temperatura;
    }

         Temperatura= "0" + Temperatura;

    if(MenosCero)
    {
        Temperatura= "N" + Temperatura;
    }

    Humedad=line.right(3);
    // qDebug() <<Humedad;
    Humedad=Humedad.left(3);
    tempo= Humedad.toInt();
    Humedad=Humedad.setNum(tempo);

    if(tempo<10)
        Humedad = "0" + Humedad;

    if(tempo !=100)
        Humedad = "0" +Humedad;

    file.close();
}
