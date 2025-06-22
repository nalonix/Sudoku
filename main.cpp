
#include "widget.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QIcon icon(":/icons/sudoku.png");
    w.setWindowIcon(icon);
    w.setWindowTitle("Sudoku");
    w.setFixedSize(439 , 537);
    w.show();
    return a.exec();
}
