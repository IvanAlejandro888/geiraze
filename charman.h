/*
 * Geiraze - 8 bit based text compression algorithm
 * Copyright (C) 2017  Ivan Alejandro <ivan.avalos.diaz@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CHARMAN_H
#define CHARMAN_H

#include "importer.h"

class Charman
{
public:
    // Functions
    char* lowcase(char* str);
    
    // Getters
    char getCharType(char c);
    char getCharValue(char c);
    char getPairValue(std::string c);
    std::string getPairFromValue(char c);
    char getCharFromValue(char c, bool t);
};

#endif // CHARMAN_H
