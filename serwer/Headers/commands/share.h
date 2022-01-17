#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>

#ifndef SERWER_SHARE_H
#define SERWER_SHARE_H

void shareCommand(void *t_data){

    printf("KOMENDA W PRZYGOTOWANIU!!\n");
    //POMYSLEC NAD ROZWIAZANIEM
    //Mamy dwie opcje udostepniania/zabezpieczenia udzielenia dostepu
    //Number uno (zabezpieczenie)
    //Przy tworzeniu pliku tworzymy rowniez uzytkownika na linuksie. Tworzymy rowniez grupe o takiej samej nazwie
    //pryz udostepnianiu uzytkownikowi dodajemy go do grupy uzytkownika wlasciciela

    //Number secondo (udostepnienie)
    //Przy kazdym zalogowaniu sie uzytkownika musimy identyfikowac czy ma stworzony folder ze swoja nazwa i dokument
    //Identyfikacja? Narazie wpisujemy przy laczeniu nazwe uzytkownika (po stronie klienta). Potem mozna zamienic na adres ip
    //Po zalogowaniu i sprawdzeniu czy dokument istnieje program pobiera deskryptor pliku -> pobiera liste zalogowanych uzytkownikow i przekazuje je do udostepnienia







}


#endif /* !SERWER_SHARE_H */
