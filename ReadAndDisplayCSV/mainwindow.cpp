#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a data model for the mapping table from a CSV file
    csvModel = new QStandardItemModel(this);
    csvModel->setSortRole(Qt::DisplayRole);
    ui->tableView->setModel(csvModel);

    //When item changes to update file
    QObject::connect(csvModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(itemChangedSlot(QStandardItem*)));

    //Variable initialisation
    filePath = "";
    isTextFound = false;
    skipFirst = true;

    //Set window to 70 % of available screen size.
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_actionSearch_triggered
 * Finds the exactly matched text and set background color to grey
 */
void MainWindow::on_actionSearch_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr(" Find "), "", QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
    {
        SetBackgroundColor(Qt::white);
        isTextFound = false;
        masterFoundItems.clear();
        for(int i=0; i< csvModel->columnCount() ; i++)
        {
            foundItems = csvModel->findItems(text,Qt::MatchExactly,i);
            masterFoundItems.append(foundItems);
        }
        SetBackgroundColor(Qt::gray);
        if(!isTextFound)
        {
            ShowMessageBox("Searched text could not be found", QMessageBox::Warning, "Find Text");
        }
    }
    else
    {
        ShowMessageBox("Searched text is empty or invalid", QMessageBox::Warning, "Find Text");
    }
}

/**
 * @brief MainWindow::SetBackgroundColor
 * @param text - find text
 * @param color - background color of text
 */
void MainWindow::SetBackgroundColor(QBrush color)
{
    csvModel->blockSignals(true);
    for(int j=0; j< masterFoundItems.count() ; j++)
    {
        isTextFound = true;
        masterFoundItems.at(j)->setBackground(color);
    }
    csvModel->blockSignals(false);
}

/**
 * @brief MainWindow::itemChangedSlot
 * @param item - Unused
 */
void MainWindow::itemChangedSlot(QStandardItem* item)
{
    Q_UNUSED(item);
    QFile f(filePath);
    if (f.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &f );
        QStringList strList;

        for( int r = 0; r < csvModel->rowCount() + 1; ++r )
        {
            strList.clear();
            for( int c = 0; c < csvModel->columnCount(); ++c )
            {
                //Writes header or item to file
                if(r==0)
                {
                    strList << csvModel->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString();
                }
                else
                {
                    strList << csvModel->item(r-1,c)->text();
                }
            }
            data << strList.join( "," )+"\n";
        }
    }
    else
    {
        ShowMessageBox("File path not found or file already open \n Close the file and save", QMessageBox::Critical, "File Exits or Open ");
    }
    f.close();
}

/**
 * @brief MainWindow::on_actionOpen_triggered
 */
void MainWindow::on_actionOpen_triggered()
{
    csvModel->clear();
    skipFirst = true;

    filePath = QFileDialog::getOpenFileName(this, "Open a file", "sample.csv", "CSV files (*.csv)");
    QFile file(filePath);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        ShowMessageBox("File not exists", QMessageBox::Critical, "File Not found");
    }
    else
    {
        QTextStream in(&file);
        //Reads the data up to the end of file
        while (!in.atEnd())
        {
            QString line = in.readLine();
            // Adding to the model in line with the elements
            QList<QStandardItem *> standardItemsList;
            // consider that the line separated by comma into columns
            for (QString item : line.split(",")) {
                standardItemsList.append(new QStandardItem(item));
            }
            if(!skipFirst)
            {
                csvModel->insertRow(csvModel->rowCount(), standardItemsList);
            }
            else
            {
                QStringList list;
                csvModel->setColumnCount(standardItemsList.count());

                for(int i=0; i< csvModel->columnCount() ; i++)
                {
                    list.append(standardItemsList.at(i)->text());
                }

                csvModel->setHorizontalHeaderLabels(list);
            }
            skipFirst = false;
        }
        file.close();
    }
}

/**
 * @brief MainWindow::on_actionSave_triggered
 */
void MainWindow::on_actionSave_triggered()
{
    itemChangedSlot(nullptr);
}

/**
 * @brief MainWindow::on_actionClear_triggered
 */
void MainWindow::on_actionClear_triggered()
{
    SetBackgroundColor(Qt::white);
    ui->tableView->selectionModel()->clear();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

/**
 * @brief MainWindow::ShowMessageBox
 * @param messageText - text string
 * @param icon - icon for message
 * @param title - window title
 */
void MainWindow::ShowMessageBox(QString messageText, QMessageBox::Icon icon, QString title)
{
    QMessageBox msgBox;
    msgBox.setText(messageText);
    msgBox.setWindowTitle(title);
    msgBox.setIcon(icon);
    msgBox.exec();
}

