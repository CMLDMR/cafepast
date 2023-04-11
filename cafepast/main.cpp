
#include "mainwindow.h"

#include <QApplication>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mongocxx::instance ins{};

    MainWindow w;
    w.show();
    return a.exec();
}
