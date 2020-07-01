#include <iostream>
#include <string.h>
#include <list>
#include <pqxx/pqxx>
#include <iterator>
#include "metric2pg.hpp"
using namespace std;
using namespace pqxx;

int metric2pg_drop (std::list <char*> arguments) { 
  
    char* fst = arguments.front();
    
    std::list <char*> tokenized = tokenize(fst);

    char* table = tokenized.back();
    tokenized.pop_back();
    char* database = tokenized.back();
    tokenized.pop_back();
    char* user = tokenized.front();
    tokenized.pop_front();
    char* pass = tokenized.back();
    tokenized.pop_back();

    string str1 = "dbname = " + std::string(database) + " ";
    string str2 = str1 + "user = " + std::string(user) + " ";
    string str3 = str2 + "password = " + std::string(pass) + " ";
    string conn_string = str3 + "hostaddr = 127.0.0.1 port = 5432";

    try {
      connection C(conn_string);
      if (C.is_open()) {
         cout << "Connection OK" << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

      /* Create SQL statement */
      string query = "DROP TABLE " + std::string(table) + ";";

      /* Execute SQL query */
      
      work W(C);
      W.exec(query);
      W.commit();
      
      
      cout << "Drop table successfully" << endl;

      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
    
    return 0;
}