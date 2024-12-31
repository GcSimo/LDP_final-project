#include "Device.h"
#include <iostream>

short IDCounter = 0;

Device::Device()
{
    this->name = "unknown";
    this->state = false;
    this->lastOn = 0;
    this->ID = IDCounter++;
}

Device::Device(std::string s, float pc, bool ses)
{
    this->name = s;
    this->powerConsumption = pc;
    this->ID = IDCounter++;
    this->lastOn = 0;
    this->state = ses;
    this->nextTimer = nullptr;
    return;
}

std::string ShortToDate(short s){
    std::string str = "";
    short first = s/60;
    short second = s%60;
    if(first < 10)
        str += "0";
    str += std::to_string(first)+":"+std::to_string(second);
    if(second < 10)
        str += "0";
    return str;
}

std::string Device::getName()
{
    return std::string(this->name);
}

float Device::getPowerCons()
{
    return this->powerConsumption;
}

bool Device::getState()
{
    return this->state;
}

void Device::ON(unsigned short timenow)
{
    this->state = true;
    this->lastOn = timenow;
}

void Device::refreshTimers(unsigned short timet,Home h)
{
    if(nextTimer == nullptr)return;
    if(this->state){
        if(nextTimer->timeOff < timet){
            OFF(this->nextTimer->timeOff);
        }
    }else{
        if((*nextTimer).isBetween(timet)){
            if(h.checkMax(this->powerConsumption,timet) > -3.5){
                ON(this->nextTimer->timeOn);
            }else{
                std::cout<<"\n\nPROBLEMA\n\n";
            }
        }else if((*nextTimer).timeOff < timet){
            if(h.checkMax(this->powerConsumption,timet) > -3.5){
                ON(this->nextTimer->timeOn);
                OFF(this->nextTimer->timeOff);
            }else{
                std::cout<<"\n\nPROBLEMA\n\n";
            }
        }
    }
    return;
}

float Device::getConsumptionAt(short ntime)
{
    float consumption = 0;
    for (auto x : deviceCycles)
    {
        if(x.second->timeOff < ntime)
            consumption += x.second->getOffset() * this->powerConsumption / 60;
    }
    if(this->state == true){
        consumption += (ntime - lastOn) * powerConsumption / 60;
    }
    return consumption;
}

bool Device::getStateAt(short t)
{
    for(auto x : deviceCycles){
        if(x.second->timeOn < t && x.second->timeOff > t){
            return true;
        }
    }
    if(lastOn < t && lastOn != 0)
        return true;
    return false;
}

void Device::OFF(unsigned short timenow)
{
    if(this->state){
        this->deviceCycles.insert({this->lastOn,new Interval(this->lastOn,timenow)});
        nextTimer.reset();
        this->nextTimer = nullptr;
        this->state = false;
    }
}
//it overwrites the old timer
void Device::setTimer(unsigned short time1, unsigned short time2)
{
    if (!nextTimer) {
        nextTimer = std::make_unique<Interval>();
    }
    if(time1 == time2)return;
    this->nextTimer->timeOn = (time1<time2)?time1:time2;
    this->nextTimer->timeOff = (time1<time2)?time2:time1;
    return;
}

CycleDevice::CycleDevice() : Device()
{
}

void CycleDevice::ON(unsigned short timenow)
{
    if(this->state == true)return;
    this->lastOn = timenow;
    this->nextTimer = std::make_unique<Interval>(timenow, timenow + this->cycleTime);
    this->state = true;
    return;
}

CycleDevice::CycleDevice(std::string s, float pc, unsigned short ct, bool ses ) : Device(s, pc, ses)
{
    this->cycleTime = ct;
    return;
}

void CycleDevice::setTimer(unsigned short time1)
{
    this->nextTimer = std::make_unique<Interval>(time1, time1 + this->cycleTime);
    return;
}