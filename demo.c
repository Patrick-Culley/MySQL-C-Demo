#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

// Displays all table rows --------------------------------------------------------------------
void retreive_rows(MYSQL* con) {
	mysql_query(con, "SELECT * FROM trackdiabetes1");
	MYSQL_RES* res = mysql_store_result(con);		// Used to iterate over all stored records 
	MYSQL_ROW row;

	// Iterate over rows, printing id & task 
	while ((row = mysql_fetch_row(res))) {
		printf("ID: %s\nMEAL: %s  \nCALORIES: %s  \nCARBS: %s  \nSUGAR: %s\n\n", row[0], row[1], row[2], row[3], row[4]);
		};
	printf("\n"); 
	mysql_free_result(res);						   // free prior to returing to main 
};

// Inserts new record -------------------------------------------------------------------------
void create_task(MYSQL* con) {
	char meal[50]; 
	char buffer[255];
	char cal[5], carb[5], sugar[5];
	int calint, carbint, sugint;

	printf("Enter meal: ");
	fgets(meal, 50, stdin);
	printf("Enter calories: ");
	fgets(cal, 5,stdin);
	printf("Enter carbohydrates: ");
	fgets(carb, 5, stdin);
	printf("Enter sugar (in grams): ");
	fgets(sugar, 5, stdin);

	calint = atoi(cal); 
	carbint = atoi(carb); 
	sugint = atoi(sugar); 

	// Replace newline with null char to prevent empty rows
	meal[strlen(meal) - 1] = '\0';		
   	sprintf(buffer, "INSERT INTO trackdiabetes1(meal, calories, carbs, sugars) VALUES('%s', %d, %d, %d)", meal, calint, carbint, sugint); 

	if (mysql_query(con, buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	};
}; 

// Deletes record from table ------------------------------------------------------------------
void delete_record(MYSQL* con) {
	char id[5];  
	char buffer[50]; 
	int num; 

	printf("Enter id of task you would like to delete: ");			 
	fgets(id, 5, stdin);		// To convert char to int
	num = atoi(id); 

	sprintf(buffer, "DELETE FROM trackdiabetes1 WHERE id=(%d)", num); 
	mysql_query(con, &buffer); 
}; 
 
int main(int argc, char** argv) {
	int count; 

	// Holds server & db connection 
	MYSQL* con = mysql_init(NULL);

	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	if (mysql_real_connect(con, "localhost", "user", "password",
		NULL, 0, NULL, 0) == NULL) {
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			exit(1);
	}

	mysql_query(con, "CREATE DATABASE IF NOT EXISTS newdb");

	// Close prior to initializing a new connection with the newly created database
	mysql_close(con);							 

	con = mysql_init(NULL);
	
	// connection containing new database. 
	if (mysql_real_connect(con, "localhost", "user", "password", "newdb", 0, NULL, 0) == NULL) {
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			exit(1);	
	};		

	//Create Table------------------------------------------------------------------------------
	if (mysql_query(con, "CREATE TABLE IF NOT EXISTS trackdiabetes1(id INT PRIMARY KEY AUTO_INCREMENT, meal VARCHAR(255), calories INT, carbs INT, sugars INT)")) {
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			exit(1);
	};

	// Instructions -----------------------------------------------------------------------------
	printf("                                      << WELCOME TO DIABEATES ANALYZER >>\n\n");
	printf("                            Enter number from one of the following options below: \n");
	printf("                                            1. View all entries \n"); 
	printf("                                            2. Create meal entry \n");
	printf("                                            3. Delete entry \n");
	printf("                                            4. Exit program \n");

	// Gather User Input -----------------------------------------------------------------------
	char choice[10];
	int num, ret;

	while (1) {
		printf("Enter number: ");
		fgets(choice, 10, stdin);
		printf("\n");
		num = atoi(choice);

		switch (num) {
			case 1:
				retreive_rows(con);
				break;
			case 2:
				create_task(con);
				break;
			case 3:
				delete_record(con);
				break;
			case 4:
				return 0;
		}; 
	}; 
	mysql_close(con);
	exit(0); 
}
