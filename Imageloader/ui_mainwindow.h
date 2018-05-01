/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_image;
    QAction *action_clearImage;
    QAction *actionSave_Image;
    QAction *actionExit;
    QAction *actionSet_penColor;
    QAction *actionSet_penWidth;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *frame_Title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_title;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_LoadImage;
    QPushButton *pushButton_drawPolygon;
    QPushButton *pushButton_ResetImage;
    QPushButton *pushButton_clearImage;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_saveCordinatesInDB;
    QPushButton *pushButton_SaveImage;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(990, 300);
        actionLoad_image = new QAction(MainWindow);
        actionLoad_image->setObjectName(QStringLiteral("actionLoad_image"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/Icons/icons8-add-image-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_image->setIcon(icon);
        action_clearImage = new QAction(MainWindow);
        action_clearImage->setObjectName(QStringLiteral("action_clearImage"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/Icons/icons8-delete-filled-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_clearImage->setIcon(icon1);
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName(QStringLiteral("actionSave_Image"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/Icons/icons8-save-as-filled-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Image->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/Icons/icons8-exit-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionSet_penColor = new QAction(MainWindow);
        actionSet_penColor->setObjectName(QStringLiteral("actionSet_penColor"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icons/Icons/icons8-compose-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_penColor->setIcon(icon4);
        actionSet_penWidth = new QAction(MainWindow);
        actionSet_penWidth->setObjectName(QStringLiteral("actionSet_penWidth"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Icons/Icons/icons8-width-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSet_penWidth->setIcon(icon5);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Icons/Icons/icons8-about-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon6);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Icons/Icons/icons8-qt-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon7);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame_Title = new QFrame(centralWidget);
        frame_Title->setObjectName(QStringLiteral("frame_Title"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_Title->sizePolicy().hasHeightForWidth());
        frame_Title->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(88, 88, 88, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(118, 116, 108, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        frame_Title->setPalette(palette);
        frame_Title->setAutoFillBackground(true);
        frame_Title->setStyleSheet(QStringLiteral(""));
        frame_Title->setFrameShape(QFrame::StyledPanel);
        frame_Title->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_Title);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_title = new QLabel(frame_Title);
        label_title->setObjectName(QStringLiteral("label_title"));
        sizePolicy.setHeightForWidth(label_title->sizePolicy().hasHeightForWidth());
        label_title->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label_title->setFont(font);
        label_title->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_title);


        gridLayout->addWidget(frame_Title, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 966, 119));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_LoadImage = new QPushButton(centralWidget);
        pushButton_LoadImage->setObjectName(QStringLiteral("pushButton_LoadImage"));
        QFont font1;
        font1.setPointSize(12);
        pushButton_LoadImage->setFont(font1);
        pushButton_LoadImage->setIcon(icon);
        pushButton_LoadImage->setIconSize(QSize(35, 35));

        horizontalLayout->addWidget(pushButton_LoadImage);

        pushButton_drawPolygon = new QPushButton(centralWidget);
        pushButton_drawPolygon->setObjectName(QStringLiteral("pushButton_drawPolygon"));
        pushButton_drawPolygon->setFont(font1);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Icons/Icons/icons8-polygon-filled-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_drawPolygon->setIcon(icon8);
        pushButton_drawPolygon->setIconSize(QSize(35, 35));

        horizontalLayout->addWidget(pushButton_drawPolygon);

        pushButton_ResetImage = new QPushButton(centralWidget);
        pushButton_ResetImage->setObjectName(QStringLiteral("pushButton_ResetImage"));
        pushButton_ResetImage->setFont(font1);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Icons/Icons/icons8-synchronize-filled-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_ResetImage->setIcon(icon9);
        pushButton_ResetImage->setIconSize(QSize(35, 35));

        horizontalLayout->addWidget(pushButton_ResetImage);

        pushButton_clearImage = new QPushButton(centralWidget);
        pushButton_clearImage->setObjectName(QStringLiteral("pushButton_clearImage"));
        pushButton_clearImage->setFont(font1);
        pushButton_clearImage->setIcon(icon1);
        pushButton_clearImage->setIconSize(QSize(35, 35));

        horizontalLayout->addWidget(pushButton_clearImage);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox_saveCordinatesInDB = new QCheckBox(centralWidget);
        checkBox_saveCordinatesInDB->setObjectName(QStringLiteral("checkBox_saveCordinatesInDB"));
        checkBox_saveCordinatesInDB->setFont(font1);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Icons/Icons/icons8-database-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        checkBox_saveCordinatesInDB->setIcon(icon10);
        checkBox_saveCordinatesInDB->setIconSize(QSize(35, 35));

        horizontalLayout->addWidget(checkBox_saveCordinatesInDB);

        pushButton_SaveImage = new QPushButton(centralWidget);
        pushButton_SaveImage->setObjectName(QStringLiteral("pushButton_SaveImage"));
        pushButton_SaveImage->setFont(font1);
        pushButton_SaveImage->setIcon(icon2);
        pushButton_SaveImage->setIconSize(QSize(35, 35));

        horizontalLayout->addWidget(pushButton_SaveImage);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 990, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QFont font2;
        font2.setPointSize(12);
        font2.setItalic(false);
        statusBar->setFont(font2);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionLoad_image);
        menuFile->addAction(action_clearImage);
        menuFile->addAction(actionSave_Image);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSettings->addAction(actionSet_penColor);
        menuSettings->addAction(actionSet_penWidth);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionLoad_image->setText(QApplication::translate("MainWindow", "Load image", Q_NULLPTR));
        action_clearImage->setText(QApplication::translate("MainWindow", "Clear Image", Q_NULLPTR));
        actionSave_Image->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionSet_penColor->setText(QApplication::translate("MainWindow", "Set Pen Color", Q_NULLPTR));
        actionSet_penWidth->setText(QApplication::translate("MainWindow", "Set Pen Width", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", Q_NULLPTR));
        label_title->setText(QApplication::translate("MainWindow", "Image Loader", Q_NULLPTR));
        pushButton_LoadImage->setText(QApplication::translate("MainWindow", "Load Image", Q_NULLPTR));
        pushButton_drawPolygon->setText(QApplication::translate("MainWindow", "Draw polygon", Q_NULLPTR));
        pushButton_ResetImage->setText(QApplication::translate("MainWindow", "Reset Coordinates", Q_NULLPTR));
        pushButton_clearImage->setText(QApplication::translate("MainWindow", "Clear Image", Q_NULLPTR));
        checkBox_saveCordinatesInDB->setText(QApplication::translate("MainWindow", "Save Cordinates in DB", Q_NULLPTR));
        pushButton_SaveImage->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
