#include "checks.h"

extern int** grid;
extern int grid_size;

int check_legal(char action) {
    switch(action) {
        case 'h':
            check_legal_left();
            break;
        case 'j':
            check_legal_down();
            break;
        case 'k':
            check_legal_up();
            break;
        case 'l':
            check_legal_right();
            break;
        default:
            return 0;
    }
}

int check_legal_left() {
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (!grid[i][j])
                for (int k = j+1; k < grid_size; k++)
                    if (grid[i][k]) return 1;
            else if (j<grid_size-1 && grid[i][j] == grid[i][j+1]) return 1;
    return 0;
}

int check_legal_right() {
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (!grid[i][j])
                for (int k = 0; k < j; k++)
                    if (grid[i][k]) return 1;
            else if (j<grid_size-1 && grid[i][j] == grid[i][j+1]) return 1;
    return 0;
}

int check_legal_up() {
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (!grid[i][j])
                for (int k = i+1; k < grid_size; k++)
                    if (grid[k][j]) return 1;
            else if (i<grid_size-1 && grid[i][j] == grid[i+1][j]) return 1;
    return 0;
}

int check_legal_down() {
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (!grid[i][j])
                for (int k = 0; k < i; k++)
                    if (grid[k][j]) return 1;
            else if (i<grid_size-1 && grid[i][j] == grid[i+1][j]) return 1;
    return 0;
}

int check_over() {
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (!grid[i][j] || (j < grid_size-1 && grid[i][j] == grid[i][j+1]) || (i < grid_size-1 && grid[i][j] == grid[i+1][j])) return 0;
    return 1;
}

int check_power_of_2(int limit) {
    int log2 = -1;
    for (;!(limit&0x1);limit>>=1)
        log2++;
    return !(limit >> 1 || log2 > grid_size*grid_size);
}

int check_won(int limit) {
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            if (grid[i][j] == limit) return 1;
    return 0;
}
