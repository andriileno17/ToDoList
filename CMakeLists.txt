cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

add_executable(ToDoList
    src/main.cpp
    src/models.h
    src/TaskManager/taskmanager.cpp
    src/TaskManager/taskmanager.h
    src/ToDoPage/todopage.cpp
    src/ToDoPage/todopage.h
    MainWindow/mainwindow.cpp
    MainWindow/mainwindow.h
)

target_link_libraries(ToDoList Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)