#ifndef DBMANAGERWINDOW_H
#define DBMANAGERWINDOW_H

#include <QMainWindow>

namespace Ui {
class DBManagerWindow;
}

class DBManagerWindowPrivate;

class DBManagerWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::DBManagerWindow *ui;
    DBManagerWindowPrivate *_pd;
public:
    explicit DBManagerWindow(QWidget *parent = 0);
    ~DBManagerWindow();
private slots:
    void create( QAction *action );
    void on_dbTreeView_customContextMenuRequested(const QPoint &pos);

private:
    void initAddMenu();
};

#endif // DBMANAGERWINDOW_H
