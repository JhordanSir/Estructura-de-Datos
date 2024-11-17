#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "playlist.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Playlist playlist;
    QListWidget *songListWidget;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *changeOrderButton;
    QPushButton *playRandomButton;

    void loadSongsFromCSV(const QString &fileName);
    void updateSongList();

private slots:
    void addSong();
    void removeSong();
    void changeOrder();
    void playRandom();
};

#endif // MAINWINDOW_H
