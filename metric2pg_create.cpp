#include <iostream>
#include <string.h>
#include <list>
#include <pqxx/pqxx>
#include <iterator>
#include "metric2pg.hpp"
using namespace std;
using namespace pqxx;

std::list <char*> tokenize(char* arg) {
    
    std::list <char*> result1, result2, result3, final_result;

    char* token = strtok(arg, "#");
    while (token != NULL) { 
        result1.push_back(token);
        token = strtok(NULL, "#"); 
    }
    // name of the table

    char *table = result1.back();
    result1.pop_back();

    token = strtok(result1.front(), "@");
    while (token != NULL) { 
        result2.push_back(token);
        token = strtok(NULL, "@"); 
    }
    // name of database

    char *database = result2.back();
    result2.pop_back();

    token = strtok(result2.front(), ":");
    while (token != NULL) { 
        result3.push_back(token);
        token = strtok(NULL, ":"); 
    }
    
    // name of user

    char* user = result3.front();
    result3.pop_front();

    // password

    char* pass = result3.front();
    result3.pop_front();

    final_result.push_back(user);
    final_result.push_back(pass);
    final_result.push_back(database);
    final_result.push_back(table);

    return final_result;


}

int metric2pg_create (std::list <char*> arguments) {

    /*std::cout << "Not implemented yet" << std::endl;*/
    // user:pass@database#tabela
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

    arguments.pop_front();
    char* field = arguments.front();

    try {
      
      pqxx::connection C(conn_string);
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

    /* Create SQL statement */
      string sql = "CREATE TABLE " + std::string(table) + "(time    TIMESTAMP     NOT NULL," \
                                                            +std::string(field) + "    DOUBLE PRECISION    NULL);";

      work W(C);
    
      /* Execute SQL query */
    
      W.exec( sql );
      cout << "Table created successfully" << endl;

      /* Create hypertable */
      string hyper = "SELECT create_hypertable('" + std::string(table) + "', 'time')"; 

      W.exec(hyper);
      W.commit();
      cout << "Hypertable created successfully" << endl;
      
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
    return 0;

}