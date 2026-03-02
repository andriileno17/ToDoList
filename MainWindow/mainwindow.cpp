#include "mainwindow.h"
#include "../src/TaskManager/taskmanager.h"
#include <QVBoxLayout>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_allData = TaskManager::load();
    setupUi();
    refreshPagesList();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    this->resize(400, 500);
    this->setWindowTitle("My Todo App");

    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(m_mainWidget);
    
    m_pagesList = new QListWidget(m_mainWidget);
    m_btnAddPage = new QPushButton("+ Створити новий список", m_mainWidget);
    
    mainLayout->addWidget(m_pagesList);
    mainLayout->addWidget(m_btnAddPage);
    
    m_stackedWidget->addWidget(m_mainWidget);

    m_todoPageView = new TodoPageView(this);
    m_stackedWidget->addWidget(m_todoPageView);

    connect(m_btnAddPage, &QPushButton::clicked, this, &MainWindow::onAddPageClicked);
    connect(m_pagesList, &QListWidget::itemDoubleClicked, this, &MainWindow::onPageDoubleClicked);
    
    connect(m_todoPageView, &TodoPageView::backRequested, this, &MainWindow::showMainPage);
    connect(m_todoPageView, &TodoPageView::dataModified, this, &MainWindow::saveData);
}

void MainWindow::refreshPagesList() {
    m_pagesList->clear();
    for (const auto& page : m_allData) {
        QString displayText = QString("%1 (Задач: %2)").arg(page.name).arg(page.tasks.size());
        m_pagesList->addItem(displayText);
    }
}

void MainWindow::onAddPageClicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Новий список", "Назва:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        m_allData.append({name, {}});
        refreshPagesList();
        saveData();
    }
}

void MainWindow::onPageDoubleClicked(QListWidgetItem *item) {
    int index = m_pagesList->row(item);
    if (index >= 0 && index < m_allData.size()) {
        m_todoPageView->loadPage(&m_allData[index]);
        m_stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::showMainPage() {
    refreshPagesList(); 
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::saveData() {
    TaskManager::save(m_allData);
}