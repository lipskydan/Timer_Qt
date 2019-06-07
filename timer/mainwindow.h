#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QVector>
#include <QSound>

namespace Ui {
class MainWindow;
}

struct TimeLeft {
    int hours;
    int minutes;
    int seconds;
    int sound_number;
    bool was_played = false;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timerForTimer;
    QTimer *timerForAlarm;
    QTimer *timerForMainClock;

    QVector<TimeLeft*> timeLeft;
    QVector<QLabel*> labels_timer;
    int iForGrid_timer;
    int jForGrid_timer;

    QVector<TimeLeft*> alarmLeft;
    QVector<QLabel*> labels_alarm;
    int iForGrid_alarm;
    int jForGrid_alarm;

    QSound* melody;
private slots:
    void updateTimer();
    void updateAlarm();
    void start_clock();
    int reduceTime(TimeLeft* timeLeft);
    void on_finish(TimeLeft* obj);
    void setSoundNumber(TimeLeft* obj);

    void on_createTimer_clicked();

    void on_stopSound_clicked();

    void on_startTimer_clicked();
    void on_startAlarm_clicked();
    void on_createAlarm_clicked();
};

#endif // MAINWINDOW_H
