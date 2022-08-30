// Copyright (C) 2021 by the IntelliStream team (https://github.com/intellistream)

#include <Utils/UtilityFunctions.hpp>

/* calculate running time*/
int64_t ADB::UtilityFunctions::getRunningUs(struct timeval tstart, struct timeval tend) {
  int64_t s0, e0, s1, e1;
  s0 = tstart.tv_sec;
  s1 = tstart.tv_usec;
  e0 = tend.tv_sec;
  e1 = tend.tv_usec;
  return 1000000 * (e0 - s0) + (e1 - s1);
}
/* read an int vector from fname*/
std::vector<int> ADB::UtilityFunctions::getIntVectorFromFile(std::string fname) {
  std::vector<int> ru;
  int getV;
  FILE *fp = fopen((char *) fname.data(), "r");
  if (!fp) {
    return ru;
  }
  while (!feof(fp)) {
    fscanf(fp, "%d,", &getV);

    ru.push_back(getV);
  }
  ru.pop_back();
  fclose(fp);
  return ru;
}
std::shared_ptr<std::barrier<>> ADB::UtilityFunctions::createBarrier(int count) {
  return std::make_shared<std::barrier<>>(count);
}