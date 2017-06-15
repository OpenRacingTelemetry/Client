#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>

#include "gui/ui/login/login.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QString("ru_RU"),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load("client-gui");
    app.installTranslator(&myappTranslator);

    LoginWindow w;
    w.show();

    return app.exec();
}
