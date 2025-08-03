#include "PossibleAlgos.hpp"
#include "AlgoHandler.hpp"
#include "DataBundle.hpp"

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    try{
        QApplication app(argc, argv);

        QWidget window;
        
        // need to correct objects draw
        QVBoxLayout main_layout(&window);

        // needed to terminate the thread before closing the window
        QObject::connect(qApp, &QGuiApplication::lastWindowClosed, [](){
            algo::end_working_thread();
        });

        const int k800 = 800;
        const int k600 = 600;

        window.resize(k800, k600);

        const std::size_t height = 800UL;
        const std::size_t width = 600UL;

        ParserCommand parser_command{height, width, PossibleAlgorithms::BubbleSort, {4, 2, 3, 1}, "", false, false};
        
        DataBundle data_bundle{parser_command};

        // crutch lambda (from scene manager)
        std::function<void()> fnc = []{};

        // create algo manager scene
        AlgoManager manager(&window, data_bundle, std::move(fnc));

        // set layout
        main_layout.addWidget(&manager);

        window.show();  

        return QApplication::exec();

    } 
    // some checks
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return -1;
    } catch(...) {
        std::cout << "Unknown error occurred" << std::endl;
        return -1;
    }
}
