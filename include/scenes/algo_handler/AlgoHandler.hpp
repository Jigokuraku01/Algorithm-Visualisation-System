#pragma once

#include "AlgorithmHelpers.hpp"
#include "AlgoUtilities.hpp"
#include "BubbleSort.hpp"
#include "DataBundle.hpp"
#include "IAlgoObject.hpp"
#include "IScene.hpp"
#include "PossibleAlgos.hpp"
#include "SelectionSort.hpp"

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
    class BaseAlgoHandler
            : public std::enable_shared_from_this<BaseAlgoHandler> {
      public:  
        explicit BaseAlgoHandler(QWidget* window);

        // method for changing objects when window resize
        virtual void resize_event(QResizeEvent* event) = 0;

        // method for running algorithm
        virtual void run_algorithm() = 0;

        // method for setting a function for working thread 
        virtual void set_function_for_thread() = 0;

        // method for setting lambdas for basic buttons
        virtual void set_lambdas_for_buttons() = 0;

        // function for switch type of button play/pause
        // and switch mode of algorithm (auto or not auto)
        virtual void switch_play_pause_icon() = 0;

        virtual ~BaseAlgoHandler();

      protected:
        // pointer to window
        QWidget* window;
    };

    template <Algorithm Algo>
    class DerivedAlgoHandler : public BaseAlgoHandler {
      public:
        // main constructor
        template <typename ReturnType, typename... ArgTypes>
        explicit DerivedAlgoHandler(
                QWidget* window, const DataBundle& data,
                std::function<ReturnType(ArgTypes...)>&& function,
                ArgTypes&&... arguments) 
                : BaseAlgoHandler(window),
                // creating buttons with icons
                prev(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSkipBackward), "", window)),
                speed_down(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSeekBackward),"", window)),
                pause(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaPlay), "", window)),
                speed_up(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSeekForward), "", window)),
                next(new QPushButton(window->style()->standardIcon(
                    QStyle::SP_MediaSkipForward), "", window)),
                // create TestAlgoObjects and fill vector
                objects([&data](){
                    std::vector<IAlgoObject*> result(data.get_array().size());
                    for (std::size_t i = 0; i < result.size(); ++i) {
                        result[i] = new TestAlgoObject(&(data.get_array()[i]));
                    }
                    return result;
                }()),
                // some crutches because there are
                // no implemented version of AlgoObjects
                algorithm([&data, this](){
                    std::vector<algo::TypeWrapper<int>> result;
                    for (std::size_t i = 0; i < data.get_array().size(); ++i) {
                        result.emplace_back(&(data.get_array()[i]), objects[i]);
                    }
                    return result;
                }()) {
            algo::remove_automatic_mode();
            resize_buttons(window->size());
            // some crutches
            auto xxx = data.get_algo();
            if (xxx != PossibleAlgorithms::BubbleSort) {
                std::invoke(function, std::forward<ArgTypes>(arguments)...);
            }
        }

        void set_lambdas_for_buttons() override {
            // create lambda for forward button
            QObject::connect(next, &QPushButton::clicked, []() {
                if (algo::steps_info.is_at_the_last_step()) {
                    algo::start_working_thread();
                } else {
                    algo::steps_info.step_forward();
                }
            });
            
            //create lambda for back button
            QObject::connect(prev, &QPushButton::clicked, []() {
                algo::steps_info.step_back();
            });

            // create lambda for speed up button
            QObject::connect(speed_up, &QPushButton::clicked, []() {
                algo::speed_up();
            });
            
            // create lambda for speed down button
            QObject::connect(speed_down, &QPushButton::clicked, []() {
                algo::speed_down();
            });

            // create shared_ptr for closing in lambda
            auto shared_this(this->shared_from_this());

            // create lambda for pause/play
            QObject::connect(pause, &QPushButton::clicked, [shared_this]() {
                shared_this->switch_play_pause_icon();
            });
        }

        void switch_play_pause_icon() override {
            // bool that show current case
            static bool is_icon_play = true;
            // some cases
            if (is_icon_play) {
                pause->setIcon(window->style()->standardIcon(
                    QStyle::SP_MediaPause));
                algo::set_automatic_mode();
            } else {
                pause->setIcon(window->style()->standardIcon(
                    QStyle::SP_MediaPlay));
                algo::remove_automatic_mode();
            }
            is_icon_play = !is_icon_play;
        }

        std::function<void()> create_function_for_algo() {
            // create shared_ptr for closing in lambda
            auto shared_this(this->shared_from_this());
            return [shared_this]() {
                shared_this->run_algorithm();
            };
        }

        void set_function_for_thread() override {
            algo::thread_info.set_function_for_thread(
                    create_function_for_algo());
        }

        void run_algorithm() override {
            algorithm.algorithm();
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

        QPushButton* prev;
        QPushButton* speed_down;
        QPushButton* pause;
        QPushButton* speed_up;
        QPushButton* next;
        std::vector<IAlgoObject*> objects;
        Algo algorithm;
    };
  
  protected:
    // overriden QWidget method for to handle the window change event
    void resizeEvent(QResizeEvent* event) override {
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
                algo_handler = std::shared_ptr<BaseAlgoHandler>(
                    new DerivedAlgoHandler<BubbleSort<algo::TypeWrapper<int>>>(
                        window, data, std::move(function),
                        std::forward<ArgTypes>(arguments)...));
                break;
            case PossibleAlgorithms::SelectionSort:
                algo_handler = std::shared_ptr<BaseAlgoHandler>(
                    new DerivedAlgoHandler<SelectionSort<algo::TypeWrapper<int>>>(
                        window, data, std::move(function),
                        std::forward<ArgTypes>(arguments)...));
                break;
            default:
                throw std::invalid_argument("This algorithm does not exist.");
        }   
        // we need set function for thread after creating object
        // because due to the features shared_ptr
        algo_handler->set_function_for_thread();
        algo_handler->set_lambdas_for_buttons();
    }

    // method for ???
    void draw() const override;

    ~AlgoManager() override;

  private:
    std::shared_ptr<BaseAlgoHandler> algo_handler;
};
