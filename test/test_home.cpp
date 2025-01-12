#include <iostream>
#include "Home.h"
using namespace std;

int main () {
	std::cout << "Programma Domotic-Home del gruppo ~BankAccount()" << std::endl << std::endl;
	
	// creazione casa
	domotic_home::Home h;

	// test accensione e spegnimento manuali
	cout << " --- TEST ACCENSIONE E SPEGNIMENTO MANUALI ---" << endl;
	cout << h.show() << endl;
	cout << h.set("Televisore", true) << endl; // 1h CP
	cout << h.set("Lavatrice", true) << endl; // 1h 50m CP
	cout << h.set("Frigorifero", true) << endl; // M
	cout << h.set_time("1:30") << endl; // dovrebbe spegnersi il televisore alle 1:00
	cout << h.show() << endl;           // mostra consumi dopo 1,5h
	cout << h.set_time("2:00") << endl; // dovrebbe spegnersi la lavatrice alle 1:50
	cout << h.show() << endl;           // mostra consumi dopo 2h
	cout << h.set_time("2:30") << endl; // non dovrebbe succedere nulla
	cout << h.set("Frigorifero", false) << endl; // spengo il frigo
	cout << h.set_time("3:00") << endl; // non dovrebbe succedere nulla
	cout << h.show() << endl;           // mostra consumi dopo 3h

	// test accensione e spegnimento automatici per dispositivi M
	cout << "\n --- TEST ACCENSIONE E SPEGNIMENTO PROGRAMMATI DISPOSITIVI M ---" << endl;
	// solo accensione e spegnimento automatici
	cout << h.set("Scaldabagno", "4:00", "5:00") << endl; // imposto timer
	cout << h.set_time("4:30") << endl; // scaldabagno si accende alle 4:00
	cout << h.set_time("5:30") << endl; // scaldabagno si spegne alle 5:00
	// pre accensione manuale
	cout << h.set("Scaldabagno", "6:00", "7:00") << endl; // imposto timer
	cout << h.set("Scaldabagno", true) << endl; // accensione anticipata (alle 5:30)
	cout << h.set_time("6:30") << endl; // scaldabagno si riaccende alle 6:00
	cout << h.set_time("7:30") << endl; // scaldabagno si spegne alle 7:00
	// pre spegnimento manuale
	cout << h.set("Scaldabagno", "8:00", "9:00") << endl; // imposto timer
	cout << h.set_time("8:30") << endl; // scaldabagno si accende alle 8:00
	cout << h.set("Scaldabagno", false) << endl; // spegnimento anticipato
	cout << h.set_time("9:30") << endl; // scaldabagno si rispegne alle 9:00
	
	// test accensione e spegnimento automatici per dispositivi CP
	cout << "\n --- TEST ACCENSIONE E SPEGNIMENTO PROGRAMMATI DISPOSITIVI CP ---" << endl;
	// solo accensione e spegnimento automatici
	cout << h.set("Asciugatrice", domotic_home::Clock("10:00")) << endl; // imposto timer
	cout << h.set_time("10:30") << endl; // asciugatrice si accende alle 10:00
	cout << h.set_time("11:30") << endl; // asciugatrice si spegne alle 11:00
	// pre accensione manuale
	cout << h.set("Asciugatrice", domotic_home::Clock("12:00")) << endl; // imposto timer
	cout << h.set("Asciugatrice", true) << endl; // accensione anticipata (alle 11:30:30)
	cout << h.set_time("12:30") << endl; // asciugatrice si riaccende alle 12:00
	cout << h.set_time("13:30") << endl; // asciugatrice si spegne alle 13:00
	// pre spegnimento manuale
	cout << h.set("Asciugatrice", domotic_home::Clock("14:00")) << endl; // imposto timer
	cout << h.set_time("14:30") << endl; // asciugatrice si accende alle 14:00
	cout << h.set("Asciugatrice", false) << endl; // spegnimento anticipato
	cout << h.set_time("15:30") << endl; // asciugatrice si rispegne alle 15:00
	
	// test rimozione timers
	cout << "\n --- TEST RIMOZIONE TIMERS ---" << endl;
	cout << h.set("Impianto_fotovoltaico", "16:00", "16:15") << endl; // imposto timer
	cout << h.set("Forno_a_microonde", domotic_home::Clock("16:05")) << endl; // imposto timer
	cout << h.rm("Impianto_fotovoltaico") << endl; // rimuovo timer
	cout << h.rm("Forno_a_microonde") << endl; // rimuovo timer
	cout << h.set_time("16:30") << endl; // siccome ho rimosso i timer, nulla dovrebbe accendersi
	cout << h.set("Forno_a_microonde", domotic_home::Clock("16:32")) << endl; // imposto timer
	cout << h.set_time("16:33") << endl; // faccio accendere il forno
	cout << h.rm("Forno_a_microonde") << endl; // elimino orario terminazione
	cout << h.set_time("16:40") << endl; // il forno a microonde non si spegne
	cout << h.set("Forno_a_microonde", false);

	// test reset time
	cout << "\n --- TEST RESET TIME ---" << endl;
	cout << h.show() << endl;
	cout << h.reset_time() << endl;
	cout << h.show() << endl;
	cout << h.set_time("2:00"); // dovrebbe provare a spegnere il frigo per riga 14 e la lavatrice per riga 15

	// test reset timers
	cout << "\n --- TEST RESET TIMERS ---" << endl;
	cout << h.set("Televisore", domotic_home::Clock("2:10")) << endl; // imposto timer
	cout << h.set("Asciugatrice", domotic_home::Clock("2:15")) << endl;
	cout << h.set("Frigorifero", "2:20", "2:30") << endl;
	cout << h.reset_timers() << endl;
	cout << h.set_time("2:30"); // non dovrebbe accendersi nulla

	// test reset all
	cout << "\n --- TEST RESET ALL ---" << endl;
	cout << h.set("Televisore", true) << endl; // accendo dispositivi
	cout << h.set("Lavatrice", true) << endl;
	cout << h.set("Frigorifero", true) << endl;
	cout << h.set_time("5:00") << endl; // faccio spengere i dispositivi
	cout << h.set("Frigorifero", false) << endl;
	cout << h.show() << endl; // mostra consumi
	cout << h.reset_all() << endl; // reset
	cout << h.show() << endl; // mostra consumi post reset

	// test eccezioni
	cout << "\n --- TEST ECCEZIONI ---" << endl;
	try { // errore formattazione orario
		h.set_time("24:00");
	} catch (const exception &e)
	{
		cout << e.what() << endl;
	}
	try { // errore orario nel passato
		h.set_time("2:00");
		h.set_time("1:00");
	} catch (const exception &e)
	{
		cout << e.what() << endl;
	}
	try { // errore nome dispositivo non valido
		h.set("banana", true);
	} catch (const exception &e)
	{
		cout << e.what() << endl;
	}
	try { // errore tipo dispositivo non valido
		h.set("Televisore","12:00","13:00");
	} catch (const exception &e)
	{
		cout << e.what() << endl;
	}

	// test overloading funzione set
	cout << "\n --- TEST OVERLOADING FUNZIONE SET ---" << endl;
	domotic_home::Clock clock_temp = "12:00";
	cout << h.set("Scaldabagno", clock_temp); // set(string, clock)
	string string_temp = "12:01";
	cout << h.set("Scaldabagno", string_temp); // set(string, clock)
	const char *lit_temp = "12:02";
	cout << h.set("Scaldabagno", lit_temp); // set(string, bool) o set(string, const char*) se definita
	cout << h.set("Scaldabagno", "12:03"); // set(string, bool) o set(string, const char*) se definita

	// test consumo massimo della casa
	cout << "\n --- TEST CONSUMO MASSIMO ---" << endl;
	cout << h.reset_all() << endl;
	cout << h.set("Frigorifero", true) << endl;
	cout << h.set("Lavastoviglie", true) << endl;
	cout << h.set("Lavatrice", true) << endl;
	cout << h.set("Tapparelle_elettriche", true) << endl;
	cout << h.set("Asciugatrice", true) << endl;
	cout << h.set("Televisore", true) << endl;
	cout << h.set("Forno_a_microonde", true) << endl;
	cout << h.set("Impianto_fotovoltaico", true) << endl;
	cout << h.set("Frigorifero", true) << endl;
	cout << h.set("Lavastoviglie", true) << endl;
	cout << h.set("Lavatrice", true) << endl;
	cout << h.set("Impianto_fotovoltaico", false) << endl;
}
