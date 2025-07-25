#pragma once

#include <memory>

#include <QApplication>

#include "Parser.hpp"

class IScene {
public:
    virtual void draw() const = 0;
};
