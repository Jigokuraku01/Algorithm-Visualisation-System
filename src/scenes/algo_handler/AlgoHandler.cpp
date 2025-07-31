#include "AlgoHandler.hpp"

AlgoManager::BaseAlgoHandler::BaseAlgoHandler(QWidget* window) 
    : window(window) {
}

AlgoManager::BaseAlgoHandler::~BaseAlgoHandler() = default;

void AlgoManager::draw() const {}

AlgoManager::~AlgoManager() = default;
