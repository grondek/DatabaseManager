#include "sqlitecreatedatabase.h"
#include "ui_sqlitecreatedatabase.h"
#include "dbdefaults.h"
#include "sqlitedbdefaults.h"

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
}

void SQLITECreateDatabase::on_tbSelectFile_clicked()
{
    QSettings settings(
                dbmanager::ORGANIZATION_NAME,
                dbmanager::APPLICATION_NAME
                );

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr( "Open database file" ),
                settings.value(
                    QString( "%1/%2" )
                    .arg( sqlitedb::SETTINGS_PREFIX )
                    .arg( sqlitedb::SETTINGS_LAST_OPEN_DIR ),
                    QDir::homePath() ).toString()
                );

    if ( filename.isEmpty() )
        return;

    settings.setValue(
                QString( "%1/%2" )
                .arg( sqlitedb::SETTINGS_PREFIX )
                .arg( sqlitedb::SETTINGS_LAST_OPEN_DIR ),
                QFileInfo( filename ).absolutePath()
                );

    ui->leDBFileName->setText(
                QDir::toNativeSeparators( filename ) );
}

void SQLITECreateDatabase::readModeChanged()
{
    ui->cbCreateMode->setEnabled( ui->rbRWMode->isChecked() );
    if ( !ui->cbCreateMode->isEnabled() )
        ui->cbCreateMode->setChecked( false );
}
