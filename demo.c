#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

void create_table(MYSQL* con) {
	char table_name[50];

};


// Retrieve tables ----------------------------------------------------------------------------
void retreive_tables(MYSQL* con) {
	mysql_query(con, "SHOW TABLES"); 
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row; 
	int count; 

	printf("Tables\n"); 
	printf("------\n"); 

	count = 1; 
	while ((row = mysql_fetch_row(res))) {
		printf("%d | ", count);
		printf("%s\n", row[0]);
		count++; 
	};
	printf("\n");
	mysql_free_result(res);

};

// Displays all table rows --------------------------------------------------------------------
void retreive_rows(MYSQL* con) {
	mysql_query(con, "SELECT * FROM diabetes1");
	MYSQL_RES* res = mysql_store_result(con);		// Used to iterate over all stored records 
	MYSQL_ROW row;

	// Iterate over rows, printing id & task 
	while ((row = mysql_fetch_row(res))) {
		printf("%s | ", row[0]);
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

	if (mysql_query(con, buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	};

	// Replace newline with null char to prevent empty rows
	meal[strlen(meal) - 1] = '\0';		
   	sprintf(buffer, "INSERT INTO trackdiabetes(meal, calories, carbs, sugars) VALUES('%s', %d, %d, %d)", meal, calint, carbint, sugint); 
	printf("%s", buffer); 
}; 

// Deletes record from table ------------------------------------------------------------------
void delete_record(MYSQL* con) {
	char id[5];  
	char buffer[50]; 
	int num; 

	printf("Enter id of task you would like to delete: ");			 
	fgets(id, 5, stdin);		// To convert char to int
	num = atoi(id); 

	sprintf(buffer, "DELETE FROM trackdiabetes WHERE id=(%d)", num); 
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
	mysql_query(con, "CREATE DATABASE newDB");		
	
	// Close prior to initializing a new connection with the newly created database
	mysql_close(con);							 

	con = mysql_init(NULL);
	mysql_real_connect(con, "localhost", "user", "password", "newDB", 0, NULL, 0);			// connection containing new database. 

	//Create Table------------------------------------------------------------------------------
	mysql_query(con, "CREATE TABLE trackd(id INT PRIMARY KEY AUTO_INCREMENT, meal VARCHAR(255), calories INT, carbs INT, sugars INT)");

	// Instructions -----------------------------------------------------------------------------
	printf("                                      << WELCOME TO DIABEATES ANALYZER >>\n\n");
	printf("                            Enter number from one of the following options below: \n");
	printf("                                            1. View all entries \n"); 
	printf("                                            2. Create meal entry \n");
	printf("                                            3. Delete entry \n");
	printf("                                            4. Exit program \n");
	printf("                                            5. View all tables\n\n");

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
			case 5: 
				retreive_tables(con);
				break; 
			case 6: 
				create_table(con); 
		}; 
	}; 
	mysql_close(con);
	exit(0); 
}
