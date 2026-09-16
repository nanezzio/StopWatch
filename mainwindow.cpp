#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stopwatch = new Stopwatch(this);

    connect(stopwatch, &Stopwatch::timeChanged,
            this, &MainWindow::updateTime);
    connect(stopwatch, &Stopwatch::lapTimeReady,
            this, &MainWindow::appendLap);

    connect(ui->startStopButton, &QPushButton::clicked,
            this, &MainWindow::onStartStopClicked);
    connect(ui->clearButton,     &QPushButton::clicked,
            this, &MainWindow::onClearClicked);
    connect(ui->lapButton,       &QPushButton::clicked,
            this, &MainWindow::onLapClicked);

    ui->lapButton->setEnabled(false);
    ui->startStopButton->setText(tr("Старт"));
    ui->timeLabel->setText(formatTime(0.0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartStopClicked()
{
    if (stopwatch->isRunning()) {
        stopwatch->stop();
        ui->startStopButton->setText(tr("Старт"));
        ui->lapButton->setEnabled(false);
    } else {
        stopwatch->start();
        ui->startStopButton->setText(tr("Стоп"));
        ui->lapButton->setEnabled(true);
    }
}

void MainWindow::onClearClicked()
{
    stopwatch->reset();
    ui->lapsBrowser->clear();
    ui->startStopButton->setText(tr("Старт"));
    ui->lapButton->setEnabled(false);
}

void MainWindow::onLapClicked()
{
    if (stopwatch->isRunning())
        stopwatch->addLap();
}

void MainWindow::updateTime(double seconds)
{
    ui->timeLabel->setText(formatTime(seconds));
}

void MainWindow::appendLap(int lapNumber, double lapTime)
{
    ui->lapsBrowser->append(
        tr("Круг %1, время: %2 сек")
            .arg(lapNumber)
            .arg(lapTime, 0, 'f', 1));
}

QString MainWindow::formatTime(double seconds)
{
    const int totalTenths = qRound(seconds * 10.0);
    const int tenths      = totalTenths % 10;
    const int totalSec    = totalTenths / 10;
    const int sec         = totalSec % 60;
    const int min         = (totalSec / 60) % 60;
    const int hour        = totalSec / 3600;

    return QString("%1:%2:%3.%4")
        .arg(hour, 2, 10, QChar('0'))
        .arg(min,  2, 10, QChar('0'))
        .arg(sec,  2, 10, QChar('0'))
        .arg(tenths);
}