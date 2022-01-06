#ifndef _MATHKMEANS_H_
#define _MATHKMEANS_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "mathtype.h"
//in lib distance funtions
ddot tvector_getEuDistance(ddot *avector,ddot *bvector,u32 n);
typedef struct KMEANSCORE
{
    u32 K,N,D;  //鑱氱被鐨勬暟鐩紝鏁版嵁閲忥紝鏁版嵁鐨勭淮鏁� amount of types, amount of trainset,.. of dims
    u8 isTrained;
    MATRIX *m_data; //鏁版嵁闆�,  the train set
    MATRIX *cluster_center;  //瀛樻斁姣忎釜鑱氱被鐨勪腑蹇冪偣, the matrix of the center of each class
    MATRIX *m_distance; //to store distance of each sample its to center
    MATRIX *m_sum; // to store sum evrey center's sample
    u32 *in_cluster; //姣忎釜鏍锋湰鐐规墍灞炵殑绫诲埆鏍囩,label of which type belong to 
    ddot (*myVecDistance)(ddot *avector,ddot *bvector,u32 n);//the fuction of vector distance
}KMEANSCORE;
//to get started , use either KMEANSCORE_initTrainData or KMEANSCORE_loadTrainedCenter
m8 KMEANSCORE_initTrainData(KMEANSCORE *kmsc,MATRIX *trainData,u32 K);
m8 KMEANSCORE_loadTrainedCenter(KMEANSCORE *kmsc,MATRIX *center);
//if you want to change the distance funtion
m8 KMEANSCORE_setDistanceFuc(KMEANSCORE *kmsc,ddot (*myVecDistance)(ddot *avector,ddot *bvector,u32 n));
//inline functions
m8 KMEANSCORE_initRandCenter(KMEANSCORE *kmsc,u32 K,u32 D);

m8 KMEANSCORE_cluster(KMEANSCORE *kmsc);
ddot KMEANSCORE_sumDistace(KMEANSCORE *kmsc);
m8 KMEANSCORE_getCenter(KMEANSCORE *kmsc);
//to train, use KMEANSCORE_runTrain
u32 KMEANSCORE_runTrain(KMEANSCORE *kmsc,u32 maxTime);
//to judge, use KMEANSCORE_judgeData
u32 KMEANSCORE_judgeData(KMEANSCORE *kmsc,ddot *vec);
//to just free data, not itself
m8 KMEANSCORE_deinit(KMEANSCORE *kmsc);
#ifdef __cplusplus
 }
#endif

#endif
