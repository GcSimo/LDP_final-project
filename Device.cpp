#include "Device.h"
#include <iostream>

Device::Device()
{
    this->name = "unknown";
    this->state = false;
}

Device::Device(std::string s, short pc, bool ses = 0)
{
    this->name = s;
    this->powerConsumption = pc;
    this->ID = IDCounter++;
    this->state = ses;
    return;
}

void Device::ON(unsigned short timenow)
{
    this->state = true;
}

void Device::OFF(unsigned short timenow)
{
    if(this->state){
        this->deviceCycles.insert({this->nextTimer->timeOn,new Interval(this->nextTimer->timeOn,timenow)});
        delete[] this->nextTimer;
        this->nextTimer = nullptr;
        this->state = false;
    }
}
//it overwrites the old timer
void Device::setTimer(unsigned short time1, unsigned short time2)
{
    if(time1 == time2)return;
    if(nextTimer == nullptr){
        nextTimer = new Interval();
    }
    this->nextTimer->timeOn = (time1<time2)?time1:time2;
    this->nextTimer->timeOff = (time1<time2)?time2:time1;
    return;
}

CycleDevice::CycleDevice() : Device()
{
    
}

CycleDevice::CycleDevice(std::string s, short pc, unsigned short ct, bool ses = 0) : Device(s, pc, ses)
{
    this->cycleTime = ct;
    this->ID = IDCounter++;
    return;
}

void CycleDevice::setTimer(unsigned short time1)
{
    this->nextTimer->timeOn = time1;
    this->nextTimer->timeOff = time1+this->cycleTime;
    return;
}