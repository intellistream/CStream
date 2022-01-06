#include <Duplicate.h>

uint8_t *loadByteFile(char *fname, uint32_t *lenP) {
  FILE *fp = fopen((char *) fname, "rb");
  uint8_t *readB;
  int len;
  if (fp == 0) {
    printf("open file error");
    return NULL;

  }
  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  //printf("open %s,size=%d \r\n",fname,len);
  fseek(fp, 0L, SEEK_SET);
  readB = (uint8_t *) malloc(len + 1);
  fread(readB, len, 1, fp);
  fclose(fp);
  *lenP = len;
  return readB;
}

int8_t writeByteFileAppend(char *fname, uint32_t size, uint8_t *data) {
  FILE *fp = fopen((char *) fname, "ab+");
  /*uint8_t *readB;
  int len;*/
  if (fp == 0) {
    printf("open file error");
    return 0;

  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  return 1;
}

int8_t writeByteFile(char *fname, uint32_t size, uint8_t *data) {
  FILE *fp = fopen((char *) fname, "wb");
  uint8_t *readB;
  int len;
  if (fp == 0) {
    printf("open file error");
    return 0;

  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  return 1;
}
void duplicateFile(char *fname, char *outName, uint64_t times) {
  uint32_t fLen;
  uint8_t *src = loadByteFile(fname, &fLen);
  if (!src) {
    return;
  }
  writeByteFile(outName, fLen, src);
  for (uint64_t i = 1; i < times; i++) {
    writeByteFileAppend(outName, fLen, src);
  }
  free(src);
}

uint8_t *loadLargeFile(char *fname, uint32_t start, uint32_t len) {
  FILE *fp = fopen((char *) fname, "rb");
  uint8_t *readB;
  long pos = start;
  if (fp == 0) {
    printf("open file error");
    return NULL;

  }

  fseek(fp, pos, SEEK_SET);
  readB = (uint8_t *) malloc(len + 1);
  fread(readB, len, 1, fp);
  fclose(fp);
  return readB;
}
void extractFile(char *fname, char *outName, uint64_t extLen) {
  int32_t fLen;
  uint8_t *src = loadLargeFile(fname, 0, extLen);
  if (!src) {
    return;
  }
  writeByteFile(outName, extLen, src);
  free(src);
}
void extractStock(char *fname, char *outName, uint64_t extLen) {
  FILE *fp = fopen((char *) fname, "rb");

  if (fp == 0) {
    printf("open file error");
    return;

  }
  FILE *outP = fopen((char *) outName, "wb");
  if (outP == 0) {
    printf("open file error");
    return;
  }
  uint32_t wkload, key;
  uint64_t ru = 0;
  while (!feof(fp)) {
    fscanf(fp, "%d|%d", &wkload, &key);
    printf("%d-%d\r\n", wkload, key);
    ru = wkload;
    ru = ru << 32 | key;
    fwrite(&ru, sizeof(uint64_t), 1, outP);

  }
  fclose(fp);
  fclose(outP);
}