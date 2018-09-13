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


void MainWindow::on_actionOpen_triggered(){
    //Open a file, set it into the player, and play the file
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File (*.*)");
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename));
    on_actionPlay_triggered();
    //Display name of the song
    ui->lbl_name->setText("Now playing: " + filename);
}
