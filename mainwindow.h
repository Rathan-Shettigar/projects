/*This sample allows you to load the .csv file from the path.
 *
 * CSV is a comma-separated values file is a delimited text file that uses a comma to separate values.
 * Each line of the file is a data record.
 * Each record consists of one or more fields, separated by commas.
 *
 * Option like save,find,sort and clear has been implemented.
 *
 * Save - Saves the changes to the file
 * Find - Finds the exactly matched text . If found changes the background color to grey.
 * Sort - Sorts the specific column (Text based)
 * Clear - Clears the background color (if any) and selection(if any).
 *
 * Tested on Windows 10 pro 64 bit Core-i7-4600U.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSearch_triggered();

    void itemChangedSlot(QStandardItem *item);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionClear_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *csvModel;
    QList<QStandardItem *> foundItems;
    QList<QStandardItem *> masterFoundItems;

    QString filePath;
    bool isTextFound;
    bool skipFirst;

    void SetBackgroundColor(QBrush color);
    void ShowMessageBox(QString messageText, QMessageBox::Icon icon, QString title);
};

#endif // MAINWINDOW_H
