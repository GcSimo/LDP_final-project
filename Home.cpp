#include "Home.h"
#include <iostream>
#include <sstream>

std::vector<CycleDevice> CycleDeviceList = {CycleDevice("Lavatrice",-2,110,false),CycleDevice("Lavastoviglie",-1.5,195,false),CycleDevice("Tapparelle elettriche",-0.3,1,false),CycleDevice("Forno a microonde",-0.8,2,false),CycleDevice("Asciugatrice",-0.5,60,false),CycleDevice("Televisore",-0.2,60,false)};
std::vector<Device> ManualDeviceList = {Device("impianto fotovoltaico",1.5), Device("Pompa di calore e termostato",-2),Device("Scaldabagno",-1),Device("Frigorifero",-0.4)};

void Home::listen(std::string s)
{
    std::vector<std::string> commandLines;
    std::istringstream stream(s);
    std::string line;

    while (std::getline(stream, line, ' ')) {
        commandLines.push_back(line);
    }

    if(commandLines[0] == "set"){
        printf("hai selezionato set:3\n");
        if(commandLines[1] == "time"){
            if(commandLines[2].empty())return;
            int timeto = std::stoi(commandLines[2]);
            printf("devo andare avanti al tempo : ");
            std::cout<<commandLines[2];
        }else if(!commandLines[1].empty()){
            Device thisDev = this->devices[(commandLines[1])];
            
        }
    }
    if(commandLines[0] == "rm"){
        printf("hai selezionato removeve :3\n");

    }
    if(commandLines[0] == "show"){
        printf("hai selezionato showww :3\n");

    }
    if(commandLines[0] == "reset"){
        printf("hai selezionato reseette te :3\n");

    }
}

Home::Home()
{
    CycleDevice lav("Lavatrice",-2,110,false);
    this->cycleDevices.insert({"Lavatrice",lav});
}
