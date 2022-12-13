#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

/*Basic MySQL functions:
* ----------------------
1. mysql_init()				Allocates or initialises a MYSQL object used by 
2. mysql_get_client_info	returns MySQL version number 
3. mysql_error				
4. mysql_query
5. 
--------------------------------------------------------------------------------------------------------*/

int main(int argc, char **argv) {
	printf("MySQL client version %s\n", mysql_get_client_info());

	// To connect to db: 
	MYSQL* con = mysql_init(NULL);		
	printf("Establishing connection to %s....\n", "server");

	// verify if connection is successful 
	if (con == NULL) {
		printf(stderr, "%s\n", mysql_error(con));
	};
	// verify if db can be created 
	if (mysql_query(con, "CREATE DATABASE maindb")) {
		printf(stderr, "%s\n", mysql_error(con)); 
	};
	
	mysql_close(con); 
	return 0; 
}
