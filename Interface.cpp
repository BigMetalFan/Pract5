#include <stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<windows.h>
#include"str.h"
#pragma warning(disable : 4996)



enum Inp {CLEAR, OPEN = 1, F_CHANGE,  EXIT, PRT, PRT_TABLE, SAVE, ADD,CHANGE,REMOVE, SORT, STAT,FILTER, Debug};  // команды для взаимодеймтвия с программой

int t_max_song, t_max_album, t_max_artist, t_max_year = 4;
//str commands[] = {"open\0", "close\0", "exit\0","print\0","print_table\0","не ждали?\0" };

int cells_count = 0;
str file_name = "Baza.txt";
str filter = "";

bool saved = true;


int get_max(Cell* cell,int &t_max_song,int &t_max_album,int &t_max_artist,int &t_max_year);
//bool str_compare(const char *s1, int s1_size, const char *s2, int s2_size);

void draw_menu();       //Функции работы с интерфейсом
void ui_open_file();
void ui_save();
void ui_print();
void ui_print_table();
void ui_add();
void ui_remove();
void ui_sort();
void ui_stat();
void ui_debug();
void ui_change_file(char* file_name);
void ui_change_fillter();
void ui_change();
bool ui_exit();
void ui_clear();


int all_mem = 5 * sizeof(Cell);


Cell* cells = (Cell*)malloc(all_mem);


int main(int argc, char* argv[])
{
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);

    draw_menu();

    if (argc == 2) {
        strcpy(file_name, argv[1]);
    }

    while (true)
    {
        Inp inp = (Inp)0;
        fflush(stdin);
        scanf_s("\n%d", &inp);
        
        
            switch (inp)
            {
            case OPEN: ui_open_file();
                break;
            case SAVE: ui_save();
                break;
            case F_CHANGE:ui_change_file(file_name);
                break;
            case PRT: ui_print();
                break;
            case PRT_TABLE: ui_print_table();
                break;
            case ADD:ui_add();
                break;
            case CHANGE:ui_change();
                break;
            case REMOVE:ui_remove();
                break;
            case SORT:ui_sort();
                break;
            case STAT:ui_stat();
                break;
            case FILTER:ui_change_fillter();
                break;
            case CLEAR: ui_clear();
                break;
            case Debug:ui_debug();
                break;
            default:  printf("Ошибка ввода\n");
                break;
            case EXIT:if(ui_exit()) return 0;
            }
            fflush(stdin);
            scanf("%*[^\n]\n"); // Очистка буфера
            
        
    }
    
    return 0;
}


int get_max(Cell* cell, int& t_max_song, int& t_max_album, int& t_max_artist, int& t_max_year) {

    t_max_song = 0;
    t_max_album = 0;
    t_max_artist = 0;
    t_max_year = 0;

    for (int i = 0; i < cells_count;i++) {

        int max_song,max_artist, max_album , max_year;

        max_year = get_str_lenght(cell[i].year);
        max_song = get_str_lenght(cell[i].song);
        max_album = get_str_lenght(cell[i].album);
        max_artist = get_str_lenght(cell[i].artist);

        if (max_year > t_max_year) t_max_year = max_year;
        if (max_song > t_max_song) t_max_song = max_song;
        if (max_album > t_max_album) t_max_album = max_album;
        if (max_artist > t_max_artist) t_max_artist = max_artist;
    }

    return 0;
}

void draw_menu() {
    printf("%2d - Очистить консоль \n%2d - Открыть файл \n%2d - Изменить файл \n%2d - Завершить работу\n%2d - Вывести строку\n%2d - Вывести таблицу\n%2d - Сохранить\\
        \n%2d - Добавить строку\n%2d - Изменить строку\n%2d - Удалить строку\n%2d - Отсортировать\n%2d - Вывод статистики\n%2d - Отфильтровать\n%2d - debug\n", 
        CLEAR, OPEN, F_CHANGE, EXIT, PRT, PRT_TABLE, SAVE, ADD, CHANGE, REMOVE, SORT, STAT, FILTER, Debug);
    printf("Файл: %s\n", file_name);
    if (filter[0] == 0) {
        puts("Фильтрация выключена\n");
    }
    else printf("Фильтр: %s\n", filter);
}

void ui_open_file() {
    system("cls");
    draw_menu();
    if (file_read(&cells, cells_count, file_name, all_mem) == 0)
        puts("Успешно. \n");
    else {
        puts("Не удалось открыть файл."); return;
    }
    get_max(cells, t_max_song, t_max_album, t_max_artist, t_max_year);
}
void ui_change_file(char* file_name) {
    puts("Введите имя файла");
    scanf("%s", file_name);
    
    system("cls");
    draw_menu();
    
}

void ui_save() {
    int c;
    puts("1 - Зашифровать\n2 - Не шифровать\n");
    scanf("%d", &c);
    system("cls");
    draw_menu();
    switch(c) {
    case 1: {
        if (file_write(cells, file_name,true) == 0)
            puts("Успешно. \n");
        else puts("Не удалось открыть файл.");
        break;
        }
    case 2: {
        if (file_write(cells, file_name, false) == 0)
            puts("Успешно. \n");
        else puts("Не удалось открыть файл.");
        break;
    }
    default: puts("Ошибка\n");
        break;
    }


}


void ui_print() {

    system("cls");
    draw_menu();

    if (!cells_count) {
        printf("Сначала откройте файл или добавьте строку.\a\n");
        return;
    }

    unsigned i;
    printf("Введите номер струкитуры для вывода: \a");
    scanf_s("%i", &i);
    putchar('\n');


    if (i >= 0 && i <= cells_count) {
        i--;                                //Для раблоты с индексами
        print_cell(cells, i);
    }
    else printf("Выход за пределы\n");
}

void ui_print_table() {
    system("cls");
    draw_menu();
    if (!cells_count) {
        printf("Сначала откройте файл или добавьте строку.\a\n");
        return;
    }
    get_max(cells, t_max_song, t_max_album, t_max_artist, t_max_year);
    print_tbl(cells, sizeof(cells));
}

void ui_add() {
    if (add(&cells, cells_count, all_mem) == -1) {
        printf("Ошибка ввода.\n");
        if (cells_count) cell_remove(cells, cells_count - 1, cells_count);
        return;
    }
    fflush(stdin);
}

void ui_remove() {
    int i;
    printf("Введите номер структуры для удаления:\a ");
    scanf_s("%d", &i);
    putchar('\n');
    if (i > 0 && i <= cells_count) i--;
    else {
        printf("Неверный номер\n");
        return;
    }
    cell_remove(cells,i,cells_count);
    printf("Успешно\n");
}

void ui_sort() {

    if (!cells_count) {
        printf("Сначала откройте файл или добавьте строку.\a\n");
        return;
    }

    int sort_inp, sort_by;

    scanf("%*[^\n]\n"); // Очистка буфера
    printf("1 - сортировка по году\n2 - сортировка по названию\n3 - сортровка по альбому\n4 - сортировка по исполнтьелю\n");
    scanf_s("\n%d", &sort_by);
    if (sort_by < 1 || sort_by>4) {
        system("cls");
        draw_menu();
        puts("Ощибка ввода.");
        return;
    }

    printf("%d - Прямая сортировка\n%d - Обратная сортировка\n%d - Отмена\n", 1, 2, 3);
    scanf_s("\n%d", &sort_inp);
    system("cls");
    draw_menu();
    if (sort_by == 1) {
        switch (sort_inp) {
        case 1: sort(cells, 1);
            break;
        case 2: sort(cells, -1);
            break;
        case 3: system("cls");  draw_menu();
            return;
        default: printf("Ошибка ввода");

        }
    }
    else {
        switch (sort_inp) {
        case 1: sort_by_str(cells, 1, sort_by-1);
            break;
        case 2: sort_by_str(cells, -1, sort_by-1);
            break;
        case 3: system("cls");  draw_menu();
            return;
        default: printf("Ошибка ввода");
        }
        system("cls");
        draw_menu();


    }
}

void ui_debug() {
    printf("Столбцы %d %d %d %d\n c_count %d\n mem_exp %d\n all_mem %d\n", t_max_song, t_max_album, 
        t_max_artist, t_max_year, cells_count,sizeof(Cell), all_mem);
    printf("%c %d %c %d\n", 'я', 'я', 'я' + 1, ' ');
}

int stat(Cell* cells) {

    if (cells_count == 0) return-1;
    struct artist {
        str name;
        int songs;
    };
    artist* artists = (artist*)malloc(0);

    Cell* local_cells = (Cell*)malloc(sizeof(Cell)*cells_count);  

    int average_year = 0, artists_count = 0, local_cells_count = cells_count;

    for(int i = 0; i < cells_count; i++) {
        memcpy(&local_cells[i], &cells[i],sizeof(Cell));   // Копирование массива структур в промежуточный массив
        average_year  += local_cells[i].year;
    }

    while (local_cells_count) {
        
        artists = (artist*)realloc(artists, (sizeof(artist) * (artists_count + 1)));

        strcpy(artists[artists_count].name, local_cells[0].artist);
        artists[artists_count].songs = 0;

        for (int i = 0; i < local_cells_count; i++) {
            if(str_compare(artists[artists_count].name, local_cells[i].artist)){
                artists[artists_count].songs++;
                cell_remove(local_cells, i, local_cells_count);
                i--;
            }
        }

        artists_count++;

    }

    average_year /= cells_count;

    printf("Средний год: %d\n", average_year);

    for (int i = 0; i < artists_count; i++) {
        int percent = (((double)artists[i].songs * 100.) / (double)(cells_count));
        printf("%s   %d %%\n", artists[i].name, percent);
    }

    free(local_cells);
    free(artists);

    return 0;
}

void ui_stat() {
    if (!cells_count) {
        printf("Сначала откройте файл или добавьте строку.\a\n");
        return;
    }
    stat(cells);
}

void ui_change_fillter() {
    int i;
    printf("1 - Изменить фильтр\n2 - Отключить фильтр\n");
    if (scanf("%d", &i) == 0 || i < 1 || i >2) {
        printf("Ошибка\n");
        return;
    }
    if (i == 1) {
        puts("Введите фильтр: ");
        scanf("%s", filter);
    }
    else filter[0] = 0;
    system("cls");
    draw_menu();

}

bool ui_exit() {

    if (saved) {
        free(cells);
        return true;
    }
    puts("Изменения не были сохранены, вы уверены, что хотите завершить работу? Y/N\n");
    char answ;
    scanf("%*[^\n]\n");
    while (true) {
        scanf("%c", &answ);
        switch (toupper(answ)) {
        case 'Y':return true;
        case 'N': return false;
        default:puts("Введите Y/N\n");
        }
    }
}

void ui_change() {

    int i;
    puts("Введите номер строки: ");
    putchar('\n');
    scanf("%d", &i);
    i--;
    if (i<0 || i > cells_count) {
        puts("Ошибка");
    }
    change_cell(cells, i);
    system("cls");
    draw_menu();
}

void ui_clear() {
    system("cls");
    draw_menu();
}