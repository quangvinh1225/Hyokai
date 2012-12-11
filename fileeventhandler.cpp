#include "fileeventhandler.h"

#include <QFileOpenEvent>
#include <QApplication>
#include "main.h"
#include "mainwindow.h";
#include <QDebug>

FileEventHandler::FileEventHandler(QObject *parent) :
    QObject(parent)
{
}

bool FileEventHandler::eventFilter(QObject *obj, QEvent *event)
{
    if (qApp == obj && event->type() == QEvent::FileOpen) {
        QFileOpenEvent *openevent = static_cast < QFileOpenEvent *>(event);
        qDebug() << openevent->file();

        if (openevent->file().endsWith(".sqlite3") ||
                openevent->file().endsWith(".sqlite")) {
            ::tableviewCleanupWindows();
            MainWindow *w = new MainWindow(NULL, openevent->file());
            w->show();
            ::windowList.append(w);
            event->accept();
            return true;
        }

        if (openevent->file().endsWith(".txt") ||
                   openevent->file().endsWith(".csv")) {

            MainWindow *w;
            foreach (MainWindow *window, ::windowList) {
                if (window->isVisible() && window->filePath() == ":memory:") {
                    window->activateWindow();
                    w = window;
                    goto opened;
                }
            }

            w = new MainWindow(NULL, ":memory:");
            w->show();
            ::windowList.append(w);

            opened:

            w->importFile(openevent->file(), false);
            w->refresh();

            return true;
        }
    }
    return false;
}