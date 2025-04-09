cmake_minimum_required(VERSION 3.16)

project(ToDoTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Додаємо підтримку автоматичного запуску MOC, UIC і RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Знаходимо необхідні пакети
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)

# Перевіряємо, чи знайдений SQLite3
if (SQLite3_FOUND)
    message(STATUS "SQLite3 found: ${SQLite3_VERSION}")
    message(STATUS "SQLite3 include dirs: ${SQLite3_INCLUDE_DIRS}")
    message(STATUS "SQLite3 libraries: ${SQLite3_LIBRARIES}")
else()
    message(FATAL_ERROR "SQLite3 not found")
endif()

# Вказуємо шляхи до вихідних файлів
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Створюємо виконуваний файл
add_executable(ToDoTest ${SOURCES} ${HEADERS})

# Підключаємо бібліотеки
target_link_libraries(ToDoTest PRIVATE Qt6::Widgets OpenSSL::SSL OpenSSL::Crypto ${SQLite3_LIBRARIES})

# Вказуємо шляхи до заголовкових файлів
target_include_directories(ToDoTest PRIVATE include ${SQLite3_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

# Додаємо більше інформації про проект
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# Встановлюємо виконуваний файл
install(TARGETS ToDoTest DESTINATION bin)