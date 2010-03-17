#ifndef WND_H
#define WND_H

#include <QtGui/QMainWindow>
#include <QSystemTrayIcon>

//#include <QxtGlobalShortcut>

#include "aboutappwnd.h"
#include "settingswnd.h"
#include "googleproto.h"

class QSettings;
class QAction;
class QMessageBox;

namespace Ui
{
    class wndClass;
}

class wnd : public QMainWindow
{
    Q_OBJECT

public:
    wnd(QWidget *parent = 0);
    ~wnd();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void on_swap_clicked();
    void on_translate_clicked();
    void translationComplete( QString text );
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void aboutQt();
    void aboutApp();
    void settingsWndOpen();
    void updateSettings();

private slots:
    void hotkeyPressed();

private:
    Ui::wndClass *ui;
    void setUpActions();
    void createTrayIcon();

    GoogleProto *googTr;

    AboutAppWnd *aboutAppWnd;
    SettingsWnd *settingsWnd;

    QAction *cmdEnter;

    QAction *restoreAction;
    QAction *quitAction;
    QAction *aboutAppAction;
    QAction *aboutQtAction;
    QAction *settingsAction;

    QStringList* langs;

    QSettings settings;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QString m_shortcutDef;
    //QxtGlobalShortcut m_hotkeyHandle;
};

#endif // WND_H
