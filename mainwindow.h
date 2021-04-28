#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionWord_Count_triggered();

    void on_action_font_color();

    void on_action_font_weight();

    void on_fontDropDown_currentFontChanged(const QFont &f);

    void on_fontSize_activated(const QString &arg1);

    void on_action_alignment();

    void on_action_UI_Theme();

private:
    Ui::MainWindow *ui;
    QString currFile = ""; // Blank filename to start off
};
#endif // MAINWINDOW_H
