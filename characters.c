#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "characters.h"

character_core *core_create(char *name, path_t path, element_t element, base_stats stats) {
    character_core *character = malloc(sizeof(character_core));
    if (character == NULL) {
        return character;
    }

    int name_length = strnlen(name, 256);
    if (name_length == 256) {
        free(character);
        return NULL;
    }
    character->name = malloc(sizeof(char) * (name_length+1));
    strncpy(character->name, name, name_length);

    character->level = 80;
    character->path = path;
    character->element = element;

    for (int i = 0; i < number_of_stats; i++) {
        character->stats[i] = 0;
    }

    for (int i = 0; i < number_of_elements; i++) {
        character->dmg_boosts[i] = character->res_boosts[i] = 0;
    }

    character->stats[HP] = stats.hp;
    character->stats[ATK] = stats.atk;
    character->stats[DEF] = stats.def;
    character->stats[SPD] = stats.spd;
    character->stats[MAX_ENERGY] = stats.max_energy;
    character->stats[CRIT_RATE] = 5;
    character->stats[CRIT_DMG] = 50;
    character->stats[ENERGY_REGENERATION_RATE] = 100;

    return character;
}

void core_destroy(character_core *character) {
    free(character->name);
    free(character);

    return;
}

// Saves to a file called CharacterCoreInfo.dat and returns the number of bytes written for success or 0 for failure
int save_core(character_core *character) {
    FILE *char_core_file = fopen("CharacterCoreInfo.dat", "wb");
    if (char_core_file == NULL) {
        return 0;
    }

    uint8_t name_length = strlen(character->name);
    
    int items_written;
    int total_bytes_written = 0;

    items_written = fwrite(&name_length, sizeof(uint8_t), 1, char_core_file);
    if (items_written != 1) {
        fclose(char_core_file);
        return 0;
    }
    total_bytes_written += items_written * sizeof(uint8_t);

    items_written = fwrite(character->name, sizeof(char), name_length+1, char_core_file);
    total_bytes_written += items_written * sizeof(char);
    if (items_written != name_length+1) {
        fclose(char_core_file);
        return 0;
    }

    items_written = fwrite(&character->level, sizeof(uint8_t), 1, char_core_file);
    total_bytes_written += items_written * sizeof(uint8_t);
    if (items_written != 1) {
        fclose(char_core_file);
        return 0;
    }

    items_written = fwrite(&character->path, sizeof(path_t), 1, char_core_file);
    total_bytes_written += items_written * sizeof(path_t);
    if (items_written != 1) {
        fclose(char_core_file);
        return 0;
    }

    items_written = fwrite(&character->element, sizeof(element_t), 1, char_core_file);
    total_bytes_written += items_written * sizeof(element_t);
    if (items_written != 1) {
        fclose(char_core_file);
        return 0;
    }

    items_written = fwrite(character->stats, sizeof(double), number_of_stats, char_core_file);
    total_bytes_written += items_written * sizeof(double);
    if (items_written != number_of_stats) {
        fclose(char_core_file);
        return 0;
    }

    items_written = fwrite(character->dmg_boosts, sizeof(double), number_of_elements, char_core_file);
    total_bytes_written += items_written * sizeof(double);
    if (items_written != number_of_elements) {
        fclose(char_core_file);
        return 0;
    }

    items_written = fwrite(character->res_boosts, sizeof(double), number_of_elements, char_core_file);
    total_bytes_written += items_written * sizeof(double);
    if (items_written != number_of_elements) {
        fclose(char_core_file);
        return 0;
    }

    fclose(char_core_file);

    return total_bytes_written;
}

character_core *load_core(void) {
    character_core *character = malloc(sizeof(character_core));
    if (character == NULL) {
        return NULL;
    }

    FILE *char_core_file = fopen("CharacterCoreInfo.dat", "rb");
    if (char_core_file == NULL) {
        free(character);
        return NULL;
    }

    uint8_t name_length;
    if (fread(&name_length, sizeof(uint8_t), 1, char_core_file) != 1) {
        free(character);
        fclose(char_core_file);
        return NULL;
    }

    character->name = malloc(sizeof(char) * (name_length+1));
    if (character->name == NULL) {
        free(character);
        fclose(char_core_file);
        return NULL;
    }
    if (fread(character->name, sizeof(char), name_length+1, char_core_file) != (name_length+1)) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    if (fread(&character->level, sizeof(uint8_t), 1, char_core_file) != 1) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    if (fread(&character->path, sizeof(path_t), 1, char_core_file) != 1) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    if (fread(&character->element, sizeof(element_t), 1, char_core_file) != 1) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    if (fread(character->stats, sizeof(double), number_of_stats, char_core_file) != number_of_stats) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    if (fread(character->dmg_boosts, sizeof(double), number_of_elements, char_core_file) != number_of_elements) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    if (fread(character->res_boosts, sizeof(double), number_of_elements, char_core_file) != number_of_elements) {
        core_destroy(character);
        fclose(char_core_file);
        return NULL;
    }

    return character;
}