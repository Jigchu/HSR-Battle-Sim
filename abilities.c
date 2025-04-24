#include "abilities/dan_heng.h"
#include "combat.h"

action DanHengBasic;

void init_abilities(void) {
    DanHengBasic.name = "Cloudlancer Art: North Wind";
    DanHengBasic.func = &dan_heng_basic;
    DanHengBasic.number_of_hits = 2;
    DanHengBasic.type = BASIC;

    return;
}