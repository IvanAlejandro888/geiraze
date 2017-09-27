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

#include "debugman.h"

int Debugman::debugCharman()
{
    // Initialize
    Charman charman;
    
    // Lowcase test
    const char* c = "Ivan is the best (worst) programmer ever born!";
    
    printf("Original: %s\n", c);
    printf("Lowcased: %s\n\n", charman.lowcase((char*)c));
    c = charman.lowcase((char*) c);
    
    // Char type
    int type;
    
    for(int i=0;i<strlen(c);i++){
        printf("%c : ", c[i]);
        
        type = charman.getCharType(c[i]);
        if(type == 0) printf("?");
        if(type == 1) printf("V");
        if(type == 2) printf("C");
        
        // Get char from value
        
        printf(" : %i ", charman.getCharValue(c[i]));
        if(type == 0) printf("%c\n", 219);
        if(type == 1) printf("-> %c\n", charman.getCharFromValue(charman.getCharValue(c[i]), 0));
        if(type == 2) printf("-> %c\n", charman.getCharFromValue(charman.getCharValue(c[i]), 1));
    }
    
    return 0;
}

int Debugman::debugFileman(int argc, char** argv)
{
    // Initialize
    Fileman fileman;
    
    // Set and get filenames
    fileman.setFilenames(argv[1], argv[2], false);
    std::vector<char*> filenames = fileman.getFilenames();
    
    printf("Input:  %s\n", filenames[0]);
    printf("Output: %s\n", filenames[1]);
    
    // Read content
    fileman.readFileContent();
    
    printf("\nSize: %i ----------------------------------------------\n", fileman.getInSize());
    printf("\n\n%s\n\n", fileman.getInContent());
    
    // Write input to output
    fileman.writeOutput(fileman.getInContent());
    
    // Don't forget cleaning
    fileman.deleteRes();
    
    return 0;
}

int Debugman::debugCodecman()
{
    // Initialize
    Codecman codecman;
    Charman charman;
    
    /* Compression */
    
        // Test string
        char* str  = charman.lowcase((char*)(const char*) "Iván is great, and I'm not great");
        char* str2 = charman.lowcase((char*)(const char*) "Don't take my life away");
        
        printf("String: %s\n----------------------\n# Compression:\n", str);
        
        // Lookup pairs
        std::vector<std::string> pairs = codecman.lookupPairs(str);
        // Replace (generate output)
        std::string geirazeChars = codecman.replace(pairs);
        
        for(int i=0;i<pairs.size();i++){
            printf("%s -> %i\n", pairs[i].c_str(), (unsigned char) geirazeChars[i]);
        }
        
        // Quality lost
        printf("\nLost:  %i\n", codecman.getTotalLost());
    
    /* Extraction */
    
        std::string uncompressed = codecman.invertReplace(geirazeChars);
        printf("\n----------------------\n# Extraction:\nString: %s\n", uncompressed.c_str());
    
    return 0;
}
