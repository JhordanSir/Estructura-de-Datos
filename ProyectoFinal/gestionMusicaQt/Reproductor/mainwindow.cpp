#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <vector>

// Incluye el espacio de nombres std para evitar prefijos como std::vector
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playlist(5) // Inicializa la lista de reproducción con el grado del B-Tree
{
    ui->setupUi(this);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Crear los widgets
    lineEditBuscar = new QLineEdit(this);
    lineEditID = new QLineEdit(this); // Inicializa lineEditID
    lineEditNombre = new QLineEdit(this);
    lineEditArtista = new QLineEdit(this);
    lineEditAlbum = new QLineEdit(this);
    lineEditDuracion = new QLineEdit(this);
    textEditResultados = new QTextEdit(this);
    btnBuscar = new QPushButton("Buscar", this);
    btnOrdenar = new QPushButton("Ordenar", this);
    btnReproducirAleatorio = new QPushButton("Reproducir Aleatorio", this);
    btnActualizar = new QPushButton("Actualizar", this);
    btnCargarArchivo = new QPushButton("Cargar Archivo CSV", this); // Nuevo botón para cargar el archivo CSV
    radioButtonArtista = new QRadioButton("Buscar por artista", this);
    comboBoxAtributo = new QComboBox(this);

    // Agregar opciones al comboBox
    comboBoxAtributo->addItems({"popularidad", "anio", "artista", "cancion", "genero", "duracion", "tempo"});

    // Configurar el diseño
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(new QLabel("Buscar:"));
    mainLayout->addWidget(lineEditBuscar);
    mainLayout->addWidget(radioButtonArtista);
    mainLayout->addWidget(btnBuscar);
    mainLayout->addWidget(new QLabel("Resultados:"));
    mainLayout->addWidget(textEditResultados);
    mainLayout->addWidget(new QLabel("Ordenar por atributo:"));
    mainLayout->addWidget(comboBoxAtributo);
    mainLayout->addWidget(btnOrdenar);
    mainLayout->addWidget(btnReproducirAleatorio);
    mainLayout->addWidget(btnActualizar);
    mainLayout->addWidget(btnCargarArchivo); // Añadir el botón al layout
    mainLayout->addWidget(new QLabel("ID:"));
    mainLayout->addWidget(lineEditID);
    mainLayout->addWidget(new QLabel("Nombre:"));
    mainLayout->addWidget(lineEditNombre);
    mainLayout->addWidget(new QLabel("Artista:"));
    mainLayout->addWidget(lineEditArtista);
    mainLayout->addWidget(new QLabel("Álbum:"));
    mainLayout->addWidget(lineEditAlbum);
    mainLayout->addWidget(new QLabel("Duración:"));
    mainLayout->addWidget(lineEditDuracion);

    // Conectar las señales a los slots
    connect(btnBuscar, &QPushButton::clicked, this, &MainWindow::on_btnBuscar_clicked);
    connect(btnOrdenar, &QPushButton::clicked, this, &MainWindow::on_btnOrdenar_clicked);
    connect(btnReproducirAleatorio, &QPushButton::clicked, this, &MainWindow::on_btnReproducirAleatorio_clicked);
    connect(btnActualizar, &QPushButton::clicked, this, &MainWindow::on_btnActualizar_clicked);
    connect(btnCargarArchivo, &QPushButton::clicked, this, &MainWindow::on_btnCargarArchivo_clicked); // Conectar el botón al slot

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBuscar_clicked()
{
    QString nombreBusqueda = lineEditBuscar->text();
    bool searchByArtist = radioButtonArtista->isChecked();

    // Llama al método buscarPorNombre y verifica que exista
    vector<Cancion> resultados = playlist.buscarPorNombre(nombreBusqueda.toStdString(), searchByArtist);

    textEditResultados->clear();
    if (!resultados.empty()) {
        for (const auto& cancion : resultados) {
            textEditResultados->append(
                QString::fromStdString(cancion.track_name + " - " + cancion.artist_name)
                );
        }
    } else {
        textEditResultados->append("No se encontraron resultados.");
    }
}

void MainWindow::on_btnOrdenar_clicked()
{
    QString atributo = comboBoxAtributo->currentText();

    // Llama al método ordenarPorAtributo y verifica que exista
    playlist.ordenarPorAtributo(atributo.toStdString());

    textEditResultados->clear();
    for (const auto& cancion : playlist.todasLasCanciones) {
        textEditResultados->append(
            QString::fromStdString(cancion.track_name + " - " + cancion.artist_name)
            );
    }
}

void MainWindow::on_btnReproducirAleatorio_clicked()
{
    // Llama al método reproduccionAleatoria y verifica que exista
    playlist.reproduccionAleatoria();
}

void MainWindow::on_btnActualizar_clicked()
{
    int id = lineEditID->text().toInt();

    // Verifica que los datos necesarios para crear la canción estén presentes
    Cancion nuevaCancion;
    nuevaCancion.track_name = lineEditNombre->text().toStdString();
    nuevaCancion.artist_name = lineEditArtista->text().toStdString();
    nuevaCancion.duration_ms = lineEditDuracion->text().toInt();

    // Llama al método actualizarCancion y verifica su resultado
    if (playlist.actualizarCancion(id, nuevaCancion)) {
        QMessageBox::information(this, "Actualización", "Canción actualizada correctamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se encontró la canción con el ID especificado.");
    }
}

void MainWindow::on_btnCargarArchivo_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir Archivo CSV", "", "Archivos CSV (*.csv)");
    if (!fileName.isEmpty()) {
        playlist.cargarCSV(fileName.toStdString());
        QMessageBox::information(this, "Carga de Archivo", "Archivo CSV cargado correctamente.");
    }
}
