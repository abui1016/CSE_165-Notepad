#include "search.h"
#include "ui_search.h"

#include <QDebug>
#include <QDirIterator>
#include <QMessageBox>

search::search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    connect(ui->OK_Button,SIGNAL(clicked()),this,SLOT(on_OK_Button_clicked()));
}

search::~search()
{
    delete ui;
}

void search::on_OK_Button_clicked()
{
    QString directory = ui->Directory->text(); //gets the dir and file names from the user input
    QString filename = ui->file_name->text();

    //QMessageBox::information(this, "OK Button", "is working"); //Debugging statement

    QDirIterator dirIt(directory, QDirIterator::Subdirectories); //searches folders and sub directories
    while(dirIt.hasNext()){
        dirIt.next();
        if(QFileInfo(dirIt.filePath()).isFile()){
            if(QFileInfo(dirIt.filePath()) == filename){
                qDebug()<<dirIt.filePath();
            }
        }
    }
}
