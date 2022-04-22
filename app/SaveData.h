//
// Created by kkeiper on 4/11/2022.
//

#ifndef OPEN_CAR2_SAVEDATA_H
#define OPEN_CAR2_SAVEDATA_H

struct Trophy {
    long animal = 0;
    long weapon;
    long phase;
    long height;
    long weight;
    long score;
    long date;
    long time;
    float scale[4];
    float range[4];
    long r1, r2, r3, r4;
};

struct HuntStats {
    long attempted;
    long succeeded;
    float path[4];
    float time[4];
};


struct SaveData {
    char name[128];
    long registryPosition;
    long credits;
    long rank;

    HuntStats previousHunt;
    HuntStats allHunts;

    Trophy trophies[24];

    // settings for the account
    long aggressivity;
    long density;
    long sensitivity;
    long resolution;
    long fong;
    long textures;
    long view_range;
    long shadows_3d;
    long mouse_sensitivity;
    long brightness;

    // keys
    long forward;
    long backward;
    long turn_up;
    long turn_down;
    long turn_left;
    long turn_right;
    long fire;
    long get_weapon;
    long step_left;
    long step_right;
    long strafe;
    long jump;
    long run;
    long crouch;
    long call;
    long change_call;
    long binoculars;

    // hunt settings
    long reverse_mouse;
    long cover_scent;
    long camouflage;
    long radar;
    long tranquilizer;
};

#endif //OPEN_CAR2_SAVEDATA_H
