#include <iostream>
#include "Home.h"

int main(){
    Home h;
    std::vector<std::string> inputs = {"show","set time 60"};
    /* while(true){
        std::string str;
        std::getline(std::cin,str);
        h.listen(str);
    } */
   for(std::string s : inputs)
   {
        h.listen(s);
   }
   
}