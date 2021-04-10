#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Webpage{
private: 
string url; 
vector<string> keywords;
double numofimpressions;
double numberofclicks;
double crt;
int index;
double rankinit;
// int pagerankfinal;
double score;


public: 
Webpage();
Webpage(string, vector<string>, int,int);
void setindex(int );
void seturl(string);
void setkeywords(string);
void setkeywords(vector<string>);
void setimpressions(int);
void setclicks(int);
void setcrt(double);
void setscore(int rank);
void setrankinit(double);
int getscore();
int getindex();
double getrankinit();
void incrementimpression();
void incrementclick();
string geturl();
vector<string> getkeyword();
double getimpressions();

double getclicks();
double getcrt();
void printwebpage();






};