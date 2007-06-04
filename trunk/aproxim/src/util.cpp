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

#include "util.h"

void LinearParameters(double x, double y, double &x1, double &y1, unsigned char func, signed char n0)
{
    switch (func)
    {
        case 0:
        x1 = x;
        y1 = y;
        break;
        case 1:
        x1 = x;
        y1 = y;
        break;
        case 2:
        x1 = 1 / x;
        y1 = y;
        break;
        case 3:
        x1 = log(abs(x));
        y1 = log(abs(y));
        break;
        case 4:
        x1 = x;
        y1 = log(abs(y));
        break;
        case 5:
        x1 = x;
        y1 = log(abs(y));
        break;
        case 6:
        x1 = x;
        y1 = log(abs(y));
        break;
        case 7:
        x1 = x;
        y1 = log(abs(y));
        break;
        case 8:
        x1 = log(abs(x)) / 2.3;
        y1 = y;
        break;
        case 9:
        x1 = log(abs(x));
        y1 = y;
        break;
        case 10:
        x1 = 1 / x;
        y1 = 1 / y;
        break;
        case 11:
        x1 = 1 / x;
        y1 = 1 / y;
        break;
        case 12:
        x1 = x;
        y1 = 1 / y;
        break;
        case 13:
        x1 = x;
        y1 = log(abs(y));
        break;
        case 14:
        x1 = exp(-x);
        y1 = 1 / y;
        break;
        case 15:
        x1 = x;
        y1 = 1 / y;
        break;
        case 16:
        x1 = 1 / x;
        y1 = log(abs(y));
        break;
        case 17:
        x1 = 1 / x;
        y1 = log(abs(y));
        break;
        case 18:
        x1 = pow(x, n0);
        y1 = y;
        break;
        case 19:
        x1 = x;
        y1 = y;
        break;
        case 20:
        x1 = log(abs(x));
        y1 = log(abs(y));
        break;
    }
}

void CalculateParameters(double a, double b, double &a1, double &b1, unsigned char func)
{
    switch (func)
    {
    case 0:
    a1 = a;
    b1 = b;
    break;
    case 1:
    a1 = a;
    b1 = b;
    break;
    case 2:
    a1 = a;
    b1 = b;
    break;
    case 3:
    a1 = a;
    b1 = exp(b);
    break;
    case 4:
    a1 = a / log((double)10);
    b1 = b / log((double)10);
    break;
    case 5:
    a1 = a;
    b1 = b;
    break;
    case 6:
    a1 = a;
    b1 = exp(b);
    break;
    case 7:
    a1 = exp(a);
    b1 = exp(b);
    break;
    case 8:
    a1 = a;
    b1 = b;
    break;
    case 9:
    a1 = a;
    b1 = b;
    break;
    case 10:
    a1 = a;
    b1 = b;
    break;
    case 11:
    a1 = a / b;
    b1 = 1 / b;
    break;
    case 12:
    a1 = a;
    b1 = b;
    break;
    case 13:
    a1 = a / log((double)10);
    b1 = exp(b);
    break;
    case 14:
    a1 = a;
    b1 = b;
    break;
    case 15:
    a1 = b / a;
    b1 = 1 / a;
    break;
    case 16:
    a1 = a;
    b1 = exp(b);
    break;
    case 17:
    a1 = a / log((double)10);
    b1 = exp(b);
    break;
    case 18:
    a1 = a;
    b1 = b;
    break;
    case 20:
    a1 = b;
    b1 = exp(a);
    break;
    }
}

int LinearData(const exp_data &src_data, exp_data &linear_data, signed char n0, unsigned char f)
{
    int row = 0;
	for (iter index = src_data.begin();index != src_data.end();index++)
    {
        row++;
        double x = (*index).first;
        double y = (*index).second;
        double x1, y1;
        try
        {
            LinearParameters(x, y, x1, y1, f, n0);
        }
        catch (exception &ee)
        {
			return row;
        }
        linear_data.push_back(point(x1,y1));
    }
	return 0;
}

int LinearData(const exp_data &src_data, exp_data_2 &linear_data_2, signed char n0, unsigned char f)
{
    int row = 0;
    for (iter index = src_data.begin();index != src_data.end();index++)
    {
        row++;
        double x = (*index).first;
        double y = (*index).second;
        double x1, y1;
        try
        {
            LinearParameters(x, y, x1, y1, f, n0);
        }
        catch (exception &ee)
        {
			return row;
        }
        linear_data_2.push_back(point_2(x1,x,y1));
    }
	return 0;
}

int CalculateData(exp_data &src_data, exp_data &dst_data, double &a1, double &b1, double &b2, signed char n0, vector<double> &mbx, unsigned char f)
{
	vector<point> linear_data;
	vector<point_2> linear_data_2;
    signed char sign = n0 >= 0 ? 1 : -1;
    linear_data.clear();
    dst_data.clear();
    linear_data_2.clear();
	int res = 0;
    if (f <= 19) res = LinearData(src_data, linear_data, n0, f);
    if (f == 20) res = LinearData(src_data, linear_data_2, n0, f);
	if (res != 0) return res;
    double a = 0;
	double b = 0;
    if (f == 19)
    {
        if (!Approximator::GetPolynom(linear_data, mbx, n0 + sign))
        {
            f = 1;
			return -1;
        }
    }
    if (f <= 18)
    {
        a = Approximator::GetA(linear_data);
        b = Approximator::GetB(linear_data);
    }
    if (f == 20)
    {
        a = Approximator_2::GetA(linear_data_2);
        b = Approximator_2::GetB(linear_data_2);
        b2 = Approximator_2::GetB2(linear_data_2);
    }
    CalculateParameters(a, b, a1, b1, f);
    function deps[17] = {Func1,Func2,Func3,Func4,Func5,Func6,Func7,Func8,
        Func9,Func10,Func11,Func12,Func13,Func14,Func15,Func16,Func17};
    for (iter index = src_data.begin();index != src_data.end();index++)
    {
        double x1 = 0;
		double y1 = 0;
        x1 = (*index).first;
        if (f <= 1)
        {
            y1 = deps[0](a1, b1, x1);
        }
        else
        {
            if (f < 18)
            {
                y1 = deps[f - 1](a1, b1, x1);
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
        dst_data.push_back(point(x1,y1));
    }
	return 0;
}

void CalculateCoefficients(const exp_data &src_data, const exp_data &dst_data, const vector<double> &mbx, signed char n0, double &delta, double &sigma, double &r, double &nu, unsigned char f)
{
	vector<point> linear_data;
	vector<point_2> linear_data_2;
    linear_data.clear();
    linear_data_2.clear();
    signed char sign = n0 >= 0 ? 1 : -1;
    if (f <= 18)
    {
        LinearData(src_data, linear_data, n0, f);
		delta = Approximator::Delta(src_data, dst_data);
        sigma = Approximator::Sigma(linear_data);
        r = Approximator::Correlation(linear_data);
    }
    if (f == 19)
    {
        LinearData(src_data, linear_data, n0, f);
        delta = Approximator::Delta(src_data, dst_data);
        sigma = Approximator::PolynomSigma(linear_data, mbx, n0 + sign);
        nu = Approximator::CorrelationRatio(linear_data, dst_data);
    }
    if (f == 20)
    {
        LinearData(src_data, linear_data_2, n0, f);
        delta = Approximator::Delta(src_data, dst_data);
        sigma = Approximator_2::Sigma(linear_data_2);
        r = Approximator_2::Correlation(linear_data_2);
    }
}

point CalculateMax(const exp_data &data)
{
	int f = 0;
	point result = data[0];
	do
	{
		f = 0;
		for (unsigned index = 0;index < data.size();index++)
		{
			if (result.first < data[index].first)
			{
				result.first = data[index].first;
				f = 1;
			}
			if (result.second < data[index].second)
			{
				result.second = data[index].second;
				f = 1;
			}
		}
	}
	while (f == 1);
	return result;
}

point CalculateMin(const exp_data &data)
{
	int f = 0;
	point result = data[0];
	do
	{
		f = 0;
		for (unsigned index = 0;index < data.size();index++)
		{
			if (result.first > data[index].first)
			{
				result.first = data[index].first;
				f = 1;
			}
			if (result.second > data[index].second)
			{
				result.second = data[index].second;
				f = 1;
			}
		}
	}
	while (f == 1);
	return result;
}
