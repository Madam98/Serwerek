#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_CREATEFOLDER_H
#define SERWER_CREATEFOLDER_H


int ExistsFolder(char* path){
    DIR *dir = opendir(path);
    if (!(dir)){
        printf("Folder nie istnieje\n");
        return 1;
    }
    return 0;
}

void createFolder(char* path, char* dirname) {
    //printf("\tFolder: %s\n", getenv("PWD"));
    //printf("\tWykonywany plik: %s/%s\n", getenv("PWD"), __FILE__);

    //char *dirname = "DOCUMENTS"; //<--- tworz ten plik zawsze gdy dziala serwer o podanej nazwie
    //DIR *dir = opendir(dirname);

    //char* path_temp;
    //strcpy(path_temp, path);

    char* folder_sciezka = (char*)malloc(strlen(dirname)+1);
    strcat(path, "/");
    strcpy(folder_sciezka, dirname);
    strcat(path, folder_sciezka);

    if (ExistsFolder(path)) {
        //strcat(path, "/");
        printf("Tworzenie folderu\n");
        mkdir(path, 0777);
    }

    //free(folder_sciezka);
    //pod koniec wywolania funkcji znajdujemy sie w folderze DOCUMENTS
}

void connectUser(char* buf, char* user_path){
    //printf("\n");
    //printBreak();
    //printf("Nazwa uzytkownika: %s\n", buf);

    char* path = strdup(user_path);
    strcpy(path, user_path);

    //char *path = (char *) malloc(strlen(t_data_ptr.path + 1));
    //strcpy(path, t_data_ptr.path);

    //printf("Sciezka pliku wykonywanego: \n\t%s\n\n", path);
    //SPRAWDZAMY CZY PODANY UZYTKOWNIK SIE JUZ LOGOWAL I CZY POSIADA FOLDER O PODANEJ NAZWIE
    createFolder(path, buf);
    printf("Sciezka utworzonego folderu: \t\t \033[1;32m%s\033[0m\n", path);
    //printBreak();
    //printf("\n");

    //free(path);
}


void folderInfo(char* path, char* info){
    printBreak();
    printf("Sciezka pliku wykonywanego: \n\t%s\n\n", path);
    createFolder(path, dirname);
    printf("Sciezka utworzonego folderu: \n\t%s\n", path);
    printBreak();
    printf("\n");
}

#endif /* !SERWER_CREATEFOLDER_H */
