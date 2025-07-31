#include "PossibleAlgos.hpp"
#include "AlgoHandler.hpp"
#include "DataBundle.hpp"

#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include <iostream>

int main(int argc, char* argv[]) {
    try{
        QApplication app(argc, argv);

        QWidget window;
        
        QVBoxLayout main_layout(&window);

        const int k800 = 800;
        const int k600 = 600;

        window.resize(k800, k600);

        const std::size_t height = 800UL;
        const std::size_t width = 800UL;

        ParserCommand parser_command{height, width, PossibleAlgorithms::BubbleSort, "", false, false};
        
        DataBundle data_bundle{parser_command};

        std::function<void()> fnc = []{};

        AlgoManager manager(&window, data_bundle, std::move(fnc));

        main_layout.addWidget(&manager);

        window.show();
        
        return QApplication::exec();

    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return -1;
    } catch(...) {
        std::cout << "Unknown error occurred" << std::endl;
        return -1;
    }
}

// #include <QApplication>
// #include <QWidget>
// #include <QPushButton>
// #include <QHBoxLayout>

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
    
//     QWidget window;
//     auto *layout = new QHBoxLayout(&window);
    
//     auto *btn1 = new QPushButton("Button 1");
//     auto *btn2 = new QPushButton("Button 2");
    
//     layout->addWidget(btn1);
//     layout->addWidget(btn2);
    
//     const int k400 = 400;
//     const int k200 = 200;

//     window.setWindowTitle("Scalable Buttons");
//     window.resize(k400, k200);
//     window.show();
    
//     return QApplication::exec();
// }