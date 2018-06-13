#include <iostream>
#include <IntelPowerGadget/EnergyLib.h>
#include "PowerStats.h"
#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <mach/mach_time.h>

using namespace std;

PowerStats::PowerStats() {
    start_time = 0;
    start_cpu_time = 0;
    IntelEnergyLibInitialize();
}

void PowerStats::Start() {
    Measure();
}

string PowerStats::Measure() {
    string response("{");

  response += "\"elapsed_time\":" + GetElapsedTime();

  // Power Data (including elapsed time)
  response += GetPowerData();

  response += "}";
  return response;
}

std::string PowerStats::GetElapsedTime() {
  double elapsed = 0;
  uint64_t now = mach_absolute_time();
  if (start_time > 0) {
    mach_timebase_info_data_t info;
    if (mach_timebase_info(&info) == KERN_SUCCESS) {
      uint64_t nanos = ((now - start_time) * info.numer) / info.denom;
      elapsed = (double)nanos / NSEC_PER_SEC;
    }
  }
  start_time = now;
  return DToS(elapsed);
}

std::string PowerStats::GetPowerData() {
  std::string result = "";

  Intel_ReadSample();
  int nodes = 0;
  if (Intel_GetNumNodes(nodes) && nodes > 0) {
    int count = 0;
    if (Intel_GetNumMsrs(count)) {
      int funcID;
      std::string name;
      for (int msr = 0; msr < count; msr++) {
        Intel_GetMsrName(msr, name);
        Intel_GetMsrFunc(msr, funcID);
        if (funcID == 1) {  // Power
          int nData = 0;
          double data[3];
          double joules = 0;
          double mWh = 0;
          for (int node = 0; node < nodes; node++) {
            if (Intel_GetPowerData(node, msr, data, &nData) && nData >= 3) {
              joules += data[1];
              mWh += data[2];
            }
          }
          result += ",\"" + name + " Joules\":" + DToS(data[1]);
          result += ",\"" + name + " mWh\":" + DToS(data[2]);
        }
      }
    }
  }
  return result;
}

string PowerStats::DToS(double num) {
  string response = "";
  char buff[100];
  sprintf(buff, "%0.6f", num);
  response = buff;
  return response;
}

bool PowerStats::Intel_ReadSample() {
  return ReadSample() != 0;
}

bool PowerStats::Intel_GetTimeInterval(double &interval){
  return GetTimeInterval(&interval) != 0;
}

bool PowerStats::Intel_GetNumNodes(int &count){
  return GetNumNodes(&count) != 0;
}

bool PowerStats::Intel_GetNumMsrs(int &count){
  return GetNumMsrs(&count) != 0;
}

bool PowerStats::Intel_GetMsrName(int iMsr, std::string &name){
  bool ok = false;
  char buff[1024];
  if (GetMsrName(iMsr, buff)) {
    ok = true;
    name = buff;
  }
  return ok;
}

bool PowerStats::Intel_GetMsrFunc(int iMsr, int &funcID){
  return GetMsrFunc(iMsr, &funcID) != 0;
}

bool PowerStats::Intel_GetPowerData(int iNode, int iMSR, double *pResult, int *nResult){
  return ::GetPowerData(iNode, iMSR, pResult, nResult) != 0;
}

int main() {
    PowerStats *powerstats = new PowerStats();
    powerstats->Start();
    cout << powerstats->Measure() << endl;
    for (int i = 0; i < 1000000; i++)
        for (int j = 0; j < 100; j++);
    cout << powerstats->Measure() << endl;
}