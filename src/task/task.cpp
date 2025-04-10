#include "task.h"
#include <sstream>

Task::Task(int id, const std::string &title, bool isCompleted, std::time_t dueDate)
		: id(id), title(title), isCompleted(isCompleted), dueDate(dueDate) {}

int Task::getId() const {
	return id;
}

std::string Task::getTitle() const {
	return title;
}

bool Task::getIsCompleted() const {
	return isCompleted;
}

std::time_t Task::getDueDate() const {
	return dueDate;
}

