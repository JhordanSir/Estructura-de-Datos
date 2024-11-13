#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "song.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Lista de canciones
    songListWidget = new QListWidget(this);
    mainLayout->addWidget(songListWidget);

    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    addButton = new QPushButton("Agregar Canción", this);
    removeButton = new QPushButton("Eliminar Canción", this);
    changeOrderButton = new QPushButton("Cambiar Orden", this);
    playRandomButton = new QPushButton("Reproducir Aleatorio", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(changeOrderButton);
    buttonLayout->addWidget(playRandomButton);

    mainLayout->addLayout(buttonLayout);

    centralWidget->setLayout(mainLayout);

    // Conexiones de los botones
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addSong);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSong);
    connect(changeOrderButton, &QPushButton::clicked, this, &MainWindow::changeOrder);
    connect(playRandomButton, &QPushButton::clicked, this, &MainWindow::playRandom);

    // Cargar canciones desde CSV
    loadSongsFromCSV("spotify_data.csv");
}

MainWindow::~MainWindow() {}

void MainWindow::loadSongsFromCSV(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo de canciones.");
        return;
    }

    QTextStream in(&file);
    in.readLine(); // Omitir la primera línea (encabezados)
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(",");

        if (values.size() < 20) continue;  // Asegurar que la línea esté completa

        Song song(values[1], values[2], values[3], values[4].toInt(), values[5].toInt(),
                  values[6], values[7].toFloat(), values[8].toFloat(), values[9].toInt(),
                  values[10].toFloat(), values[11].toInt(), values[12].toFloat(), values[13].toFloat(),
                  values[14].toFloat(), values[15].toFloat(), values[16].toFloat(), values[17].toFloat(),
                  values[18].toInt(), values[19].toInt());
        playlist.addSong(song);
    }
    file.close();

    // Actualizar la interfaz con las canciones
    updateSongList();
}

void MainWindow::updateSongList() {
    songListWidget->clear();
    QList<Song> songs = playlist.getSongs();
    for (const Song &song : songs) {
        songListWidget->addItem(song.trackName + " - " + song.artistName);
    }
}

void MainWindow::addSong() {
    bool ok;
    QString trackName = QInputDialog::getText(this, "Agregar Canción", "Nombre de la canción:", QLineEdit::Normal, "", &ok);
    if (!ok || trackName.isEmpty()) return;

    QString artistName = QInputDialog::getText(this, "Agregar Canción", "Nombre del artista:", QLineEdit::Normal, "", &ok);
    if (!ok || artistName.isEmpty()) return;

    QString trackId = QInputDialog::getText(this, "Agregar Canción", "ID de la canción:", QLineEdit::Normal, "", &ok);
    if (!ok || trackId.isEmpty()) return;

    // Crear una canción con valores predeterminados para el resto de los campos
    Song newSong(artistName, trackName, trackId,
                 0, // Popularity (int)
                 2020, // Year (int)
                 QString(""), // Genre (QString) - empty string
                 0.5f, // Danceability (float)
                 0.5f, // Energy (float)
                 0, // Key (int)
                 0.0f, // Loudness (float)
                 1, // Mode (int)
                 0.0f, // Speechiness (float)
                 0.0f, // Acousticness (float)
                 0.0f, // Instrumentalness (float)
                 0.0f, // Liveness (float)
                 0.0f, // Valence (float)
                 120.0f, // Tempo (float)
                 200000, // Duration (int)
                 4); // Time Signature (int)
    playlist.addSong(newSong);
    updateSongList();
}

void MainWindow::removeSong() {
    QListWidgetItem *item = songListWidget->currentItem();
    if (!item) return;

    QString trackName = item->text().split(" - ").first();
    // Buscar la canción en la lista y eliminarla
    playlist.removeSong(trackName);
    updateSongList();
}

void MainWindow::changeOrder() {
    bool ok;
    int currentPos = QInputDialog::getInt(this, "Cambiar Orden", "Posición actual:", 0, 0, playlist.getSongs().size() - 1, 1, &ok);
    if (!ok) return;

    int newPos = QInputDialog::getInt(this, "Cambiar Orden", "Nueva posición:", 0, 0, playlist.getSongs().size() - 1, 1, &ok);
    if (!ok) return;

    playlist.changeOrder(currentPos, newPos);
    updateSongList();
}

void MainWindow::playRandom() {
    QList<Song> songs = playlist.getSongs();
    if (songs.isEmpty()) {
        QMessageBox::information(this, "Reproducción Aleatoria", "No hay canciones en la lista.");
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(songs.size());
    Song randomSong = songs[randomIndex];
    QMessageBox::information(this, "Reproducción Aleatoria", "Reproduciendo: " + randomSong.trackName + " de " + randomSong.artistName);
}
