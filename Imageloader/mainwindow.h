
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <drawwidget.h>
#include <qdbinterface.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void penColor();
    void penWidth();
    void about();

    void on_pushButton_LoadImage_clicked();

    void on_pushButton_ResetImage_clicked();

    void on_pushButton_SaveImage_clicked();

    void on_pushButton_drawPolygon_clicked();

    void on_checkBox_saveCordinatesInDB_toggled(bool checked);

    void showCoordinatesOnStatusBar(int xCord, int yCord);

    void on_pushButton_clearImage_clicked();

private:
    Ui::MainWindow *ui;
    void ShowStatusBarMessage(QString str);
    bool isSaved();

    QDbInterface *dbIntf;
    DrawWidget *drawWig;
    QString imageName;
    QString fileName;
    bool dbConnectionStatus;
};

#endif // MAINWINDOW_H
