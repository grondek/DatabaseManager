#include "sqlitecreatedatabase.h"
#include "ui_sqlitecreatedatabase.h"
#include "dbdefaults.h"
#include "sqlitedbdefaults.h"
//#include "sqlitedbobject.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QDir>

#include <QtDebug>

SQLITECreateDatabase::SQLITECreateDatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SQLITECreateDatabase)
{
    ui->setupUi(this);

    connect( ui->rbRWMode, SIGNAL(toggled(bool) ),
             this, SLOT(readModeChanged() ) );
    connect( ui->rbROMode, SIGNAL(toggled(bool) ),
             this, SLOT(readModeChanged() ) );
}

SQLITECreateDatabase::~SQLITECreateDatabase()
{
    delete ui;
}

void SQLITECreateDatabase::create()
{
    QVariantMap params;
    params.insert( dbmanager::NAME_PROPERTY, ui->leName->text() );
    params.insert( dbmanager::PARENT_PROPERTY, QVariant() );
    params.insert( "filename", ui->leDBFileName->text() );
    params.insert( "create_if_not_exists", ui->cbCreateMode->isChecked() );
    params.insert( "rw_mode",
                      ui->rbRWMode->isChecked()
                      ? QString( "rw" )
                      : QString( "ro" )
                        );

    emit createObject(
                dbmanager::OBJECT_TYPE_DATABASE,
                QString::null,
                params
                );
}

void SQLITECreateDatabase::on_tbSelectFile_clicked()
{
    QSettings settings(
                dbmanager::ORGANIZATION_NAME,
                dbmanager::APPLICATION_NAME
                );

    QFileDialog dlg( this,
                     tr( "Open database file" ),
                     settings.value(
                         QString( "%1/%2" )
                         .arg( sqlitedb::SETTINGS_PREFIX )
                         .arg( sqlitedb::SETTINGS_LAST_OPEN_DIR ),
                         QDir::homePath() ).toString()
                     );
    dlg.setAcceptMode( QFileDialog::AcceptOpen );

    if ( dlg.exec() != QDialog::Accepted )
        return;

    if ( dlg.selectedFiles().isEmpty() )
        return;

    settings.setValue(
                QString( "%1/%2" )
                .arg( sqlitedb::SETTINGS_PREFIX )
                .arg( sqlitedb::SETTINGS_LAST_OPEN_DIR ),
                dlg.directory().absolutePath()
                );

    ui->leDBFileName->setText(
                QDir::toNativeSeparators( dlg.selectedFiles().first() ) );
}

void SQLITECreateDatabase::readModeChanged()
{
    ui->cbCreateMode->setEnabled( ui->rbRWMode->isChecked() );
    if ( !ui->cbCreateMode->isEnabled() )
        ui->cbCreateMode->setChecked( false );
}
