#include <iostream>
#include <map>

#include "../include/Dispositivo.h"
#include "../include/Disp_M.h"
#include "../include/Disp_CP.h"
#include "../include/MyClock.h"

using namespace std;
using namespace my_clock;

void testTime(const multimap<Clock, Dispositivo*>&, const Clock&, const Clock&);

int main() {
    DispM impiantoFotovoltaico("Impianto Fotovoltaico", 1.5);
    DispCP Lavatrice("Lavatrice", -2.0, Clock(1, 50));
    DispCP Lavastoviglie("Lavastoviglie", -1.5, Clock(3, 15));
    
    multimap<Clock, Dispositivo*> prog;

    // Setto l'orario di accensione e di spegnimento all'impianto fotovoltaico --> Dispositivo MANUALE
    impiantoFotovoltaico.set_onTime(8, 0);
    impiantoFotovoltaico.set_offTime(15, 0);

    // Setto il solo orario di accensione della Lavatrice e della Lavastoviglie  --> Dispositivo CICLO PREFISSATO
    Lavatrice.set_onTime(10, 0);
    Lavastoviglie.set_onTime(12, 30);

    // Inserisco il tutto in una MULTIMAPPA
    prog.insert({impiantoFotovoltaico.get_onTime(), &impiantoFotovoltaico});
    prog.insert({impiantoFotovoltaico.get_offTime(), &impiantoFotovoltaico});

    prog.insert({Lavatrice.get_onTime(), &Lavatrice});
    prog.insert({Lavatrice.get_offTime(), &Lavatrice});

    prog.insert({Lavastoviglie.get_onTime(), &Lavastoviglie});
    prog.insert({Lavastoviglie.get_offTime(), &Lavastoviglie});

    // Creo i due orologi con l'ora di inizio e fine della simulazione, quindi chiamo la funzione
    Clock initTime(7, 0);
    Clock stopTime(19, 0);
    testTime(prog, initTime, stopTime);
    return 0;
}

/*
    Ore 8.00 Accensione Impianto Fotovoltaico
    Ore 10.00 Accensione Lavatrice
    Ore 11.50 Spegnimento Lavatrice
    Ore 12.30 Accensione Lavastoviglie
    Ore 15.00 Spegnimento Impianto Fotovoltaico
    Ore 15.45 Spegnimento Lavastoviglie
*/

void testTime(const multimap<Clock, Dispositivo*>& p, const Clock& initTime, const Clock& stopTime) {
    auto iter = p.begin();

    // Simulazione di test comando set time

    // Con l'iteratore scorro fino a trovare la prima programmazione la cui ora rientra nel range richiesto.
    while (iter->first < initTime && iter != p.end()) iter++;

    Clock tempTime = iter->first;
    while (tempTime <= stopTime && iter != p.end()) {
        (*iter->second).changeStatus();
        cout << "[" << iter->first << "] Il dispositivo \"" << (*iter->second).get_name() << "\" si e' ";
        if ((*iter->second).get_status() == 1) cout << "acceso\n";
        else cout << "spento\n";
        cout << endl << endl;
        iter++;
        tempTime = iter->first;
    }
}