#ifndef TODOPAGE_H
#define TODOPAGE_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include "../models.h"

class TodoPageView : public QWidget{
    Q_OBJECT

public:
    explicit TodoPageView(QWidget *parent = nullptr);
    void loadPage(ToDoPage *pageData);

signals:
    void backRequested();
    void dataModified();

private slots:
    void onAddTaskClicked();
    void onItemChanged(QListWidgetItem *item);

private:
    ToDoPage *m_currentPage;
    QLabel *m_titleLabel;
    QListWidget *m_tasksList;
    QPushButton *m_btnAdd;
    QPushButton *m_btnBack;

    void refreshList();
};

#endif