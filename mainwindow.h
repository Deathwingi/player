#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<Phonon>
#include<QListview>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void changeEvent(QEvent *e);
private slots:
    void addFiles();
    void playFile();
    void pauseFile();
    void stopFile();
    void furFile();
    void nextFile();
    void on_addBtn_clicked();

private:
    Ui::MainWindow *ui;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    Phonon::SeekSlider *seekSlider;
    QList<Phonon::MediaSource>sourceList;
};

#endif // MAINWINDOW_H

