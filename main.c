#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "abilities.h"
#include "characters.h"
#include "combat.h"
#include "core_mechanics.h"

character_core *create_character(void);

int main(void) {
    printf("What do you want to do?\n");
    printf("1: Create Character\t2: Load Character\t3: Do an attack\n");
    
    char buffer[3]; // 3 to include the int newline and nul byte
    fgets(buffer, 3, stdin);
    int command = strtod(buffer, NULL);

    character_core *character;

    if (command == 1) {
        character = create_character();
        printf("Saving %s\n", character->name);
        int bytes_written = save_character_core(character);
        printf("%d Bytes Written\n", bytes_written);
    } else if (command == 2) {
        character = load_character_core();
        printf("Loaded %s\n", character->name);
        printf("%s's path is %s\n", character->name, path_to_str(character->path));
        printf("%s's element is %s\n", character->name, element_to_str(character->element));
        printf("%s's hp is %lf\n", character->name, character->stats[HP]);
        printf("%s's atk is %lf\n", character->name, character->stats[ATK]);
        printf("%s's def is %lf\n", character->name, character->stats[DEF]);
        printf("%s's spd is %lf\n", character->name, character->stats[SPD]);
    } else if (command == 3) {
        character = load_character_core();
        outcome_t *outcomes = DanHengBasic.func(character);
        if (outcomes == NULL) {
            return 1;
        }
        double base_dmg = 0;
        for (int i = 0; i < DanHengBasic.number_of_hits; i++) {
            printf("%s did %lf %s DMG\n", character->name, outcomes[i].amount, element_to_str(outcomes[i].element));
            base_dmg += outcomes[i].amount;
        }
        printf("TOTAL DMG: %lf\n", base_dmg);
    }

    free(character);

    return 0;
}

character_core *create_character(void) {
    char name_buffer[256];
    printf("Name: ");
    fgets(name_buffer, 256, stdin);
    name_buffer[strcspn(name_buffer, "\n")] = '\0';

    int name_length = strlen(name_buffer);
    char *name = malloc(sizeof(char) * (name_length+1));
    if (name == NULL) {
        return NULL;
    }
    strcpy(name, name_buffer);

    char buffer[20];
    printf("Path: ");
    fgets(buffer, 20, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    path_t path = parse_path(buffer);

    printf("Element: ");
    fgets(buffer, 20, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    element_t element = parse_element(buffer);
    
    printf("HP: ");
    fgets(buffer, 20, stdin);
    double hp = strtod(buffer, NULL);
    
    printf("ATK: ");
    fgets(buffer, 20, stdin);
    double atk = strtod(buffer, NULL);

    printf("DEF: ");
    fgets(buffer, 20, stdin);
    double def = strtod(buffer, NULL);

    printf("SPD: ");
    fgets(buffer, 20, stdin);
    double spd = strtod(buffer, NULL);

    printf("Max Energy: ");
    fgets(buffer, 20, stdin);
    double max_energy = strtod(buffer, NULL);

    base_stats stats;
    stats.hp = hp;
    stats.atk = atk;
    stats.def= def;
    stats.spd = spd;
    stats.max_energy = max_energy;

    return init_char_core(name, path, element, stats);
}