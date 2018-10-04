#include "core.h"

int** grid;
int grid_size;

void initialize_grid() {
    int first_cell, second_cell;
    srand(time(NULL));
    first_cell = rand()%(grid_size*grid_size-1);
    second_cell = first_cell;
    while (second_cell == first_cell)
        second_cell = rand()%(grid_size*grid_size-1);
    grid[first_cell/grid_size][first_cell%grid_size] = 2;
    grid[second_cell/grid_size][second_cell%grid_size] = 2;
}

void print_grid (FILE* stream) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid[i][j]) {
                if (grid[i][j] < 100)
                    if (grid[i][j] < 10)
                        fprintf(stream, "  %d  ", grid[i][j]);
                    else
                        fprintf(stream, " %d  ", grid[i][j]);
                else
                    if (grid[i][j]<1000)
                        fprintf(stream, " %d ", grid[i][j]);
                    else
                        if (grid[i][j]<10000)
                            fprintf(stream, "%d ", grid[i][j]);
                        else
                            fprintf(stream, "%d", grid[i][j]);
            }
            else
                fprintf(stream, "  .  ");
        }
        fprintf(stream, "\n");
    }
}

char prompt_action (FILE* instream, FILE* outstream) {
    char choice = 'a';
    fputs("Pick a move ([hjkl])\n", outstream);
    while (!check_legal(choice)) {
        choice = getc(instream);
    }
    return choice;
}

void game(int limit, FILE* influx, FILE* outflux) {
    int game_over = 0, game_won = 0;
    char action;
    while (1) {
        print_grid(outflux);
        game_over = check_over();
        game_won = check_won(limit);
        if (game_over || game_won) break;
        action = prompt_action(influx, outflux);
        perform_action(action);
        place_new_random();
    }
    if (game_won)
        fprintf(outflux, "Congratulations, you won!\n");
    else if (game_over)
        fprintf(outflux, "Sucker, you lost!\n");
}

void deinitialize_grid() {
    for (int i = 0; i < grid_size; i++)
        free(grid[i]);
    free(grid);
    grid = NULL;
}

int main (int argc, char* argv[]) {
    int limit = (argc > 1)?atoi(argv[1]):DEFAULT_LIMIT;
    grid_size = (argc > 2)?atoi(argv[2]):DEFAULT_SIZE;
    if (limit < 1 || !check_power_of_2(limit) || grid_size < 1) {
        fprintf(stdout, "This is madness!\n");
        return EXIT_FAILURE;
    }
    grid = (int**) malloc (4*sizeof(int*));
    for (int i = 0; i < 4; i++) {
        grid[i] = (int*) malloc (4*sizeof(int));
        for (int j = 0; j < 4; j++)
            grid[i][j] = 0;
    }
    initialize_grid();
    game(limit, stdin, stdout);
    deinitialize_grid();
    return EXIT_SUCCESS;
}
