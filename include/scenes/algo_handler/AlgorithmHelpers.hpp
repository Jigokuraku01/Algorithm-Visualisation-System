#pragma once

#include <functional>
#include <deque>

#include "IAlgoObject.hpp"

// algorithm concept
template <typename Algo>
concept Algorithm = requires(Algo algorithm) {
    { algorithm.algorithm() };
};

// abstract base step info class (for type erasure)
class BaseStepInfo {
  public:
    // method for run main animation
    virtual void run_animation_of_this_step() = 0;

    // method for run reverse animation
    virtual void run_reverse_animation_of_this_step() = 0;

    virtual ~BaseStepInfo();
};

template <Animation AnimType>
class DerivedStepInfo : public BaseStepInfo {
  public:
    // main constructor
    DerivedStepInfo(IAlgoObject* first, IAlgoObject* second) 
        : first_arg(first), second_arg(second) {}

    // some trivial methods

    void run_animation_of_this_step() override {
        AnimType::run_animation(first_arg, second_arg);
    }

    void run_reverse_animation_of_this_step() override {
        AnimType::run_reverse_animation(first_arg, second_arg);
    }

    ~DerivedStepInfo() override = default;

  private:
    IAlgoObject* first_arg;
    IAlgoObject* second_arg;
};

class AlgoStepsInfo {
  public:

    // method for step forward algorithm
    void step_forward();


    // method for step forward algorithm
    void step_back();

    // method that check is current step last
    bool is_at_the_last_step();
    
    // method that handle new step and step forward
    // (you can handle step if current step is last)
    template <Animation AnimType>
    void handle_new_step(IAlgoObject* first, IAlgoObject* second) {
        if (is_at_the_last_step()) {
          steps_taken.push_back(new DerivedStepInfo<AnimType>(first, second));
          step_forward();
        }
    }

  private:
    // deque needs to prevent iterators for being invalidated
    std::deque<BaseStepInfo*> steps_taken;
    // current step is iterator
    decltype(steps_taken)::iterator current_step = steps_taken.end();
};
