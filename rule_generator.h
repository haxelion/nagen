/*
This file is part of nagen.

Nagen is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nagen is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Copyright 2012 Charles Hubain <haxelion@gmail.com>
*/
#include "nagen.h"

Rule* generateRules(Arguments *args, int *rules_number);
int countSymbols(FILE *file);
void loadSymbols(FILE *file, char **symbols, int symbols_number);
void sortByLength(char **symbols, int symbols_number);
int calculateFrequency(FILE *file, char **symbols, int **frequency, int symbols_number);
int findSymbols(char *buffer, char **symbols, int symbols_number, int *found_symbols);
void buildRules(char **symbols, int **frequency, int symbols_number, float tolerance, Rule *rules);
void writeRules(Rule* rules, int rules_number, FILE *file);
