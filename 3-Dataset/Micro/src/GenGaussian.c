#include <GenGaussian.h>
#include <math.h>

uint64_t gaussian64(double mu, double sigma) {
  double k = tgaussian() * sigma + mu;
  if (k < 0) {
    k = 0;

  }
  uint64_t ru;
  ru = (uint64_t) k;
  return ru;
}
uint32_t gaussian32(double mu, double sigma) {
  double k = tgaussian() * sigma + mu;
  if (k < 0) {
    k = 0;

  }
  uint32_t ru;
  ru = (uint32_t) k;
  return ru;
}
void genGaussian32Csv(char *fname, double sigma, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  tsrand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint32_t mu0 = 0xffffffff / 4;
    double k = mu0;
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    fprintf(fp, "%ld \r\n", gaussian32(mu0, sigma));
  }
  fclose(fp);
}
void genGaussian32Bin(char *fname, double sigma, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  tsrand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint32_t mu0 = 0xffffffff / 4;
    double k = mu0;
    uint32_t ru = gaussian32(mu0, sigma);
    fwrite(&ru, sizeof(uint32_t), 1, fp);
  }
  fclose(fp);
}

void genGaussian64Bin(char *fname, double sigma, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  tsrand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint64_t mu0 = 0xffffffffffff / 4;
    double k = mu0;
    uint64_t ru = gaussian64(mu0, sigma);
    fwrite(&ru, sizeof(uint64_t), 1, fp);
  }
  fclose(fp);
}

void genGaussianFloatBin(char *fname, double sigma, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  tsrand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint64_t mu0 = 0xffffffffffff / 4;
    double k = mu0;
    double ru = tgaussian() * sigma + k;
    float tru = (float) ru;
    fwrite(&tru, sizeof(float), 1, fp);
  }
  fclose(fp);
}

void genGaussian64Csv(char *fname, double sigma, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  tsrand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint64_t mu0 = 0xffffffffffff / 4;
    double k = mu0;
    // double ru=tgaussian()+k;
    // fprintf(fp,"%lf \r\n",ru);
    fprintf(fp, "%ld \r\n", gaussian64(mu0, sigma));
  }
  fclose(fp);
}