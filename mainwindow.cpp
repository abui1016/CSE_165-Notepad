#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

//the following static variables are used to check if the bold and italics button are pressed
//if true, then the code should turn these options off.
static bool boldValid = false;
static bool italicValid = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Linking the font operations to the appropriate function
    // Used lab7 as a guide for button operations
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
    connect(ui->getCounts, SIGNAL(released()), this, SLOT(on_actionWord_Count_triggered()));

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

/*
 * Creating a new file.
 * - It first calls on_actionSave_triggered() to save the current file before making a new one
 * - Once saved, it will clear the current file
*/
void MainWindow::on_actionNew_triggered()
{
    on_actionSave_triggered();
    currFile.clear();
    ui->textEdit->setText(QString());
}

/*
 *  Open another file
 *  - It first searches for the file then it opens it
 *  - QFileDialog allows the user to access the file directory and select files they desire to work with
 *  - QIODevice allows data to be written and read
 */
void MainWindow::on_actionOpen_triggered()
{
    QString fileContent;
    QString filename= QFileDialog::getOpenFileName(this, "Open File");

    //if the user hasn't put in a file name, then just stop the process
   if(filename.isEmpty()){
       return;
   }

    //open the file with Read/Write privileges
   QFile file(filename);
   if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
   {
       return;
   }

   QTextStream in(&file);

    //open the file, save all the data in a string, close the file, then add the text into the UI
    fileContent= in.readAll();
    file.close();
    ui->textEdit->clear();
    ui->textEdit->setPlainText(fileContent);
}

/*
 * Save current file
 */
void MainWindow::on_actionSave_triggered()
{
    //use QFileDialog to work with the filesystem
    QString filename= QFileDialog::getSaveFileName(this, "Save");

    //if the user inputs no name, stop the process
    if (filename.isEmpty()){
           return;
    }

    QFile file(filename);
    //Open the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << ui->textEdit->toPlainText() << "\n";

    file.close();
}

/*
 * Get the word and character count in the file
 * - When the Get Counts button is pressed, it will analyze/ parse the file and count the amount of words and characters in the file
*/
void MainWindow::on_actionWord_Count_triggered()
{
    int word_count=0;  // store the number of word
    int char_count=0;  // store the number of character

    // get the text as a string fron the text edit
    QString text = ui->textEdit->toPlainText();

    // method to remove the white space at the start and end, and cut any sequence of white space into one.
    text = text.simplified();

    // check and remove the white space and the return line (\n) at the start, end of the Qstring
    while(text.endsWith(' ') || text.endsWith('\n')){
        text.chop(1);
    }

    // Here we count the number of white space which is the number of word
    word_count = 1+text.count(QLatin1Char(' ')) + text.count(QLatin1Char('\n'));
    char_count= ui->textEdit->toPlainText().length();

   if (char_count==0){
       word_count=0;
   }

   ui->wordCounter->setText("Word Count: " + QString::number(word_count));
   ui->characterCounter->setText("Character Count: " + QString::number(char_count));

}
/* Change the font color
 *  After choosing a button and operations are done, make the setChecked to false. This allows other buttons to be pressed
 *  - Used the QT documentation for QTextEdit to figure out the operations available for the font in a QTextEdit:
 *      https://stackoverflow.com/questions/9554435/qtextedit-background-color-change-also-the-color-of-scrollbar
*/
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
    //if global variable bold valid is true, then the bold is turned on and needs to be turned off
    if (ui->boldOption->isChecked() && boldValid == true){
        ui->textEdit->setFontWeight(1);
        boldValid = false;
        ui->boldOption->setChecked(false);
        return;
    }
    //if boldValid is false, then the bold option is turned off and should be turned on
    if (ui->boldOption->isChecked() && boldValid == false){
        ui->textEdit->setFontWeight(70);
        ui->boldOption->setChecked(false);
        boldValid = true;
    }

    //if italic option picked, set the following text to italic.
    //if global variable is true, then the italics is turned on and needs to be turned off
    if (ui->italicsOption->isChecked() && italicValid == true){
        ui->textEdit->setFontItalic(false);
        italicValid = false;
        ui->italicsOption->setChecked(false);
        return;
    }
    //if italicValid is true, then the italic options is turned off and should be turned on.
    if (ui->italicsOption->isChecked() && italicValid == false){
        ui->textEdit->setFontItalic(true);
        ui->italicsOption->setChecked(false);
        italicValid = true;
    }
}

/*
 *  Change the font face. The following is called when the user presses on a new font in the drop down menu
 *   it calls this event which changes the font face for the entire text in the text editor
 *   - Used the following Youtube link to learn how to use a fontDropDown:
 *      https://stackoverflow.com/questions/9554435/qtextedit-background-color-change-also-the-color-of-scrollbar
 *   - Used same idea for the font size drop down.
*/
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

/*
 *  Change the text alignment
*/
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

/*
 *  Change the UI Theme between light and dark mode.
 *  - Used the following link to figure out how to change the color of a QTextEdit:
 *      https://stackoverflow.com/questions/9554435/qtextedit-background-color-change-also-the-color-of-scrollbar
*/
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
