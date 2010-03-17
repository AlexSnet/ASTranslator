#include "settingswnd.h"
#include "ui_settingswnd.h"
#include <QtDebug>

SettingsWnd::SettingsWnd(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SettingsWnd)
{
    m_ui->setupUi(this);
    this->setWindowTitle(tr("Options"));
    //m_ui->buttonBox->clicked(QAbsctractButton)
    restoreValues();
}


SettingsWnd::~SettingsWnd()
{
    delete m_ui;
}

void SettingsWnd::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void SettingsWnd::restoreValues(){
    // Font settings
    m_ui->fontBoxFr->setCurrentFont( settings.value("font/fr/name",QFont("Arial")).value<QFont>() );
    m_ui->fontBoxTo->setCurrentFont( settings.value("font/to/name",QFont("Arial")).value<QFont>() );
    m_ui->fontSizeFr->setValue( settings.value("font/fr/size", 10 ).value<int>() );
    m_ui->fontSizeTo->setValue( settings.value("font/to/size", 10 ).value<int>() );

    // Proxy settings
    m_ui->proxy->setChecked( settings.value("proxy/useProxy", false ).value<bool>() );
    m_ui->proxyHost->setText( settings.value("proxy/host", QString("") ).value<QString>() );
    m_ui->proxyPort->setValue( settings.value("proxy/port", 3128 ).value<int>() );
    m_ui->proxyUser->setText( settings.value("proxy/user", QString("") ).value<QString>() );
    m_ui->proxyPass->setText( settings.value("proxy/pass", QString("") ).value<QString>() );
}

void SettingsWnd::on_buttonBox_accepted(){
    qDebug() << "OK Clicked";

    // Font settings
    settings.setValue("font/to/name", m_ui->fontBoxTo->currentFont() );
    settings.setValue("font/to/size", m_ui->fontSizeTo->value() );
    settings.setValue("font/fr/name", m_ui->fontBoxFr->currentFont() );
    settings.setValue("font/fr/size", m_ui->fontSizeFr->value() );

    // Proxy settings
    settings.setValue("proxy/useProxy", m_ui->proxy->isChecked() );
    settings.setValue("proxy/host", m_ui->proxyHost->text() );
    settings.setValue("proxy/port", m_ui->proxyPort->value() );
    settings.setValue("proxy/user", m_ui->proxyUser->text() );
    settings.setValue("proxy/pass", m_ui->proxyPass->text() );

    emit(updateSettings());
}
void SettingsWnd::on_buttonBox_rejected() {
    qDebug() << "Cancel Clicked";

}
