#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QVector>

struct Task{
    QString title;
    bool isDone;
};

struct ToDoPage{
    QString name;
    QVector<Task> tasks; 
};

#endif