#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_MSLEEP_H
#define SERWER_MSLEEP_H

int msleep(long tms)
{
    struct timespec ts;
    int ret;
    if (tms < 0){
        errno = EINVAL;
        return -1;
    }
    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;
    do {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);

    return ret;
}

#endif /* !SERWER_MSLEEP_H */
