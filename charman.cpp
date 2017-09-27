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

#include "charman.h"

/* Geiraze dictionary */

// Vowels
char vowels[] = {'a', 'e', 'i', 'o', 'u'};
char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z', 32, '.', ',', ':', ';', 'y', 10, 9, '?', '!'};

char * Charman::lowcase(char* str)
{
    char* output = (char*) malloc(strlen(str)*8);
    
    for(int i=0;i<strlen(str);i++){
        
        if(str[i] >= 65 && str[i] <= 90){
            output[i] = str[i] + 32;
        } else {
            output[i] = str[i];
        }
    }
    
    return output;
}

char Charman::getCharType(char c)
{
    
    // Vowel = 1
    for(int i=0;i<strlen(vowels);i++){
        if(c == vowels[i]){
            return 1;
        }
    }
    
    // Consonant = 2
    for(int i=0;i<strlen(consonants);i++){
        if(c == consonants[i]){
            return 2;
        }
    }
    
    // Else return 0
    return 0;
}

char Charman::getCharValue(char c)
{
    // Is vowel
    for(int i=0;i<strlen(vowels);i++){
        if(c == vowels[i]){
            return i+1;
        }
    }
    
    // Is consonant
    for(int i=0;i<strlen(consonants);i++){
        if(c == consonants[i]){
            return i+1;
        }
    }
    
    // Else return 0
    return 0;
}

char Charman::getPairValue(std::string c)
{
    char o = 0;
    
    // C + V
    if(c.size() == 2){
        // Consonant
        o = getCharValue(c[0]) << 3;
        
        // Vowel
        o += getCharValue(c[1]);
    }else{
        char type = getCharType(c[0]);
        
        // Consonant
        if(type == 2){
            o = getCharValue(c[0]) << 3;
        } else
        // Vowel
        if(type == 1){
            o = getCharValue(c[0]);
        } else
        // Other
        if(type == 0){
            o = 255;
        }
    }
    
    return o;
}

std::string Charman::getPairFromValue(char c)
{
    std::string output;
    
    // Not unknown
    if((unsigned char)c != (unsigned char) 255){
        
        char consonant = (c >> 3) & 31;
        char vowel = c & 7;
        
        if(consonant!=0) output.push_back(getCharFromValue(consonant, true));
        if(vowel!=0) output.push_back(getCharFromValue(vowel, false));
        
    }else{
        output.push_back(218);
    }
    
    return output;
}

char Charman::getCharFromValue(char c, bool t)
{
    char output = 0;
    
    // Vowel
    if(t==false)
        output = vowels[c-1];
    else
    // Consonant
    if(t==true)
        output = consonants[c-1];
    
    return output;
}
