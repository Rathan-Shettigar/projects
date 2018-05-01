#include "drawwidget.h"
#include <QFileDialog>
#include <QTextStream>
#include <qdatetime.h>
#include <qmessagebox.h>

//! Constructor of DrawWidget
DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    isImageLoadedToWidget=false;
    isCodModified=false;
    myPenWidth = 3;
    myPenColor = Qt::blue;
}

//! This will load the image from the filename provided
bool DrawWidget::openImage(const QString &fileName)
{    
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    //! This will scale the image to the rect wigth and height keeping Aspect ratio
    image = loadedImage.scaled(rect().width(), rect().height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation );
    update();
    isCodModified=false;
    isImageLoadedToWidget=true;
    return true;
}

//! Draws the rectangular portion source of the given image into the target rectangle in the paint device.
void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

//! Clears the loaded image.
void DrawWidget::clearImage()
{    
    if(!image.isNull())
    {
        image.fill(qRgb(255, 255, 255));
        pointList.clear();
        update();
        isCodModified=false;
        isImageLoadedToWidget=false;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("No Image to clear");
        msgBox.exec();
    }
}

//! Saves the Coordinates to the text file.
bool DrawWidget::saveCoordinatesToFile(const QString &fileName, const QString &imageName)
{
    if(pointList.count()>0)
    {
        // file save dialog
        QString dialogcaption = "Save in Text File";
        QString exportname = QFileDialog::getSaveFileName(this, dialogcaption, fileName, "*.txt");
        if (exportname.isEmpty()) return false;
        if (QFileInfo(exportname).suffix().isEmpty())
            exportname.append(".txt");

        /* Try and open a file for output */
        QString currentDate=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString coordinates="";
        QFile outputFile(exportname);
        outputFile.open(QIODevice::WriteOnly| QIODevice::Append);

        /* Check it opened OK */
        if(!outputFile.isOpen()){
            QMessageBox msgBox;
            msgBox.setText("The file you are trying to save is open.");
            msgBox.exec();
            return 1;
        }

        /* Point a QTextStream object at the file */
        QTextStream outStream(&outputFile);

        for (int count=0; count <pointList.count(); count ++)
        {
            /* Write the line to the file */
            if(count ==pointList.count()-1)
            {
                coordinates += "("+QString::number(pointList.at(count).x())+","+QString::number(pointList.at(count).y())+")";
            }
            else
            {
                coordinates += "("+QString::number(pointList.at(count).x())+","+QString::number(pointList.at(count).y())+"),";
            }
        }
        outStream << '\n'+ currentDate+","+imageName +","+coordinates + "\r\n" ;

        /* Close the file */
        outputFile.close();
        isCodModified=false;

        /*Display message for confirmation*/
        QMessageBox msgBox;
        msgBox.setText(" Coordinates Saved     ");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("   No coordinates to save  ");
        msgBox.exec();
    }
}

//! Exectues when left mouse button is pressed and draws the point on the image.
void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isImageLoadedToWidget)
    {
        lastPoint = event->pos();
        pointList.append(lastPoint);
        drawPointTo(event->pos());

        /*Sends the coordinates to mainwindow to display in status bar*/
        if(isImageLoadedToWidget)
        {
            int xPos= event->localPos().x();
            int yPos= event->localPos().y();
            emit sendCoordinates(xPos,yPos);
        }
    }
}

//! Sends the Coordinates to mainwindow to display to Status Bar.
void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(isImageLoadedToWidget)
    {
        int xPos= event->localPos().x();
        int yPos= event->localPos().y();
        emit sendCoordinates(xPos,yPos);
    }
}

//! Draws the point on the image and updates the Ui.
void DrawWidget::drawPointTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth));
    painter.drawPoint(endPoint);
    int rad = (myPenWidth / 2) + 2;
    update(QRect(endPoint,QSize(11, 16)).normalized()
           .adjusted(-rad, -rad, +rad, +rad));

    lastPoint = endPoint;
}

//! Drwas the polygon with the given coordinates
void DrawWidget::drawPolygon()
{
    if(pointList.count() >=3)
    {
        QPainter painter(&image);
        QPolygon mainPolygon(pointList);
        painter.setPen(Qt::green);
        painter.setBrush(Qt::green);
        painter.drawPolygon(mainPolygon,Qt::WindingFill);
        update();
        isCodModified=true;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Number of points should be >= 3 to draw polygon");
        msgBox.exec();
    }
}

//! Sets the pen color
void DrawWidget::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

//! sets the pen width
void DrawWidget::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}
