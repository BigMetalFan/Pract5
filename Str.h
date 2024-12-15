#pragma once
#include<string.h>

typedef char str[128];

struct Cell {
    str song;
    str album;
    str artist;
    int year;
};

int print_cell(const Cell* cells, int i);

int print_tbl(Cell* cells, short size);

bool str_compare(const char* s1,  const char* s2);

int file_read(Cell** cells, int& cells_count, char* file_name, int& all_mem);

int file_write(Cell* cells, char* file_name, bool encrypt);

int add(Cell** cells, int& cells_count, int& all_mem);

bool cell_remove(Cell* cells, int ID, int& cells_count);

int sort(Cell* cells, char back);

int str_in(char* s1,char* s2);

int change_cell(Cell* cells, int ID);

int sort_by_str(Cell* cells, char back, int ID);

int get_str_lenght(int value);

int get_str_lenght(char* str);