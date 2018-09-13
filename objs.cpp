#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QtPlugin>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QDial>

void MainWindow::volslidinit(){
    dial = new QDial(this);
    dial->setRange(0, 100);
    dial->setFixedWidth(100);
    dial->setValue(100);
    ui->statusBar->addPermanentWidget(dial);
    int vol = 0;
    connect(dial, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));
    connect(dial, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    player->setVolume(vol);
}
