#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &Stopwatch::onTick);
}

bool Stopwatch::isRunning() const
{
    return timer->isActive();
}

void Stopwatch::start()
{
    if (timer->isActive()) return;
    elapsed.restart();
    timer->start();
    emit timeChanged(currentMs() / 1000.0);
}

void Stopwatch::stop()
{
    if (!timer->isActive()) return;
    totalMs += elapsed.elapsed();
    timer->stop();
    emit timeChanged(totalMs / 1000.0);
}

void Stopwatch::reset()
{
    timer->stop();
    totalMs    = 0.0;
    lastLapMs  = 0.0;
    lapCounter = 0;
    emit timeChanged(0.0);
}

double Stopwatch::addLap()
{
    const double cur     = currentMs();
    const double lapTime = (cur - lastLapMs) / 1000.0;
    lastLapMs = cur;
    ++lapCounter;
    emit lapTimeReady(lapCounter, lapTime);
    return lapTime;
}

void Stopwatch::onTick()
{
    emit timeChanged(currentMs() / 1000.0);
}

double Stopwatch::currentMs() const
{
    if (timer->isActive())
        return totalMs + elapsed.elapsed();
    return totalMs;
}