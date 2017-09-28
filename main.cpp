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

#include "importer.h"

double percentOf(size_t a, size_t b);

const char* help = "\nUsage: geiraze [OPTION] [INPUT] [OUTPUT]\nGeiraze is a lossy text compression tool that just keeps text and few symbols.\n\nOperations:\n\t--c\tCompress a text file\n\t--e\tExtract a file compressed used Geiraze\n\n";

int main(int argc, char **argv) {
    
    // Initialize
    Fileman fileman;
    Charman charman;
    Codecman codecman;
    
    // Check if there is first argument
    if(argc < 2){
        printf(help);
        return 0;
    }
    
    // Help
    if(strncmp("--help", argv[1], strlen(argv[1])) == 0){
        printf(help);
        return 0;
    }else
    
    // Compress
    if(strncmp("--c", argv[1], strlen(argv[1])) == 0){
        
        // Check if there is second and third argument
        if(argc < 4){
            printf("Missing arguments!\n");
            printf(help);
            return 0;
        }
        
        // Get data from user
        fileman.setFilenames(argv[2], argv[3], false);
        // Read content
        fileman.readFileContent();
        
        // Lookup pairs
        std::vector<std::string> pairs = codecman.lookupPairs(charman.lowcase(fileman.getInContent()));
        // Replace (generate output)
        std::string geirazeChars = codecman.replace(pairs);
        
        // Write output
        fileman.writeOutput((char*) geirazeChars.c_str());
        
        // Compare size
        double compressedSize = percentOf(fileman.getInSize(), geirazeChars.size());
        
        printf("Original size:  %dB (100%%)\n", fileman.getInSize());
        printf("Final size:     %zuB (%g%%)\n", geirazeChars.size(), compressedSize);
        
        printf("Size reduction: %zuB (-%g%%)\n", fileman.getInSize() - geirazeChars.size(), 100-compressedSize);
        
        // Print quality lost
        printf("Quality lost:   %lu\n", (unsigned long int) codecman.getTotalLost());
        
        // Free memory
        fileman.deleteRes();
    }else
    
    // Extract
    if(strncmp("--e", argv[1], strlen(argv[1])) == 0){
        
        // Check if there is second and third argument
        if(argc < 4){
            printf("Missing arguments!\n");
            printf(help);
            
            return 0;
        }
        
        // Get data from user
        fileman.setFilenames(argv[2], argv[3], true);
        // Read content
        fileman.readFileContent();
        
        // Rebuild file
        std::string uncompressed = codecman.invertReplace(fileman.getInContent());
        
        // Write output
        fileman.writeOutput((char*) uncompressed.c_str());
        
        // Free memory
        fileman.deleteRes();
    }else{
        printf("Invalid option!\n");
        printf(help);
    }
    
    return 0;
}

double percentOf(size_t a, size_t b){
    return (b*100/a);
}
