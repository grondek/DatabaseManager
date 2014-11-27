#include "sqlitecreatedatabase.h"
#include "ui_sqlitecreatedatabase.h"
#include "dbdefaults.h"
#include "sqlitedbdefaults.h"
#include "sqlitedbobject.h"

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
    qDebug() << "CREATE DATABASE!";

    SQLITEDBObject *obj = new SQLITEDBObject;
    obj->setProperty( dbmanager::NAME_PROPERTY, ui->leName->text() );
    obj->setProperty( dbmanager::PARENT_PROPERTY, QVariant() );
    obj->setProperty( "filename", ui->leDBFileName->text() );
    obj->setProperty( "create_if_not_exists", ui->cbCreateMode->isChecked() );
    obj->setProperty( "rw_mode",
                      ui->rbRWMode->isChecked()
                      ? QString( "rw" )
                      : QString( "ro" )
                        );

    emit created( obj );
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
