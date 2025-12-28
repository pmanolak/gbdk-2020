// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org>
// bbbbbr 2020

#ifndef _FILES_H
#define _FILES_H

#include "common.h"

typedef struct file_item {
    char     name_in[MAX_FILE_STR];
    uint16_t bank_num;
    bool     rewrite_needed;
    char     name_out[MAX_FILE_STR];
    unsigned int obj_file_format;
    uint32_t linkerfile_order;
} file_item;

typedef struct file_order_t {
    uint32_t file_id;
    uint32_t linkerfile_order;
} file_order_t;

#define LINKERFILE_ORDER_FIRST 0

void files_init(void);
void files_cleanup(void);
void files_add(char *);

void files_read_linkerfile(char *);
void files_set_linkerfile_outname(char *);
void files_write_linkerfile(void);

char * file_get_name_in_by_id(uint32_t);
char * file_get_name_out_by_id(uint32_t);

void files_set_out_ext(char *);
void files_set_out_path(char *);

void files_extract(void);
void files_rewrite(void);

#endif // _FILES_H
