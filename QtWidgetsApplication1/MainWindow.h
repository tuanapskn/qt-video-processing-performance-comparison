#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QtCharts/QChartView>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QString>


namespace MOOP {

    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow() = default;

    private slots:
        void onLoadVideo();
        void onLoadImage();
        void onStartProcess();

    private:
        QMediaPlayer* mediaPlayer;
        QVideoWidget* videoWidget;
        QPushButton* btnLoadVideo;
        QPushButton* btnLoadImage;
        QComboBox* comboProcessType;
        QComboBox* comboMethod;
        QPushButton* btnStart;
        QChartView* chartView;
        QString videoPath;
        QString imagePath;
    };

} // namespace MOOP
