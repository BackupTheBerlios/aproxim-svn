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
#include "xls_table.h"

XLS_Table::XLS_Table()
{
}

XLS_Table::XLS_Table(int rows, int cols)
{
	this->cols = cols;
	this->rows = rows;
	this->cells = new string*[rows];
	for (int index = 0;index < rows;index++)
	{
		this->cells[index] = new string[cols];
	}
}

XLS_Table::~XLS_Table()
{
}

void XLS_Table::setCell(int row, int col, string &value)
{
	cells[row - 1][col - 1] = value;
}

string XLS_Table::toXLS()
{
	string s = "";
	for(int i = 0;i < rows;i++)
	{
		for(int j = 0;j < cols;j++)
		{
			s += cells[i][j];
			if (j < cols - 1) s += '\t';
		}
		s += '\n';
	}
	return s;
}

void XLS_Table::saveXLS(string filename)
{
	for(int y = 1;y <= cols;y++)
	{
		for(int x = 1;x <= rows;x++)
		{
			setCell(y, x, cells[y - 1][x - 1]);
		}
	}
	ofstream out(filename.c_str());
	out << toXLS();
	out.flush();
}
