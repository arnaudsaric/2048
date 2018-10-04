
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "checks.h"
#include "config.h"
#include "actions.h"

void deinitialize_grid();
void game(int limit, FILE* influx, FILE* outflux);
void initialize_grid();
void print_grid (FILE* stream);
char prompt_action (FILE* instream, FILE* outstream);
int main (int argc, char* argv[]);
