#pragma once

#include "BubbleSort.hpp"
#include "IAlgoObject.hpp"
#include "IScene.hpp"
#include "IVisualizedAlgorithm.hpp"
#include "Parser.hpp"
#include <QPushButton>
#include <memory>
#include <tuple>
#include <vector>

class AlgoManager : public IScene {
  public:
    class BaseAlgoHandler {
      public:
        explicit BaseAlgoHandler(QWidget& window);

      private:
        QWidget window;
    };

    template <class Algo>
    class DerivedAlgoHandler : BaseAlgoHandler {
      public:
        template <typename ReturnType, typename... ArgTypes>
        explicit DerivedAlgoHandler(
            QWidget& window, const ParserCommand& parser_command,
            std::function<ReturnType(ArgTypes...)>&& function,
            ArgTypes&&... arguments);

      private:
        Algo algorithm;
        QPushButton pause;
        QPushButton speed_up;
        QPushButton speed_down;
        QPushButton next;
        QPushButton prev;
        std::vector<std::unique_ptr<IAlgoObject>> objects;
    };

    AlgoManager() = delete;

    template <typename ReturnType, typename... ArgTypes>
    explicit AlgoManager(QWidget& window, const ParserCommand& parser_command,
                         std::function<ReturnType(ArgTypes...)>&& function,
                         ArgTypes&&... arguments);

    void draw() const override;

  private:
    std::unique_ptr<BaseAlgoHandler> algo_handler;
};
