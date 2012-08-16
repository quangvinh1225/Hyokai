#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, QString path = ":memory:");
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QSqlDatabase theDb;
    QSqlTableModel *tableModel;
    QString filepath;

    void open(QString path);

private slots:
    void filterFinished();
    void tableChanged(const QString &name);
    void sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);

    void quit();
    void on_actionGo_github_triggered();
    void on_actionCommit_triggered();
    void on_actionRevert_triggered();
    void on_actionCreateTable_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionInsert_triggered();
    void on_actionDelete_triggered();
};

#endif // MAINWINDOW_H
