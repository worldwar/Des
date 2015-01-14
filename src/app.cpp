#include <QApplication>
#include "MainWidget.h"
int main(int argc, char * argv[]){
    QApplication app(argc, argv);
    (new MainWidget())->show();
    return app.exec();
}
