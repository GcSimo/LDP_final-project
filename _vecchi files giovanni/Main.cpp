#include <iostream>

#include "../include/MyClock.h"
#include "../include/Disp_M.h"
#include "../include/Disp_CP.h"

int main() {
    DispM Televisione("Televisione", -0.2);
    
    // Verifico la correttezza del nome
    std::cout << "Le seguenti operazioni vengono eseguite sul seguente dispositivo: " << Televisione.get_name() << "\n";
    std::cout << std::endl << std::endl;

    // Test accensione e spegnimento della Televisione
    std::cout << "Stato iniziale della Televisione: " << Televisione.get_status() << "\n";
    Televisione.turnOn();
    std::cout << "Stato successivo n. 1 della Televisione: " << Televisione.get_status() << "\n";
    Televisione.turnOff();
    std::cout << "Stato successivo n. 2 della Televisione: " << Televisione.get_status() << "\n";
    std::cout << std::endl << std::endl;

    // Ricevo il codice indentificativo (ID) del dispositivo Televisione
    std::cout << "ID Televisione = " << Televisione.get_id() << "\n";
    std::cout << std::endl << std::endl;

    // Ricevo il dato di consumo della Televisione
    std::cout << "Consumo della Televisione: " << Televisione.get_energy() << "\n";
    std::cout << std::endl << std::endl;

    // Ricevo e stampo l'ora di accensione impostata del dispositivo
    std::cout << "Ora di accensione impostata: " << Televisione.get_onTime() << "\nSetto l'ora di accensione della Televisione alle 10:25\n";
    Televisione.set_onTime(10, 25);
    std::cout << "Ora di accensione impostata: " << Televisione.get_onTime() << "\n";
    std::cout << std::endl << std::endl;

    // Ricevo e stampo l'ora di spegnimento impostata del dispositivo
    std::cout << "Ora di spegnimento impostata: " << Televisione.get_offTime() << "\nSetto l'ora di spegnimento della Televisione alle 11:13\n";
    Televisione.set_offTime(11, 13);
    std::cout << "Ora di spegnimento impostata: " << Televisione.get_offTime() << "\n";
    std::cout << std::endl << std::endl;


    DispM Lavatrice("Lavatrice", 1.5);
    std::cout << "Per test creo un altro dispositivo, verifico il funzionamento della variabile statica.\nID " << Lavatrice.get_name() << " = " << Lavatrice.get_id() << std::endl << std::endl;

    std::cout << "Creo un dispositivo CP per veerificare il funzionamento di get_offTime()\n";
    DispCP Caldaia("Caldaia", -0.75, my_clock::Clock(0, 5));
    Caldaia.set_onTime(17, 5);
    std::cout << "Dispositivo " << Caldaia.get_name() << " accensione ore " << Caldaia.get_onTime() << ", spegnimento ore " << Caldaia.get_offTime() << ".\n";
    return 0;
}