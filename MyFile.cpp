#include<stdio.h>
#include"Str.h"
#include<stdlib.h>
#include<math.h>
#pragma warning(disable : 4996)

extern int cells_count;
extern bool saved;

int inline mem_reall(Cell** cells, int& all_mem);
int encrypt_cell(Cell* encrypted_cell, Cell* cell);
int desypher_cell(Cell* cell, Cell* encrypted_cell);

    int file_read(Cell** cells,int &cells_count, char* file_name, int& all_mem) {
        FILE* fp;

        fopen_s(&fp, file_name, "r");
        if (fp == NULL)
            return -1;
        int iencrypt;
        Cell encrypted_cell;
        if(fscanf(fp, "count: %d encrypted: %d\n", &cells_count, &iencrypt) != 2) return -1;
        bool encrypt = iencrypt;
        mem_reall(cells, all_mem);

        for (int i = 0; i < cells_count; i++) {
            if (fscanf(fp, "%d;%[^;];%[^;];%[^;];\n",
               &encrypted_cell.year, &encrypted_cell.song, &encrypted_cell.album, &encrypted_cell.artist) != 4) return-1;
            if (encrypt) {
                desypher_cell(&(*cells)[i], &encrypted_cell);         
            }
            else {
                memcpy(&(*cells)[i], &encrypted_cell,sizeof(Cell));
            }
        }
        fclose(fp);
        saved = true;
        return 0;
    }

    int file_write(Cell* cells, char* file_name, bool encrypt) {

        FILE* fp;
        fopen_s(&fp, file_name, "w");
        if (fp == NULL)
            return -1;

        Cell encrypted_cell;

        fprintf(fp, "count: %d encrypted: %d\n", cells_count, encrypt);

        for (int i = 0; i < cells_count; i++) {

            if (encrypt) {
                encrypt_cell(&encrypted_cell, &cells[i]);
            }
            else {
                memcpy(&encrypted_cell, &cells[i],sizeof(Cell));
            }
            fprintf(fp, "%hd;%s;%s;%s;\n", encrypted_cell.year, encrypted_cell.song, encrypted_cell.album, encrypted_cell.artist);
        }
        fclose(fp);
        saved = true;
        return 0;
    }

    int inline mem_reall(Cell** cells,int &all_mem) {

        if (all_mem < cells_count * sizeof(Cell)) {
            all_mem = (cells_count * sizeof(Cell)*2);

            Cell* new_cells = (Cell*)realloc(*cells, all_mem);

            if (new_cells != NULL)
                *cells = new_cells;
            else return -1;
        }
        return 0;
    }

    int encrypt_cell(Cell* encrypted_cell,Cell* cell) {
        memcpy(encrypted_cell, cell,sizeof(Cell));
        
        for (int k = 0; encrypted_cell->song[k] != 0; k++) {
            encrypted_cell->song[k] = (encrypted_cell->song[k] == -1) ? 32 : encrypted_cell->song[k]+1;
        }
        for (int k = 0; encrypted_cell->album[k] != 0; k++) {
            encrypted_cell->album[k] = (encrypted_cell->album[k] == -1) ? 32 : encrypted_cell->album[k]+1;
        }
        for (int k = 0; encrypted_cell->artist[k] != 0; k++) {
            encrypted_cell->artist[k] = (encrypted_cell->artist[k] == -1) ? 32 : encrypted_cell->artist[k]+1;
        }
        return 0;
    }

    int desypher_cell(Cell* cell, Cell* encrypted_cell) {
        memcpy(cell,encrypted_cell,sizeof(Cell));

        for (int k = 0; cell->song[k] != 0; k++) {
            if (cell->song[k] == 32) cell->song[k] = -1;
            else 
            cell->song[k]--;
        }
        for (int k = 0; cell->album[k] != 0; k++) {
            if (cell->album[k] == 32) cell->album[k] = -1;
            else 
            cell->album[k]--;
      
        }
        for (int k = 0; cell->artist[k] != 0; k++) {
            if (cell->artist[k] == 32) cell->artist[k] = -1;
            else 
            cell->artist[k]--;
        }
        return 0;
    }