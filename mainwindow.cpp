#include<QtGui>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->addBtn,SIGNAL(clicked()),this,SLOT(addFiles()));
    connect(this->ui->playBtn,SIGNAL(clicked()),this,SLOT(playFile()));
    connect(this->ui->pauseBtn,SIGNAL(clicked()),this,SLOT(pauseFile()));
    connect(this->ui->stopBtn,SIGNAL(clicked()),this,SLOT(stopFile()));
    connect(this->ui->furBtn,SIGNAL(clicked()),this,SLOT(furFile()));
    connect(this->ui->nextBtn,SIGNAL(clicked()),this,SLOT(nextFile()));
    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(this);
    seekSlider = new Phonon::SeekSlider(this);
    Phonon::createPath(mediaObject,audioOutput);
    seekSlider->setMediaObject(mediaObject);
    this->ui->seekLayout->addWidget(seekSlider);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
  default:
      break;
  }
}

void MainWindow::addFiles()
{
   QStringList files = QFileDialog::getOpenFileNames(this,tr("Selec File to play"));
   QString file;
foreach(file,files)
{
   this->ui->listWidget->addItem(file);
    sourceList.append(file);
}
}
void MainWindow::playFile()
{
  if(sourceList.isEmpty())
  {
       QMessageBox::information(this,tr("no music files"),tr("no files to play"));
       return;
  }
  mediaObject->setQueue(sourceList);
  mediaObject->play();
  this->ui->playBtn->setEnabled(false);
  this->ui->pauseBtn->setEnabled(true);
}
void MainWindow::pauseFile()
{
  mediaObject->pause();
  this->ui->pauseBtn->setEnabled(false);
  this->ui->playBtn->setEnabled(true);
}
void MainWindow::stopFile()
{
  mediaObject->stop();
  this->ui->pauseBtn->setEnabled(true);
  this->ui->playBtn->setEnabled(true);
}
void MainWindow::furFile()
{
    int index=sourceList.indexOf(mediaObject->currentSource());
    mediaObject->setCurrentSource(sourceList.at(index-1));
    mediaObject->play();
}
void MainWindow::nextFile()
{
    int index=sourceList.indexOf(mediaObject->currentSource());
    mediaObject->setCurrentSource(sourceList.at(index+1));
    mediaObject->play();
}
