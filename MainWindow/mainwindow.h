#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>
#include <QPushButton>
#include "../src/models.h"
#include "../src/ToDoPage/todopage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddPageClicked();
    void onPageDoubleClicked(QListWidgetItem *item);
    void showMainPage();
    void saveData();

private:
    QVector<ToDoPage> m_allData;
    QStackedWidget *m_stackedWidget;

    QWidget *m_mainWidget;
    QListWidget *m_pagesList;
    QPushButton *m_btnAddPage;

    TodoPageView *m_todoPageView;

    void setupUi();
    void refreshPagesList();
};

#endif