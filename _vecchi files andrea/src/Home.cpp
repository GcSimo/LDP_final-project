#include "Home.h"
#include <iostream>
#include <sstream>

std::string ShortToDate(short);

std::vector<CycleDevice*> CycleDeviceList = {new CycleDevice("Lavatrice",-2,110,false),new CycleDevice("Lavastoviglie",-1.5,195,false),new CycleDevice("Tapparelle elettriche",-0.3,1,false),new CycleDevice("Forno a microonde",-0.8,2,false),new CycleDevice("Asciugatrice",-0.5,60,false),new CycleDevice("Televisore", -0.2 ,60,false)};
std::vector<Device*> ManualDeviceList = {new Device("Impianto_Fotovoltaico",1.5),new Device("PompaDiCaloreETermostato",-2),new Device("Scaldabagno",-1),new Device("Frigorifero",-0.4)};

void Home::listen(std::string s)
{
    std::vector<std::string> commandLines;
    std::istringstream stream(s);
    std::string line;

    while (std::getline(stream, line, ' ')) {
        commandLines.push_back(line);
    }

    if(commandLines[0] == "set"){
        if(commandLines[1] == "time"){
            if(commandLines[2].empty())return;
            int timeto = std::stoi(commandLines[2]);
            std::cout<<"\n\nTempo : "<<ShortToDate(time)<<" ---> "<<ShortToDate(timeto)<<"\n\n";
            time = timeto;
            this->goForward(timeto);
        }else if(!commandLines[1].empty()){
            if(commandLines[2] == "on"){
                if(devices.count(commandLines[1])){
                    (devices.at(commandLines[1]))->ON(time);
                    std::cout<<"dispositivo "<<commandLines[1]<<" ON";
                }
                else if(cycleDevices.count(commandLines[1])){
                    (cycleDevices.at(commandLines[1]))->ON(time);
                    std::cout<<"dispositivo "<<commandLines[1]<<" ON";
                }
            }else if(commandLines[2] == "off"){
                if(devices.count(commandLines[1])){
                    devices.at(commandLines[1])->OFF(time);
                    std::cout<<"dispositivo "<<commandLines[1]<<" OFF";
                }
                else if(cycleDevices.count(commandLines[1])){
                    cycleDevices.at(commandLines[1])->OFF(time);
                    std::cout<<"dispositivo "<<commandLines[1]<<" OFF";
                }
            }else{
                int timefromtimer = std::stoi(commandLines[2]);
                if(devices.count(commandLines[1])){
                    int timetotimer = std::stoi(commandLines[3]);
                    devices.at(commandLines[1])->setTimer(timefromtimer,timetotimer);
                }
                if(cycleDevices.count(commandLines[1])){
                    cycleDevices.at(commandLines[1])->setTimer(timefromtimer);
                }
            }
        }
    }
    if(commandLines[0] == "rm"){

    }
    if(commandLines[0] == "show"){
        float cons = 0;
        float actualcons = 0;
        std::cout<<"Show al tempo "<<ShortToDate(time)<<" :\n";
        for(auto &d : devices){
            float thiscons = d.second->getConsumptionAt(time);
            std::cout<<d.first<<" : "<<(d.second)->getState()<<", ha consumato "<<thiscons<<"KW fino ad ora\n";
            if((d.second)->getState()){
                actualcons += d.second->getPowerCons();
            }
            cons += thiscons;
        }
        for(auto &d : cycleDevices){
            float thiscos = d.second->getConsumptionAt(time);
            std::cout<<d.first<<" : "<<(d.second)->getState()<<", ha consumato "<<thiscos<<"KW fino ad ora\n";
            if((d.second)->getState()){
                actualcons += d.second->getPowerCons();
            }
            cons += thiscos;
        }
        std::cout<<"\nConsumo totale della casa fino alle "<<ShortToDate(time)<<" : "<<cons<<"Kw/h\nE con un attuale consumo di "<<actualcons<<"Kw\n\n";
        return;
    }
    if(commandLines[0] == "reset"){

    }
}

void Home::goForward(short ti)
{
    for (Device* d : ManualDeviceList)
    {
        d->refreshTimers(ti);
    }
    for (CycleDevice* c : CycleDeviceList)
    {
        c->refreshTimers(ti);
    }
    this->time = ti;
    return;
}

Home::Home()
{
    this->time = 0;
    for (Device* d : ManualDeviceList)
    {
        devices.insert({d->getName(),d});
    }
    for (CycleDevice* c : CycleDeviceList)
    {
        this->cycleDevices.insert({c->getName(),c});
    }
}
