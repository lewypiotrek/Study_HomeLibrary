#include "homelibrary.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeLibrary w;
    w.show();

    return a.exec();
}
