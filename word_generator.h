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


int interpret(char *buffer);
int extractLine(FILE *file, int length, char *buffer);
Rule* processRuleFile(Arguments *args);
int countRules(FILE *file);
void initPass(FILE *file, Rule *rules, int rules_number); 
void finalPass(FILE *file, Rule *rules, int rules_number); 
void setName(char *name, Rule *rule);
void setConnection(char *buffer, Rule *rules, int rules_number, int i, int j);
void setSymbol(char *buffer, Rule *rule, int j);
void generateName(FILE *file,Rule *rules, int length);
