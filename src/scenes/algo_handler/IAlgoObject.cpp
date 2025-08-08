#include "IAlgoObject.hpp"

// here are implementations

void SwapAnimation::run_animation(
        IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "swap animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

void SwapAnimation::run_reverse_animation(
        IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "reverse swap animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

void SelectAnimation::run_animation(
        IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "select animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

void SelectAnimation::run_reverse_animation(
        IAlgoObject* first, IAlgoObject* second) {
    std::cout << "reverse select animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
    std::cout << "{" << std::endl;
    DeselectAnimation::run_animation(first, second);
    std::cout << "}" << std::endl;
}

void DeselectAnimation::run_animation(
        IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "deselect animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

void DeselectAnimation::run_reverse_animation(
        IAlgoObject* first, IAlgoObject* second) {
    std::cout << "reverse deselect animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
    std::cout << "{" << std::endl;
    SelectAnimation::run_animation(first, second);
    std::cout << "}" << std::endl;;
}

void CompareAnimation::run_animation(
        IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "compare animation: " << first->get_value() << ' '
        << second->get_value() << std::endl;
}

void CompareAnimation::run_reverse_animation(
        IAlgoObject* first, IAlgoObject* second) {
    if (first == second) {
        return;
    }
    std::cout << "reverse compare animation: " << first->get_value() << ' '
        << second->get_value() << std::endl; 
}

TestAlgoObject::TestAlgoObject(const int* value) : value(value) {}

TestAlgoObject::~TestAlgoObject() = default;
