#include "actions.h"

extern int** grid;
extern int grid_size;

int* get_available_tiles() {
    int* available_tiles;
    available_tiles = (int*) malloc(sizeof(int));
    available_tiles[0] = 0;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (!grid[i][j]) {
                int* new_available_tiles;
                new_available_tiles = (int*) malloc((available_tiles[0]+2)*sizeof(int));
                new_available_tiles[0] = available_tiles[0]+1;
                for (int k = 1; k <= available_tiles[0]; k++)
                    new_available_tiles[k] = available_tiles[k];
                new_available_tiles[available_tiles[0]+1] = i*grid_size+j;
                free(available_tiles);
                available_tiles = new_available_tiles;
            }
        }
    }
    return available_tiles;
}

void perform_action(char action) {
    switch(action) {
        case 'h':
            perform_left();
            break;
        case 'j':
            perform_down();
            break;
        case 'k':
            perform_up();
            break;
        case 'l':
            perform_right();
            break;
        default:
            return;
    }
}

void perform_left() {
    int index = 0;
    for (int i = 0; i < grid_size; i++) { //for each row
        for (int j = 0; j < grid_size; j++) //for every item in the row
            if (grid[i][j] != 0) { //if the tile is occupied
                grid[i][index] = grid[i][j]; //then we move it to the left as much as we can
                index++;
            }
        for (int j = index; j < grid_size; j++)//and we fill the rest with 0's
            grid[i][j] = 0;
        for (int j = 0; j < index - 1; j++)//then we go through the row again
            if (grid[i][j] == grid[i][j+1]) {//to check for equal numbers
                grid[i][j] *= 2;//if we find one, we merge them
                index--;
                for (int k = j+1; k < index; k++)//and we push everything right of it one tile to the left
                    grid[i][k] = grid[i][k+1];
                grid[i][index] = 0;//and we get one more free tile
            }
        index = 0;
    }
}

void perform_right(){
    int index = grid_size-1;
    for (int i = 0; i < grid_size; i++) {
        for (int j = grid_size-1; j >= 0; j--)
            if (grid[i][j] != 0) {
                grid[i][index] = grid[i][j];
                index--;
            }
        for (int j = index; j >= 0; j--)
            grid[i][j] = 0;
        for (int j = grid_size-1; j > index + 1; j--)//then we go through the row again
            if (grid[i][j] == grid[i][j-1]) {//to check for equal numbers
                grid[i][j] *= 2;//if we find one, we merge them
                index++;
                for (int k = j-1; k > index; k--)//and we push everything left of it one tile to the right
                    grid[i][k] = grid[i][k-1];
                grid[i][index] = 0;//and we get one more free tile
            }
        index = grid_size-1;
    }
}

void perform_up(){
    int index = 0;
    for (int j = 0; j < grid_size; j++) {
        for (int i = 0; i < grid_size; i++)
            if (grid[i][j] != 0) {
                grid[index][j] = grid[i][j];
                index++;
            }
        for (int i = index; i < grid_size; i++)
            grid[i][j] = 0;
        for (int i = 0; i < index - 1; i++)//then we go through the column again
            if (grid[i][j] == grid[i+1][j]) {//to check for equal numbers
                grid[i][j] *= 2;//if we find one, we merge them
                index--;
                for (int k = i+1; k < index; k++)//and we push everything at the bottom of it one tile to the top
                    grid[k][j] = grid[k+1][j];
                grid[index][j] = 0;//and we get one more free tile
            }
        index = 0;
    }
}

void perform_down(){
    int index = grid_size-1;
    for (int j = 0; j < grid_size; j++) {
        for (int i = grid_size-1; i >= 0; i--)
            if (grid[i][j] != 0) {
                grid[index][j] = grid[i][j];
                index--;
            }
        for (int i = index; i >= 0; i--)
            grid[i][j] = 0;
        for (int i = grid_size-1; i > index + 1; i--)//then we go through the column again
            if (grid[i][j] == grid[i-1][j]) {//to check for equal numbers
                grid[i][j] *= 2;//if we find one, we merge them
                index++;
                for (int k = i-1; k > index; k--)//and we push everything at the top of it one tile to the bottom
                    grid[k][j] = grid[k-1][j];
                grid[index][j] = 0;//and we get one more free tile
            }
        index = grid_size-1;
    }
}

void place_new_random() {
    int* available_tiles;
    int random_index;
    available_tiles = get_available_tiles(grid);
    if (available_tiles[0]) {
        srand(time(NULL));
        random_index = (rand() % (available_tiles[0])) + 1;
        grid[available_tiles[random_index]/grid_size][available_tiles[random_index]%grid_size] = (rand()%10==9)?4:2;
    }
}
