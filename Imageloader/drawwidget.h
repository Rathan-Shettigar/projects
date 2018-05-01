#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <qpainter.h>
#include <QPaintEvent>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent =0);

    bool openImage(const QString &fileName);
    bool saveCoordinatesToFile(const QString &fileName, const QString &imageName);
    void clearImage();
    void drawPolygon();
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    bool isCordinatesModified() const{ return isCodModified; }

    QVector<QPoint> pointList;

signals:
    void sendCoordinates(int x, int y);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawPointTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool isImageLoadedToWidget;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    bool isCodModified;
};

#endif // DRAWWIDGET_H
