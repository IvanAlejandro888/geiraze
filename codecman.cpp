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

#include "codecman.h"

unsigned long int lost = 0;

int ant = 0;
int act = 1;

void Codecman::incAnt()
{
    ant++;
}

void Codecman::incAct()
{
    act++;
}

int Codecman::getTotalLost()
{
    int r = lost;
    lost = 0;
    return r;
}

std::vector<std::string> Codecman::lookupPairs(char* c)
{
    std::vector<std::string> output;
    Charman charman;
    
    // Walk through string
    while(act!=strlen(c)+1){
        
        std::string current;
        
        char tant = charman.getCharType(c[ant]);
        char tact = charman.getCharType(c[act]);
        
        // Valid pair (C+V)
        if(tant == 2 && tact == 1){
            current.push_back(c[ant]);
            current.push_back(c[act]);
            
            output.push_back(current);
            
            // Jump twice
            incAnt();
            incAnt();
            incAct();
            incAct();
            
        // Non valid pair (Save and recycle)
        } else {
            current.push_back(c[ant]);
            output.push_back(current);
            
            // Jump once (recycle)
            incAnt();
            incAct();
        }
    }
    
    ant = 0;
    act = 1;
    
    return output;
}

std::string Codecman::replace(std::vector<std::string> pairs)
{
    std::string output;
    Charman charman;
    
    for(int i=0;i<pairs.size();i++){
        char value = charman.getPairValue(pairs[i]);
        if((unsigned char)value == (unsigned char)255){ lost+=1; }
        output.push_back(value);
    }
    
    return output;
}


std::string Codecman::invertReplace(std::string geiraze)
{
    std::string output;
    Charman charman;
    
    for(int i=0;i<geiraze.size();i++){
        output.append(charman.getPairFromValue(geiraze[i]));
    }
    
    return output;
}
