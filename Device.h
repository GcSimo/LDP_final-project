#ifndef HOMEDEVICEH
#define HOMEDEVICEH

#include <string>
#include <map>
#include <vector>

short IDCounter = 0;

struct Interval
{
    unsigned short timeOn;
    unsigned short timeOff;
    Interval(unsigned short time1,unsigned short time2) : timeOn{time1},timeOff{time2}{}
    Interval() : timeOn{0},timeOff{0}{}
};

class Device{
    protected:
        short ID;
        short powerConsumption;
        bool state;
        std::string name;
        std::map<short, Interval*> deviceCycles;
        Interval* nextTimer;
    public:
        Device();
        Device(std::string,short,bool=false);
        void ON(unsigned short timenow);
        void OFF(unsigned short);
        virtual void setTimer(unsigned short,unsigned short);
};

class CycleDevice : private Device{
    private:
        unsigned short cycleTime;
    public:
        CycleDevice();
        CycleDevice(std::string,short,unsigned short,bool=false);
        void setTimer(unsigned short);
};

#endif