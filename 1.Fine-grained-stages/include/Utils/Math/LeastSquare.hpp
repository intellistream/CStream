//
// Created by tony on 2021/11/15
//
#ifndef ADB_INCLUDE_UTILS_MATH_LeastSqure_H_
#define ADB_INCLUDE_UTILS_MATH_LeastSqure_H_
#include <stdint.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
namespace MATH_FUNC {

/*class:LeastSquare
description: The class of a LeastSqure model

date:202101115
*/    
class LeastSquare
{
private:
    /* data */
    double k=0.0,b=0.0;
    double error=0,corelation=0;
public:
    //init by trainning data
    LeastSquare(vector<double> x,vector<double> y)
    {
        train(x,y);
    }
    //init directly
    LeastSquare(double k,double b)
    {
        set(k,b);
    }
    //calculate for only one value
    double forward(double x)
    {
        return k*x+b;
    }
    //cacu;ate for vector
    vector<double> forward(vector<double> x)
    {
        size_t n=x.size();
        vector <double> y(n);
        for(size_t i=0;i<n;i++)
        {
            y[i]=k*x[i]+b;
        }
        return y;
    }
    ~LeastSquare()
    {
        
    }
    void train(vector<double> x,vector<double> y);
    void set(double _k,double _b)
    {
        k=_k;
        b=_b;
    }
    double getK()
    {
        return k;
    }
    double getB()
    {
        return b;
    }
    double getError()
    {
        return error;
    }
     double getCorelation()
    {
        return corelation;
    }
    vector<double> getWeight()
    {
        vector<double> weight(2);
        weight[0]=k;
        weight[1]=b;
        return weight;
    }
    string getEquation()
    {
        string ru="y=";
        ru+=to_string(k)+"*x+(";
        ru+=to_string(b)+")";
        return ru;
    }
};



};
#endif