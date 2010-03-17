#include "aboutappwnd.h"

AboutAppWnd::AboutAppWnd()
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    QLabel *label = new QLabel(tr("About Google Translator"));

    QTextBrowser *text = new QTextBrowser(this);
    text->setHtml(
            "<a href=\"http://alexsnet.ru/opensource/translator/\">Google Translator</a> is a native GUI application for "
            "Google Translate Engine.<br />This application is free and open source.<br />"
            "Developers:<ul>"
            "<li>Alex Snet (<a href=\"http://alexsnet.ru\">WWW</a> | <a href=\"mailto:me@alexsnet.ru\">Mail</a>)</li>"
            "</ul>"
    );
    text->setReadOnly(true);
    text->setOpenExternalLinks(true);

    QPushButton *okBtn = new QPushButton(tr("Ok"),this);
    connect( okBtn, SIGNAL(clicked()), this, SLOT(close()) );

    layout->addWidget( label );
    layout->addWidget( text );
    layout->addWidget( okBtn );
    this->setWindowTitle( tr("About Google Translator") );
    this->setLayout(layout);
}
