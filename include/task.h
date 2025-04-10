#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime> //for fate and time

class Task {
private:
	int id;
	std::string title;
	bool isCompleted;
	std::time_t dueDate;

public:
	Task(int id, const std::string &title, bool isCompleted=false, std::time_t dueDate=0);

	int getId() const;
	std::string getTitle() const;
	bool getIsCompleted() const;
	std::time_t getDueDate() const;

	void setTitle(const std::string &newTitle);
	void marksAsCompleted();
	void setDueDate(std::time_t newDueDate);

	std::string toSQLInsert() const;
	std::string toSQLDelete() const;
	static Task fromSQLRow(char **row);
};

#endif