/*
	FILE HEADER PARSER.H
	Autore:     Andrea Visonà
*/

#ifndef PARSER_H
#define PARSER_H

#include "Home.h"
#include <string>

namespace robotic_home{
	void parser(const std::string &s, Home &h);
}

#endif // PARSER_H
