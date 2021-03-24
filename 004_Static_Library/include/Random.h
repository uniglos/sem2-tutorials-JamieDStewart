#pragma once
//\=====================================================================================
/// Class that implements a random number generator (linear congruential generator)
/// that uses the following rule:
///	                      seed = (a*seed + c) & m;
///	                      randomInt = seed & L;
/// More rules available here: https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
//\=====================================================================================
namespace Random
{
    /// Gets current seed
    int					GetSeed();
    /// Sets current seed
    void				SetSeed(const int& iSeed);
    /// Gets maximun allowed integer
    int					RandMax();

    /// Random integer number generator
    int					RandInt();
    int					RandRange(const int& iMin, const int& iMax);
    /// Random float number generator from 0.0f to 1.0f
    float				RandFloat();
    /// Random float number generator from interval [x0,x1]
    float				RandRange(const float& fX0, const float& fX1);
};