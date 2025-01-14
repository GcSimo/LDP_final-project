/*
	FILE HEADER PARSER.H
	Autore:     Andrea Visonà

	La libreria contiene una funzione parser per permettere all'utente di
	interfacciarsi con la classe Home. Interpreta i messaggi di testo forniti
	dall'utente e invoca le corrispettive funzioni con i parametri specificati.
*/

#ifndef PARSER_H
#define PARSER_H

#include "Home.h"
#include <string>

namespace domotic_home {
	std::string parser(const std::string &s, Home &h);

	// classe di eccezione quando si inserisce un comando non valido
	class ParserError : public std::logic_error {
		public:
			ParserError() : std::logic_error("") {}
			const char *what() const noexcept override { return "Errore: comando sconosciuto!"; }
	};
}

#endif // PARSER_H
