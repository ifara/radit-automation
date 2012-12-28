
/****************************************************************************
 **
 ** Copyright (C) 2012 Victor Algaba .
 ** All rights reserved.
 ** Contact: (www.radit.org)
 **
 ** *************************************************************************/





#ifndef ADDHORA_H
#define ADDHORA_H

#include "ui_FrmHora.h"


class AddHora : public QDialog, public Ui::FrmHora
 {
     Q_OBJECT

 private:


 public:
     explicit AddHora(QWidget *parent = 0);
     virtual ~AddHora(){;}

public slots:
void Todos();
void Ninguna();

private slots:


signals:



 };







#endif // ADDHORA_H
