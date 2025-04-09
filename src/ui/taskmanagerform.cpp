#include "taskmanagerform.h"

TaskManagerForm::TaskManagerForm(Database &db, Auth &auth, QWidget *parent)
	: QWidget(parent), db(db), auth(auth) {
	QVBoxLayout *layout = new QVBoxLayout(this);

	taskEdit = new QLineEdit(this);
	taskEdit->setPlaceholderText("Enter new task");

	addButton = new QPushButton(this);
	connect(addButton, &QPushButton::clicked, this, &TaskManagerForm::addTask);

	removeButton = new QPushButton(this);
	connect(removeButton, &QPushButton::clicked, this, &TaskManagerForm::removeTask);

	taskList = new QListWidget(this);

	layout->addWidget(taskEdit);
	layout->addWidget(addButton);
	layout->addWidget(removeButton);
	layout->addWidget(taskList);

	setLayout(layout);

	loadTasks();
}

TaskManagerForm::~TaskManagerForm() {
	//It can be empty, but if needed, it can contain code to clean up resources.
}

void TaskManagerForm::addTask() {
	QString task = taskEdit->text();

	if (task.isEmpty()) {
		QMessageBox::warning(this, "Add task failed", "Please, enter a task.");
		return;
	}

	if (db.addTask(auth.getCurrentUser(), task.toStdString())) {
		taskList->addItem(task);
		taskEdit->clear();
	} else {
		QMessageBox::warning(this, "Add task failde", "Failed to add taskt yo the datatbase");
	}
}

void TaskManagerForm::removeTask() {
	QListWidgetItem *item = taskList->currentItem();

	if (!item) {
		QMessageBox::warning(this, "Remove task failed", "Please, select a task to remove.");
	}

	QString task = item->text();

	if (db.removeTask(auth.getCurrentUser(), task.toStdString())) {
		delete item;
	} else {
		QMessageBox::warning(this, "Remove task failde", "Failed to remove task from the database.");
	}
}

void TaskManagerForm::loadTasks() {
	taslList->clear();

	std::vector<std::string> tasks = db.getTasks(auth.getCurrentUser());

	for (const auto &task : tasks) {
		taskList->addItem(QString::fromStdString(task));
	}
}