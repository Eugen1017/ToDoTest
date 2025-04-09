#ifndef TASKMANEGERFORM_H
#define TASKMANEGERFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include "database.h"
#include "auth.h"

class TaskManagerForm : public QWidget {
	Q_OBJECT

public:
	TaskManagerForm(Database &database, Auth &auth, QWidget *parent = nullptr);
	~TaskManagerForm();

private slots:
	void addTask();
	void removeTask();
	void loadTasks();

private:
	Database &db;
	Auth &auth;
	QLineEdit *taskEdit;
	QPushButton *addButton;
	QPushButton *removeButton;
	QListWidget *taskList;
};

#endif