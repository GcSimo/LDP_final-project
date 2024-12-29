#include <iostream>
#include "Home.h"

int main(){
    Home* h = new Home();
    std::vector<std::string> inputs = {"show","set Impianto_Fotovoltaico 600 1200","set PompaDiCaloreETermostato 120 720","set time 60","set Televisore 1000","set time 200","show",
    "set time 300","set Frigorifero on","set time 600","set Frigorifero off",
    "set time 660","set Frigorifero on","set time 1260","set Frigorifero off","set Televisore 1300",
    "set time 1400","show"};
    /* while(true){
        std::string str;
        std::getline(std::cin,str);
        h.listen(str);
    } */
   for(std::string s : inputs)
   {
        h->listen(s);
   }
   
}