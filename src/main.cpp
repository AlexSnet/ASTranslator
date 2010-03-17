#include <QtGui/QApplication>
#include "wnd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("AlexSnet");
    QCoreApplication::setOrganizationDomain("alexsnet.ru");
    QCoreApplication::setApplicationName("Translator");
    a.setQuitOnLastWindowClosed(false);

    wnd w;
    w.show();
    return a.exec();
}
