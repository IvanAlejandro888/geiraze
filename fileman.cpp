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

#include "fileman.h"

void Fileman::setFilenames(char* in, char* ou, bool mode)
{
    inFile = (char*) malloc(strlen(in)*8);
    strncpy(inFile, in, strlen(in));
    
    // Compress
    if(mode == 0){
        const char* ext = ".grz";
    
        ouFile = (char*) malloc(strlen(ou)+strlen(ext)*8);
        strncpy(ouFile, ou, strlen(ou));
        strncat(ouFile, ext, strlen(ext));
        
    // Extract
    }else{
        ouFile = (char*) malloc(strlen(ou)*8);
        strncpy(ouFile, ou, strlen(ou));
    }
}

std::vector <char*> Fileman::getFilenames(){
    std::vector <char*> output;

    output.push_back(inFile);
    output.push_back(ouFile);
    
    return output;
}

void Fileman::readFileContent()
{
    // Open file
    ptrIn = fopen(inFile, "r");
    
    if(ptrIn != NULL){
        
        // Get file size
        fseek(ptrIn, 0L, SEEK_END);
        inSize = ftell(ptrIn);
        rewind(ptrIn);
        
        // Allocate
        resIn = (char*) malloc(inSize*8);
        if(resIn==NULL) {
            printf("Memory error!\n");
            exit(2);
        }
        
        // Read content
        while(!feof(ptrIn))
		{
			char byte = (char) fgetc(ptrIn);
			strncat(resIn, &byte, 1);
		}
        
        // Close
        fclose(ptrIn);
    } else {
        printf("Error: Cannot read file content");
        exit(1);
    }
}

void Fileman::writeOutput(char* output)
{
    ptrOu = fopen(ouFile, "w");
    if(ptrOu != NULL){
        
        // Write output to file
        fwrite(output, sizeof(char), strlen(output), ptrOu);
        
        // Close
        fclose(ptrOu);
    } else {
        printf("Error: Cannot write output file");
    }
}

char * Fileman::getInContent()
{
    char* output = (char*) malloc(inSize*8);
    strncpy(output, resIn, inSize);
    return output;
}

int Fileman::getInSize()
{
    return inSize;
}

void Fileman::deleteRes(){
    free(resIn);
}
