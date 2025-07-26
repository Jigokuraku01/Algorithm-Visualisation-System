#include "PossibleAlgos.hpp"
#include <QApplication>
#include <QDebug>
#include <QPushButton>
#include <any>
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QPushButton button("Button!", &window);

    QObject::connect(&button, &QPushButton::clicked,
                     [&]() { qDebug() << "Click!"; });

    window.show();
    return QApplication::exec();
}
