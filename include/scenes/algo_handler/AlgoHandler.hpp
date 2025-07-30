#pragma once

#include "BubbleSort.hpp"
#include "DataBundle.hpp"
#include "IAlgoObject.hpp"
#include "IScene.hpp"
#include "IVisualizedAlgorithm.hpp"
#include "PossibleAlgos.hpp"

#include <QIcon>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>

#include <memory>
#include <tuple>
#include <vector>

class AlgoManager : public IScene {
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
                prev(new QPushButton(window.style()->standardIcon(
                    QStyle::SP_MediaSkipBackward), "", &window)),
                speed_down(new QPushButton(window.style()->standardIcon(
                    QStyle::SP_MediaSeekBackward),"", &window)),
                pause(new QPushButton(window.style()->standardIcon(
                    QStyle::SP_MediaPlay), "", &window)),
                speed_up(new QPushButton(window.style()->standardIcon(
                    QStyle::SP_MediaSeekForward), "", &window)),
                next(new QPushButton(window.style()->standardIcon(
                    QStyle::SP_MediaSkipForward), "", &window)) {
            const int k20 = 20;
            int window_height = window.height();
            int window_width = window.width();
            int button_height = window_height / k20;
            int button_width = window_width / k20;
            int first_button_pos_x = window_width / 2 - 
                button_width / 2 - button_width * 2;
            int button_pos_y = window_height / 4 * 3 - button_height / 2;

            std::vector<QPushButton*> buttons{
                prev, speed_down, pause, speed_up, next
            };

            for (std::size_t i = 0; i < buttons.size(); ++i) {
                buttons[i]->setGeometry(first_button_pos_x +
                                        button_width * static_cast<int>(i),
                                        button_pos_y, button_width,
                                        button_height);
            }
            auto xxx = data.get_algo();
            if (xxx != PossibleAlgorithms::BubbleSort) {
                BaseAlgoHandler::window.addAction(nullptr);
                std::invoke(function, std::forward<ArgTypes>(arguments)...);
                throw std::invalid_argument("penis");
            }
        }

        ~DerivedAlgoHandler() override = default;
      private:
        Algo algorithm;
        QPushButton* prev;
        QPushButton* speed_down;
        QPushButton* pause;
        QPushButton* speed_up;
        QPushButton* next;
        std::vector<IAlgoObject*> objects;
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
