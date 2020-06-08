#include <iostream>
#include <string>
#include <list>
#include <pqxx/pqxx>
#include <iterator>
#include "metric2pg.hpp"
using namespace std;
using namespace pqxx;



int metric2pg_create (std::list <char*> arguments) {

    /*std::cout << "Not implemented yet" << std::endl;*/
    std::cout << "The arguments are: " << std::endl;
    showlist(arguments);
    try {
      pqxx::connection C("dbname = postgres user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

       /* Create SQL statement */
    string sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( sql );
      W.commit();
      cout << "Table created successfully" << endl;
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
    return 0;

}