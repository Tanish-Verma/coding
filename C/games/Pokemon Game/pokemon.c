#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_MOVES 4
typedef enum pokemon_type {
    NULL_TYPE = 0,
    NORMAL = 1,
    FIGHTING = 2,
    FLYING = 3,
    POISON = 4,
    GROUND = 5,
    ROCK = 6,
    BUG = 7,
    GHOST = 8,
    STEEL = 9,
    FIRE = 10,
    WATER = 11,
    GRASS = 12,
    ELECTRIC = 13,
    PSYCHIC = 14,
    ICE = 15,
    DRAGON = 16,
    DARK = 17,
    FAIRY = 18, // Custom type for demonstration
    // Add any additional types here as needed
} PokemonType;

typedef struct moves{
    void (*move1)(struct pokemon);
    void (*move2)(struct pokemon);
    void (*move3)(struct pokemon);
    void (*move4)(struct pokemon);
}move;

typedef enum status_effect{
    burn=1,
    paralysis=2,
    poison=3,
    sleep=4,
    freeze=5,
}Status;

typedef struct pokemon{
    PokemonType type1;
    PokemonType type2;
    int health;
    Status  status;
    int counter;
    bool Mega_evolve;
    bool  is_fainted;
    float accuracy;
    float critical_hit_rate;
    float critical_hit_multiplier;
    float attack;
    float defense;
}pokemon;
int main(){
    // pokemon 

    return 0;
}