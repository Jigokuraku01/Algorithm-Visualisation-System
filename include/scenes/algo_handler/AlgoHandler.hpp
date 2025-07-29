#pragma once

#include "BubbleSort.hpp"
#include "DataBundle.hpp"
#include "IAlgoObject.hpp"
#include "IScene.hpp"
#include "IVisualizedAlgorithm.hpp"
#include "PossibleAlgos.hpp"

#include <QPushButton>

#include <memory>
#include <tuple>
#include <vector>

class AlgoManager : public QObject, public IScene {
  Q_OBJECT
  private:
    class BaseAlgoHandler {
      public:
        explicit BaseAlgoHandler(QWidget& window);

        virtual ~BaseAlgoHandler();

      protected:
        QWidget& window;
    };

    template <class Algo>
    class DerivedAlgoHandler : public BaseAlgoHandler {
      public:
        template <typename ReturnType, typename... ArgTypes>
        explicit DerivedAlgoHandler(
                QWidget& window, const DataBundle& data,
                std::function<ReturnType(ArgTypes...)>&& function,
                ArgTypes&&... arguments) 
                : BaseAlgoHandler(window), algorithm(),
                pause(new QPushButton(&window)),
                speed_up(new QPushButton(&window)),
                speed_down(new QPushButton(&window)),
                next(new QPushButton(&window)),
                prev(new QPushButton(&window)) {
            auto xxx = data.get_algo();
            // here are some crutches for linter
            if (xxx != PossibleAlgorithms::BubbleSort) {
                BaseAlgoHandler::window.addAction(nullptr);
                std::invoke(function, std::forward<ArgTypes>(arguments)...);
                throw std::invalid_argument("penis");
            }
        }

        ~DerivedAlgoHandler() override = default;
      private:
        Algo algorithm;
        std::unique_ptr<QPushButton> pause;
        std::unique_ptr<QPushButton> speed_up;
        std::unique_ptr<QPushButton> speed_down;
        std::unique_ptr<QPushButton> next;
        std::unique_ptr<QPushButton> prev;
        std::vector<std::unique_ptr<IAlgoObject>> objects;
    };

  public:
    AlgoManager() = delete;

    template <typename ReturnType, typename... ArgTypes>
    explicit AlgoManager(QWidget& window, const DataBundle& data,
                         std::function<ReturnType(ArgTypes...)>&& function,
                         ArgTypes&&... arguments) {
        switch (data.get_algo()) {
            case PossibleAlgorithms::BubbleSort:
                algo_handler = std::unique_ptr<BaseAlgoHandler>(
                    new DerivedAlgoHandler<BubbleSort>(
                        window, data, std::move(function),
                        std::forward<ArgTypes>(arguments)...));
                break;
            default:
                throw std::invalid_argument("This algorithm does not exist.");
        }
    }

    void draw() const override;

    ~AlgoManager() override;

  private:
    std::unique_ptr<BaseAlgoHandler> algo_handler;
};
