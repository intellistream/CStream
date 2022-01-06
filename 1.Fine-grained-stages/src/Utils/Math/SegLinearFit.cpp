#include <Utils/Math/SegLinearFit.hpp>
using namespace std;
using namespace MATH_FUNC;
void SegLinearFit::train(vector<double> x,vector<double> y)
{
    size_t i,j;
    coeff={};
    size_t lastLen=0;
    double lx=0;
    double ly=0;
    for(i=0;i<seg.size()-1;i++)
    {
        vector<double> tx={};
        vector<double> ty={};
        if(lastLen>=1)
        {
            tx.push_back(lx);
            ty.push_back(ly);
        }
        for(j=0;j<x.size();j++)
        {
            if(x[j]>seg[i]&&x[j]<=seg[i+1])
            {
                tx.push_back(x[j]);
                ty.push_back(y[j]);
            }
        }
        lastLen=tx.size();
        if(lastLen>=1)
        {
           lx=tx[lastLen-1];
           ly=ty[lastLen-1];  
        }
        LeastSquare ls(tx,ty);
        coeff.push_back(ls.getK());
        coeff.push_back(ls.getB());
    }
}
void SegLinearFit::trainWithoutSeg(vector<double> x,vector<double> y,double ratio)
{
    vector<double> sx=x;
    vector<double> sy=y;
    //first, sorting
    size_t i,j;
    size_t maxLen=x.size()-1;
    for(j=0;j<maxLen;j++) /**/ 
    {
         for(i=0;i<maxLen-j;i++) 
         {
             
            if(sx[i]>sx[i+1]) /*相邻两个数比较,想降序只要改成a[i]<a[i+1]*/ 

            { 
                double t=sx[i]; 
                sx[i]=sx[i+1]; 
                sx[i+1]=t; 
                //sy accordingly
                 t=sy[i]; 
                sy[i]=sy[i+1]; 
                sy[i+1]=t; 
            }    
         }
    }
     maxLen+=1;
   
    //then detect delta change
    vector<double> tseq={};
    tseq.push_back(sx[0]-1);
    double delta=(sy[1]-sy[0])/(sx[1]-sx[0]);
    double deltaP;
    double d2a,d2b;
   
      for(j=2;j<maxLen;j++) /**/ 
    {
        deltaP=delta;
        delta=(sy[j]-sy[j-1])/(sx[j]-sx[j-1]);
        d2a=(delta-deltaP)/delta;
        d2b=(delta-deltaP)/deltaP;
        if(fabs(d2a)>fabs(ratio)||fabs(d2b)>fabs(ratio))
        {
            double segt=(sx[j]+sx[j-1])/2;
            tseq.push_back(segt);
        }
    }
    tseq.push_back(sx[maxLen-1]+1);  
    /*printf("auto-segmentation:\r\n");
    for(i=0;i<tseq.size();i++)
    {
        printf("%lf,",tseq[i]);
    }
    printf("\r\n");*/
    setSegment(tseq);
    train(x,y);

}