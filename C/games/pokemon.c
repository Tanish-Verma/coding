#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_MOVES 4

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
    char *type1;
    char *type2;
    int health;
    Status  status;
    bool Mega_evolve;
    bool  is_fainted;
    move *Moves;
}pokemon;

int main(){
    pokemon 

    return 0;
}