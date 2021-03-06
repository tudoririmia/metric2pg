#include <iostream>
#include <string.h>
#include <list>
#include <pqxx/pqxx>
#include <iterator>
#include "metric2pg.hpp"
using namespace std;
using namespace pqxx;

int metric2pg_fetch (std::list <char*> arguments) {
  
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
      string query = "SELECT * FROM " + std::string(table) + ";";

      /* Create a transactional object. */
      nontransaction N(C);
      
      /* Execute SQL query */
      result R( N.exec( query ));

      cout << "--------------------------------------------" << endl;
      cout << "TIME                       | TEMPERATURE"  << endl;
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         
         cout <<c[0].as<string>() << " | ";
         cout << c[1].as<float>() << endl;

      }
      cout << "--------------------------------------------" << endl;
      cout << "Operation done successfully" << endl;

      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
    
    return 0;
}