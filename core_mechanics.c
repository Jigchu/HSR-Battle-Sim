#include <stdlib.h>

#include "core_mechanics.h"

static const char *PATHS[number_of_paths] = {
    "Destruction", "Hunt", "Erudition", "Harmony",
    "Nihility", "Preservation", "Abundance", "Remembrance",
};

static const char *ELEMENTS[number_of_elements] = {
    "Physical", "Fire", "Ice", "Lightning",
    "Wind", "Quantum", "Imaginary",
};

path_t str_to_path(char *in) {
    for (uint8_t i = 0; i < number_of_paths; i++) {
        if (strcasecmp(in, PATHS[i]) == 0) {
            return i;
        }
    }

    return NO_PATH;
}

char *path_to_str(path_t path) {
    return PATHS[path];
}

element_t str_to_element(char *in) {
    for (uint8_t i = 0; i < number_of_elements; i++) {
        if (strcasecmp(in, ELEMENTS[i]) == 0) {
            return i;
        }
    }
    
    return NO_ELEMENT;
}

char *element_to_str(element_t element) {
    return ELEMENTS[element];
}