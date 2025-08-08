#include "AlgorithmHelpers.hpp"

BaseStepInfo::~BaseStepInfo() = default;

// some trivial implementation

void AlgoStepsInfo::step_forward() {
    if (current_step == steps_taken.end()) {
        return;
    }
    (*current_step)->run_animation_of_this_step();
    ++current_step;
}

void AlgoStepsInfo::step_back() {
    if (current_step == steps_taken.begin()) {
        return;
    }
    --current_step;
    (*current_step)->run_reverse_animation_of_this_step();
}

bool AlgoStepsInfo::is_at_the_last_step() {
    return current_step == steps_taken.end();
}
