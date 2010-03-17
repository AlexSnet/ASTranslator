#ifndef SETTINGSWND_H
#define SETTINGSWND_H

#include <QtGui/QDialog>
#include <QSettings>

namespace Ui {
    class SettingsWnd;
}

class SettingsWnd : public QDialog {
    Q_OBJECT
public:
    SettingsWnd(QWidget *parent = 0);
    ~SettingsWnd();
public slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
signals:
    void updateSettings();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::SettingsWnd *m_ui;
    QSettings settings;
    void restoreValues();
};

#endif // SETTINGSWND_H
