#include <GenZipf.hpp>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
using namespace std;
using namespace ZIPF;
void GenZipf::gen_alphabet() {
  srand(time(NULL));
  alphabet = vector<uint64_t>(alen);
  /* populate */
  for (uint64_t i = 0; i < alen; i++)
    alphabet[i] = i + 1;   /* don't let 0 be in the alphabet */

  /* permute */
  for (uint64_t i = alen - 1; i > 0; i--) {
    uint64_t k = (unsigned long) i * rand() / RAND_MAX;
    uint64_t tmp;

    tmp = alphabet[i];
    alphabet[i] = alphabet[k];
    alphabet[k] = tmp;
  }
  printf("alpha done\r\n");
}
void GenZipf::gen_zipf_lut() {
  lut = vector<double>(alen);
  double scaling_factor;
  double sum;
  scaling_factor = 0.0;
  /*
* Compute scaling factor such that
*
*   sum (lut[i], i=1..alphabet_size) = 1.0
*
*/
  for (uint64_t i = 1; i <= alen; i++) {

    //printf("i=%d,alne=%d\r\n",i,alen);
    scaling_factor += 1.0 / pow(i, factor);
  }

  /*
   * Generate the lookup table
   */
  sum = 0.0;
  entropy = 0;
  freqMax = 0;
  double px;
  for (uint64_t i = 1; i <= alen; i++) {
    double ps = 1.0 / pow(i, factor);
    sum += ps;
    lut[i - 1] = sum / scaling_factor;
    px = ps / scaling_factor;
    entropy += -px * log(px) / log(2.0);

    if (px > freqMax) {
      freqMax = px;
    }
    // printf("%lf\r\n",px);
  }
  // printf("lut done,fm=%lf\r\n",freqMax);
}

void ZIPF::genZipf32Csv(char *fname, double factor, uint64_t range, uint64_t times) {
  GenZipf gz(factor, range);
  vector<uint32_t> ru = gz.outPutArray<uint32_t>(times);
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  uint64_t i;
  for (i = 0; i < times; i++) {
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    fprintf(fp, "%ld \r\n", ru[i]);
  }
  fclose(fp);
  printf("%s, Hx=%lf\r\n", fname, gz.getEntropy());
}

void ZIPF::genZipf64Csv(char *fname, double factor, uint64_t range, uint64_t times) {
  GenZipf gz(factor, range);
  vector<uint64_t> ru = gz.outPutArray<uint64_t>(times);
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  uint64_t i;
  for (i = 0; i < times; i++) {
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    fprintf(fp, "%ld \r\n", ru[i]);
  }
  fclose(fp);
  printf("%s, Duplication=%lf\r\n", fname, gz.getMaxFreq() * times);
}

void ZIPF::genZipf32Bin(char *fname, double factor, uint64_t range, uint64_t times) {
  GenZipf gz(factor, range);
  vector<uint32_t> ru = gz.outPutArray<uint32_t>(times);
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  uint64_t i;

  for (i = 0; i < times; i++) {
    uint32_t k = ru[i];
    fwrite(&k, sizeof(uint32_t), 1, fp);
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    //fprintf(fp,"%ld \r\n",ru[i]);
  }
  fclose(fp);
  printf("%s, Hx=%lf\r\n", fname, gz.getEntropy());
}

void ZIPF::genZipf64Bin(char *fname, double factor, uint64_t range, uint64_t times) {
  GenZipf gz(factor, range);
  vector<uint64_t> ru = gz.outPutArray<uint64_t>(times);
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  uint64_t i;
  for (i = 0; i < times; i++) {
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    //fprintf(fp,"%ld \r\n",ru[i]);
    uint64_t k = ru[i];
    fwrite(&k, sizeof(uint64_t), 1, fp);
  }
  fclose(fp);
  printf("%s, Duplication=%lf\r\n", fname, gz.getMaxFreq() * times);
}

void ZIPF::genZipfFloatBin(char *fname, double factor, uint64_t range, uint64_t times) {
  GenZipf gz(factor, range);
  vector<uint64_t> ru = gz.outPutArray<uint64_t>(times);
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  uint64_t i;
  for (i = 0; i < times; i++) {
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    //fprintf(fp,"%ld \r\n",ru[i]);
    float k = ru[i];
    fwrite(&k, sizeof(float), 1, fp);
  }
  fclose(fp);
  printf("%s, Duplication=%lf\r\n", fname, gz.getMaxFreq() * times);
}