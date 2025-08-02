#pragma once

 #include <iostream>

// interface for AlgoObjects
class IAlgoObject {
  public:
    virtual int get_value() = 0;

    virtual ~IAlgoObject() = default;
};

// swap animation class
class SwapAnimation {
  public:
    static void run_swap_anim(IAlgoObject* first, IAlgoObject* second); 
};

// compare animation class
class CompareAnimation {
  public:
    static void run_compare_anim(IAlgoObject* first, IAlgoObject* second);
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