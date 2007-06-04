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

#ifndef UtilH
#define UtilH

#include <vector>

#include "approximator.h"
#include "approximator_2.h"
#include "functions.h"

typedef vector<point> exp_data;
typedef vector<point_2> exp_data_2;
typedef vector<point>::const_iterator iter;

void LinearParameters(double x, double y, double &x1, double &y1, unsigned char func, signed char n0);
int LinearData(const exp_data &src_data, exp_data &linear_data, signed char n0, unsigned char f);
int LinearData(const exp_data &src_data, exp_data_2 &linear_data_2, signed char n0, unsigned char f);
void CalculateParameters(double a, double b, double &a1, double &b1, unsigned char func);
int CalculateData(exp_data &src_data, exp_data &dst_data, double &a1, double &b1, double &b2, signed char n0, vector<double> &mbx, unsigned char f);
void CalculateCoefficients(const exp_data &src_data, const exp_data &dst_data, const vector<double> &mbx, signed char n0, double &delta, double &sigma, double &r, double &nu, unsigned char f);
point CalculateMax(const exp_data &data);
point CalculateMin(const exp_data &data);

#endif
