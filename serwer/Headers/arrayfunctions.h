#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_ARRAYFUNCTIONS_H
#define SERWER_ARRAYFUNCTIONS_H

// funkcja wypisująca zawartość tablicy typu int
void print_array_content(int *arr, int len) {
    printf("Polaczone gniazda\n");
    for (int i = 0; i < len; i++)
        printf("\t %d ", *(arr+i));
    printf("\n\n");
}


// funkcja zerująca komórki tablicy, w których dotychczas znajdowała się podana wartość
void clear_array_cell(int *arr, int len, int value) {
    for(int i = 0; i < len; i++)
        if (arr[i] == value)
            arr[i] = 0;
}

// funkcja znajdująca indeks tablicy typu int, dla którego wartość tablicy = 0
// jeśli nie ma takiego indeksu, funkcja zwraca -1
int find_empty_cell(int *arr, int len) {
    for (int i = 0; i < len; i++)
        if (arr[i] == 0)
            return(i);
    return(-1);
}

#endif /* !SERWER_ARRAYFUNCTIONS_H */
