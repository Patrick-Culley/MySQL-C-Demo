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
 
	mysql_query(con, "DROP TABLE IF EXISTS items"); 
	mysql_query(con, "CREATE TABLE items(id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255))");
	mysql_query(con, "INSERT INTO items VALUES(1, 'eat eggs'\n)");
	mysql_query(con, "INSERT INTO items VALUES(2, 'eat steak'\n)");
	mysql_query(con, "INSERT INTO items VALUES(3, 'eat chcken')");
	mysql_query(con, "INSERT INTO items VALUES(4, 'eat broccolli')");
	mysql_query(con, "INSERT INTO items VALUES(5, 'eat salad')");
	mysql_query(con, "INSERT INTO items VALUES(6, 'eat rice & beans')");
	mysql_close(con);
	exit(0); 
}
