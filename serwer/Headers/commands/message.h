#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_MESSAGE_H
#define SERWER_MESSAGE_H

void message(struct clients_struct *client_data, char *arguments[], int size_of_array){

    int descriptor = client_data->file_descriptor;

    //read(descriptor, "example", 7);
    //printf("WPISALEM: example do pliku\n");

    long Fin;
    long lSize;

    //INFORMACJE DO SERWERU
    //POZYCJA
    long position;

    //SLOWO (LITERKA)
    char* word;

    FILE* file_descriptor ;
    descriptor = fopen("/home/oem/Desktop/17.01/Serwerek/serwer/cmake-build-debug/DOCUMENTS/adam/1.txt", "w+");


    fseek(descriptor, 0L, SEEK_END);  //<-- "0L" - 0 long
    Fin = ftell(descriptor);//get the old file size
    fseek(descriptor, position, SEEK_SET);//"position" must be declared and initialized
    char * buffer;
    lSize = Fin - position;//length from where you want to insert the chars to the eof

    buffer = (char*) malloc(sizeof(char) * lSize);
    size_t result = fread(buffer, 1, lSize, descriptor);//fread (Fin - position) into buffer
    fseek(descriptor, position, SEEK_SET);//fseek to position

    fputs(word, descriptor);//word is a char pointer that contains the text to be inserted
    fputs(buffer, descriptor);//fwrite the buffer





    //fclose(descriptor);
}


#endif /* !SERWER_MESSAGE_H*/
