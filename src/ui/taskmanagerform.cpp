#include "taskmanagerform.h"
#include "task.h"

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
	QString taskTitle = taskEdit->text();

	if (taskTitle.isEmpty()) {
		QMessageBox::warning(this, "Add task failed", "Please, enter a task.");
		return;
	}

	Task newTask(0, taskTitle.toStdString());

	if (db.execute(newTask.toSQLInsert())) {
		taskList->addItem(taskTitle);
		taskEdit->clear();
	} else {
		QMessageBox::warning(this, "Add Task Failed", "Failed to add task to the database.");
	}
}

void TaskManagerForm::removeTask() {
	QListWidgetItem *selectedItem = taskList->currentItem();

	if (!selectedItem) {
		QMessageBox::warning(this, "Remove Task Failed", "Please select a task to remove.");
		return;
	}

	QString taskTitle = selectedItem->text();
	Task taskToRemove(0, taskTitle.toStdString());

	if (db.execute(taskToRemove.toSQLDelete())) {
		delete selectedItem;
	} else {
		QMessageBox::warning(this, "Remove Task Failed", "Failed to remove task from the database.");
	}
}

void TaskManagerForm::loadTasks() {
	taslList->clear();

	std::vector<std::string> tasks = db.getTasks(auth.getCurrentUser());

	for (const auto &task : tasks) {
		taskList->addItem(QString::fromStdString(task));
	}
}