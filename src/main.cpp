
#include <QtSingleApplication>
#include <QtCore/qtextcodec.h>
#include <QtGui/qmessagebox.h>

#include "wnd.h"


int main(int argc, char *argv[])
{

    QtSingleApplication a(argc, argv);

    a.setOrganizationName("AlexSnet");
    a.setOrganizationDomain("alexsnet.ru");
    a.setApplicationName("Translator");

    a.setQuitOnLastWindowClosed(false);

    if (a.isRunning())
        return 0;

    wnd w;
    a.setActivationWindow(&w, true);

    w.show();
    return a.exec();
}
