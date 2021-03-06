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

#ifndef ApproximatorH
#define ApproximatorH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <cmath>
#include <boost/multi_array.hpp>
using namespace std;
using namespace boost;

typedef pair<double,double> point;
typedef multi_array<double,2> matrix;

class Approximator
{
public:
    static double GetA(const vector<point> &data);
    static double GetB(const vector<point> &data);
    static double Delta(const vector<point> &data1, const vector<point> &data2);
    static double Sigma(const vector<point> &data);
    static double Correlation(const vector<point> &data);
    static bool GetPolynom(const vector<point> &data, vector<double> &mbx, signed char n);
    static double PolynomSigma(const vector<point> &data, const vector<double> &mbx, signed char n0);
    static double CorrelationRatio(const vector<point> &linear_data, const vector<point> &dst_data);
protected:
    static double GetParameter(const vector<point> &data, string operation);
	Approximator();
private:
    static bool Zeidel(const matrix &a, const vector<double> &b, vector<double> &x, unsigned char n);
};
#endif
