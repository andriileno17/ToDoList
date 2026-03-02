#include "taskmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

void TaskManager::save(const QVector<ToDoPage>& pages, const QString& filepath){
    QJsonArray rootArray;
    for (const auto& page : pages){
        QJsonObject pageObj;
        pageObj["name"] = page.name;

        QJsonArray taskArray;
        for (const auto& task : page.tasks){
            QJsonObject taskObj;
            taskObj["title"] = task.title;
            taskObj["done"] = task.isDone;
            taskArray.append(taskObj);
        }

        pageObj["tasks"] = taskArray;
        rootArray.append(pageObj);
    }

    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly)){
        file.write(QJsonDocument(rootArray).toJson());
    }
}

QVector<ToDoPage> TaskManager::load(const QString& filepath){
    QVector<ToDoPage> pages;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly))return pages;

    QJsonArray rootArray = QJsonDocument::fromJson(file.readAll()).array();
    for(int i = 0; i < rootArray.size(); ++i){
        QJsonObject pageObj = rootArray[i].toObject();
        ToDoPage page;
        page.name = pageObj["name"].toString();
        QJsonArray tasksArray = pageObj["tasks"].toArray();
        for(int j = 0; j < tasksArray.size(); ++j){
            QJsonObject taskObj = tasksArray[j].toObject();
            page.tasks.append({taskObj["title"].toString(), taskObj["done"].toBool()});
        }
        pages.append(page);
    }
    return pages;
}