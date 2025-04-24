#pragma once

#include <stdint.h>

enum path {
    NO_PATH = -1,
    DESTRUCTION = 0,
	HUNT = 1,
	ERUDITION = 2,
	HARMONY = 3,
	NIHILITY = 4,
    PRESERVATION = 5,
	ABUNDANCE = 6,
	REMEMBRANCE = 7,
    number_of_paths = 8,
};

typedef int8_t path_t;

enum element {
    NO_ELEMENT = -1,
    PHYSICAL = 0,
	FIRE = 1,
	ICE = 2,
	LIGHTNING = 3,
	WIND = 4,
	QUANTUM = 5,
	IMAGINARY = 6,
    number_of_elements = 7,
};

typedef int8_t element_t;

enum stats_t {
    HP = 0,
    ATK = 1,
    DEF = 2,
    SPD = 3,
    CRIT_RATE = 4,
    CRIT_DMG = 5,
    BREAK_EFFECT = 6,
    OUTGOING_HEALING_BONUS = 7,
    MAX_ENERGY = 8,
    ENERGY_REGENERATION_RATE = 9,
    EFFECT_HIT_RATEE = 10,
    EFFECT_RES = 11,
    number_of_stats = 12,
};

path_t str_to_path(char *in);
char *path_to_str(path_t path);

element_t str_to_element(char *in);
char *element_to_str(element_t element);