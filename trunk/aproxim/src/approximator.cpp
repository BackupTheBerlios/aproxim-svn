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
//---------------------------------------------------------------------------


#include "approximator.h"
//---------------------------------------------------------------------------

double Approximator::GetParameter(const vector<point> &data, string operation)
{
    double result = 0;
    int n = data.size();
    typedef vector<point>::const_iterator iter;
    for (iter index = data.begin();index != data.end();index++)
    {
        if (operation == "AV_X")
        {
            result += (*index).first / n;
        }
        if (operation == "AV_Y")
        {
            result += (*index).second / n;
        }
        if (operation == "SUM_X")
        {
            result += (*index).first;
        }
        if (operation == "SUM_Y")
        {
            result += (*index).second;
        }
        if (operation == "SUM_XY")
        {
            result += (*index).first * (*index).second;
        }
        if (operation == "SUM_X2")
        {
            result += pow((*index).first, 2);
        }
        if (operation == "SIGMA_X")
        {
            result += pow((*index).first - GetParameter(data, "AV_X"), 2);
        }
        if (operation == "SIGMA_Y")
        {
            result += pow((*index).second - GetParameter(data, "AV_Y"), 2);
        }
        if (operation == "SIGMA_XY")
        {
            double val1 = (*index).first - GetParameter(data, "AV_X");
            double val2 = (*index).second - GetParameter(data, "AV_Y");
            result += val1 * val2;
        }
    }
    if (operation == "SIGMA_X" || operation == "SIGMA_Y" || operation == "SIGMA_XY")
    {
        result /= n;
        result = sqrt(abs(result));
    }
    return result;
}

double Approximator::GetA(const vector<point> &data)
{
    double result = 0;
    int n = data.size();
    double sx = GetParameter(data, "SUM_X");
    double sy = GetParameter(data, "SUM_Y");
    double sxy = GetParameter(data, "SUM_XY");
    double sx2 = GetParameter(data, "SUM_X2");
    result = sx * sy - n * sxy;
    result /= (pow(sx, 2) - n * sx2);
    return result;
}

double Approximator::GetB(const vector<point> &data)
{
    double result = 0;
    int n = data.size();
    double sx = GetParameter(data, "SUM_X");
    double sy = GetParameter(data, "SUM_Y");
    double sxy = GetParameter(data, "SUM_XY");
    double sx2 = GetParameter(data, "SUM_X2");
    result = sx * sxy - sy * sx2;
    result /= (pow(sx, 2) - n * sx2);
    return result;
}

double Approximator::Delta(const vector<point> &data1, const vector<point> &data2)
{
    double result = 0;
    int n = data1.size();
    for (int index = 0;index < n;index++)
    {
        result += (100 * abs(data1[index].second - data2[index].second)) / data1[index].second;
    }
    result /= n;
    return result;
}

double Approximator::Sigma(const vector<point> &data)
{
    double result = 0;
    typedef vector<point>::const_iterator iter;
    int n = data.size();
    double a = GetA(data);
    double b = GetB(data);
    for (iter index = data.begin();index != data.end();index++)
    {
        result += pow((*index).second - b - a * (*index).first, 2);
    }
    result /= n;
    result = sqrt(abs(result));
    return result;
}

double Approximator::PolynomSigma(const vector<point> &data, const vector<double> &mbx, signed char n0)
{
    double result = 0;
    typedef vector<point>::const_iterator iter;
    int n = data.size();
    for (iter index = data.begin();index != data.end();index++)
    {
        double r = 0;
	    signed char sign = n0 >= 0 ? 1 : -1;
        for (signed char idx = sign;idx != n0;idx += sign)
        {
            r += mbx[abs(idx)] * pow((*index).first, idx);
        }
        r += mbx[0];
        result += pow((*index).second - r, 2);
    }
    result /= n;
    result = sqrt(abs(result));
    return result;
}

double Approximator::Correlation(const vector<point> &data)
{
    double result = 0;
    result = pow(GetParameter(data, "SIGMA_XY"), 2);
    result /= GetParameter(data, "SIGMA_X");
    result /= GetParameter(data, "SIGMA_Y");
    return result;
}

double Approximator::CorrelationRatio(const vector<point> &linear_data, const vector<point> &dst_data)
{
    double result = 0;
    int n = dst_data.size();
    double sry = GetParameter(dst_data, "AV_Y");
    double sigma2 = 0;
    double lambda2 = 0;
    typedef vector<point>::const_iterator iter;
    for (iter index = dst_data.begin();index != dst_data.end();index++)
    {
        sigma2 += pow((*index).second - sry, 2);
    }
    sigma2 /= n;
    for (iter index = linear_data.begin();index != linear_data.end();index++)
    {
        lambda2 += pow((*index).second - sry, 2);
    }
    lambda2 /= n;
    result = sqrt(sigma2 / lambda2);
    return result;
}

bool Approximator::Zeidel(const matrix &a, const vector<double> &b, vector<double> &x, unsigned char n)
{
	double e = 0.0001;
	unsigned char i, j;
	double s1, s2, v, m;
	int iCount = 0;
	do
	{
		m = 0;
		for (i = 0;i < n;i++)
		{
			s1 = 0;
			s2 = 0;
			for (j = 0;j < i;j++) s1 += a[i][j] * x[j];
			for (j = i;j < n;j++) s2 += a[i][j] * x[j];
			v=x[i];
			x[i] -= ((double)1 / a[i][i]) * (s1 + s2 - b[i]);
			if (fabs(v - x[i]) > m) m = fabs(v - x[i]);
		}
		iCount++;
		if (iCount > 1000000) return false;
	}
	while (m >= e);
	return true;
}

bool Approximator::GetPolynom(const vector<point> &data, vector<double> &mbx, signed char n)
{
    vector<double> sy;
    sy.resize(abs(n), 0);
    vector<double> sx;
    sx.resize(2 * abs(n) - 1, 0);
    matrix a(extents[n][n]);
	mbx.clear();
    mbx.resize(abs(n), 0);
    typedef vector<point>::const_iterator iter;
    signed char sign = n >= 0 ? 1 : -1;
    for (signed char index = 0;index != 2 * n - sign;index += sign)
    {
        for (iter idx = data.begin();idx != data.end();idx++)
        {
            sx[abs(index)] += pow((*idx).first, index);
        }
    }
    for (signed char index = 0;index != n;index += sign)
    {
        for (iter idx = data.begin();idx != data.end();idx++)
        {
            sy[abs(index)] += (*idx).second * pow((*idx).first, index);
        }
    }
    for (signed char i = 0;i < abs(n);i++)
    {
        for (signed char j = 0;j < abs(n);j++)
        {
			a[i][j] = sx[i+j];           
        }
    }
	bool result = Zeidel(a, sy, mbx, abs(n));
    return result;
}

