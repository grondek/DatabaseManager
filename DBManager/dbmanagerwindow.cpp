#include "dbmanagerwindow.h"
#include "ui_dbmanagerwindow.h"

#include "dbpluginloader.h"
#include "dbdefaults.h"
#include "dbtreemodel.h"

#include <QAction>
#include <QDialog>
#include <QDialogButtonBox>
#include <QSortFilterProxyModel>
#include <QMenu>
#include <QToolButton>

#include <QtDebug>

class DBManagerWindowPrivate
{
public:
    DBPluginLoader *loader;

    DBTreeModel *dbmodel;
    QSortFilterProxyModel *dbproxy;

    DBManagerWindowPrivate( DBManagerWindow *parent )
    {
        loader = new DBPluginLoader( parent );
        /*QStringList plugins = */loader->availablePlugins();
        loader->loadAll();

        dbmodel = new DBTreeModel( parent );
        dbproxy = new QSortFilterProxyModel( parent );
        dbproxy->setSourceModel( dbmodel );

    }

    ~DBManagerWindowPrivate()
    {

    }

    QAction *createAddAction( const QString &iid, DBInterface *dbi )
    {
        QAction *action = new QAction(
                    dbi->icon(),
                    DBManagerWindow::tr( "Add %1 database" ).arg( dbi->name() ),
                    NULL
                    );
        QVariantMap data;
        data.insert( "parent", QVariant() );
        data.insert( "iid", iid );
        data.insert( "objecttype", dbmanager::OBJECT_TYPE_DATABASE );
        action->setData( data );

        return action;
    }
};

DBManagerWindow::DBManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DBManagerWindow)
{
    ui->setupUi(this);

    _pd = new DBManagerWindowPrivate( this );

    ui->dbTreeView->setModel( _pd->dbproxy );

    initAddMenu();
}

DBManagerWindow::~DBManagerWindow()
{
    delete _pd;
    delete ui;
}

void DBManagerWindow::initAddMenu()
{
    QToolButton *addbutton = qobject_cast< QToolButton* >( ui->mainToolBar->widgetForAction( ui->actionAddConnection ) );
    addbutton->setMenu( new QMenu( addbutton ) );
    addbutton->setPopupMode( QToolButton::InstantPopup );
    connect( addbutton->menu(), SIGNAL(triggered(QAction*) ),
             this, SLOT(create(QAction*) ) );

    foreach ( const QString &iid, _pd->loader->availablePlugins() ) {
        DBInterface *dbi = _pd->loader->plugin( iid );
        qDebug() << dbi;
        if ( !dbi )
            continue;

        addbutton->menu()->insertAction(
                    NULL,
                    _pd->createAddAction( iid, dbi )
                    );
    }
}

void DBManagerWindow::create(QAction *action)
{
    if ( !action )
        return;

    qDebug() << action->data().toMap();

    DBInterface *dbi = _pd->loader->plugin( action->data().toMap().value( "iid" ).toString() );
    if ( !dbi )
        return;

    QDialog *dlg = new QDialog( this );
    dlg->setLayout( new QVBoxLayout );
    dlg->setAttribute( Qt::WA_DeleteOnClose, true );

    QWidget *widget = dbi->createObjectEditor(
                action->data().toMap().value( "objecttype" ).toString(),
                QString(),
                dlg
                );
    dlg->layout()->addWidget( widget );

    QDialogButtonBox *bbox = new QDialogButtonBox( dlg );
    dlg->layout()->addWidget( bbox );
    bbox->addButton( tr( "Create" ), QDialogButtonBox::AcceptRole );
    bbox->addButton( QDialogButtonBox::Cancel );
    connect( bbox, SIGNAL(accepted() ),
             widget, SLOT(create() ) );
    connect( bbox, SIGNAL(accepted() ),
             dlg, SLOT(accept() ) );
    connect( bbox, SIGNAL(rejected() ),
             dlg, SLOT(reject() ) );
    connect( widget, SIGNAL(created(DBObject*) ),
             _pd->dbmodel, SLOT(addObject(DBObject*) )
             );

    dlg->show();
}
