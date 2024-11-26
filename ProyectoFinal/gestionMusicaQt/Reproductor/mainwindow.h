#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "D:\Estructura-de-Datos\ProyectoFinal\gestionMusicaConsola/playlist.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBuscar_clicked();
    void on_btnOrdenar_clicked();
    void on_btnReproducirAleatorio_clicked();
    void on_btnActualizar_clicked();
    void on_btnCargarArchivo_clicked(); // Nuevo slot para cargar el archivo CSV

private:
    Ui::MainWindow *ui;
    PlayList playlist;
    QLineEdit *lineEditBuscar;
    QLineEdit *lineEditID;
    QLineEdit *lineEditNombre;
    QLineEdit *lineEditArtista;
    QLineEdit *lineEditAlbum;
    QLineEdit *lineEditDuracion;
    QTextEdit *textEditResultados;
    QPushButton *btnBuscar;
    QPushButton *btnOrdenar;
    QPushButton *btnReproducirAleatorio;
    QPushButton *btnActualizar;
    QPushButton *btnCargarArchivo; // Nuevo botón para cargar el archivo CSV
    QRadioButton *radioButtonArtista;
    QComboBox *comboBoxAtributo;

    // Layout principal
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H
