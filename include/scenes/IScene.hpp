#pragma once

#include "Parser.hpp"
#include <QApplication>
#include <memory>

class IScene {
  public:
    virtual void draw() const = 0;

    virtual ~IScene() = default;
};
