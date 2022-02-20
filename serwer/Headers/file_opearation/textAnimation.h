#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>
#include <Headers/file_opearation/msleep.h>

#ifndef SERWER_TEXTANIMATION_H
#define SERWER_TEXTANIMATION_H
int textAnimation(){
    int counter = 0;
    while(counter <= 5) {
        long tms = 300;
        char *f, a[] = "\rlaczenie ";
        for (f = a; *++f; *f &= 95, printf(a), *f |= 32, fflush(msleep(tms)));
        memset(a, 0, strlen(a));
        counter++;
        //sleep(tms/100*strlen(a));
    }
    printf("\n");
}
#endif /* !SERWER_TEXTANIMATION_H */
