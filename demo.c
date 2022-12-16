#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

/*Basic MySQL functions:
* ----------------------
1. mysql_init()				Allocates or initialises a MYSQL object used by mysql_real_connect
2. mysql_get_client_info	Returns MySQL version number 
3. mysql_error()							
4. mysql_query() 
5. mysql_close()			
5. mysql_real_connect() 

   Hierarchy: Database (top) --> Table --> Rows --> ?? 
--------------------------------------------------------------------------------------------------------*/

int main(int argc, char** argv) {


	// Connect to DB -----------------------------------------------------------------------------------
	MYSQL* con = mysql_init(NULL);
	printf("Connected to %s\n\n", "server");

	// verify if connection is successful 
	if (con == NULL) {
		printf(stderr, "%s\n", mysql_error(con));
		exit(1);
	};

	// 2 Steps to create DATABASE ----------------------------------------------------------------------
	if (mysql_real_connect(con, "localhost", "root", "Gh33c@t86",
		"maindb", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		//mysql_close(con);
		//exit(1);
	}
	// Verify if db can be created 
	// This is required to create DATABASE (2) 

	if (mysql_query(con, "CREATE DATABASE maindb")) {
		printf(stderr, "%s\n", mysql_error(con));
		//mysql_close(con);
	};
	//mysql_real_connect(con, "localhost", "user12", "34klq*", "maindb", 0, NULL, 0);
 
	// Create Table ------------------------------------------------------------------------------
	mysql_query(con, "DROP TABLE IF EXISTS items"); 
	mysql_query(con, "CREATE TABLE items(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255))");

	// Insert Data - DEMO PURPOSES ONLY ---------------------------------------------------
	mysql_query(con, "INSERT INTO items VALUES(1, 'eat eggs'\n)");
	mysql_query(con, "INSERT INTO items VALUES(2, 'eat steak'\n)");
	mysql_query(con, "INSERT INTO items VALUES(3, 'eat chcken')");
	mysql_query(con, "INSERT INTO items VALUES(4, 'eat broccolli')");
	mysql_query(con, "INSERT INTO items VALUES(5, 'eat salad')");
	mysql_query(con, "INSERT INTO items VALUES(6, 'eat rice & beans')");

	// Retrieve rows from list -------------------------------------------------------------------
	mysql_query(con, "SELECT * FROM items"); 

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row; 
	
	while ((row = mysql_fetch_row(res))) {
		printf("%s) ", row[0]);
		printf("%s\n", row[1]);
	};

	mysql_free_result(res); 
	mysql_close(con);
	exit(0); 
}
