#include "MainWindow.h"
#include "VideoProcessor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QMessageBox>

using namespace MOOP;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    mediaPlayer->setVideoOutput(videoWidget);
    mainLayout->addWidget(videoWidget);

    QHBoxLayout* controls = new QHBoxLayout();
    btnLoadVideo = new QPushButton("Video Yukle", this);
    btnLoadImage = new QPushButton("Gorsel Yukle", this);
    comboProcessType = new QComboBox(this);
    comboProcessType->addItems({ "Renk Donusumu (Grayscale)", "Goruntu Harmanlama (Blending)" });
    comboMethod = new QComboBox(this);
    comboMethod->addItems({ "CPU (Tek Thread)", "CPU (Cok Thread)", "GPU (CUDA)" });
    btnStart = new QPushButton("Islemi Baslat", this);

    controls->addWidget(btnLoadVideo);
    controls->addWidget(btnLoadImage);
    controls->addWidget(comboProcessType);
    controls->addWidget(comboMethod);
    controls->addWidget(btnStart);
    mainLayout->addLayout(controls);

    chartView = new QChartView(this);
    mainLayout->addWidget(chartView);

    setCentralWidget(central);

    connect(btnLoadVideo, &QPushButton::clicked, this, &MainWindow::onLoadVideo);
    connect(btnLoadImage, &QPushButton::clicked, this, &MainWindow::onLoadImage);
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::onStartProcess);
}

void MainWindow::onLoadVideo() {
    videoPath = QFileDialog::getOpenFileName(this, "Video Sec", "", "Video Files (*.mp4 *.avi)");
    if (!videoPath.isEmpty()) {
QBarSet* set = new QBarSet("Sure (ms)");
        mediaPlayer->play();
    }
}

void MainWindow::onLoadImage() {
    imagePath = QFileDialog::getOpenFileName(this, "Gorsel Sec", "", "Image Files (*.png *.jpg *.bmp)");
}

void MainWindow::onStartProcess() {
    int processType = comboProcessType->currentIndex();

    if (videoPath.isEmpty() || (processType == 1 && imagePath.isEmpty())) {
        QMessageBox::warning(this, "Uyari", "Lutfen gerekli dosyalari yukleyin.");
        return;
    }

    double elapsedSingle = 0, elapsedMulti = 0, elapsedGpu = 0;
	VideoProcessor processor;

    if (processType == 0) { // Grayscale
        processor.processGrayscale(videoPath, 0, elapsedSingle);
        processor.processGrayscale(videoPath, 1, elapsedMulti);
        processor.processGrayscale(videoPath, 2, elapsedGpu);
    }
    else { // Blending
        processor.processBlending(videoPath, imagePath, 0, elapsedSingle);
        processor.processBlending(videoPath, imagePath, 1, elapsedMulti);
        processor.processBlending(videoPath, imagePath, 2, elapsedGpu);
    }

    QBarSet* set = new QBarSet("Sure (ms)");
    *set << elapsedSingle << elapsedMulti << elapsedGpu;

    QBarSeries* series = new QBarSeries();
    series->append(set);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Islem Yontemleri Sure Karsilastirmasi");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "CPU Tek" << "CPU Cok" << "GPU";
    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chartView->setChart(chart);
}
