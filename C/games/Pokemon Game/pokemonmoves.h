#ifndef POKEMONMOVES_H
#define POKEMONMOVES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

bool percentcheck(float percent){
    float random = (float)rand() / RAND_MAX;
    if(random <= percent){
        return true;
    }
    return false;
}

float attackcalculator(int attack, float critical_hit_multiplier, float accuracy,int defense);

// Fire Type Moves
void Flamethrower(pokemon *p);
void FireBlast(pokemon *p);
void Ember(pokemon *p);
void HeatWave(pokemon *p);
void FireSpin(pokemon *p);
void Inferno(pokemon *p);
void FlameCharge(pokemon *p);
void WillOWisp(pokemon *p);
void BlazeKick(pokemon *p);
void LavaPlume(pokemon *p);

// Water Type Moves
void HydroPump(pokemon *p);
void Surf(pokemon *p);
void WaterGun(pokemon *p);
void AquaTail(pokemon *p);
void BubbleBeam(pokemon *p);
void RainDance(pokemon *p);
void Waterfall(pokemon *p);
void Dive(pokemon *p);
void Whirlpool(pokemon *p);
void IceBeam(pokemon *p); // Also an Ice move

// Grass Type Moves
void SolarBeam(pokemon *p);
void RazorLeaf(pokemon *p);
void LeafStorm(pokemon *p);
void VineWhip(pokemon *p);
void GrassKnot(pokemon *p);
void GigaDrain(pokemon *p);
void PetalDance(pokemon *p);
void SeedBomb(pokemon *p);
void NaturePower(pokemon *p);
void Synthesis(pokemon *p);

// Electric Type Moves
void Thunderbolt(pokemon *p);
void ThunderWave(pokemon *p);
void Spark(pokemon *p);
void VoltTackle(pokemon *p);
void ChargeBeam(pokemon *p);
void ElectroBall(pokemon *p);
void WildCharge(pokemon *p);
void Discharge(pokemon *p);
void Thunder(pokemon *p);
void Magnet_Bomb(pokemon *p);

// Psychic Type Moves
void Psychic(pokemon *p);
void Psybeam(pokemon *p);
void FutureSight(pokemon *p);
void CalmMind(pokemon *p);
void Confusion(pokemon *p);
void Hypnosis(pokemon *p);
void DreamEater(pokemon *p);
void Telekinesis(pokemon *p);
void StoredPower(pokemon *p);
void PsychoCut(pokemon *p);

// Rock Type Moves
void RockSlide(pokemon *p);
void StoneEdge(pokemon *p);
void RockThrow(pokemon *p);
void SmackDown(pokemon *p);
void AncientPower(pokemon *p);
void StealthRock(pokemon *p);
void Head_Smash(pokemon *p);
void Power_Gem(pokemon *p);
void Rock_Polish(pokemon *p);
void Sandstorm(pokemon *p);

// Ground Type Moves
void Earthquake(pokemon *p);
void MudSlap(pokemon *p);
void Dig(pokemon *p);
void Fissure(pokemon *p);
void Sand_Tomb(pokemon *p);
void Bulldoze(pokemon *p);
void Mud_Bomb(pokemon *p);
void Bonemerang(pokemon *p);
void Earth_Power(pokemon *p);
void Stealth_Rock(pokemon *p); // Also a Rock move

// Ice Type Moves
void IceBeam(pokemon *p);
void Blizzard(pokemon *p);
void Frost_Breath(pokemon *p);
void Ice_Shard(pokemon *p);
void Hail(pokemon *p);
void Avalanche(pokemon *p);
void Ice_Punch(pokemon *p);
void Cryogonal(pokemon *p);
void Freeze_Dry(pokemon *p);
void Icicle_Crash(pokemon *p);

// Fairy Type Moves
void Moonblast(pokemon *p);
void Dazzling_Gleam(pokemon *p);
void Play_Rough(pokemon *p);
void Fairy_Wind(pokemon *p);
void Draining_Kiss(pokemon *p);
void Misty_Terrain(pokemon *p);
void Charm(pokemon *p);
void Sweet_Kiss(pokemon *p);
void Fairy_Lock(pokemon *p);
void Play_Rough(pokemon *p);

// Fighting Type Moves
void CloseCombat(pokemon *p);
void Karate_Chop(pokemon *p);
void Dynamic_Punch(pokemon *p);
void Low_Kick(pokemon *p);
void Drain_Punch(pokemon *p);
void Bulk_Up(pokemon *p);
void Focus_Punch(pokemon *p);
void High_Jump_Kick(pokemon *p);
void Cross_Chop(pokemon *p);
void Mach_Punch(pokemon *p);

// Dark Type Moves
void Bite(pokemon *p);
void DarkPulse(pokemon *p);
void Night_Slash(pokemon *p);
void Foul_Play(pokemon *p);
void Crunch(pokemon *p);
void Shadow_Ball(pokemon *p); // Also a Ghost move
void Pursuit(pokemon *p);
void Sucker_Punch(pokemon *p);
void Taunt(pokemon *p);
void Dark_Void(pokemon *p);

// Steel Type Moves
void Iron_Tail(pokemon *p);
void Steel_Wing(pokemon *p);
void Flash_Cannon(pokemon *p);
void Gyro_Ball(pokemon *p);
void Metal_Claw(pokemon *p);
void Magnet_Bomb(pokemon *p);
void Bullet_Punch(pokemon *p);
void Steel_Roller(pokemon *p);
void Iron_Head(pokemon *p);
void Heavy_Slam(pokemon *p);

// Dragon Type Moves
void Dragon_Claw(pokemon *p);
void Dragon_Breath(pokemon *p);
void Draco_Meteor(pokemon *p);
void Outrage(pokemon *p);
void Dragon_Dance(pokemon *p);
void Dragon_Pulse(pokemon *p);
void Dragon_Rush(pokemon * p);
void Dragon_Tail(pokemon *p);
void Hyper_Beam(pokemon *p); // Also a Normal move
void Twister(pokemon *p);

// Flying Type Moves
void Fly(pokemon *p);
void Hurricane(pokemon *p);
void Air_Slash(pokemon *p);
void Aerial_Ace(pokemon *p);
void Brave_Bird(pokemon *p);
void Roost(pokemon *p);
void Wing_Attack(pokemon *p);
void Sky_Attack(pokemon *p);
void Acrobatics(pokemon *p);
void Tailwind(pokemon *p);

// Ghost Type Moves
void Shadow_Ball(pokemon *p); // Also a Dark move
void Night_Shade(pokemon *p);
void Phantom_Force(pokemon *p);
void Shadow_Sneak(pokemon *p);
void Curse(pokemon *p);
void Spite(pokemon *p);
void Ominous_Wind(pokemon *p);
void Poltergeist(pokemon *p);
void Lick(pokemon *p);
void Destiny_Bond(pokemon *p);

// Bug Type Moves
void Bug_Buzz(pokemon *p);
void X_Scissor(pokemon *p);
void Signal_Beam(pokemon *p);
void U_Turn(pokemon *p);
void Leech_Life(pokemon *p);
void Pin_Missile(pokemon *p);
void Bug_Bite(pokemon *p);
void Fury_Cutter(pokemon *p);
void Struggle_Bug(pokemon *p);
void Silver_Wind(pokemon *p);

// Normal Type Moves
void Tackle(pokemon *p);
void Quick_Attack(pokemon *p);
void Hyper_Beam(pokemon *p); // Also a Dragon move
void Body_Slam(pokemon *p);
void Take_Down(pokemon *p);
void Double_Edge(pokemon *p);
void Last_Resort(pokemon *p);
void Giga_Impact(pokemon *p);
void Rollout(pokemon *p);
void Facade(pokemon *p);

// Poison Type Moves
void Poison_Sing(pokemon *p);
void Sludge_Bomb(pokemon *p);
void Toxic(pokemon *p);
void Acid(pokemon *p);
void Poison_Jab(pokemon *p);
void Venoshock(pokemon *p);
void Cross_Poison(pokemon *p);
void Gunk_Shot(pokemon *p);
void Acid_Spray(pokemon *p);
void Belch(pokemon *p);

// Unique Moves (not included in original code)
void Hydro_Cannon(pokemon *p); // Unique to Blastoise
void Frenzy_Plant(pokemon *p); // Unique to Venusaur
void Blast_Burn(pokemon *p);   // Unique to Charizard
void Sacred_Sword(pokemon *p);  // Unique to Keldeo
void Spacial_Rend(pokemon *p);   // Unique to Palkia
void Roar_of_Time(pokemon *p);   // Unique to Dialga
void Origin_Pulse(pokemon *p);    // Unique to Kyogre
void Precipice_Blades(pokemon *p); // Unique to Groudon
void Z_Move(pokemon *p);          // Generic placeholder for Z-Moves
void Fusion_Flare(pokemon *p);    // Unique to Reshiram
void Fusion_Blast(pokemon *p);    // Unique to Zekrom

#endif