#include "Webpage.h"
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>

vector<double> calculate_rank(Graph webgraph, vector<Webpage> webvector){

    vector<vector<double>> final_table;
    vector<double> firstrow(webvector.size(),1/double(webvector.size()));
    final_table.push_back(firstrow);
   
    // for(int i=0;i<final_table[0].size();i++)
    //     cout<<final_table[0][i]<<endl;
    
    double temprank=0;
    //cout<<"this is it \n";
   //vector <int> ingoing(webvector.size());

   vector <int> ingoing;
   vector <double> output;
    for (int i=1;i<3;i++){
//cout<<"this is it "<<"i"<<i<<endl;

        

        for (int j=0;j<webvector.size();j++){
            int size(0);
            //cout<<"this is it j"<<j<<endl;
             //int* ingoingarr= new int[webvector.size()];
            //ingoingarr=webgraph.getIncomingNodesarr(j,size);
            ingoing=webgraph.getIncomingNodes(j);

            for (int m=0;m<ingoing.size();m++){
                // cout<<"this is it m"<<m<<endl;
                // cout<<final_table[i-1][ingoing[m]]<<endl;
                // cout<<webgraph.getNumberOfOutgoingEdges(ingoing[m])<<endl;
                temprank=temprank+(final_table[i-1][ingoing[m]]/webgraph.getNumberOfOutgoingEdges(ingoing[m]));
                //cout<<"temp rank "<<temprank<<endl;
            }

        //arr[i]=temprank;
        //cout<<"I reached the end of the loop\n";
        output.push_back(temprank);
        temprank=0;
        
        //delete [] ingoingarr;
        //ingoing.clear();
        }

        final_table.push_back(output);
        output.clear();


    }


return final_table[2];



}

vector<Webpage> SortRankBubble(vector<Webpage>  webvector)  
{  
    int i, j;  
    for (i = 0; i < webvector.size()-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < webvector.size()-i-1; j++)  
        if (webvector[j].getrankinit() > webvector[j+1].getrankinit()) { 
            Webpage temp=webvector[j];
            webvector[j]=webvector[j+1];
            webvector[j+1]=temp;
            
            
            }
            //cout<<"The size of the vector is "<<webvector.size()<<endl;
           
    return webvector;
} 

vector<Webpage> SortScoreBubble(vector<Webpage> webvector)  
{  
    int i, j;  
    for (i = 0; i < webvector.size()-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < webvector.size()-i-1; j++)  
        if (webvector[j].getscore() < webvector[j+1].getscore()) { 
            Webpage temp=webvector[j];
            webvector[j]=webvector[j+1];
            webvector[j+1]=temp;
            
            
            }
    return webvector;
} 

vector<Webpage> SortWebPages(vector<Webpage> webvector){
vector<Webpage> tempranksorted;
tempranksorted=SortRankBubble(webvector);

// cout<<"this is the rank you're looking for\n";
// for (int i=0;i<tempranksorted.size();i++)
//    cout<<tempranksorted[i].getrankinit()<<endl;

//this is to calculate the score;
for (int i=0;i<tempranksorted.size();i++){
tempranksorted[i].setscore(i+1);
}

vector<Webpage> tempscoresorted;
tempscoresorted=SortScoreBubble(tempranksorted);


//  cout<<"this is the score you're looking for\n";
// for (int i=0;i<tempranksorted.size();i++)
//    cout<<tempranksorted[i].getscore()<<endl;

return tempscoresorted;
    


}

vector<string> split(string str, char seperator) { 
  vector<string> internal; 
  stringstream ss(str); // Turn the string into a stream. 
  string temp; 
 
  while(getline(ss, temp, seperator)) { 
    internal.push_back(temp); 
  } 
 
  return internal; 
} 

void removequotes(string& strbefore){
   
     strbefore.erase(
    remove( strbefore.begin(), strbefore.end(), '\"' ),
    strbefore.end()
    );

    strbefore.erase(
    remove( strbefore.begin(), strbefore.end(), '\"' ),
    strbefore.end()
    );
    strbefore.erase(
    remove( strbefore.begin(), strbefore.end(), '\'' ),
    strbefore.end()
    );

}


vector<string> determineOp(string input, char& op){

vector<string> result;
result=split(input,' ');
op='o';
if (input[0]=='\'' || input[0]=='\"'){
    op='q'; //quotation
    removequotes(input);
    cout<<"input me "<<input<<endl;
    result.push_back(input);
    return result;
    }

else{
    for (int i=0;i<result.size();i++){
        if (result[i]=="AND"){
        op='a'; //AND
        result.erase(result.begin()+i);
        
        }
        if (result[i]=="OR"){
        op='o'; //AND
        result.erase(result.begin()+i);
        
        }
        
    }
     
    return result;
}


}

vector<Webpage> findpage(vector<Webpage> webvector, vector<string> extkeywords,char op){
//if the op is anding results
vector<string> intkeywords;
vector <Webpage> result;
vector<bool> flags(extkeywords.size(),false);
int i=0;

int truecount=0; 
int falsecount=extkeywords.size(); 
while(i<webvector.size()){
   
   //initializing flags
   for (int i=0;i<flags.size();i++)
        flags[i] = false;
    truecount=0; 
    falsecount=extkeywords.size(); 
    //end up initializing
intkeywords=webvector[i].getkeyword(); 

 

 for (int m=0;m<extkeywords.size();m++){
     for (int k=0;k<intkeywords.size();k++){
         if (extkeywords[m]==intkeywords[k]){
            flags[m]=true;
            truecount++; 
            falsecount--;
            break;

            }

     }
 }
//  cout<<"i "<<i<<endl;
//  for (int i=0;i<flags.size();i++)
//     cout<<flags[i]<<endl;

if(op=='q' || op=='a'){
    if (falsecount==0)
        result.push_back(webvector[i]);
}

if(op=='o'){
    if (truecount!=0)
        result.push_back(webvector[i]);
}



i++;
}

return result; 
}

void performSearch(vector<Webpage>& webvector){
    string searchword;
cout<<"New Search Window\n\nType in your search keyword: ";
cin.ignore();
std::getline(cin,searchword);
//cin.getline(searchword,1000,'\n');
char op;  
vector <string> searchvector;

searchvector=determineOp(searchword,op);
vector<Webpage> filteredwebpages;
filteredwebpages=findpage(webvector,searchvector,op);
for (int i=0;i<filteredwebpages.size(); i++){
    int index=filteredwebpages[i].getindex(); 
    for (int j=0;j<webvector.size();j++){
        if(index==webvector[j].getindex())
            webvector[j].incrementimpression();
    }
}




char choice; 

//in Case filtered is empty;
if (filteredwebpages.size()==0){
    cout<<"Oops!! We did not find any webpage that match the key words you entered\n\n";
    while(true){ 
cout<<"Welcome!\nWhat would you like to do\n1.New Search\n2.Exit\n\n\nType in your choice: ";
cin>>choice;
if (choice=='1'){
    performSearch(webvector);
    break;
    }
else if (choice=='2'){
cout<<"Your choice is to Exit\nThank you for using our SearchQuery\n";
return;
}
else{
    cout<<"Please Enter a valid choice\n";
}
}
}


else{

while(true){ 
    cout<<"Here are the webpages we found:\n";
    for (int i=0;i<filteredwebpages.size();i++)
        cout<<i+1<<". "<<filteredwebpages[i].geturl()<<endl;
    cout<<" would you like to: \n1.choose webpage to open\n2.New Search\n3.Exit\n\n\nType in your choice: ";
    cin>>choice;
    if (choice=='1'){

    while(true){
        cout<<"Here are the webpages we found:\n";
        for (int i=0;i<filteredwebpages.size();i++)
        cout<<i+1<<". "<<filteredwebpages[i].geturl()<<endl;
        cout<<"Type in your url number: ";
        int pagechoice;
        cin>>pagechoice;
        if (pagechoice>0 && pagechoice<=filteredwebpages.size()){
        cout<<"This is the content of the url: ";
        cout<<filteredwebpages[pagechoice-1].geturl()<<endl; 
        int index2=filteredwebpages[pagechoice-1].getindex(); 
        for (int j=0;j<webvector.size();j++){
        if(index2==webvector[j].getindex())
            webvector[j].incrementclick();
        }

        cout<<"What would you like to do next: \n1.back  to the result window\n2.New Search\n3.Exit\n\n\nType in your choice: ";
        cin>>pagechoice; 
        if (pagechoice<0 || pagechoice>3){
            cout<<"Invalid choice, Redirecting to the search window...........\n";
        performSearch(webvector);

        }
        else if (pagechoice==2){
            performSearch(webvector);
            break;
            }
        else if (pagechoice==3){
        cout<<"Your choice is to Exit\nThank you for using our SearchQuery\n";
        return;
        }
        


        }

    }


    }
    else if (choice=='2'){
        performSearch(webvector);
        break;
        }
    else if (choice=='3'){
    cout<<"Your choice is to Exit\nThank you for using our SearchQuery\n";
    return;
    }
    else{
        cout<<"Please Enter a valid choice\n";
    }

}
}





}



int main(){

vector<Webpage> webvector; 


//here begins the input form files to form the Webvector
ifstream inkeywordfile; 
inkeywordfile.open("keywordfile.csv");
string line,url;
vector<string> pageinfo;

while (!(inkeywordfile>>ws).eof()){
    
getline(inkeywordfile,line);
cout<<line<<endl;

if (inkeywordfile.fail()){
break;
}
else{

pageinfo=split(line,',');
url=pageinfo[0];
pageinfo.erase(pageinfo.begin());
Webpage temp;
temp.seturl(url);
temp.setkeywords(pageinfo);
webvector.push_back(temp);

}

}


ifstream inimpressionfile;
inimpressionfile.open("impressionfile.csv");
vector <string> impressioninfo;
while (!(inimpressionfile>>ws).eof()){
getline(inimpressionfile,line);
if (inimpressionfile.fail()){
    break;
}
impressioninfo=split(line,',');
url=impressioninfo[0];

for (int i=0;i<webvector.size();i++){
    if (webvector[i].geturl()==url)
        webvector[i].setimpressions(stoi(impressioninfo[1]));
}


}



ifstream incrtfile;
incrtfile.open("clickfile.csv");
vector <string> crtinfo;
while (!(incrtfile>>ws).eof()){
getline(incrtfile,line);
if (incrtfile.fail())
    break;
crtinfo=split(line,',');
url=crtinfo[0];

for (int i=0;i<webvector.size();i++){
    if (webvector[i].geturl()==url){
        webvector[i].setclicks(stoi(crtinfo[1]));
        
        }
}


}




//setting the index
for (int i=0;i<webvector.size();i++)
    webvector[i].setindex(i);



Graph Webgraph(webvector.size());
ifstream ingraphfile;
ingraphfile.open("graphfile.csv");
vector<string> graphinfo;
string url1,url2; 
while(!(ingraphfile>>ws).eof()){
getline(ingraphfile,line);
if (ingraphfile.fail())
    break;
graphinfo=split(line,',');
url1=graphinfo[0];
url2=graphinfo[1];
int index1; 
int index2; 

for (int i=0;i<webvector.size();i++){
    if (webvector[i].geturl()==url1)
        index1=webvector[i].getindex();
    
    if (webvector[i].geturl()==url2)
        index2=webvector[i].getindex();

}

Webgraph.addEdge(index1,index2);


}

// for (int i=0; i<webvector.size();i++)
// webvector[i].printwebpage(); 

// Webgraph.print(); 

// Here ends Input from the files


vector<Webpage> Sortedwebvector; 
Sortedwebvector=SortWebPages(webvector);


char choice;
while(true){ 
cout<<"Welcome!\nWhat would you like to do\n1.New Search\n2.Exit\n\n\nType in your choice: ";
cin>>choice;
if (choice=='1'){
    performSearch(Sortedwebvector);
    break;
    }
else if (choice=='2'){
cout<<"Your choice is to Exit\nThank you for using our SearchQuery\n";
break;
}
else{
    cout<<"Please Enter a valid choice\n";
}
}

for (int i=0;i<Sortedwebvector.size();i++)
    Sortedwebvector[i].printwebpage();

ofstream outclick; 
outclick.open("clickfile.csv");
for (int i=0;i<Sortedwebvector.size();i++)
    outclick<<Sortedwebvector[i].geturl()<<","<<Sortedwebvector[i].getclicks()<<endl;

ofstream outimpression; 
outimpression.open("impressionfile.csv");
for (int i=0;i<Sortedwebvector.size();i++)
    outimpression<<Sortedwebvector[i].geturl()<<","<<Sortedwebvector[i].getimpressions()<<endl;




return 0;
}