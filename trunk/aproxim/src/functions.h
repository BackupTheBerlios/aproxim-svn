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

#ifndef FunctionsH
#define FunctionsH
//---------------------------------------------------------------------------
#include <vector>
#include <cmath>
using namespace std;

//---------------------------------------------------------------------------

typedef double (*function)(double a, double b, double x);

double Func1(double a, double b, double x);
double Func2(double a, double b, double x);
double Func3(double a, double b, double x);
double Func4(double a, double b, double x);
double Func5(double a, double b, double x);
double Func6(double a, double b, double x);
double Func7(double a, double b, double x);
double Func8(double a, double b, double x);
double Func9(double a, double b, double x);
double Func10(double a, double b, double x);
double Func11(double a, double b, double x);
double Func12(double a, double b, double x);
double Func13(double a, double b, double x);
double Func14(double a, double b, double x);
double Func15(double a, double b, double x);
double Func16(double a, double b, double x);
double Func17(double a, double b, double x);
double Func18(double a, double b, double x, signed char n0);
double Func19(vector<double> &mbx, double x, signed char n0);
double Func20(double a, double b1, double b2, double x);
#endif
