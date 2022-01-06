#include <GenRand.h>
void genRandBin(char *fname, uint64_t maxRange, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  srand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint32_t k = rand() % maxRange;
    fwrite(&k, sizeof(uint32_t), 1, fp);
  }
  fclose(fp);
}
void genRandCsv(char *fname, uint64_t maxRange, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  srand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint64_t k = rand() % maxRange;
    fprintf(fp, "%ld \r\n", k);
  }
  fclose(fp);
}
void genFullRandBin(char *fname, uint64_t times) {
  FILE *fp = fopen(fname, "wb");
  if (!fp) {
    printf("error in creating\r\n");
    return;
  }
  srand(time(NULL));
  uint64_t i;
  for (i = 0; i < times; i++) {
    uint32_t k = rand();
    uint32_t k2 = rand();
    uint64_t su = k2;
    su = su << 32 | k;
    fwrite(&su, sizeof(uint64_t), 1, fp);
  }
  fclose(fp);
}