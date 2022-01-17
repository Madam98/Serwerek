#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_SIGSEGV_H
#define SERWER_SIGSEGV_H

void handler(int nSignum, siginfo_t* si, void* vcontext) {
    //printf("Segmentation fault\n");
    //printf("Powyzszy port jest zajety. Czekam na zwolnienie portu\n");

    ucontext_t* context = (ucontext_t*)vcontext;
    context->uc_mcontext.gregs[REG_RIP]++;
}

#endif /* !SERWER_SIGSEGV_H */
