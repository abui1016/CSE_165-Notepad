#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Linking the font operations to the appropriate function
    connect(ui->BlackColorOption, SIGNAL(released()), this, SLOT(on_action_font_color()));
    connect(ui->BlueColorOption, SIGNAL(released()), this, SLOT(on_action_font_color()));
    connect(ui->RedColorOption, SIGNAL(released()), this, SLOT(on_action_font_color()));
    connect(ui->boldOption, SIGNAL(released()), this, SLOT(on_action_font_weight()));
    connect(ui->italicsOption, SIGNAL(released()), this, SLOT(on_action_font_weight()));
    connect(ui->leftAlignOption, SIGNAL(released()), this, SLOT(on_action_alignment()));
    connect(ui->centerAlignOption, SIGNAL(released()), this, SLOT(on_action_alignment()));
    connect(ui->rightAlignOption, SIGNAL(released()), this, SLOT(on_action_alignment()));
    connect(ui->lightThemeOption, SIGNAL(released()), this, SLOT(on_action_UI_Theme()));
    connect(ui->darkThemeOption, SIGNAL(released()), this, SLOT(on_action_UI_Theme()));

    // let all of the buttons be checkable. This will let us check if a button was pressed
    ui->BlackColorOption->setCheckable(true);
    ui->BlueColorOption->setCheckable(true);
    ui->RedColorOption->setCheckable(true);
    ui->boldOption->setCheckable(true);
    ui->italicsOption->setCheckable(true);
    ui->leftAlignOption->setCheckable(true);
    ui->centerAlignOption->setCheckable(true);
    ui->rightAlignOption->setCheckable(true);
    ui->lightThemeOption->setCheckable(true);
    ui->darkThemeOption->setCheckable(true);

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

// Change the font color
// After choosing a button and operations are done, make the setChecked to false. This allows other buttons to be pressed
void MainWindow::on_action_font_color(){
    //if the black font color option checked, change the following text color to black
    if (ui->BlackColorOption->isChecked()){
        ui->textEdit->setTextColor(Qt::black);
        ui->BlackColorOption->setChecked(false);
    }
    //if the blue font color option checked, change the following text color to blue
    else if(ui->BlueColorOption->isChecked()){
        ui->textEdit->setTextColor(Qt::blue);
        ui->BlueColorOption->setChecked(false);
    }
    //if the red font color option checked, change the following text color to red
    else if(ui->RedColorOption->isChecked()){
        ui->textEdit->setTextColor(Qt::red);
        ui->RedColorOption->setChecked(false);
    }
}

// Change the font weight to bold or italics. Bold works sometimes... depends on the font chosen. Not all fonts let bold text
void MainWindow::on_action_font_weight(){
    //if bold option picked, set the following text to bold font
    if (ui->boldOption->isChecked()){
        ui->textEdit->setFontWeight(20);
        ui->boldOption->setChecked(false);
    }
    //if itlic option picked, set the following text to italic.
    if (ui->italicsOption->isChecked()){
        ui->textEdit->setFontItalic(true);
        ui->italicsOption->setChecked(false);
    }
}

// Change the font face. The following is called when the user presses on a new font in the drop down menu
// it calls this event which changes the font face for the entire text in the text editor
void MainWindow::on_fontDropDown_currentFontChanged(const QFont &f)
{
    ui->textEdit->setFont(f);
}

// Change the font size to the size specified in the size drop down menu
void MainWindow::on_fontSize_activated(const QString &arg1)
{
    int size = arg1.toInt();
    ui->textEdit->setFontPointSize(size);
}

// Change the text alignment
void MainWindow::on_action_alignment(){
    // if left alignment picked, move current text line to left
    if (ui->leftAlignOption->isChecked()){
        ui->textEdit->setAlignment(Qt::AlignLeft);
        ui->leftAlignOption->setChecked(false);
    }
    // if center alignment picked, move current text line to center
    else if (ui->centerAlignOption->isChecked()){
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->centerAlignOption->setChecked(false);
    }
    // if right alignment picked, move current text line to right
    else if (ui->rightAlignOption->isChecked()){
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->rightAlignOption->setChecked(false);
    }
}

// Change the UI Theme between light and dark mode
void MainWindow::on_action_UI_Theme(){
    // if light theme picked, set the background of the text entry to white
    if (ui->lightThemeOption->isChecked()){
        ui->textEdit->setStyleSheet("QTextEdit#textEdit { color: black; background-color: #ffffff }");

        ui->lightThemeOption->setChecked(false);
    }
    // if dark theme picked, set the background of the text entry to grey
    else if (ui->darkThemeOption->isChecked()){
        ui->textEdit->setStyleSheet("QTextEdit#textEdit { background-color: #2b2b29}");

        ui->darkThemeOption->setChecked(false);
    }
}
