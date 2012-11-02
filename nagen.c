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


int blank(char *buffer)
{
    int i;
    for(i=0;buffer[i]!='\0'; i++)
        if((unsigned char)buffer[i]>32)
            return 0;
    return 1;
}

int getLine(char *buffer, int size, FILE *file)
{
    int i;
    int valid = 0;
    while(valid == 0)
    {
        if(fgets(buffer, BUFFER_LENGTH, file)==NULL)
            return 0;
        if(blank(buffer) == 0)
            valid = 1;
    }
    for(i=0; buffer[i] != '\0'; i++)
        if((buffer[i] == '\n')||(buffer[i] == '\r')||(buffer[i] == '\t'))
            buffer[i] = '\0';
    return 1;
}

