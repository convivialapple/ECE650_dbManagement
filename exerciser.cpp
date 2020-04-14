#include "exerciser.h"

void exercise(connection *C)
{
  //  ofstream outfile;
  //outfile.open("queries.txt", ios::out | ios::trunc );
  query1(C, 1, 35, 40, 0, 0, 0, 0, 5, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query2(C, "LightBlue");
  query2(C, "Orange");
  query2(C, "Green");
  query2(C, "Red");
  query2(C, "DarkBlue");
  query2(C, "Gold");
  query2(C, "Maroon");
  query2(C, "Black");
  query3(C, "BostonCollege");
  query3(C, "Clemson");
  query3(C, "Duke");
  query4(C, "NC", "DarkBlue");
  query4(C, "VA", "LightBlue");
  query5(C, 5);
  query5(C, 8);
}
