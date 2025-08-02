#include "IAlgoObject.hpp"

// here are implementations

void SwapAnimation::run_swap_anim(IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "swap animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

void CompareAnimation::run_compare_anim(IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "compare animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

TestAlgoObject::TestAlgoObject(const int* value) : value(value) {}

TestAlgoObject::~TestAlgoObject() = default;
