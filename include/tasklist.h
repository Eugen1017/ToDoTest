#ifndef TASKLIST_H
#define TASKLIST_H

#include <vector>
#include <task.h>
#include <database.h>

class TaskList {
private:
	Database &db;

	static int collectTasksCallback(void *data, int argc, char **argv, char **calNames);

public:
	TaskList(Database &database);

	std::vector<Task> getTasks(int userId);
};

#endif