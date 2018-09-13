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
    QMainWindow(parent),
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

    connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_obj_list_itemDoubleClicked(QListWidgetItem *item){
    //player->setMedia(item);
    ui->lbl_name->setText(item);
}

void MainWindow::on_actionOpen_triggered(){
    //Open a file, set it into the player, and play the file
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.*)");
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename));
    on_actionPlay_triggered();
    //Display name of the song
    ui->lbl_name->setText("Now playing: " + filename);
    ui->obj_list->addItem(filename);
}

void MainWindow::on_actionPlay_triggered(){
    player->play();
    ui->statusBar->showMessage("Playing...");
}

void MainWindow::on_actionPause_triggered(){
    player->pause();
    ui->statusBar->showMessage("Paused...");
}

void MainWindow::on_actionStop_triggered(){
    player->stop();
    ui->statusBar->showMessage("Stopped");
}


