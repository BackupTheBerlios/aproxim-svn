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


#include "approximator_2.h"

//---------------------------------------------------------------------------

double Approximator_2::GetParameter(const vector<point_2> &data, string operation)
{
    double result = 0;
    int n = data.size();
    typedef vector<point_2>::const_iterator iter;
    for (iter index = data.begin();index != data.end();index++)
    {
        if (operation == "AV_X1")
        {
            result += tuples::get<0>(*index);
        }
        if (operation == "AV_X2")
        {
            result += tuples::get<1>(*index);
        }
        if (operation == "AV_Y")
        {
            result += tuples::get<2>(*index);
        }
        if (operation == "SUM_X1X2")
        {
            double sx1 = GetParameter(data, "AV_X1");
            double sx2 = GetParameter(data, "AV_X2");
            double v1 = tuples::get<0>(*index) - sx1;
            double v2 = tuples::get<1>(*index) - sx2;
            result += v1 * v2;
        }
        if (operation == "SUM_X1Y")
        {
            double sx1 = GetParameter(data, "AV_X1");
            double sy = GetParameter(data, "AV_Y");
            double v1 = tuples::get<0>(*index) - sx1;
            double v2 = tuples::get<2>(*index) - sy;
            result += v1 * v2;
        }
        if (operation == "SUM_X2Y")
        {
            double sx2 = GetParameter(data, "AV_X2");
            double sy = GetParameter(data, "AV_Y");
            double v1 = tuples::get<1>(*index) - sx2;
            double v2 = tuples::get<2>(*index) - sy;
            result += v1 * v2;
        }
        if (operation == "SUM_X12")
        {
            double sx1 = GetParameter(data, "AV_X1");
            result += pow(tuples::get<0>(*index) - sx1, 2);
        }
        if (operation == "SUM_X22")
        {
            double sx2 = GetParameter(data, "AV_X2");
            result += pow(tuples::get<1>(*index) - sx2, 2);
        }
        if (operation == "SIGMA_X")
        {
            double b = GetB(data);
            double b2 = GetB2(data);
            double sx1 = GetParameter(data, "AV_X1");
            double sx2 = GetParameter(data, "AV_X2");
            double v1 = (b / b2) * (tuples::get<0>(*index) - sx1);
            double v2 = (b2 / b) * (tuples::get<1>(*index) - sx2);
            double s = v1 + v2;
            result += pow(s, 2);
        }
        if (operation == "SIGMA_Y")
        {
            double sy = GetParameter(data, "AV_Y");
            result += pow(tuples::get<2>(*index) - sy, 2);
        }
        if (operation == "SIGMA_XY")
        {
            double b = GetB(data);
            double b2 = GetB2(data);
            double sx1 = GetParameter(data, "AV_X1");
            double sx2 = GetParameter(data, "AV_X2");
            double sy = GetParameter(data, "AV_Y");
            double v1 = (b / b2) * (tuples::get<0>(*index) - sx1);
            double v2 = (b2 / b) * (tuples::get<1>(*index) - sx2);
            double s = v1 + v2;
            result += s * (tuples::get<2>(*index) - sy);
        }
    }
    if (operation == "SIGMA_X" || operation == "SIGMA_Y" || operation == "SIGMA_XY")
    {
        result /= n;
        result = sqrt(abs(result));
    }
    return result;
}

double Approximator_2::GetA(const vector<point_2> &data)
{
    double result = 0;
    double sx1 = GetParameter(data, "AV_X1");
    double sx2 = GetParameter(data, "AV_X2");
    double sy = GetParameter(data, "AV_Y");
    double b = GetB(data);
    double b2 = GetB2(data);
    result = sy - b2 * sx1 - b * sx2;
    return result;
}

double Approximator_2::GetB(const vector<point_2> &data)
{
    double result = 0;
    double sx1x2 = GetParameter(data, "SUM_X1X2");
    double sx1y = GetParameter(data, "SUM_X1Y");
    double sx2y = GetParameter(data, "SUM_X2Y");
    double sx12 = GetParameter(data, "SUM_X12");
    double sx22 = GetParameter(data, "SUM_X22");
    result = sx12 * sx2y - sx1x2 * sx1y;
    result /= (sx12 * sx22 - pow(sx1x2, 2));
    return result;
}

double Approximator_2::GetB2(const vector<point_2> &data)
{
    double result = 0;
    double sx1x2 = GetParameter(data, "SUM_X1X2");
    double sx1y = GetParameter(data, "SUM_X1Y");
    double sx2y = GetParameter(data, "SUM_X2Y");
    double sx12 = GetParameter(data, "SUM_X12");
    double sx22 = GetParameter(data, "SUM_X22");
    result = sx1y * sx22 - sx2y * sx1x2;
    result /= (sx12 * sx22 - pow(sx1x2, 2));
    return result;
}

double Approximator_2::Delta(const vector<point_2> &data1, const vector<point_2> &data2)
{
    double result = 0;
    int n = data1.size();
    for (int index = 0;index < n;index++)
    {
        result += (100 * abs(tuples::get<2>(data1[index]) - tuples::get<2>(data2[index]))) / tuples::get<2>(data1[index]);
    }
    result /= n;
    return result;
}

double Approximator_2::Sigma(const vector<point_2> &data)
{
    double result = 0;
    typedef vector<point_2>::const_iterator iter;
    int n = data.size();
    double a = GetA(data);
    double b = GetB(data);
    double b2 = GetB2(data);
    for (iter index = data.begin();index != data.end();index++)
    {
        result += pow(tuples::get<2>(*index) - a - b * tuples::get<0>(*index) - b2 * tuples::get<1>(*index), 2);
    }
    result /= n;
    result = sqrt(abs(result));
    return result;
}

double Approximator_2::Correlation(const vector<point_2> &data)
{
    double result = 0;
    result = pow(GetParameter(data, "SIGMA_XY"), 2);
    result /= GetParameter(data, "SIGMA_X");
    result /= GetParameter(data, "SIGMA_Y");
    return result;
}

