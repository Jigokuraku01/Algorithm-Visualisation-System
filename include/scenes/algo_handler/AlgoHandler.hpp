#pragma once

#include "BubbleSort.hpp"
#include "DataBundle.hpp"
#include "IAlgoObject.hpp"
#include "IScene.hpp"
#include "IVisualizedAlgorithm.hpp"
#include "PossibleAlgos.hpp"

#include <QIcon>
#include <QPushButton>
#include <QResizeEvent>
#include <QStyle>
#include <QVBoxLayout>

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

// widget that manages the algorithm selection
class AlgoManager : public QWidget, public IScene {
  Q_OBJECT
  private:
    // type erasure for algorithm handler 
    class BaseAlgoHandler {
      public:  
        explicit BaseAlgoHandler(QWidget* window);

        // method for changing objects when window resize
        virtual void resize_event(QResizeEvent* event) = 0;

        virtual ~BaseAlgoHandler();

      protected:
        // pointer to window
        QWidget* window;
    };

    template <class Algo>
    class DerivedAlgoHandler : public BaseAlgoHandler {
      public:
        // main constructor
        template <typename ReturnType, typename... ArgTypes>
        explicit DerivedAlgoHandler(
                QWidget* window, const DataBundle& data,
                std::function<ReturnType(ArgTypes...)>&& function,
                ArgTypes&&... arguments) 
                : BaseAlgoHandler(window), algorithm(),
                prev(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSkipBackward), "", window)),
                speed_down(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSeekBackward),"", window)),
                pause(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaPlay), "", window)),
                speed_up(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSeekForward), "", window)),
                next(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSkipForward), "", window)) {
            resize_buttons(window->size());
            // some crutches
            auto xxx = data.get_algo();
            if (xxx != PossibleAlgorithms::BubbleSort) {
                BaseAlgoHandler::window->addAction(nullptr);
                std::invoke(function, std::forward<ArgTypes>(arguments)...);
                throw std::invalid_argument("penis");
            }
        }
 
        // overridden parent method to change objects when window resize
        void resize_event(QResizeEvent *event) override {
            resize_buttons(event->size());
        }

        ~DerivedAlgoHandler() override = default;

      private:
        // method that changes the size of buttons when the screen size changes
        void resize_buttons(const QSize& sizes) {
            // the buttons size is 20 times smaller than the screen size
            const int mult = 20;
            // minimum button size
            const int min_button_size = 25;
            int window_height = sizes.height();
            int window_width = sizes.width();
            int button_height = std::max(min_button_size, window_height / mult);
            int button_width = std::max(min_button_size, window_width / mult);
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
        }

        Algo algorithm;
        QPushButton* prev;
        QPushButton* speed_down;
        QPushButton* pause;
        QPushButton* speed_up;
        QPushButton* next;
        std::vector<IAlgoObject*> objects;
    };
  
  protected:
    // overriden QWidget method for to handle the window change event
    void resizeEvent(QResizeEvent* event) override {
        std::cout << "here" << std::endl;
        QWidget::resizeEvent(event);
        algo_handler->resize_event(event);
    }

  public:
    AlgoManager() = delete;

    // main constructor
    template <typename ReturnType, typename... ArgTypes>
    explicit AlgoManager(QWidget* window, const DataBundle& data,
                         std::function<ReturnType(ArgTypes...)>&& function,
                         ArgTypes&&... arguments) : QWidget(window) {
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

    // ???
    void draw() const override;

    ~AlgoManager() override;

  private:
    std::unique_ptr<BaseAlgoHandler> algo_handler;
};
