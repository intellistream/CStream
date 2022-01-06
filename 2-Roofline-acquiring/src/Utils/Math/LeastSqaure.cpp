#include <Utils/Math/LeastSquare.hpp>
using namespace std;
using namespace MATH_FUNC;

void LeastSquare::train(vector<double> x,vector<double> y)
{
    double d1, d2, d3;
    double sumx,sumy,sumxx,sumyy,sumxy,mx,my;
    size_t n=x.size();
    size_t i;
    d1 = d2 = d3 =sumx=sumy=sumxx=sumyy=sumxy=0.0;
    double sumerrorsquare;
    //main part
     for (i = 0; i < n; i++) {
           sumx += x[i];
           sumy += y[i];
           sumxx += x[i]*x[i];
           sumyy += y[i]*y[i];
           sumxy += x[i]*y[i];
       }
       mx = sumx / n;
       my = sumy / n;
      // mxx = sumxx / n;
      // myy = sumyy / n;
      // mxy = sumxy / n;

       //
       this->k=(n*sumxy-sumx*sumy)/(n*sumxx-sumx*sumx);
       this->b=(sumxx*sumy-sumx*sumxy)/(n*sumxx-sumx*sumx);
      //corelation
       for (i = 0; i < n; i++) {
           d1 += (x[i] - mx) * (y[i] - my);
           d2 += (x[i] - mx) * (x[i] - mx);
           d3 += (y[i] - my) * (y[i] - my);
       }
      this->corelation=d1 / sqrt(d2 * d3);
    //error
    vector<double>yy(n);
     for(i=0;i<n;i++) {
           yy[i]=k*x[i]+b;
           sumerrorsquare+=(yy[i]-y[i])*(yy[i]-y[i]);
       }
       error=sqrt(sumerrorsquare/(n-1));
}