/*
 * Copyright (c) 2006, Anatoly Sova All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution. 
 * Neither the name of the author nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <qapplication.h>
#include <qstylefactory.h>

#include "form1.h"

#define WORDS 11

QString English[WORDS] = {"Average deflection: ","Average quadratic deflection: ",
    "Correlation coefficient: ","Select function","Input power N","Chart","Language","Data","Precision",
    "Correlation ratio: ","Style"};
QString Ukrainian[WORDS] = {"Середнє відхилення: ","Середньоквадратичне відхилення: ",
    "Коефіціент кореляції: ","Оберіть функцію",
    "Введіть ступінь N","Діаграма","Мова","Дані","Точність",
    "Кореляційне відношення: ","Стиль"};
QString Russian[WORDS] = {"Среднее отклонение: ","Среднеквадратическое отклонение: ",
    "Коэффициент корреляции: ","Выберите функцию","Введите степень N","Диаграмма","Язык","Данные",
    "Точность","Корреляционное отношение: ","Стиль"};
QString German[WORDS] = {"Mittel Abweichen: ","Mittelquadratisch Abweichen: ",
    "Korrelation Koeffizient: ","Funktion wahlen","Hineinfuhren Potenz N","Schaubild","Sprache","Daten",
    "Prazision","Ansatz: ","Stil"};
QString Spanish[WORDS] = {"Medio desviacion: ","Medio cuadrado desviacion: ",
    "Coeficiente de correlacion: ","Elegir funcion","Establecer grado N","Diagrama","Lengua","Datos",
    "Precision","Razon de correlacion: ","Estilo"};
QString* Language[5] = {English,Ukrainian,Russian,German,Spanish};
int lang = 0;

void Options::OK_Click()
{
	QApplication::setStyle(comboBox1->text(comboBox1->currentItem()));
	lang = comboBox2->currentItem();
}


void Options::init()
{
	for (unsigned index = 0;index < QStyleFactory::keys().size();index++)
	{
		comboBox1->insertItem(QStyleFactory::keys()[index]);
	}
}


void Options::destroy()
{

}
