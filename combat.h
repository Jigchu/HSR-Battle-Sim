#pragma once

enum effect_t {
    HEALING,
    SHIELDING,
    DAMAGE,
    NONE,
};

typedef enum effect_t effect_t;

typedef struct outcome {
    effect_t type;
    double amount;
    element_t element;
    void *additional_effects; // To change later
} outcome_t;

enum action_t{
    BASIC,
    SKILL,
    ULTIMATE,
    FOLLOW_UP,
};

typedef enum action_t action_t;

typedef struct action {
    char *name;
    uint8_t number_of_hits;
    action_t type;
    outcome_t * (*func) (character_core *);
} action;
