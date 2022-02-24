#pragma once

#include <Headers/headers/headers.h>
#include <Headers/data/variables.h>
#include <Headers/data/structs.h>

#ifndef SERWER_INSERTCHAR_H
#define SERWER_INSERTCHAR_H

int finsert (FILE* file, const char *buffer) {

    long int insert_pos = ftell(file);
    if (insert_pos < 0) return insert_pos;

    // Grow from the bottom
    int seek_ret = fseek(file, 0, SEEK_END);
    if (seek_ret) return seek_ret;
    long int total_left_to_move = ftell(file);
    if (total_left_to_move < 0) return total_left_to_move;

    char move_buffer[1024];
    long int ammount_to_grow = strlen(buffer);
    if (ammount_to_grow >= sizeof(move_buffer)) return -1;

    total_left_to_move -= insert_pos;

    for(;;) {
        //u16 ammount_to_move = sizeof(move_buffer);
        int ammount_to_move = sizeof(move_buffer);

        if (total_left_to_move < ammount_to_move) ammount_to_move = total_left_to_move;

        long int read_pos = insert_pos + total_left_to_move - ammount_to_move;

        seek_ret = fseek(file, read_pos, SEEK_SET);
        if (seek_ret) return seek_ret;
        fread(move_buffer, ammount_to_move, 1, file);
        if (ferror(file)) return ferror(file);

        seek_ret = fseek(file, read_pos + ammount_to_grow, SEEK_SET);
        if (seek_ret) return seek_ret;
        fwrite(move_buffer, ammount_to_move, 1, file);
        if (ferror(file)) return ferror(file);

        total_left_to_move -= ammount_to_move;

        if (!total_left_to_move) break;

    }

    seek_ret = fseek(file, insert_pos, SEEK_SET);
    if (seek_ret) return seek_ret;
    fwrite(buffer, ammount_to_grow, 1, file);
    if (ferror(file)) return ferror(file);

    return 0;
}


/*
 * Use it like this:

FILE * file= fopen("test.data", "r+");
ASSERT(file);
const char *to_insert = "INSERT";

fseek(file, 3, SEEK_SET);
finsert(file, to_insert);

ASSERT(ferror(file) == 0);
fclose(file);
 *
 */

#endif /* !SERWER_INSERTCHAR_H */
