#include "todopage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>

TodoPageView::TodoPageView(QWidget *parent) : QWidget(parent), m_currentPage(nullptr) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *headerLayout = new QHBoxLayout();
    m_btnBack = new QPushButton("< Назад", this);
    m_titleLabel = new QLabel("Назва сторінки", this);

    QFont titleFont = m_titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(14);
    m_titleLabel->setFont(titleFont);

    headerLayout->addWidget(m_btnBack);
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    m_tasksList = new QListWidget(this);
    m_btnAdd = new QPushButton("+ Додати задачу", this);

    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(m_tasksList);
    mainLayout->addWidget(m_btnAdd);

    connect(m_btnBack, &QPushButton::clicked, this, &TodoPageView::backRequested);
    connect(m_btnAdd, &QPushButton::clicked, this, &TodoPageView::onAddTaskClicked);
    connect(m_tasksList, &QListWidget::itemChanged, this, &TodoPageView::onItemChanged);
}

void TodoPageView::loadPage(ToDoPage *pageData){
    m_currentPage = pageData;
    m_titleLabel->setText(m_currentPage->name);
    refreshList();
}

void TodoPageView::refreshList(){
    m_tasksList->blockSignals(true);
    m_tasksList->clear();

    if(m_currentPage){
        for(const auto& task : m_currentPage->tasks){
            QListWidgetItem *item = new QListWidgetItem(task.title);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(task.isDone ? Qt::Checked : Qt::Unchecked);
            m_tasksList->addItem(item);
        }
    }
    m_tasksList->blockSignals(false);
}

void TodoPageView::onAddTaskClicked(){
    if(!m_currentPage) return;

    bool ok;
    QString title = QInputDialog::getText(this, "Нова задача", "Текст задачі: ", QLineEdit::Normal, "", &ok);
    if(ok && !title.isEmpty()){
        m_currentPage->tasks.append({title, false});
        refreshList();
        emit dataModified();
    }
}

void TodoPageView::onItemChanged(QListWidgetItem *item){
    if (!m_currentPage) return;

    int row = m_tasksList->row(item);
    if(row >= 0 && row < m_currentPage->tasks.size()){
        m_currentPage->tasks[row].isDone = (item->checkState() == Qt::Checked);
        emit dataModified();
    }
}