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
        dbmodel = new DBTreeModel( parent );
        dbproxy = new QSortFilterProxyModel( parent );
        dbproxy->setSourceModel( dbmodel );

        loader = new DBPluginLoader( parent );
        loader->connect( loader, SIGNAL(newObject(DBObject*) ),
                         dbmodel, SLOT(addObject(DBObject*) )
                         );
        loader->connect( loader, SIGNAL(beginAddChildren(DBObject*,int,int) ),
                         dbmodel, SLOT(beginAddObjectChild(DBObject*,int,int) ) );
        loader->connect( loader, SIGNAL(endAddChildren() ),
                         dbmodel, SLOT(endAddObjectChild() ) );

        /*QStringList plugins = */loader->availablePlugins();
        loader->loadAll();
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

    connect( ui->actionExpandAll, SIGNAL(triggered() ),
             ui->dbTreeView, SLOT(expandAll() ) );

    connect( ui->dbTreeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection) ),
             this, SLOT(dbTreeSeelctionChanged() ) );
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

    DBInterface *dbi = _pd->loader->plugin( action->data().toMap().value( "iid" ).toString() );
    if ( !dbi )
        return;

    QDialog *dlg = new QDialog( this );
    dlg->setLayout( new QVBoxLayout );
    dlg->setAttribute( Qt::WA_DeleteOnClose, true );

    QWidget *widget = dbi->createObjectEditor(
                action->data().toMap().value( "objecttype" ).toString(),
                0,
                dlg
                );
    if ( !widget ) {
        dlg->deleteLater();
        return;
    }

    dlg->setWindowTitle( widget->windowTitle() );
    dlg->setWindowIcon( widget->windowIcon() );
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

    dlg->show();
}

void DBManagerWindow::on_dbTreeView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->dbTreeView->indexAt( pos );

    DBObject *obj = _pd->dbmodel->data(
                _pd->dbproxy->mapToSource( index ),
                DBTreeModel::DBObjectRole
                ).value< DBObject* >();

    if ( !obj || obj->actions().isEmpty() )
        return;

    QMenu *menu = new QMenu( this );
    menu->insertActions( NULL, obj->actions() );
    menu->popup( ui->dbTreeView->viewport()->mapToGlobal( pos ) );
}

void DBManagerWindow::dbTreeSeelctionChanged()
{
    foreach( const QModelIndex &proxy_index, ui->dbTreeView->selectionModel()->selectedRows( 0 ) ){
        QModelIndex index = _pd->dbproxy->mapToSource( proxy_index );
        Q_UNUSED( index );
    }

}
