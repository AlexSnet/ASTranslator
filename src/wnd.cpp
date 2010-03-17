#include "wnd.h"
#include "ui_wnd.h"
#include <QtNetwork>
#include <QtGui>

// Debugging
#include<QtDebug>

wnd::wnd(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::wndClass)
{
    // Setuping User Interface from wnd.ui
    ui->setupUi(this);

    // Initializing Google Translate Engine
    googTr = new GoogleProto();
    connect( googTr, SIGNAL(translationComplete(QString)), this, SLOT(translationComplete(QString)) );

    // Setting up languages list
    QStringList
            translates = googTr->translatesFull ,
            list = googTr->translatesShort ;

    langs = new QStringList(list);

    // Connecting languages list to language selectors (ComboBoxes)
    ui->langFrom->addItem( "Auto detect" );
    ui->langFrom->setItemIcon( 0 ,QIcon(QString(":/flags/res/flags/auto.png")));

    ui->langFrom->addItems(translates);
    ui->langTo->addItems(translates);
    qDebug("Langs setted");

    // Setting up icons for ComboBoxes
    for(int i=0;i<ui->langTo->count();i++)
    {
        QString path = QString(":/flags/res/flags/%1.png").arg(langs->at(i));
        ui->langFrom->setItemIcon( i+1 ,QIcon(path));
        ui->langTo->setItemIcon(i,QIcon(path));
    }
    qDebug("Lang flags configured...");

    // Setting up last used languages
    // If application runs firs time on this computer by default setting up English2English
    ui->langFrom->setCurrentIndex(settings.value("lang/from",10).value<int>());
    ui->langTo->setCurrentIndex(settings.value("lang/to",10).value<int>());
    qDebug("Last pair loaded");

    // Font settings
    updateSettings();

    // Translated text must be readOnly
    ui->textTo->setReadOnly(true);

    // Setuping actions
    setUpActions();

    // Creating tray icon
    createTrayIcon();
    trayIcon->show();

    //Windows
    aboutAppWnd = new AboutAppWnd();
    settingsWnd = new SettingsWnd();
    connect( settingsWnd, SIGNAL(updateSettings()), this, SLOT(updateSettings()) );

    //Debug output
    qDebug("All buttons are connected");

    // Initializing shortcuts
    m_shortcutDef = QString("Ctrl+G+T");
    //m_hotkeyHandle.setShortcut( QKeySequence(m_shortcutDef) );
    //m_hotkeyHandle.setEnabled(true);
    //connect( &m_hotkeyHandle, SIGNAL(activated()), this, SLOT(hotkeyPressed()) );
}
wnd::~wnd()
{
    // Saves current language pair
    settings.setValue("lang/from",ui->langFrom->currentIndex());
    settings.setValue("lang/to",ui->langTo->currentIndex());
    qDebug("Last language pair saved");

    qDebug("Good bye.");
    delete ui;
}
void wnd::updateSettings(){

    // Font updating
    ui->textFrom->setFont( settings.value("font/fr/name",QFont("Arial")).value<QFont>() );
    ui->textTo->setFont( settings.value("font/to/name",QFont("Arial")).value<QFont>() );

    ui->textFrom->setFontPointSize( settings.value("font/fr/size", 10 ).value<int>() );
    ui->textTo->setFontPointSize( settings.value("font/to/size", 10 ).value<int>() );

    // Proxy

    if( settings.value("proxy/useProxy", false ).value<bool>() ){
        googTr->setProxy(
                settings.value("proxy/host", QString("localhost") ).value<QString>(),
                settings.value("proxy/port", 3128 ).value<int>(),
                settings.value("proxy/user", QString("") ).value<QString>(),
                settings.value("proxy/pass", QString("") ).value<QString>()
                );
    }else{
        googTr->unsetProxy();
    }
}
void wnd::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}
void wnd::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction( restoreAction );
    trayIconMenu->addSeparator();
    trayIconMenu->addAction( settingsAction );
    trayIconMenu->addSeparator();
    trayIconMenu->addAction( aboutQtAction );
    trayIconMenu->addAction( aboutAppAction );
    trayIconMenu->addSeparator();
    trayIconMenu->addAction( quitAction );

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon( QIcon(":/res/icon.png") );
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}
void wnd::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::MiddleClick:
        //case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            show();
            break;
        default: break;
    }
}
void wnd::aboutQt() {
    QMessageBox::aboutQt(this);
}
void wnd::aboutApp() {
    aboutAppWnd->show();
}
void wnd::settingsWndOpen() {
    settingsWnd->show();
}
void wnd::setUpActions()
{
    cmdEnter = new QAction(tr("&Translate"), this);
    cmdEnter->setShortcut( Qt::Key_Shift + Qt::Key_Return );
    ui->textFrom->addAction(cmdEnter);
    connect(cmdEnter, SIGNAL(triggered()), this, SLOT(on_translate_clicked()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    aboutQtAction = new QAction(tr("Abou&t Qt"), this);
    connect( aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()) );

    aboutAppAction = new QAction(tr("&About App"), this);
    connect( aboutAppAction, SIGNAL(triggered()), this, SLOT(aboutApp()) );

    settingsAction = new QAction(tr("&Settings"), this);
    connect( settingsAction, SIGNAL(triggered()), this, SLOT(settingsWndOpen()) );
}

void wnd::on_swap_clicked()
{
    // Swapping languages (e.g. English<->Russian)
    if( ui->langFrom->currentIndex() != 0 ){
        int tmp = ui->langTo->currentIndex();
        ui->langTo->setCurrentIndex( ui->langFrom->currentIndex()-1 );
        ui->langFrom->setCurrentIndex( tmp+1 );
    }
}
void wnd::on_translate_clicked()
{
    qDebug("Starting translation.");
    QString text;
    googTr->startTranslation( ui->langFrom->currentIndex()-1 , ui->langTo->currentIndex(), ui->textFrom->toPlainText() );
}
void wnd::translationComplete( QString text)
{
    ui->textTo->setText( text );
}
void wnd::hotkeyPressed(){
    qDebug() << "Hotkey pressed";
}
