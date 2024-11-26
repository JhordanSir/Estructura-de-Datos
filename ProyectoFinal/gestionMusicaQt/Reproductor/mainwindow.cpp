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
    buscarLayout = new QHBoxLayout();
    atributosLayout = new QHBoxLayout();
    botonesLayout = new QHBoxLayout();
    actualizarLayout = new QHBoxLayout();

    // Añadir widgets al layout de búsqueda
    buscarLayout->addWidget(new QLabel("Buscar:"));
    buscarLayout->addWidget(lineEditBuscar);
    buscarLayout->addWidget(radioButtonArtista);
    buscarLayout->addWidget(btnBuscar);

    // Añadir widgets al layout de atributos
    atributosLayout->addWidget(new QLabel("Ordenar por atributo:"));
    atributosLayout->addWidget(comboBoxAtributo);
    atributosLayout->addWidget(btnOrdenar);

    // Añadir widgets al layout de botones
    botonesLayout->addWidget(btnReproducirAleatorio);
    botonesLayout->addWidget(btnCargarArchivo);

    // Añadir widgets al layout de actualización
    actualizarLayout->addWidget(new QLabel("ID:"));
    actualizarLayout->addWidget(lineEditID);
    actualizarLayout->addWidget(new QLabel("Nombre:"));
    actualizarLayout->addWidget(lineEditNombre);
    actualizarLayout->addWidget(new QLabel("Artista:"));
    actualizarLayout->addWidget(lineEditArtista);
    actualizarLayout->addWidget(new QLabel("Álbum:"));
    actualizarLayout->addWidget(lineEditAlbum);
    actualizarLayout->addWidget(new QLabel("Duración:"));
    actualizarLayout->addWidget(lineEditDuracion);
    actualizarLayout->addWidget(btnActualizar);

    // Añadir layouts al layout principal
    mainLayout->addLayout(buscarLayout);
    mainLayout->addWidget(new QLabel("Resultados:"));
    mainLayout->addWidget(textEditResultados);
    mainLayout->addLayout(atributosLayout);
    mainLayout->addLayout(botonesLayout);
    mainLayout->addLayout(actualizarLayout);


    // Aplicar estilos CSS
    QString styleSheet = "QLineEdit {"
                         "  border: 2px solid #1E90FF;" // Azul metálico
                         "  border-radius: 10px;"
                         "  padding: 0 8px;"
                         "  background: #000000;" // Negro
                         "  color: #FFFFFF;" // Texto blanco
                         "  selection-background-color: #4682B4;" // Azul metálico oscuro
                         "}"
                         "QPushButton {"
                         "  border: 2px solid #1E90FF;" // Azul metálico
                         "  border-radius: 10px;"
                         "  padding: 6px 12px;"
                         "  background: #000000;" // Negro
                         "  color: #FFFFFF;" // Texto blanco
                         "}"
                         "QRadioButton {"
                         "  padding: 6px 12px;"
                         "  color: #FFFFFF;" // Texto blanco
                         "}"
                         "QComboBox {"
                         "  border: 2px solid #1E90FF;" // Azul metálico
                         "  border-radius: 10px;"
                         "  padding: 6px 12px;"
                         "  background: #000000;" // Negro
                         "  color: #FFFFFF;" // Texto blanco
                         "}"
                         "QTextEdit {"
                         "  border: 2px solid #1E90FF;" // Azul metálico
                         "  border-radius: 10px;"
                         "  padding: 6px 12px;"
                         "  background: #000000;" // Negro
                         "  color: #FFFFFF;" // Texto blanco
                         "}";
    setStyleSheet(styleSheet);


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
        if (atributo == "popularidad") {
            textEditResultados->append(
                QString::fromStdString(to_string(cancion.popularity) + " - " + cancion.track_name)
                );
        } else if (atributo == "anio") {
            textEditResultados->append(
                QString::fromStdString(to_string(cancion.year) + " - " + cancion.track_name)
                );
        } else if (atributo == "artista") {
            textEditResultados->append(
                QString::fromStdString(cancion.artist_name + " - " + cancion.track_name)
                );
        } else if (atributo == "cancion") {
            textEditResultados->append(
                QString::fromStdString(cancion.track_name)
                );
        } else if (atributo == "genero") {
            textEditResultados->append(
                QString::fromStdString(cancion.genre + " - " + cancion.track_name)
                );
        } else if (atributo == "duracion") {
            textEditResultados->append(
                QString::fromStdString(to_string(cancion.duration_ms) + " ms - " + cancion.track_name)
                );
        } else if (atributo == "tempo") {
            textEditResultados->append(
                QString::fromStdString(to_string(cancion.tempo) + " - " + cancion.track_name)
                );
        }
    }
}

void MainWindow::on_btnReproducirAleatorio_clicked()
{
    // Llama al método reproduccionAleatoria y verifica que exista
    Cancion cancion = playlist.reproduccionAleatoria();

    textEditResultados->clear();
    textEditResultados->append(
        QString::fromStdString(cancion.track_name + " - " + cancion.artist_name)
        );
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
