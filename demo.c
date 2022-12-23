#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

/*
--------------------------------------------------------------------------------------------------------*/
void retreive_rows(MYSQL* con) {
	mysql_query(con, "SELECT * FROM tasks");
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;

	while ((row = mysql_fetch_row(res))) {
		printf("%s | ", row[0]);
		printf("%s\n", row[1]);
	};
	printf("\n"); 
	mysql_free_result(res);
};

void create_task(MYSQL* con) {
	char task[50]; 
	char buffer[50];

	printf("Enter task to add	: ");
	fgets(task, 50, stdin);
	task[strlen(task) - 1] = '\0';
   	sprintf(buffer, "INSERT INTO tasks(task) VALUES('%s')", task); 
	mysql_query(con, &buffer); 
}; 

void delete_record(MYSQL* con) {
	char id[5]; 
	char buffer[50]; 
	int num; 

	printf("Enter id of task you would like to delete: "); 
	fgets(id, 5, stdin);
	num = atoi(id); 

	sprintf(buffer, "DELETE FROM tasks WHERE id=(%d)", num); 
	mysql_query(con, &buffer); 
}; 

int main(int argc, char** argv) {
	int count; 
	MYSQL* con = mysql_init(NULL);

	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	if (mysql_real_connect(con, "localhost", "root", "Gh33c@t86",
		NULL, 0, NULL, 0) == NULL) {
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			exit(1);
	}
	mysql_query(con, "CREATE DATABASE aarrgghh"); 
	mysql_close(con); 

	con = mysql_init(NULL);
	mysql_real_connect(con, "localhost", "root", "Gh33c@t86", "aarrgghh", 0, NULL, 0); 
	

	//Create Table------------------------------------------------------------------------------
	mysql_query(con, "CREATE TABLE tasks(id INT PRIMARY KEY AUTO_INCREMENT, task VARCHAR(255))");

	// Gather input 
	printf("                                      << WELCOME TO TASK TRACKER >>\n\n");
	printf("                            Enter number from one of the following options below: \n");
	printf("                                            1. View tasks \n"); 
	printf("                                            2. Create task \n");
	printf("                                            3. Delete task \n");
	printf("                                            4. Exit program \n\n");

	char choice[10];
	int num, ret;

	// Add switch statement 

	while (1) {
		printf("Enter number: ");
		fgets(choice, 10, stdin);
		num = atoi(choice);

		if (num == 1) {
			retreive_rows(con);
		};
		if (num == 2) {
			create_task(con);
		};
		if (num == 3) {
			delete_record(con);
		};
		if (num == 4) {
			return 0;
		}; 
	}; 

	exit(1);
	mysql_close(con);
	exit(0); 
}
