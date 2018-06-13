#include <IntelPowerGadget/EnergyLib.h>

class PowerStats {
    public:
        PowerStats();
        void Start();
        std::string Measure();

    private:
        std::string GetPowerData();
        std::string GetElapsedTime();
        std::string DToS(double num);

        uint64_t start_time;
        uint64_t start_cpu_time;

        bool Intel_ReadSample();
        bool Intel_GetTimeInterval(double &interval);
        bool Intel_GetNumNodes(int &count);
        bool Intel_GetNumMsrs(int &count);
        bool Intel_GetMsrName(int iMsr, std::string &name);
        bool Intel_GetMsrFunc(int iMsr, int &funcID);
        bool Intel_GetPowerData(int iNode, int iMSR, double *pResult, int *nResult);   
};