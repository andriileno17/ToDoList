#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "../models.h"
#include <QVector>
#include <QString>

class TaskManager {
public:
    static void save(const QVector<ToDoPage>& pages, const QString& filepath = "todo_storage.json");
    static QVector<ToDoPage> load(const QString& filepath = "todo_storage.json");
};

#endif // TASKMANAGER_H