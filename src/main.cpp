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
        
        const int k800 = 800;
        const int k600 = 600;

        window.resize(k800, k600);

        const std::size_t height = 800UL;
        const std::size_t width = 800UL;

        ParserCommand parser_command{height, width, PossibleAlgorithms::BubbleSort, "", false, false};
        
        DataBundle data_bundle{parser_command};

        std::function<void()> fnc = []{};

        AlgoManager manager(window, data_bundle, std::move(fnc));

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
