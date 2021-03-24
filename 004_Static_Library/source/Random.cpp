#include "Random.h"
static int rand_seed = 0xDEADBEEF;		//Default value for seed
//values set to glibc (used by GCC)
static const int rand_mod = 0x80000000;	//Set Rand Mod value 2^31
static const int rand_a = 1103515245;	//Set LCG A value
static const int rand_c = 12345;		//Set LCG C value
static const int rand_L = 0x3FFFFFFF;	//Set LCG L (or bitmask) value

int Random::GetSeed() 
{
	return rand_seed;
}

void Random::SetSeed(const int& a_seed)
{
	rand_seed = a_seed;
}

int Random::RandMax()
{
	return rand_L;
}

int Random::RandInt()
{
	rand_seed = (rand_seed * rand_a + rand_c) % rand_mod;	//calc seed value
	return rand_seed & rand_L;								//& with L to keep value in bit range.
}

int Random::RandRange(const int& min, const int& max)
{
	return RandInt() % max + min;
}

float Random::RandFloat()
{
	return static_cast<float>(RandInt()) / static_cast<float>(RandMax());
}

float Random::RandRange(const float& min, const float& max)
{
	return min + ((max - min) * RandFloat());
}