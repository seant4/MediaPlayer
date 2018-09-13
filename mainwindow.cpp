#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <objs.cpp>
#include <QtCore/QtPlugin>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QDial>
#include <QStyleFactory>
#include <QList>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),                                            //Creates player, and status bar in ui
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    volslidinit();                                                              
    bar = new QProgressBar(this);
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    ui->statusBar->addPermanentWidget(slider);
    ui->statusBar->addPermanentWidget(bar);

    connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);   //sets progress bar to music position
    connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);     

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);     //sets music position to slider position
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);
}

MainWindow::~MainWindow(){
    delete ui;
}
//WORK IN PROGRESS----------------------------------------------------
void MainWindow::on_obj_list_itemDoubleClicked(QListWidgetItem *item){
    //player->setMedia(item);
    ui->lbl_name->setText(item);
}
//---------------------------------------------------------------------
void MainWindow::on_actionOpen_triggered(){
    //Open a file, set it into the player, and play the file
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.*)"); //open file dialog
    on_actionStop_triggered();                                                           
    player->setMedia(QUrl::fromLocalFile(filename));        //Sets player media to song
    on_actionPlay_triggered();                              
    ui->lbl_name->setText("Now playing: " + filename);      //Sets now playing text to song destination
    ui->obj_list->addItem(filename);                        //Adds song to list
}

void MainWindow::on_actionPlay_triggered(){                 //Sets status bar label to playing when music is playing
    player->play();
    ui->statusBar->showMessage("Playing...");
}

void MainWindow::on_actionPause_triggered(){                //Sets status bar label to paused when music is paused
    player->pause();
    ui->statusBar->showMessage("Paused...");
}

void MainWindow::on_actionStop_triggered(){                //Sets Status bar lable to stopped when music is stopped
    player->stop();
    ui->statusBar->showMessage("Stopped");
}


