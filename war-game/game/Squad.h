#ifndef __JJC__SQUAD__H__
#define __JJC__SQUAD__H__

#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "../RenderHelp.h"
#include "ProjectileRep.h"
#include <stdlib.h>
#include "Tile.h"

// number of hits a single member can take before dying
#define START_MEMBER_HEALTH 3

class SquadMember {
private:
    const float __member_size = 0.2f; // assist with rendering

public:

    int health = START_MEMBER_HEALTH;

    SquadMember(void) {
        ;
    }

    SquadMember(int health) {
        this->health = health;
    }

    // render at some place between 0 and 1
    void render(SDL_Renderer* ren, float* p, Tile* tile, ColorPack& cp) {
        SDL_Rect r;

        // horizontal displacement
        r.x = Tile::tile_size * (tile->getX() + p[0] - (__member_size/2.0f));

        // vertical displacement
        r.y = Tile::tile_size * (tile->getY() + p[1] - (__member_size/2.0f));

        r.w = __member_size * Tile::tile_size;
        r.h = r.w;

        ColorPack tmp_color = ColorPack::scale(cp, ((float)health)/3.0f); // lower health = darker color
        Render::axisAlignedBox(ren, r, tmp_color);
    }

    SquadMember& operator=(const SquadMember& sm) {
        if(&sm == this)
            return *this;

        this->health = sm.health;
        return *this;
    }

};

class Squad {
private:
    std::vector<SquadMember> __members;
    int target_indices[5]; // at most 5

    // given in x/y coordinate pairs
    const float _1_member[2]   = { 0.5f,  0.5f };
    const float _2_members[4]  = { 0.25f, 0.5f,  0.75f, 0.5f };
    const float _3_members[6]  = { 0.5f,  0.33f, 0.30f, 0.7f,  0.70f, 0.7f };
    const float _4_members[8]  = { 0.25f, 0.25f, 0.75f, 0.25f, 0.25f, 0.75f, 0.75f, 0.75f };
    const float _5_members[10] = { 0.2f,  0.2f,  0.8f,  0.2f,  0.5f,  0.5f,  0.2f,  0.8f, 0.8f, 0.8f };

    // return index of dead member, -1 if none
    int hasDeadMember(void) {
        for(int i = 0; i < __members.size(); i++) {
            if(__members[i].health <= 0)
                return i;
        }
        return -1;
    }

public:

    bool addSquadMember(int health) {
        if(__members.size() >= 5)
            return false;
        __members.push_back(SquadMember(health));
        return true;
    }

    Squad(int squad_members) {
        for(int i = 0; i < squad_members; i++) {
            addSquadMember(START_MEMBER_HEALTH);
        }
    }

    Squad(void) {
        for(int i = 0; i < 5; i++)
            addSquadMember(START_MEMBER_HEALTH);
    }

    // number of squad members in this squad
    int size(void) { return __members.size(); }

    // this method is called for each squad in battle
    // supervisor function takes care of all external data manipulation
    void prepareFire(Squad& enemy_squad, Tile& enemy_tile, Tile& my_tile, std::vector<ProjectileRep>& prv, ColorPack& cp) {
        for(int i = 0; i < size(); i++) {
            int enemy_target_index = rand()%enemy_squad.size();
            prv.push_back(ProjectileRep(
                    getTargetLocation(&my_tile, rand()%size()),
                    enemy_squad.getTargetLocation(&enemy_tile, enemy_target_index),
                    2.00f,
                    cp
            ));
            target_indices[i] = enemy_target_index;
        }
    }

    // squad already knows how many members it has
    glm::vec2 getTargetLocation(Tile* tile, int index) {
        float x = tile->getX();
        float y = tile->getY();

        switch(__members.size()) {
            case 1:
                return glm::vec2(x+_1_member[0], y+_1_member[1]);
            case 2:
                return glm::vec2(x+_2_members[2*index], y+_2_members[2*index+1]);
            case 3:
                return glm::vec2(x+_3_members[2*index], y+_3_members[2*index+1]);
            case 4:
                return glm::vec2(x+_4_members[2*index], y+_4_members[2*index+1]);
            case 5:
                return glm::vec2(x+_5_members[2*index], y+_5_members[2*index+1]);
            default:
                std::cerr << "Unknown squad size: " << __members.size();
                return glm::vec2(0.0f, 0.0f);
        }
    }

    // after prepareFire, get targets for each
    int getTargetIndex(int i) {
        return target_indices[i];
    }

    // damage a specific target
    void applyDamage(int index, int damage) {
        __members[index].health -= damage;
    }

    void applySquadDamage(std::vector<int>& hits) {
        for(int i : hits) {
            __members[i].health--;
        }
        clean();
    }

    // take 1 health from random squad member
    void damageRandom(void) {
        int index = rand() % __members.size();
        __members[index].health--;
    }

    // remove dead squad members
    void clean(void) {
        int dead = -1;
        do {
            dead = hasDeadMember();

            if(dead >= 0) {
                // shift other members over
                for(int i = dead; i < __members.size()-1; i++) {
                    __members[i] = __members[i+1];
                }

                __members.pop_back();
            }

        } while(dead != -1);
    }

    void render(SDL_Renderer* ren, Tile* tile, ColorPack& cp) {
        switch(__members.size()) { // render changes based on how many members there are in a squad
            case 1:
                __members[0].render(ren, (float*)_1_member, tile, cp);
                break;
            case 2:
                for(int i = 0; i < 2; i++)
                    __members[i].render(ren, (float*)_2_members+(i*2), tile, cp);
                break;
            case 3:
                for(int i = 0; i < 3; i++)
                    __members[i].render(ren, (float*)_3_members+(i*2), tile, cp);
                break;
            case 4:
                for(int i = 0; i < 4; i++)
                    __members[i].render(ren, (float*)_4_members+(i*2), tile, cp);
                break;
            case 5:
                for(int i = 0; i < 5; i++)
                    __members[i].render(ren, (float*)_5_members+(i*2), tile, cp);
                break;
            default:
                std::cerr << "Too many squad members" << std::endl;
                break;
        }
    }



    static void PrepSkirmish(Squad& s1, Squad& s2, Tile& t1, Tile& t2, ColorPack& c1, ColorPack& c2, std::vector<ProjectileRep>& prv) {
        prv.clear();

        // squad 1 prepares to fire on squad 2
        s1.prepareFire(s2, t2, t1, prv, c1);

        // squad 2 prepares to fire on squad 1
        s2.prepareFire(s1, t1, t2, prv, c2);

        // both squads are now prepped

    }

};

#undef START_MEMBER_HEALTH

#endif // __JJC__SQUAD__H__
