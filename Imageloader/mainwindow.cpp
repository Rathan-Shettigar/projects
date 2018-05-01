#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QInputDialog>

///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Image Loader");
    this->showMaximized();
    drawWig = new DrawWidget;
    drawWig->setCursor(Qt::ForbiddenCursor);
    ui->scrollArea->setWidget(drawWig);
    ShowStatusBarMessage("Load image to mark coordinates.");

    //! set black background of scrollarea
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    ui->scrollArea->setPalette(pal);

    //! Database connectivity
    dbIntf = new QDbInterface();
    dbConnectionStatus= dbIntf->Connect("LOADIMAGEDB","localhost","Admin","Pass@123");

    //! connect actions to SLOT.
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionLoad_image,SIGNAL(triggered()),this,SLOT(on_pushButton_LoadImage_clicked()));
    connect(ui->action_clearImage,SIGNAL(triggered()),this,SLOT(on_pushButton_clearImage_clicked()));
    connect(ui->actionSave_Image,SIGNAL(triggered()),this,SLOT(on_pushButton_SaveImage_clicked()));
    connect(ui->actionSet_penColor,SIGNAL(triggered()),this,SLOT(penColor()));
    connect(ui->actionSet_penWidth,SIGNAL(triggered()),this,SLOT(penWidth()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(drawWig,SIGNAL(sendCoordinates(int,int)),this,SLOT(showCoordinatesOnStatusBar(int,int)));
}

///
/// \brief MainWindow::~MainWindow
///
MainWindow::~MainWindow()
{
    delete drawWig;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    isSaved();
    event->accept();
}

//! Loads the image.
void MainWindow::on_pushButton_LoadImage_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open File"), QDir::currentPath(),tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty())
    {
        QFileInfo fileInfo(fileName);
        imageName= fileInfo.fileName();
        drawWig->openImage(fileName);
        drawWig->setCursor(Qt::CrossCursor);
        ShowStatusBarMessage("Click on image to draw coordinates and click on draw polygon button");
    }
}

//! Reset the coordinates.
void MainWindow::on_pushButton_ResetImage_clicked()
{
    if (!fileName.isEmpty())
    {
        if(drawWig->pointList.count() >0 )
        {
            QFileInfo fileInfo(fileName);
            imageName= fileInfo.fileName();
            drawWig->openImage(fileName);
            drawWig->pointList.clear();
            drawWig->setCursor(Qt::CrossCursor);
            ShowStatusBarMessage("Click on image to draw coordinates and click on draw polygon button");
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("No Coordinates to clear");
            msgBox.exec();
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("No Coordinates to clear");
        msgBox.exec();
    }
}

//! Saves the image to file and Database.
void MainWindow::on_pushButton_SaveImage_clicked()
{
    if(ui->checkBox_saveCordinatesInDB->isChecked())
    {
        QMessageBox msgBox;
        if(dbConnectionStatus)
        {
            dbIntf->InsertImageCoordinates(imageName,drawWig->pointList);
            msgBox.setText("Database Connection Sucessful");
            ShowStatusBarMessage("Database Connection Sucessful");
        }
        else
        {
            msgBox.setText("Database Connection Failed");
            ShowStatusBarMessage("Database Connection Failed");
        }
        msgBox.exec();
    }
    else
    {
        if(drawWig!= NULL)
        {
            QString outputFileName=QCoreApplication::applicationDirPath();
            outputFileName= outputFileName+"/"+"coordinates.txt";

            drawWig->saveCoordinatesToFile(outputFileName,imageName);
            ShowStatusBarMessage("Load image and draw polygon to save coordinates");
        }
    }
}

//! draws the polygon with coordinates given.
void MainWindow::on_pushButton_drawPolygon_clicked()
{
    drawWig->drawPolygon();
    ShowStatusBarMessage("Click on save button to save coordinates");
}

//! Shows the status bar message
void MainWindow::ShowStatusBarMessage(QString str)
{
    ui->statusBar->showMessage(str);
}

//! Checks if SaveCoordinatesInDB is checked or not
void MainWindow::on_checkBox_saveCordinatesInDB_toggled(bool checked)
{
    if(checked)
        ShowStatusBarMessage("Check database connectivity. This will save first 10 coordinates.");
    else
        ShowStatusBarMessage("Click on save button after drawing the polygon");
}

//! Shows the coordinate on status bar when mouse is pressed or moved.
void MainWindow::showCoordinatesOnStatusBar(int xCord, int yCord)
{
    QString str="X: " + QString::number(xCord)+" Y: " + QString::number(yCord);
    ShowStatusBarMessage(str);
}

//! Clears the loaded image.
void MainWindow::on_pushButton_clearImage_clicked()
{
    if(drawWig!= NULL)
    {
        drawWig->clearImage();
        fileName="";
        drawWig->setCursor(Qt::ForbiddenCursor);
        ShowStatusBarMessage("Load image to mark coordinates.");
    }
}

//! Sets the pen color.
void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(drawWig->penColor());
    if (newColor.isValid())
        drawWig->setPenColor(newColor);
}

//! Sets the pen width.
void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        drawWig->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        drawWig->setPenWidth(newWidth);
}

//! About message.
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Image Loader"),
                       tr("<p>The <b>Image Loader</b> example shows how to use QMainWindow as the "
                          "base widget for an application, and how to reimplement some of "
                          "QWidget's event handlers to receive the events generated for "
                          "the application's widgets:</p><p> We reimplement the mouse event "
                          "handlers to facilitate drawing, the paint event handler to "
                          "update the application. In addition we reimplement the "
                          "close event handler to intercept the close events before "
                          "terminating the application.</p><p> The example also demonstrates "
                          "how to use QPainter to draw an image in real time, as well as "
                          "to repaint widgets.</p>"));
}

//! Checks if coordinates are saved or not.
bool MainWindow::isSaved()
{
    if (drawWig->isCordinatesModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Image Loader"),
                                   tr("The coordinates has been modified.\n"
                                      "Do you want to save coordinates?"),
                                   QMessageBox::Save | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            on_pushButton_SaveImage_clicked();
            return true;
        }
        else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}
