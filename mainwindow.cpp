#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // textEdit will take up entire interface
}

MainWindow::~MainWindow()
{
    delete ui;
}

// New File
void MainWindow::on_actionNew_triggered()
{
    currFile.clear();
    ui->textEdit->setText(QString());
}

// Open another file (Search)
void MainWindow::on_actionOpen_triggered()
{

}

// Save current file
void MainWindow::on_actionSave_triggered()
{

}

// Copy highlighted text
void MainWindow::on_actionCopy_triggered()
{

}

// Cut highlighted text
void MainWindow::on_actionCut_triggered()
{

}

// Paste from clipboard
void MainWindow::on_actionPaste_triggered()
{

}

// Undo
void MainWindow::on_actionUndo_triggered()
{

}

// Get Word Count
void MainWindow::on_actionWord_Count_triggered()
{

}

// Change UI and theme
void MainWindow::on_actionTheme_triggered()
{

}


