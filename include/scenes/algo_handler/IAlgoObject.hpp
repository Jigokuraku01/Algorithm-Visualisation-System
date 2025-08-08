#pragma once

 #include <iostream>

// interface for AlgoObjects
class IAlgoObject {
  public:
    virtual int get_value() = 0;

    virtual ~IAlgoObject() = default;
};

// animation concept
template <typename Anim>
concept Animation = requires(IAlgoObject* first, IAlgoObject* second) {
    { Anim::run_animation(first, second) };
    { Anim::run_reverse_animation(first, second) };
};

// swap animation class
class SwapAnimation {
  public:
    static void run_animation(IAlgoObject* first, IAlgoObject* second);

    static void run_reverse_animation(IAlgoObject* first, IAlgoObject* second);
};

// select animation class
class SelectAnimation {
  public:
    static void run_animation(IAlgoObject* first, IAlgoObject* second);

    static void run_reverse_animation(IAlgoObject* first, IAlgoObject* second);
};

// deselect animation class
class DeselectAnimation {
  public:
    static void run_animation(IAlgoObject* first, IAlgoObject* second);

    static void run_reverse_animation(IAlgoObject* first, IAlgoObject* second);
};

// compare animation class
class CompareAnimation {
  public:
    static void run_animation(IAlgoObject* first, IAlgoObject* second);

    static void run_reverse_animation(IAlgoObject* first, IAlgoObject* second);
};

// reverse compare animation class
class ReverseCompareAnimation {
  public:
    static void run_animation(IAlgoObject* first, IAlgoObject* second);

    static void run_reverse_animation(IAlgoObject* first, IAlgoObject* second);
};

// AlgoObject for example of algorithm work
class TestAlgoObject : public IAlgoObject {
  public:
    explicit TestAlgoObject(const int* value);

    int get_value() override {
        return *value;
    }

    ~TestAlgoObject() override;
  private:
    const int* value;
};
