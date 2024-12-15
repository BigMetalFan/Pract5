#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "Str.h"
#pragma warning(disable : 4996)

extern int t_max_song, t_max_album, t_max_artist, t_max_year;


extern int cells_count;
extern str filter;
extern bool saved;

int get_str_lenght(char* str) {
    int lenght;
    for (int k = 0; str[k] != 0; k++) {
        lenght = k + 1;
    }
    return lenght;
}

int get_str_lenght(int value) {
    int lenght;
    for (int k = 0; value > 0; k++) {
        value /= 10;
        lenght = k;
    }
    return lenght;
}




    int print_cell(const Cell* cells, int i) {

        printf("\n|%-2i|%*i|%-*s|%-*s|%-*s|\n", i + 1, t_max_year, cells[i].year, t_max_song, cells[i].song,
            t_max_album, cells[i].album, t_max_artist, cells[i].artist);
        return 0;
    }



    int print_tbl(Cell* cells, short size) {
        for (unsigned i = 0; i < cells_count; i++) {
            if((filter[0]!=0)&&!(str_in(filter, cells[i].song) || str_in(filter, cells[i].artist) || str_in(filter, cells[i].album))) continue;
            putchar(' ');
            for (int k = 0; k < t_max_song + t_max_album + t_max_artist + t_max_year+5; k++) {
                printf("_");
            }
            printf("\n");
            print_cell(cells, i);
        }
        return 0;
    }


    bool str_compare(const char* s1, const char* s2) {

            for (int i = 0; s1[i] != 0; i++) {
                if (s1[i] != s2[i]&& s1[i] != 0) 
                    return false;
            }
            return true;

    }


    int add(Cell** cells, int  &cells_count, int& all_mem) {

        int i = cells_count;
        
        if ((cells_count + 1) * sizeof(Cell) > all_mem) {

            all_mem *= 2;

            Cell* new_cells = (Cell*)realloc(*cells, all_mem);
               
            if (new_cells != NULL)
                *cells = new_cells;
        }

        cells_count++;

        puts("Введите год: ");
        if (!scanf("%d", &(*cells)[i].year)) return -1;
        putchar('\n');

        puts("Введите название песни: ");
        if (!scanf("\n%[^\n]", &(*cells)[i].song)) return -1;
        putchar('\n');

        puts("Введите название альбома: ");
        if (!scanf("\n%[^\n]", &(*cells)[i].album)) return -1;
        putchar('\n');

        puts("Введите название группы: ");
        if (!scanf("\n%[^\n]", &(*cells)[i].artist)) return -1;
        putchar('\n');

        saved = false;

        return 0;
    }

    bool cell_remove(Cell* cells, int ID, int &cells_count) {

        memset(&cells[ID], 0, sizeof(Cell));
            for (int i = ID; i < cells_count; i++) {
                memcpy(&cells[i], &cells[i + 1],sizeof(Cell));
            }
        
        cells_count--;
        saved = false;
        return 0;
    }

    int sort(Cell* cells, char back) {

        for (int i = 0; i < cells_count; i++) {
            bool flag = true;
            for (int j = 0; j < cells_count - (i + 1); j++) {
                if (cells[j].year * back > cells[j + 1].year * back) {
                    flag = false;
                    Cell temporary_cell;
                    if (back > 0) {
                        memcpy(&temporary_cell, &cells[j],sizeof(Cell));
                        memcpy(&cells[j], &cells[j + 1],sizeof(Cell));
                        memcpy(&cells[j + 1], &temporary_cell,sizeof(Cell));
                    }
                    else {
                        memcpy(&temporary_cell, &cells[j+1], sizeof(Cell));
                        memcpy(&cells[j+1], &cells[j], sizeof(Cell));
                        memcpy(&cells[j], &temporary_cell, sizeof(Cell));
                    }
                }
            }
            if (flag) {
                break;
            }
        }

        saved = false;
        return 0;
    }



    int get_field(Cell cell, int i, char* str) {
        switch (i) {
        case 1:strcpy(str, cell.song);
            break;
        case 2:strcpy(str, cell.album);
            break;
        case 3:strcpy(str, cell.artist);
            break;
        }
        return 0;
    }

    int sort_by_str(Cell* cells, char back, int ID) {

        for (int i = 0; i < cells_count; i++) {
            bool flag = true;
            for (int j = 0; j < cells_count - (i + 1); j++) {
                
                str str1, str2;
                get_field(cells[j], ID, str1);
                get_field(cells[j+1], ID, str2);
                int k = 0;
                while (toupper(str1[k]) == toupper(str2[k]) || str1[k] == 0 || str2[k] == 0) k++;
                
                if (toupper(str1[k]) * back > toupper(str2[k]) * back) {
                    flag = false;
                    Cell temporary_cell;
                    if (back > 0) {
                        memcpy(&temporary_cell, &cells[j],sizeof(Cell));
                        memcpy(&cells[j], &cells[j + 1], sizeof(Cell));
                        memcpy(&cells[j + 1], &temporary_cell, sizeof(Cell));
                    }
                    else {
                        memcpy(&temporary_cell, &cells[j + 1], sizeof(Cell));
                        memcpy(&cells[j + 1], &cells[j], sizeof(Cell));
                        memcpy(&cells[j], &temporary_cell, sizeof(Cell));
                    }
                }
            }
            if (flag) {
                break;
            }
        }

        saved = false;
        return 0;
    }

    int str_in(char* s1, char* s2) {

        int s1_lenght = 0, s2_lenght = 0;
        
        s1_lenght = get_str_lenght(s1);
        s2_lenght = get_str_lenght(s2);

        for (int i = 0; i <= s2_lenght - s1_lenght; i++) {

            if(str_compare(s1,&s2[i])) return 1;
        }
        return 0;
    }

    int change_cell(Cell* cells, int ID) {
        int c;

        while (true) {
            puts("1 - Изменить год\n2 - Изменить название песни\n3 - Изменить альбом\n4 - Изменить автора\n5 - Отмена");

                scanf("%*[^\n]\n"); // Очистка буфера
                scanf("%1d", &c);

                switch (c) {
                case 1: {
                    puts("Введите год: ");
                    if (!scanf("%d", &cells[ID].year)) puts("\nОшибка\n");
                    else puts("\nУспешно\n");
                    break;
                }
                case 2: {
                    puts("Введите название песни: ");
                    if (!scanf("%[^\n]", &cells[ID].song)) puts("\nОшибка\n");
                    else puts("\nУспешно\n");
                    break;
                }
                case 3: {
                    puts("Введите название альбома: ");
                    if (!scanf("%[^\n]", &cells[ID].album)) puts("\nшибка\n");
                    else puts("\nУспешно\n");
                    break;
                }
                case 4: {
                    puts("Введите название исполнителя: ");
                    if (!scanf("%[^\n]", &cells[ID].artist)) puts("\nОшибка\n");
                    else puts("\nУспешно\n");
                    break;
                }
                case 5:  return 1;
                default: puts("Ошибка\n");
                }
            }         
        return 0;
    }
