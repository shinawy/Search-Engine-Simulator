#include "Webpage.h"

Webpage::Webpage(){

url=" ";
numberofclicks=0;
numofimpressions=1;
crt=(numberofclicks/numofimpressions)*100;
keywords.resize(10);
score=0;
rankinit=0;

}

Webpage::Webpage(string a, vector<string> b, int impression, int pindex){
url=a;
numberofclicks=0;
numofimpressions=impression;
crt=(numberofclicks/numofimpressions)*100;
keywords=b;
score=0; //page rank is zero at the moment;
index=pindex;



}

void Webpage::setindex(int a){

index=a;


}

void Webpage::seturl(string a){

url=a;


}

void Webpage::setkeywords(string a){

keywords.push_back(a);

}

void Webpage::setkeywords(vector<string> b){

keywords=b;


}

void Webpage::setimpressions(int impression){
numofimpressions=impression;
if (impression !=0)
crt=(numberofclicks/numofimpressions)*100;
}

void Webpage::setclicks(int a) {
numberofclicks= a;
crt=(numberofclicks/numofimpressions)*100;

}

void Webpage::setcrt(double c){

crt=c;

}

void Webpage:: setrankinit(double rank){
rankinit=rank;


}



void Webpage:: setscore(int rank){

score= 0.4*rank+((1-(0.1*numofimpressions)/(1+0.1*numofimpressions))*rank+((0.1*numofimpressions)/(1+0.1*numofimpressions))*crt)*0.6;



}
int Webpage:: getscore(){


    return score;
}

void Webpage::incrementimpression(){

numofimpressions++;
crt=(numberofclicks/numofimpressions)*100;

}


void Webpage::incrementclick(){

numberofclicks++;
crt=(numberofclicks/numofimpressions)*100;



}


string Webpage::geturl(){

return url;

}

vector<string> Webpage::getkeyword(){
return keywords;


}

double Webpage:: getrankinit(){



    return rankinit;
}

double Webpage::getimpressions(){

return numofimpressions;

}

double Webpage::getclicks(){

return numberofclicks;


}

double Webpage::getcrt(){
return crt;


}
int Webpage::getindex(){
return index;


}
void Webpage:: printwebpage(){

cout<<"New Webpage "<<endl;
cout<<"-----------\nURL: "<<url<<endl;
cout<<"Numofclicks: "<<numberofclicks<<endl;
cout<<"NumofImpressions: "<<numofimpressions<<endl;
cout<<"CRT:    "<<crt<<endl;
cout<<"keywords: ";
for (int i=0;i<keywords.size();i++)
    cout<<keywords[i]<<", ";
cout<<endl;
cout<<"Score: "<<score<<endl;
cout<<"Index: "<<index<<endl;
cout<<"Rank: "<<rankinit<<endl;
}

