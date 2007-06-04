/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include <string>
#include <vector>
#include <exception>
#include <cstdio>
#include <qapplication.h>
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include <qpen.h>
#include <qcolor.h>
#include <qtextcodec.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "xls_table.h"
#include "options.h"

#include "approximator.h"
#include "approximator_2.h"
#include "functions.h"
#include "util.h"
#include "dataanalysis.h"

using namespace std;

double a1, b1, b2;
vector<double> mbx;
double *data_x = 0; 
double *data_y = 0; 
double *data_y1 = 0;
signed char n0 = 0;
extern QString* Language[5];
extern int lang;
QwtPlotCurve *curve1;
QwtPlotCurve *curve2;

void Form1::toolButton1Click()
{
    for (int i = 0;i < table1->numCols();i++)
    {
		for (int j = 0;j < table1->numRows();j++)
		{
			table1->setText(j, i, "");
		}
    }
}

int split(string &src, vector <string> &dst, char c)
{
    int count = 0;
    int old_pos = -1, pos = -1;
    dst.clear();
    do
    {
        old_pos = pos;
        pos = src.find(c, pos + 1);
        if (pos != -1)
        {
            dst.push_back(src.substr(old_pos + 1, pos - old_pos - 1));
            count++;
        }
    }
    while(pos != -1);
    string str = src.substr(old_pos + 1, src.length() - old_pos - 1);
    dst.push_back(str);
    count++;
    return count;
}

void Form1::toolButton2Click()
{
	QString filename = QFileDialog::getOpenFileName(NULL,"Text files (*.txt)",this);
	if (filename != "")
    {
        FILE *f;
		f = fopen((const char*)filename, "rb");
        char *s = new char[100];
        int index = 0;
		while (!feof(f))
        {
		int idx = -1;
		do
		{
			idx++;
			fread(&s[idx], 1, 1, f);
		}
		while (s[idx] != '\n');
		s[idx] = '\0';
		string str = s;
	    vector <string> values;
        split(str, values, '\t');
        if (!feof(f))
		{
			table1->setText(index, 0, values[0].c_str());
			table1->setText(index, 1, values[1].c_str());
		}
	        index++;
        }
        delete[] s;
        fclose(f);
    }
}


void Form1::toolButton3Click()
{
	QString filename = QFileDialog::getSaveFileName(NULL,"Text files (*.txt)",this);
	if (filename != "")
	{
        FILE *f;
        f = fopen((const char*)filename, "wb+");
		char t = '\t';
		char n = '\n';
		fwrite((const char*)table1->text(0, 0), 1, table1->text(0, 0).length(), f);
        fwrite(&t, 1, 1, f);
		fwrite((const char*)table1->text(0, 1), 1, table1->text(0, 1).length(), f);
	    fwrite(&n, 1, 1, f);
        int index = 0;
		do
	    {
        	index++;
			if (table1->text(index, 0) != "" && table1->text(index, 1) != "")
		    {
				fwrite((const char*)table1->text(index, 0), 1, table1->text(index, 0).length(), f);
        		fwrite(&t, 1, 1, f);
				fwrite((const char*)table1->text(index, 1), 1, table1->text(index, 1).length(), f);
		    	fwrite(&n, 1, 1, f);
            }
        }
        while (table1->text(index, 0) != "" && table1->text(index, 1) != "");
        fclose(f);
    }
}

void Form1::toolButton4Click()
{
	vector<point> src_data;
	vector<point> linear_data;
	vector<point> dst_data;
	vector<point_2> linear_data_2;
	double delta = 0;
	double sigma = 0;
	double r = 0;
	double nu = 0;
	unsigned char f = 0;
    src_data.clear();
    linear_data.clear();
    dst_data.clear();
    linear_data_2.clear();
    double precision = pow((double)10, (int)spinBox1->value());
    double x, y;
    int index = -1;
    f = comboBox1->currentItem() + 1;
    do
    {
        index++;
        if (table1->text(index, 0) != "" && table1->text(index, 1) != "")
        {
			table1->text(index, 0).replace(',', '.');
        	table1->text(index, 1).replace(',', '.');
    		x = strtod((const char*)table1->text(index, 0), NULL);
	        y = strtod((const char*)table1->text(index, 1), NULL);
           	src_data.push_back(point(x,y));
        }
    }
    while (table1->text(index, 0) != "" && table1->text(index, 1) != "");
    typedef vector<point>::const_iterator iter;
    if (f == 18 || f == 19)
    {
        n0 = (signed char)QInputDialog::getInteger(tr(Language[lang][4]),"",1);
    }
    int row = CalculateData(src_data, dst_data, a1, b1, b2, n0, mbx, f);
	if (row != 0)
	{
		if (row == -1)
		{
			QMessageBox::about(this, "Error", "Solution not found");
		}
		if (row > 0)
		{
			QMessageBox::about(this, "Error", "Division by zero in row " + QString::number(row));
		}
		return;
	}
    qwtPlot1->clear();
	curve1 = new QwtPlotCurve("Graph 1");
	curve2 = new QwtPlotCurve("Graph 1");
	QColor blue(0, 0, 255);
	QColor red(255, 0, 0);
	QPen blue_pen(blue);
	QPen red_pen(red);
	curve1->setPen(blue_pen);
	curve2->setPen(red_pen);
	if (data_x) delete data_x;
	if (data_y) delete data_y;
	if (data_y1) delete data_y1;
	data_x = new double[src_data.size()]; 
	data_y = new double[src_data.size()]; 
	data_y1 = new double[src_data.size()];
    int idx = 0;
	for (iter index = src_data.begin();index != src_data.end();index++)
    {
		data_x[idx] = (*index).first;
		data_y[idx] = (*index).second;
		idx++;
    }
    idx = 0;
	for (iter index = dst_data.begin();index != dst_data.end();index++)
    {
        data_y1[idx] = (*index).second;
        double value = (*index).second;
        value = floor(value * precision);
        value /= precision;
        table1->setText(idx, 2, QString::number(value));
        table1->text(idx, 2).replace(',', '.');
        idx++;
    }
    for (unsigned index = 0;index < src_data.size();index++)
    {
        double d = (100 * abs(src_data[index].second - dst_data[index].second));
        d /= src_data[index].second;
        d = floor(d * precision);
        d /= precision;
        table1->setText(index, 3, QString::number(d));
        table1->text(index, 3).replace(',', '.');
    }
	curve1->setData(data_x, data_y, src_data.size());
	curve2->setData(data_x, data_y1, src_data.size());
	curve1->attach(qwtPlot1);
	curve2->attach(qwtPlot1);
	qwtPlot1->replot();
    CalculateCoefficients(src_data, dst_data, mbx, n0, delta, sigma, r, nu, f);
    b1 = floor(b1 * precision);
    b1 /= precision;
    a1 = floor(a1 * precision);
    a1 /= precision;
    if (f <= 18 || f == 20)
    {
        textLabel2->setText("A = " + QString::number(b1));
        textLabel3->setText("B = " + QString::number(a1));
    }
    if (f == 19)
    {
        textLabel2->setText("");
        textLabel3->setText("");
        textLabel4->setText("");
        QString caption = "";
        for (unsigned char index = 0;index < abs(n0) + 1;index++)
        {
            caption += "B";
            caption += QString::number(index);
            caption += " = ";
            mbx[index] = floor(mbx[index] * precision);
            mbx[index] /= precision;
            caption += QString::number(mbx[index]);
            caption += ";";
        }
        textLabel2->setText(caption);
    }
    if (f == 20)
    {
        b2 = floor(b2 * precision);
        b2 /= precision;
        textLabel4->setText("B2 = " + QString::number(b2));
    }
    delta = floor(delta * precision);
    delta /= precision;
    textLabel5->setText(tr(Language[lang][0] + QString::number(delta)));
    sigma = floor(sigma * precision);
    sigma /= precision;
    textLabel6->setText(tr(Language[lang][1] + QString::number(sigma)));
    r = floor(r * precision);
    r /= precision;
   	nu = floor(nu * precision);
    nu /= precision;
    if (f <= 18 || f == 20)
    {
	    textLabel7->setText(tr(Language[lang][2] + QString::number(r)));
	}
    if (f == 19)
    {
        textLabel7->setText(tr(Language[lang][9] + QString::number(nu)));
	}
}

void Form1::toolButton5Click()
{
    unsigned char f = comboBox1->currentItem() + 1;
    function deps[17] = {Func1,Func2,Func3,Func4,Func5,Func6,Func7,Func8,
        Func9,Func10,Func11,Func12,Func13,Func14,Func15,Func16,Func17};
    double x1 = 0;
	double y1 = 0;
    double precision = pow((double)10, (int)spinBox1->value());
    lineEdit1->text().replace(',', '.');
    x1 = strtod((const char*)lineEdit1->text(), NULL);
    if (comboBox1->currentItem() <= 0)
    {
        y1 = deps[0](a1, b1, x1);
    }
    else
    {
        if (f < 18)
        {
            y1 = deps[comboBox1->currentItem()](a1, b1, x1);
        }
        else
        {
            if (f == 18)
            {
                y1 = Func18(a1, b1, x1, n0);
            }
            if (f == 19)
            {
                y1 = Func19(mbx, x1, n0);
            }
            if (f == 20)
            {
                y1 = Func20(a1, b1, b2, x1);
            }
        }
    }
    y1 = floor(y1 * precision);
    y1 /= precision;
    lineEdit2->setText(QString::number(y1));
}


void Form1::toolButton6Click()
{
	QTextCodec *codec = QTextCodec::codecForName("CP1251");
	QTextCodec::setCodecForTr(codec);
	Options *options = new Options();
	options->textLabel1->setText(tr(Language[lang][10]));
	options->textLabel2->setText(tr(Language[lang][6]));
	options->exec();
	if (options->result() == QDialog::Accepted)
	{
		textLabel10->setText(tr(Language[lang][8]));
		textLabel1->setText(tr(Language[lang][3]));
		textLabel5->setText(tr(Language[lang][0]));
		textLabel6->setText(tr(Language[lang][1]));
		textLabel7->setText(tr(Language[lang][2]));
	}
}


void Form1::toolButton7Click()
{
	QMessageBox::about(this, "About", "Approximator 1.5. Author - Anatoly Sova.");
}


void Form1::init()
{
	int width = table1->width();
        for (int index = 0;index < table1->numCols();index++)
        {
        	table1->setColumnWidth(index, width / table1->numCols());
        }
}


void Form1::destroy()
{
	if (data_x) delete data_x;
	if (data_y) delete data_y;
	if (data_y1) delete data_y1;
	if (curve1) delete curve1;
	if (curve2) delete curve2;
}


void Form1::toolButton10Click()
{
	vector <point> src_data;
	double x, y;
    int index = -1;
	do
    {
        index++;
        if (table1->text(index, 0) != "" && table1->text(index, 1) != "")
        {
			table1->text(index, 0).replace(',', '.');
        	table1->text(index, 1).replace(',', '.');
    		x = strtod((const char*)table1->text(index, 0), NULL);
	        y = strtod((const char*)table1->text(index, 1), NULL);
           	src_data.push_back(point(x,y));
        }
    }
    while (table1->text(index, 0) != "" && table1->text(index, 1) != "");
	for (unsigned idx = 0;idx < src_data.size();idx++)
	{
		double val = DataAnalysis::Simpson(0, src_data[idx].first, src_data);
		table1->setText(idx, 1, QString::number(val));
	}
}


void Form1::toolButton9Click()
{
	vector <point> src_data;
	double x, y;
    int index = -1;
	do
    {
        index++;
        if (table1->text(index, 0) != "" && table1->text(index, 1) != "")
        {
			table1->text(index, 0).replace(',', '.');
        	table1->text(index, 1).replace(',', '.');
    		x = strtod((const char*)table1->text(index, 0), NULL);
	        y = strtod((const char*)table1->text(index, 1), NULL);
           	src_data.push_back(point(x,y));
        }
    }
    while (table1->text(index, 0) != "" && table1->text(index, 1) != "");
	for (unsigned idx = 0;idx < src_data.size();idx++)
	{
		double val = DataAnalysis::LagrangeD(src_data, src_data[idx].first);
       	table1->setText(idx, 1, QString::number(val));
	}
}

void Form1::toolButton11Click()
{
	QString filename = QFileDialog::getSaveFileName(NULL,"Excel files (*.xls)",this);
	if (filename != "")
	{
		int count = 0;
	    int index = -1;
		do
	    {
        	index++;
    	    if (table1->text(index, 0) != "" && table1->text(index, 1) != "")
	        {
        		count++;
			}
    	}
	    while (table1->text(index, 0) != "" && table1->text(index, 1) != "");
		XLS_Table *excel = new XLS_Table(count, 4);
		string value;
	    index = -1;
		do
	    {
        	index++;
    	    if (table1->text(index, 0) != "" && table1->text(index, 1) != "")
	        {
				for (int n = 0;n < 4;n++)
				{
		        	table1->text(index, n).replace('.', ',');
    				value = (const char*)table1->text(index, n);
		        	table1->text(index, n).replace(',', '.');
					excel->setCell(index + 1, n + 1, value);
				}
        	}
    	}
	    while (table1->text(index, 0) != "" && table1->text(index, 1) != "");
		int len = filename.length();
		bool isXLS = false;
		if (len > 4)
		{
			isXLS = (filename[len - 4] == '.' && filename[len - 3] == 'x' && filename[len - 2] == 'l' && filename[len - 1] == 's');
		}
		if (!isXLS) filename += ".xls";
		excel->saveXLS(string((const char*)filename));
		delete excel;
	}
}




