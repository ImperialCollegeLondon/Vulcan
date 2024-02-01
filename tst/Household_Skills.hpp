#ifndef HOUSEHOLD_SKILLS_HPP
#define HOUSEHOLD_SKILLS_HPP

#include <vector>

class Household_Skills{
    public:

    // Constructor:
    Household_Skills();

    private:
    double initial_skill;
    double initial_productivity;
    double productivity_factor;
    double skill_volatility;
    double time_step;
    double days;
};

#endif
