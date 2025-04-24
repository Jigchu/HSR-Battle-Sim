#pragma once

#include "core_mechanics.h"

typedef struct character_core {
    char *name;
    uint8_t level;
    path_t path;
    element_t element;
    double stats[number_of_stats];
    double dmg_boosts[number_of_elements];
    double res_boosts[number_of_elements];
} character_core;

typedef struct base_stats {
    double hp;
    double atk;
    double def;
    double spd;
    double max_energy;
} base_stats;

character_core *core_create(char *name, path_t path, element_t element, base_stats stats);
void core_destroy(character_core *character);

int save_core(character_core *character);
character_core *load_core(void);