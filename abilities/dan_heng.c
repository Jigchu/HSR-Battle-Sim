#include "abilities/dan_heng.h"
#include "characters.h"
#include "combat.h"
#include "core_mechanics.h"

outcome_t *dan_heng_basic(character_core *character) {
    outcome_t *outcomes = malloc(sizeof(outcome_t) * 2);
    if (outcomes == NULL) {
        return NULL;
    }

    double base_dmg = character->stats[ATK] * 1.0;
    double hit_split[2] = {0.45, 0.55};

    for (int i = 0; i < 2; i++) {
        outcomes[i].type = DAMAGE;
        outcomes[i].amount = base_dmg * hit_split[i];
        outcomes[i].element = WIND;
        outcomes[i].additional_effects = NULL;
    }

    return outcomes;
}