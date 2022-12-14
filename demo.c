#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

/*Basic MySQL functions:
* ----------------------
1. mysql_init()				Allocates or initialises a MYSQL object used by 
2. mysql_get_client_info	Returns MySQL version number 
3. mysql_error()							
4. mysql_query() 
5. mysql_close()			
5. mysql_real_connect() 
--------------------------------------------------------------------------------------------------------*/

int main(int argc, char** argv) {
	printf("MySQL client version %s\n", mysql_get_client_info());

	// To connect to db: 
	MYSQL* con = mysql_init(NULL);
	printf("Establishing connection to %s....\n", "server");

	// verify if connection is successful 
	if (con == NULL) {
		printf(stderr, "%s\n", mysql_error(con));
		exit(1);
	};

	// 2 Steps to create DATABASE: 
	// ---------------------------
	// ANALYZE THIS! what does it do? How does it do it? 
	// This is required to create a DATABASE (1)
	if (mysql_real_connect(con, "localhost", "root", "Gh33c@t86",
		NULL, 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	// Verify if db can be created 
	// This is required to create DATABASE (2) 
	if (mysql_query(con, "CREATE DATABASE maindb")) {

		printf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
	};

	// Print all databases: 
	MYSQL_RES* result = mysql_list_dbs(con, NULL);			// Returns a result set of databases 


	/* Steps to create and populate TABLE
	* -----------------------------------
	* 
	*/ 

	mysql_close(con); 
	return 0; 
}
