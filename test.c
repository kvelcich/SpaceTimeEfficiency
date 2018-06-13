#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <IntelPowerGadget/EnergyLib.h>
 
int main(int argc, char* argv[]) {
 
    IntelEnergyLibInitialize();
     
    int numMsrs = 0;
    GetNumMsrs(&numMsrs);
    ReadSample();
    for (int i = 0; i < 2; i++) {
         
        sleep(1);
        ReadSample();
        
        for (int k = 0; k < 1000000000; k++);

        for (int j = 0; j < numMsrs; j++) {
            int funcID;
            char szName[1024];
            GetMsrFunc(j, &funcID);
            GetMsrName(j, szName);
             
            int nData;
            double data[3];
            GetPowerData(0, j, data, &nData);
             
            // Power
            if (funcID == MSR_FUNC_POWER) {
                //printf("%s Power (W) = %3.2f", szName, data[0]);
                //printf(", %s Energy(J) = %3.2f", szName, data[1]);
                //printf(", %s Energy(mWh)=%3.2f", szName, data[2]);
            }

            printf("%d\n", GetTimeInterval(NULL));
        }
        printf("\n");
    }
     
    sleep(1);
    StopLog();// causes a sample to be read
     
    return 0;
}
