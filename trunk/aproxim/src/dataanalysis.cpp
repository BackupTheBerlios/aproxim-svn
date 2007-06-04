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
#include "dataanalysis.h"

DataAnalysis::DataAnalysis()
{
}


DataAnalysis::~DataAnalysis()
{
}


double DataAnalysis::Lagrange(const exp_data &data, double t, double &p)
{
    vector <double> x;
	vector <double> f;
	for (iter index = data.begin();index != data.end();index++)
	{
		x.push_back((*index).first);
		f.push_back((*index).second);
	}
	int m;
    int i;
	int n = data.size();
    vector <double> df(n + 1);

    n = n-1;
    for(i = 0; i <= n; i++)
    {
        df[i] = 0;
    }
    for(m = 1; m <= n; m++)
    {
        for(i = 0; i <= n-m; i++)
        {
            df[i] = ((t-x[i + m]) * df[i] + f[i] + (x[i] - t) * df[i + 1]-f[i + 1]) / (x[i] - x[i + m]);
            f[i] = ((t-x[i + m]) * f[i] + (x[i] - t) * f[i + 1]) / (x[i] - x[i + m]);
        }
    }
    p = f[0];
	return df[0];
}


double DataAnalysis::Simpson(double a, double b, const exp_data &data)
{
	double epsilon = 0.0001;
    double h;
    double s;
    double s1;
    double s2;
    double s3;
    double x;

    s2 = 1;
    h = b - a;
    s = LagrangeI(data, a) + LagrangeI(data, b);
    do
    {
        s3 = s2;
        h = double(h) / double(2);
        s1 = 0;
        x = a + h;
        do
        {
            s1 = s1 + 2 * LagrangeI(data, x);
            x = x + 2 * h;
        }
        while(x < b);
        s = s + s1;
        s2 = double((s + s1) * h) / double(3);
        x = double(fabs(s3 - s2)) / double(15);
    }
    while(x > epsilon);
    return s2;
}

double DataAnalysis::LagrangeI(const exp_data &data, double t)
{
	double res;
	Lagrange(data, t, res);
	return res;
}

double DataAnalysis::LagrangeD(const exp_data &data, double t)
{
	double p;
	return Lagrange(data, t, p);
}





	
	
	
