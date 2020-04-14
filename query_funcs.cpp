#include "query_funcs.h"
#include <iostream>
#include <vector>

void printResult(result r) {
  for (result::const_iterator it = r.begin(); it != r.end(); ++it) {
    for (int i = 0; i < it.size(); i++) {
      cout << it[i].as<string>() << " ";
    }
    cout << endl;
  }
}

void writeToSQL(connection *C, string toWrite) {
  work W(*C);
  W.exec(toWrite);
  W.commit();
}

//add tuple into player. Player_id is not included, so it is auto field 
void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg)
{
  stringstream toWrite;
  work W(*C);
  toWrite << "INSERT INTO PLAYER(TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG,"
	  << "RPG, APG, SPG, BPG) VALUES(";
  string fname = W.quote(first_name);
  string lname = W.quote(last_name);
  W.commit();
  toWrite << team_id << ", " << jersey_num << ", ";
  toWrite << fname << ", ";
  toWrite  << lname << ", " << mpg << ", " << ppg << ", ";
  toWrite << rpg << ", " << apg << ", ";
  toWrite << spg << ", " << bpg << ");";
  //cout << toWrite.str() << endl;
  writeToSQL(C, toWrite.str());
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
  stringstream toWrite;
  work W(*C);
  string qname = W.quote(name);
  W.commit();
    
  toWrite << "INSERT INTO TEAM(NAME, STATE_ID, COLOR_ID, WINS, LOSSES)"
	  << "VALUES(";
  toWrite << qname << ", " << state_id << ", ";
  toWrite << color_id << ", " << wins << ", " << losses << ");";
  //cout << toWrite.str() << endl;
  writeToSQL(C, toWrite.str());
}


void add_state(connection *C, string name)
{
  work W(*C);
  string qname = W.quote(name);
  W.commit();
  string toWrite = "INSERT INTO STATE(NAME) VALUES(" + qname + ");";
  //cout << toWrite << endl;
  writeToSQL(C, toWrite);
}


void add_color(connection *C, string name)
{
  work W(*C);
  string qname = W.quote(name);
  W.commit();
  string toWrite = "INSERT INTO COLOR(NAME) VALUES(" + qname + ");";
  //cout << toWrite << endl;
  writeToSQL(C, toWrite);
}


void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
  vector<string> names{"mpg", "ppg", "rpg", "apg", "spg", "bpg"};
  vector<double> mins{(double)min_mpg, (double)min_ppg, (double)min_rpg, (double)min_apg, min_spg, min_bpg};
  vector<double> maxs{(double)max_mpg, (double)max_ppg, (double)max_rpg, (double)max_apg, max_spg, max_bpg};
  vector<int> index;
  if(use_mpg) index.push_back(0);
  if(use_ppg) index.push_back(1);
  if(use_rpg) index.push_back(2);
  if(use_apg) index.push_back(3);
  if(use_spg) index.push_back(4);
  if(use_bpg) index.push_back(5);
  stringstream toWrite;
  toWrite << "SELECT * FROM PLAYER ";
  for (int i = 0; i < index.size(); i++) {
    if (i == 0) {
      toWrite << "WHERE";
    }
    else {
      toWrite << "AND";
    }
    toWrite << "(" << names[index[i]] << " BETWEEN " << mins[index[i]] << " AND " << maxs[index[i]] << ") ";
  }
  toWrite << ";";
  work W(*C);
  result r(W.exec(toWrite.str()));
  cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
  printResult(r);
  W.commit();
}

void query2(connection *C, string team_color)
{
  work W(*C);
  string toWrite = "SELECT team.name FROM color, team WHERE team.color_id = color.color_id AND color.name = ";
  toWrite += W.quote(team_color) + ";";
  result r(W.exec(toWrite));
  cout << "NAME" << endl;
  printResult(r);
  W.commit();
}


void query3(connection *C, string team_name)
{
  work W(*C);
  string toWrite = "SELECT first_name, last_name FROM team, player WHERE player.team_id = team.team_id AND team.name = ";
  toWrite += W.quote(team_name);
  toWrite += "ORDER by ppg DESC;";
  result r(W.exec(toWrite));
  cout << "FIRST_NAME LAST_NAME" << endl;
  printResult(r);
  W.commit();
}


void query4(connection *C, string team_state, string team_color)
{
  work W(*C);
  string toWrite = "SELECT first_name, last_name, uniform_num FROM player, team, state, color WHERE player.team_id = team.team_id";
  toWrite += " AND team.state_id = state.state_id AND team.color_id = color.color_id AND state.name = ";
  toWrite += W.quote(team_state);
  toWrite += " AND color.name = ";
  toWrite += W.quote(team_color) + ";";
  result r(W.exec(toWrite));
  cout << "FIRST_NAME LAST_NAME UNIFORM_NUM" << endl;
  printResult(r);
  W.commit();
}


void query5(connection *C, int num_wins)
{
  stringstream toWrite;
  toWrite << "SELECT first_name, last_name, team.name, team.wins FROM player, team WHERE player.team_id = "
	  << "team.team_id AND team.wins > ";
  toWrite << num_wins << ";";
  work W(*C);
  result r(W.exec(toWrite.str()));
  cout << "FIRST_NAME LAST_NAME TEAM_NAME WINS" << endl;
  printResult(r);
  W.commit();
 }
