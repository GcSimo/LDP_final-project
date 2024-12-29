#include <iostream>
#include "Home.h"

int main(){
    Home* h = new Home();
    std::vector<std::string> inputs = {"show","set time 60","set Televisore on","set time 200","show"};
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