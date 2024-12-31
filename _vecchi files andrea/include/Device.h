#ifndef HOMEDEVICEH
#define HOMEDEVICEH

#include <string>
#include <map>
#include <vector>
#include "Home.h"
#include <memory>

class Home;

struct Interval
{
    unsigned short timeOn;
    unsigned short timeOff;
    Interval(unsigned short time1,unsigned short time2) : timeOn{time1},timeOff{time2}{}
    Interval() : timeOn{0},timeOff{0}{}
    short getOffset(){
        return timeOff - timeOn;
    }
    bool isBetween(unsigned short t){
        return (timeOff > t && timeOn < t);
    }
};

class Device{
    protected:
        short ID;
        float powerConsumption;
        bool state;
        std::string name;
        short lastOn;
        std::map<short, Interval*> deviceCycles;
        std::unique_ptr<Interval> nextTimer;
    public:
        Device();
        Device(std::string,float,bool=false);
        std::string getName();
        float getPowerCons();
        bool getState();
        void ON(unsigned short);
        void refreshTimers(unsigned short,Home);
        float getConsumptionAt(short=1440);
        bool getStateAt(short);
        virtual void OFF(unsigned short);
        virtual void setTimer(unsigned short,unsigned short);
};

class CycleDevice : public Device{
    private:
        unsigned short cycleTime;
    public:
        CycleDevice();
        CycleDevice(std::string,float,unsigned short,bool=false);
        virtual void ON(unsigned short);
        void setTimer(unsigned short);
};

#endif