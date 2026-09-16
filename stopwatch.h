#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);

    bool isRunning() const;

public slots:
    void start();
    void stop();
    void reset();
    double addLap();

signals:
    void timeChanged(double seconds);
    void lapTimeReady(int lapNumber, double lapTime);

private slots:
    void onTick();

private:
    double currentMs() const;

    QTimer        *timer      = nullptr;
    QElapsedTimer  elapsed;
    double         totalMs    = 0.0;
    double         lastLapMs  = 0.0;
    int            lapCounter = 0;
};

#endif // STOPWATCH_H