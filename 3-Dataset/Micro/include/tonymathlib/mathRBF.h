#ifndef _MATHRBF_H_
#define _MATHRBF_H_
#include "mathtype.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct RBFCORE {
  u32 inD, hideD, outD;
  ddot df, dmax;
  MATRIX *w;//隐藏层到输出层的权值,size=hideD*outD
  MATRIX *c;//cj为第j个隐层的中心向量,c为hideD*inD
  //  MATRIX *d;//d
  ddot (*rbfFunc)(struct RBFCORE *, ddot);
  ddot (*myVecDistance)(ddot *avector, ddot *bvector, u32 n);//the fuction of vector distance
} RBFCORE;
/* Q and A
Q:How to train?
A:_init->_loadTrainData_(mid or kmeans)->_train_(pInv)
Q:how to load a trained one?
A:use  _loadTrainedWandC.
Q:how to run a single out put?
A:use _output
Q：what if the distance or RBF need a change?
A:do this using funtion pointer between init and loadTrainData 


*/
m8 RBFCORE_init(RBFCORE *rbfCore, u32 ind, u32 hided, u32 outd, ddot df);
m8 RBFCORE_loadTrainedWandC(RBFCORE *rbfCore, MATRIX *w, MATRIX *c, ddot df);
m8 RBFCORE_loadTrainData_mid(RBFCORE *rbfCore, MATRIX *x, MATRIX *expect);//x(n*ind),expect(n*outd)
m8 RBFCORE_loadTrainData_kmeans(RBFCORE *rbfCore, MATRIX *x, MATRIX *expect, u32 maxTurn);
MATRIX *RBFCORE_hideLayelOutput(RBFCORE *rbfCore, MATRIX *x);//
MATRIX *RBFCORE_finalOutput(RBFCORE *rbfCore, MATRIX *hv);//
MATRIX *RBFCORE_output(RBFCORE *rbfCore, MATRIX *x);
m8 RBFCORE_train_pInv(RBFCORE *rbfCore, MATRIX *x, MATRIX *expect);
void RBFCORE_getDmax(RBFCORE *rbfCore);
#ifdef __cplusplus
}
#endif

#endif