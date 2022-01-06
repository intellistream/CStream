// Copyright (C) 2021 by the RoofLine team (https://github.com/intellistream)

/**
 * @brief This is the main entry point of the entire program.
 * We use this as the entry point for benchmarking.
 */
#include <Utils/Logger.hpp>
#include <thread>
#include <Utils/PerfTool.hpp>
#include <stdint.h>
#include <CpuFreq/cpufreq.h>
#include <CpuFreq/cpupower.h>

#include <Utils/Meters/AbstractMeter.hpp>
#include <MeterHelp.hpp>
#include <Utils/Math/SegLinearFit.hpp>
using namespace std;
using namespace ROOFLINE;
using namespace MATH_FUNC;
using namespace DIVERSE_METER;
#define MEM_SIZE (100*1024)
vector <double>g_IPM={};
vector <double>g_MINTOPS={};
vector <double>g_energy={};
vector<double> seg={0,35,50,70,1000,5020,1e5,1e6};
double g_staticPower=3.14;
typedef std::shared_ptr<uint32_t> memPtr_shared;
void runRoof(ThreadPerf *tp, uint32_t IPM, FILE *fp) {
  memPtr_shared outBuf0 = std::shared_ptr<uint32_t>(new uint32_t[MEM_SIZE],
                                                    [](uint32_t *p) {
                                                      delete[] p;
                                                    });
  uint32_t *pt = outBuf0.get();
  //must in register to avoid additional mem access
  register uint32_t i;
  register uint32_t j;
  register uint32_t sum;
  AbstractMeterPtr powerMeter=newEnergyMeter();
  sum = 0;
  powerMeter->startMeter();
  tp->start();
  for (i = 0; i < MEM_SIZE; i++) {
    //run IPM
    sum = 0;
    for (j = 0; j < IPM; j++) {
      sum += j;
    }
    pt[i] = sum;
  }
  tp->end();
  powerMeter->stopMeter();
  uint64_t rtime = tp->getRunTime();
  printf("time=%d,IPM=%d\r\n", rtime, IPM);
  uint64_t mFlops = tp->getResultById(COUNT_HW_INSTRUCTIONS);

  mFlops = mFlops / rtime;
  uint64_t IPMR = tp->getResultById(COUNT_HW_INSTRUCTIONS) / MEM_SIZE;
  double eng= powerMeter->getE();
  double staticEng=g_staticPower*rtime/(1e6);
  double netEng=eng-staticEng;
  double mintopj=tp->getResultById(COUNT_HW_INSTRUCTIONS);
  mintopj=mintopj/netEng/(1e6);
  fprintf(fp, "%d,%d,%ld,%ld,%ld,%lf,%lf,%lf,%lf%s", IPM, MEM_SIZE, tp->getRunTime(), mFlops, IPMR,eng,powerMeter->getPeak(),\
  netEng,
  mintopj,
  tp->resultStringCsv().data());
  double t=IPMR;
  g_IPM.push_back(t);
  t=mFlops;
 g_MINTOPS.push_back(t);
}
void testMemAddress(ThreadPerf *tp)
{
   memPtr_shared outBuf0 = std::shared_ptr<uint32_t>(new uint32_t[MEM_SIZE*10],
                                                    [](uint32_t *p) {
                                                      delete[] p;
                                                    });
  std::shared_ptr<uint8_t>outBuf1 = std::shared_ptr<uint8_t>(new uint8_t[MEM_SIZE*10],
                                                    [](uint8_t *p) {
                                                      delete[] p;
                                                    });
  uint32_t *pt = outBuf0.get();
  uint8_t *pt1=outBuf1.get();
  AbstractMeterPtr powerMeter=newEnergyMeter();
  powerMeter->startMeter();
  tp->start();
  register uint32_t i;
   for (i = 0; i < MEM_SIZE*10; i++) {
  
    pt[i] = 0xfefefefe;
  }
  tp->end();
  powerMeter->stopMeter();
  double a=tp->getRunTime();
  printf("time=%d in uint32_t access,energy=%lf\r\n",tp->getRunTime(),powerMeter->getE());
  powerMeter->startMeter();
   tp->start();

   for (i = 0; i < MEM_SIZE*10; i++) {
  
    pt1[i] = 0xfe;
  }
  tp->end();
    powerMeter->stopMeter();
  printf("time=%d in uint8_t access,,energy=%lf\r\n",tp->getRunTime(),powerMeter->getE());
  double b=tp->getRunTime();
  printf("ratio =%lf(U32:U8)\r\n",a/b);
}
double mesPower(uint32_t sleepTimeMs)
{ AbstractMeterPtr powerMeter=newEnergyMeter();
  powerMeter->startMeter();
  usleep(sleepTimeMs*1000);
   powerMeter->stopMeter();
   double eng=powerMeter->getE();
  double p=eng;
  p=p*1000.0/(sleepTimeMs);
   printf("sleep %d ms,energy=%lf J,power=%lf W\r\n",sleepTimeMs,eng,p);
   return p;
}
void genPredictCsv(vector<double> x,vector<double> yr,vector<double> yp,string name)
{
  FILE *fp = fopen(name.data(), "w");
  if (!fp) {
    ROOFLINE_ERROR("faile to creat file\r\n");
    exit(0);
  }
   fprintf(fp,"input,real value,predic\r\n");
   size_t i;
   for(i=0;i<x.size();i++)
   {
     fprintf(fp,"%lf,%lf,%lf\r\n",x[i],yr[i],yp[i]);
   }
   fclose(fp);
}
void genRoofLineCSV(string name, ThreadPerf *tp) {
  FILE *fp = fopen(name.data(), "w");
  if (!fp) {
    ROOFLINE_ERROR("faile to creat file\r\n");
    exit(0);
  }
  g_staticPower=mesPower(1000);
  printf("static power is %lf W\r\n",g_staticPower);
  fprintf(fp, "set,mem,time,mfops,IPM,energy,peakPower,netEnergy,MINTOPJ%s", tp->headStringCsv().data());
  //note, you can use another IPM-setting parameters here
  runRoof(tp, 1, fp);
  runRoof(tp, 2, fp);
  runRoof(tp, 5, fp);
  runRoof(tp, 6, fp);
  runRoof(tp, 7, fp);
  runRoof(tp, 8, fp);
  runRoof(tp, 10, fp);
  runRoof(tp, 100, fp);
  runRoof(tp, 200, fp);
  runRoof(tp, 500, fp);
  runRoof(tp, 1000, fp);
  //runRoof(tp,5000,fp);
  runRoof(tp, 10000, fp);
  runRoof(tp, 20000, fp);
  runRoof(tp, 50000, fp);
  //runRoof(tp,100000,fp);

  /*double t1=g_IPM[g_IPM.size()];
  g_IPM.push_back(t1*10);
  t1=g_MINTOPS[g_MINTOPS.size()];
  g_MINTOPS.push_back(t1);*/
  //runRoof(tp,100000,fp);
  fclose(fp);
  SegLinearFit sf(g_IPM,g_MINTOPS,seg);
  //SegLinearFit sf(g_IPM,g_MINTOPS,0.1);
  vector<double> yp=sf.forward(g_IPM);
  genPredictCsv(g_IPM,g_MINTOPS,yp,name+"_fit.csv");
  printf("the function is as below:\r\n%s\r\n",sf.getEquation().data());
}
int main(int argc, char **argv) {
  //Setup Logs.
  ThreadPerf tp;
  string fname, runame;
  int cpu;
  //assign the core
  if (argc >= 2) {
    cpu = atoi(argv[1]);
    printf("bind to core %d\r\n", cpu);
    UtilityFunctions::bind2Cpu(cpu);
    tp = ThreadPerf(cpu);
    fname += "core";
    fname += argv[1];
  } else {
    fname += "core";
    fname += "0";
    cpu = 0;
  }
  //note, the scan_freq and set_freq only work when the hardware support
  if (argc >= 3) {
    string a = "";
    a += argv[2];
    if (a == "scan_freq") {
      printf("warnning, scan all frequencies\r\n");
      struct cpufreq_available_frequencies *af, *tf;
      af = cpufreq_get_available_frequencies(cpu);
      tf = af;
      for (tf = af; tf != NULL; tf = tf->next) {
        printf("\t%dKHz is available\r\n", tf->frequency);
      }
      struct cpupower_topology mytopo;
      get_cpu_topology(&mytopo);
      for (tf = af; tf != NULL; tf = tf->next) {
        printf("\t%dKHz is available\r\n", tf->frequency);
        cpufreq_set_frequency(cpu, tf->frequency);
        printf("now freq is %d kHZ\r\n", cpufreq_get_freq_hardware(cpu));
        runame = fname + to_string(tf->frequency) + "k_rl.csv";
        genRoofLineCSV(runame, &tp);

      }

    } else if (a == "set_freq") {
      printf("try to set to the assigned frequency\r\n");
      int freq;
      if (argc < 4) {
        printf("input your freq in KHz:\r\n");
        scanf("%d", &freq);
      } else {
        freq = atoi(argv[3]);
      }
      cpufreq_set_frequency(cpu, freq);
      freq = cpufreq_get_freq_hardware(cpu);
      printf("now freq is %d kHZ\r\n", freq);
      runame = fname + to_string(freq) + "k_rl.csv";
      genRoofLineCSV(runame, &tp);
    }
    else if (a == "mem") {
     testMemAddress(&tp);
    }
    else if (a == "power") {
    uint32_t su=1000;
    if (argc < 4) {
        printf("input your time in ms:\r\n");
        scanf("%d", &su);
      } else {
        su = atoi(argv[3]);
      }
      printf("sleep %d ms to measure power\r\n",su);
      mesPower(su);
    }
  } else {
    runame = fname + "_rl.csv";
    genRoofLineCSV(runame, &tp);
  }

  return 0;
}
