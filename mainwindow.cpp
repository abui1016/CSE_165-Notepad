#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "search.h"

#include <QDebug>
#include <QDirIterator>
#include <QLineEdit>
#include <QTextEdit>

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
    QString fileContent;

        QString filename= QFileDialog::getOpenFileName(this, "Open File");


       if(filename.isEmpty())
           return;

       QFile file(filename);

       if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
           return;

       QTextStream in(&file);

       fileContent= in.readAll();

       file.close();

       ui->textEdit->clear();
       ui->textEdit->setPlainText(fileContent);
}

// Save current file
void MainWindow::on_actionSave_triggered()
{
    QString filename= QFileDialog::getSaveFileName(this, "Save");

        if (filename.isEmpty())
            return;

        QFile file(filename);


        //Open the file
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);

        out << ui->textEdit->toPlainText() << "\n";

        file.close();
}

void MainWindow::on_actionSearch_triggered()
{
    search_box = new search(this);
    search_box->show();
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
    int word_count=0;  // store the number of word
    int char_count=0;  // store the number of character
  

    QString text=ui->textEdit->toPlainText();  // get the text as a string fron the text edit
    text=text.simplified();      // method to remove the white space at the start and end, and cut any sequence of white space into one.

    while(text.endsWith(' ')||text.endsWith('\n')) text.chop(1); // check and remove the white space and the return line (\n) at the satr, end of the Qstring
    

    word_count = 1+text.count(QLatin1Char(' ')) + text.count(QLatin1Char('\n')); // Here we count the number of white space which is the number of word

   char_count= ui->textEdit->toPlainText().length();// not useful

   if (char_count==0){
       word_count=0;
   }
    
    QString status = QString("Found %1 words:").arg(word_count);
    QMessageBox::information(this, tr("Info"), status);

}

// Change UI and theme
void MainWindow::on_actionTheme_triggered()
{

}


