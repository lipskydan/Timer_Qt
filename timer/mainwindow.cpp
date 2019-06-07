#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerForMainClock = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    connect(timerForMainClock, SIGNAL(timeout()), this, SLOT(start_clock())); // Подключаем сигнал таймера к нашему слоту
    if (timerForMainClock != NULL)
        timerForMainClock->start(1000);

    timerForTimer = NULL;
    timerForAlarm = NULL;

    iForGrid_timer = 0;
    jForGrid_timer = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timerForTimer;
}


void MainWindow::on_createTimer_clicked()
{
    TimeLeft* newTimer = new TimeLeft;
    newTimer->hours = ui->hourEdit->text().toInt();
    newTimer->minutes = ui->minuteEdit->text().toInt();
    newTimer->seconds = ui->secondEdit->text().toInt();

    setSoundNumber(newTimer);

    timeLeft.push_back(newTimer);

    QString time = ui->hourEdit->text() + " : " + ui->minuteEdit->text() + " : " + ui->secondEdit->text();

    QLabel* label = new QLabel(time);
    labels_timer.push_back(label);

    ui->gridLayoutTimer->addWidget(label, iForGrid_timer, jForGrid_timer);

    if (iForGrid_timer == 4)
    {
        jForGrid_timer++;
        iForGrid_timer = 0;
    } else {
        iForGrid_timer++;
    }
}

int MainWindow::reduceTime(TimeLeft* timeLeft)
{
    if (timeLeft->seconds > 0)
        timeLeft->seconds--;
    else if (timeLeft->seconds == 0)
    {
        if (timeLeft->minutes > 0)
        {
            timeLeft->minutes--;
        }
        else if (timeLeft->minutes == 0)
        {
            if (timeLeft->hours > 0)
            {
                timeLeft->hours--;
                timeLeft->minutes = 59;
            }
            else if (timeLeft->hours == 0)
            {
                return -1;
            }
        }
        timeLeft->seconds = 59;
    }
    return 1;
}
void MainWindow::updateAlarm()
{
    // For alarms
    for (int i = 0; i < ui->gridLayoutAlarm->count(); i++)
    {
        QString result;
        QTime alarmTime(alarmLeft[i]->hours, alarmLeft[i]->minutes, alarmLeft[i]->seconds);

        if (alarmTime.currentTime().toString() == alarmTime.toString())
        {
                on_finish(alarmLeft[i]);
                result = "finish";
                labels_alarm[i]->setText(result);
        }
    }
}
void MainWindow::updateTimer()
{
    // For timers
    for (int i = 0; i < ui->gridLayoutTimer->count(); i++)
    {
        if (timeLeft[i]->was_played)
            continue;
        QString result;
        if (reduceTime(timeLeft[i]) == -1)
        {
                on_finish(timeLeft[i]);
                result = "finish";
                timeLeft[i]->was_played = true;
        } else {
                result =    QString::number(timeLeft[i]->hours) + " : " +
                            QString::number(timeLeft[i]->minutes) + " : " +
                            QString::number(timeLeft[i]->seconds);
        }

        labels_timer[i]->setText(result);
    }
}

void MainWindow::on_finish(TimeLeft* obj)
{
    if (ui->doNotDisturb->isChecked() == false)
    {
        QString sound_name = "/Users/danial/timer/";
        sound_name += QString::number(obj->sound_number) + ".wav";
        melody = new QSound(sound_name);
        melody->play();
    }
}

void MainWindow::setSoundNumber(TimeLeft* obj)
{
    if (ui->radioButton_1->isChecked() == true)
    {
        obj->sound_number = 1;
    } else if (ui->radioButton_2->isChecked() == true)
    {
        obj->sound_number = 2;
    } else if (ui->radioButton_3->isChecked() == true)
    {
        obj->sound_number = 3;
    } else if (ui->radioButton_4->isChecked() == true)
    {
        obj->sound_number = 4;
    }
}

void MainWindow::start_clock()
{
    QTime curr_time = curr_time.currentTime();
    ui->label_5->setText(curr_time.toString());
}

void MainWindow::on_stopSound_clicked()
{
    melody->stop();
}

void MainWindow::on_startTimer_clicked()
{
    timerForTimer = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    connect(timerForTimer, SIGNAL(timeout()), this, SLOT(updateTimer())); // Подключаем сигнал таймера к нашему слоту

    if (timerForTimer != NULL)
        timerForTimer->start(1000);

    ui->startTimer->deleteLater();
}

void MainWindow::on_startAlarm_clicked()
{
    timerForAlarm = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    connect(timerForAlarm, SIGNAL(timeout()), this, SLOT(updateAlarm())); // Подключаем сигнал таймера к нашему слоту

    if (timerForAlarm != NULL)
        timerForAlarm->start(1000);

    ui->startAlarm->deleteLater();
}

void MainWindow::on_createAlarm_clicked()
{
    TimeLeft* newAlarm = new TimeLeft;
    newAlarm->hours = ui->hourEdit->text().toInt();
    newAlarm->minutes = ui->minuteEdit->text().toInt();
    newAlarm->seconds = ui->secondEdit->text().toInt();

    setSoundNumber(newAlarm);

    alarmLeft.push_back(newAlarm);

    QString time = ui->hourEdit->text() + " : " + ui->minuteEdit->text() + " : " + ui->secondEdit->text();

    QLabel* label = new QLabel(time);
    labels_alarm.push_back(label);

    ui->gridLayoutAlarm->addWidget(label, iForGrid_alarm, jForGrid_alarm);

    if (iForGrid_alarm == 4)
    {
        jForGrid_alarm++;
        iForGrid_alarm = 0;
    } else {
        iForGrid_alarm++;
    }
}
