#ifndef HOMEH
#define HOMEH

#include "Device.h"

class Device;
class CycleDevice;

class Home{
    private:
        unsigned short time;
        std::map<std::string, Device*> devices;
        std::map<std::string, CycleDevice*> cycleDevices;
    public:
        void listen(std::string);
        void goForward(short);
        Home();
        float checkMax(float,short);
};

#endif