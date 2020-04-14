#include <iostream>
#include <pqxx/pqxx>
#include <fstream>
#include <string>
#include <cstdlib>
#include "exerciser.h"


using namespace std;
using namespace pqxx;
using namespace std;

void createPlayer(connection *C, string filename) {
  //Firstly create table
  stringstream toWrite;
  toWrite << "DROP TABLE IF EXISTS PLAYER CASCADE;";
  toWrite << "CREATE TABLE PLAYER ("
	  << "PLAYER_ID SERIAL PRIMARY KEY NOT NULL," //serial means auto-incrementing
	  << "TEAM_ID int NOT NULL,"
	  << "UNIFORM_NUM int NOT NULL,"
	  << "FIRST_NAME varchar(256) NOT NULL,"
	  << "LAST_NAME varchar(256),"
	  << "MPG int,"
	  << "PPG int,"
	  << "RPG int,"
	  << "APG int,"
	  << "SPG numeric(32,1),"
	  << "BPG numeric(32,1),"
	  << "CONSTRAINT FK_TEAMID FOREIGN KEY (TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE SET NULL ON UPDATE CASCADE);";
  writeToSQL(C, toWrite.str());
  //Then insert each entry in file
  ifstream f;
  string s;
  string fName, lName;
  int player_id, team_id, jersey_num, mpg, ppg, rpg, apg;
  double spg, bpg;
  f.open(filename);
  if (f.fail() || f.bad()) {
    cerr << "Fail to open file " << filename << endl;
    exit(EXIT_FAILURE);
  }
  while (!(getline(f, s).eof())) {
    stringstream toWrite;
    toWrite << s;
    toWrite >> player_id;
    toWrite >> team_id;
    toWrite >> jersey_num;
    toWrite >> fName;
    toWrite >> lName;
    toWrite >> mpg;
    toWrite >> ppg;
    toWrite >> rpg;
    toWrite >> apg;
    toWrite >> spg;
    toWrite >> bpg;
    add_player(C, team_id, jersey_num, fName, lName, mpg, ppg, rpg, apg, spg, bpg);
  }
  f.close();
}

void createTeam(connection *C, string filename) {
  //Firstly create table
  stringstream toWrite;
  toWrite << "DROP TABLE IF EXISTS TEAM CASCADE;";
  toWrite << "CREATE TABLE TEAM ("
	  << "TEAM_ID SERIAL PRIMARY KEY NOT NULL,"
	  << "NAME varchar(256) NOT NULL," 
	  << "STATE_ID int NOT NULL," 
	  << "COLOR_ID int NOT NULL," 
	  << "WINS int NOT NULL," 
	  << "LOSSES int NOT NULL,"
	  << " CONSTRAINT FK_STATE_ID FOREIGN KEY (STATE_ID) REFERENCES STATE(STATE_ID) ON DELETE SET NULL ON UPDATE CASCADE,"
	  << "CONSTRAINT FK_COLOR_ID FOREIGN KEY (COLOR_ID) REFERENCES COLOR(COLOR_ID) ON DELETE SET NULL ON UPDATE CASCADE);";
  writeToSQL(C, toWrite.str());
  
  //Then insert each entry in file
  ifstream f;
  string s;
  string name;
  int team_id, state_id, color_id, wins, losses;
  double spg, bpg;
  f.open(filename);
  if (f.fail() || f.bad()) {
    cerr << "Fail to open file " << filename << endl;
    exit(EXIT_FAILURE);
  }
  while (!(getline(f, s).eof())) {
    stringstream toWrite;
    toWrite << s;
    toWrite >> team_id;
    toWrite >> name;
    toWrite >> state_id;
    toWrite >> color_id;
    toWrite >> wins;
    toWrite >> losses;
    add_team(C, name, state_id, color_id, wins, losses);
  }
  f.close();
}

void createState(connection * C, string filename) {
  //Firstly create table
  stringstream toWrite;
  toWrite << "DROP TABLE IF EXISTS STATE CASCADE;";
  toWrite << "CREATE TABLE STATE ("
	  << "STATE_ID SERIAL PRIMARY KEY NOT NULL," 
	  << "NAME varchar(256) NOT NULL);";
  writeToSQL(C, toWrite.str());
  
  //Then insert each entry in file
  ifstream f;
  string s;
  string name;
  int state_id;
  f.open(filename);
  if (f.fail() || f.bad()) {
    cerr << "Fail to open file " << filename << endl;
    exit(EXIT_FAILURE);
  }
  while (!(getline(f, s).eof())) {
    stringstream toWrite;
    toWrite << s;
    toWrite >> state_id;
    toWrite >> name;
    add_state(C, name);
  }
  f.close();
}

void createColor(connection * C, string filename) {
   //Firstly create table
  stringstream toWrite;
  toWrite << "DROP TABLE IF EXISTS COLOR CASCADE;";
  toWrite << "CREATE TABLE COLOR ("
	  << "COLOR_ID SERIAL PRIMARY KEY NOT NULL," 
	  << "NAME varchar(256) NOT NULL);";
  writeToSQL(C, toWrite.str());
  
  //Then insert each entry in file
  ifstream f;
  string s;
  string name;
  int color_id;
  f.open(filename);
  if (f.fail() || f.bad()) {
    cerr << "Fail to open file " << filename << endl;
    exit(EXIT_FAILURE);
  }
  while (!(getline(f, s).eof())) {
    stringstream toWrite;
    toWrite << s;
    toWrite >> color_id;
    toWrite >> name;
    add_color(C, name);
  }
  f.close();
}
  
    
int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }
  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files
  createState(C, "state.txt");
  createColor(C, "color.txt");
  createTeam(C, "team.txt");
  createPlayer(C, "player.txt");

  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}


