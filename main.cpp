#include <stdio.h>
#include <iostream>
using namespace std;
#include <fstream>
#include <time.h>
#include <vector>
#include <list>
using namespace std;

struct Node{
    string data;
    string parent;
};
class Graph{//graph with list
private:
    unsigned long V;// Nvertice number
    vector<string> values;
    vector<string> dictionary; // dictionary of words
public:
    Graph(vector<string> dict);  // Constructor
    list<string> shortestPath(string s, string d);//shortest path
    int index(string value);//search vector
    string value(int location);//access vector
    list<Node> path;//the words from begin to end
    list<Node> BFS(string start ,string destination);
};
Graph::Graph(vector<string> dict){
    dictionary = dict;
    this->V = dictionary.size();
}
int Graph::index(string value){
    for (int i = 0; i < dictionary.size(); i++) {
        if (dictionary[i] == value)
            return i;
    }
    exit(1);
}
string Graph::value(int location)
{
    if (location <= dictionary.size()) {
        return dictionary[location];
    } else {
        exit(1);
    }
}
list<string> Graph::shortestPath(string s, string d)
{
    BFS(s, d);
    list<Node>::iterator it;
    list<string> myPath;
    
    for (it = path.begin(); it->data != d; ++it) {}
    string num = it->data;
    myPath.push_front(num);
    
    while (it != path.begin()) {
        num = it->parent;
        myPath.push_front(num);
        for (it=it; it->data != num; --it) {}
    }
    return myPath;
}
list<Node> Graph::BFS(string s, string d)
{
    int start = index(s);
    int destination = index(d);
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
    list<int> queue;
    visited[start] = true;
    queue.push_back(start);
    list<int> wordsVaryByOneLetter;
    Node n;
    n.data = s;
    n.parent = s;
    path.push_back(n);
    while(start != destination && !queue.empty()){
        start = queue.front();
        queue.pop_front();
        n.parent = value(start);
        wordsVaryByOneLetter.clear();
        for (int i = 0; i < dictionary.size(); i++)
        {
            if (dictionary[i][0] != dictionary[start][0] && dictionary[i][1] == dictionary[start][1] && dictionary[i][2] == dictionary[start][2] && dictionary[i][3] == dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            } else if (dictionary[i][0] == dictionary[start][0] && dictionary[i][1] != dictionary[start][1] && dictionary[i][2] == dictionary[start][2] && dictionary[i][3] == dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            } else if (dictionary[i][0] == dictionary[start][0] && dictionary[i][1] == dictionary[start][1] && dictionary[i][2] != dictionary[start][2] && dictionary[i][3] == dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            }
            else if (dictionary[i][0] == dictionary[start][0] && dictionary[i][1] == dictionary[start][1] && dictionary[i][2] == dictionary[start][2] && dictionary[i][3] != dictionary[start][3])
            {
                wordsVaryByOneLetter.push_back(i);
            }
        }
        list<int>::iterator it;
        for (it = wordsVaryByOneLetter.begin(); it != wordsVaryByOneLetter.end(); ++it){
            if(!visited[*it] ){
                visited[*it] = true;
                queue.push_back(*it);
                n.data = dictionary[*it];
                path.push_back(n);
            }
        }
    }
    return path;
}
class Wordladder {
private:
    string initialWord;//start word
    string finalWord;//end word
    ifstream wordsFile; //file ready to open
    vector<string> dictionary; // put word from dictionary inside
    vector<string>::iterator dictionaryIt; // iterator
    
public:
    Wordladder(){
        wordsFile.open("/Users/binglin/Desktop/words.txt");
        if (wordsFile.fail()) {
            cout << "ERROR: Unable to open file" << endl;
            exit(1);
        }
    }
    ~Wordladder(){
        wordsFile.close();
    }
    void loadWords() {
        string tempWord;//find common letters
        bool first=false, second=false, third=false, fourth=false;
        short int numLettersInCommon = 0;//similiarity of two words
        short int x=-1, y=-1, z=-1;
        for (int i = 0; i < 4; i++) {
            if (initialWord[i] == finalWord[i]) {
                if (i == 0) { first=true; numLettersInCommon++; }
                else if (i == 1) { second=true; numLettersInCommon++; }
                else if (i == 2) { third=true; numLettersInCommon++; }
                else { fourth=true; numLettersInCommon++; }
            }//check the each letters between two words
        }
        wordsFile.seekg(0, ios::beg);
        switch (numLettersInCommon) {
            case 1://when have one same letter
                if (first) x=0;
                else if (second) x=1;
                else if (third) x=2;
                else if (fourth) x=3;
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    if (tempWord[x] == initialWord[x]) {
                        dictionary.push_back(tempWord); // load word into list
                    }
                }
                break;
            case 2:
                if (first) {
                    x=0;
                    if (second) y=1;
                    else if (third) y=2;
                    else if (fourth) y=3;
                }
                else if (second) {
                    x=1;
                    if (third) y=2;
                    else if (fourth) y=3;
                }
                else if(third) {
                    x=2;
                    y=3;
                }
                
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    // test the conditions
                    if (tempWord[x] == finalWord[x] && tempWord[y] == finalWord[y]) {
                        dictionary.push_back(tempWord); // load word
                    }
                }
                break;
            case 3:
                if (first) {
                    x=0;
                    if (second) {
                        y=1;
                        if (third) z=2;
                        else if (fourth) z=4;
                    }
                    else if (third) {
                        y=2;
                        z=3;
                    }
                }
                else if (second) {
                    x=1;
                    if (third) {
                        y=2;
                        z=3;
                    }
                }
                
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    // test the conditions
                    if (tempWord[x] == initialWord[x] && tempWord[y] == initialWord[y] && tempWord[z] == initialWord[z]) {
                        dictionary.push_back(tempWord); // load word into list
                    }
                }
                break;
            case 4://exactly same word
                cerr << "WARNING : \nThe word you entered two same words, please re-enter\n";
                exit(1);
                break;
            default://two completely different word, execute these
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    dictionary.push_back(tempWord); // load word into list
                }
                break;
        }
    }
    void getWords(){
        cout << "\nGame Rule : Enter 2 different words in four letters\n" << endl;
        cout<<"Please enter the word\n";
        cout << "Initial Word: ";
        cin >> initialWord;
        while (initialWord.length() != 4) {//if word entered does not meet criteria
            cout << "Invalid entry, please re-enter";
            cout << "Initial Word: ";
            cin >> initialWord;
        }
        cout << "Final Word: ";
        cin >> finalWord;
        while (finalWord.length() != 4) { //check if meet criteria
            cout << "Invalid entry, please re-enter";
            cout << "Final Word: ";
            cin >> finalWord;
        }
        for (int i = 0; i < initialWord.length(); i++) {
            initialWord[i] = initialWord[i] & 0xDF;
            finalWord[i] = finalWord[i] & 0xDF;
        }
    }
    int checkWords(){
        string tempWord;
        bool word1Found = false;
        bool word2Found = false;
        while (!wordsFile.eof() && (word1Found != true || word2Found != true)) {
            wordsFile >> tempWord;
            if (initialWord == tempWord) word1Found = true;
            if (finalWord == tempWord) word2Found = true;
        }
        if (word1Found == true && word2Found == true) {
            return 0;
        }
        else {
            cerr << "Sorry, I can not found the word\n";
            exit(1);
        }
    }
    void gameSolution(){
        Graph g(dictionary);
        // Get shortest path
        list<string> lePath = g.shortestPath(initialWord, finalWord);
        cout << "This is my answer: " << endl;
        for (list<string>::iterator it = lePath.begin(); it != lePath.end(); ++it) {
            cout << *it << endl;
        }
    }
    void gameStart(){
        getWords();
        checkWords();
        loadWords();
        gameSolution();
    }
};


class Wordladder5 {
private:
    string initialWord;//start word
    string finalWord;//end word
    ifstream wordsFile; //file ready to open
    vector<string> dictionary; // put word from dictionary inside
    vector<string>::iterator dictionaryIt; // iterator
    
public:
    Wordladder5(){
        wordsFile.open("/Users/binglin/Desktop/words.txt");
        if (wordsFile.fail()) {
            cout << "ERROR: Unable to open file" << endl;
            exit(1);
        }
    }
    ~Wordladder5(){
        wordsFile.close();
    }
    void loadWords() {
        string tempWord;//find common letters
        bool first=false, second=false, third=false;
        short int numLettersInCommon = 0;//similiarity of two words
        short int x=-1, y=-1, z=-1;
        for (int i = 0; i < 4; i++) {
            if (initialWord[i] == finalWord[i]) {
                if (i == 0) { first=true; numLettersInCommon++; }
                else if (i == 1) { second=true; numLettersInCommon++; }
                else if (i == 2) { third=true; numLettersInCommon++; }
                //else { fourth=true; numLettersInCommon++; }
            }//check the each letters between two words
        }
        wordsFile.seekg(0, ios::beg);
        switch (numLettersInCommon) {
            case 1://when have one same letter
                if (first) x=0;
                else if (second) x=1;
                else if (third) x=2;
                //else if (fourth) x=3;
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    if (tempWord[x] == initialWord[x]) {
                        dictionary.push_back(tempWord); // load word into list
                    }
                }
                break;
            case 2:
                if (first) {
                    x=0;
                    if (second) y=1;
                    else if (third) y=2;
                    //else if (fourth) y=3;
                }
                else if (second) {
                    x=1;
                    if (third) y=2;
                    //else if (fourth) y=3;
                }
                else if(third) {
                    x=2;
                    y=3;
                }
                
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    // test the conditions
                    if (tempWord[x] == finalWord[x] && tempWord[y] == finalWord[y]) {
                        dictionary.push_back(tempWord); // load word
                    }
                }
                break;
            case 3:
                if (first) {
                    x=0;
                    if (second) {
                        y=1;
                        if (third) z=2;
                        //else if (fourth) z=4;
                    }
                    else if (third) {
                        y=2;
                        z=3;
                    }
                }
                else if (second) {
                    x=1;
                    if (third) {
                        y=2;
                        z=3;
                    }
                }
                
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    // test the conditions
                    if (tempWord[x] == initialWord[x] && tempWord[y] == initialWord[y] && tempWord[z] == initialWord[z]) {
                        dictionary.push_back(tempWord); // load word into list
                    }
                }
                break;
            case 4://exactly same word
                cerr << "WARNING : \nThe word you entered two same words, please re-enter\n";
                exit(1);
                break;
            default://two completely different word, execute these
                while (!wordsFile.eof()) {
                    wordsFile >> tempWord;
                    dictionary.push_back(tempWord); // load word into list
                }
                break;
        }
    }
    void getWords(){
        cout << "\nGame Rule : Enter 2 different words in four letters\n" << endl;
        cout<<"Please enter the word\n";
        cout << "Initial Word: ";
        cin >> initialWord;
        while (initialWord.length() != 4) {//if word entered does not meet criteria
            cout << "Invalid entry, please re-enter";
            cout << "Initial Word: ";
            cin >> initialWord;
        }
        cout << "Final Word: ";
        cin >> finalWord;
        while (finalWord.length() != 4) { //check if meet criteria
            cout << "Invalid entry, please re-enter";
            cout << "Final Word: ";
            cin >> finalWord;
        }
        for (int i = 0; i < initialWord.length(); i++) {
            initialWord[i] = initialWord[i] & 0xDF;
            finalWord[i] = finalWord[i] & 0xDF;
        }
    }
    int checkWords(){
        string tempWord;
        bool word1Found = false;
        bool word2Found = false;
        while (!wordsFile.eof() && (word1Found != true || word2Found != true)) {
            wordsFile >> tempWord;
            if (initialWord == tempWord) word1Found = true;
            if (finalWord == tempWord) word2Found = true;
        }
        if (word1Found == true && word2Found == true) {
            return 0;
        }
        else {
            cerr << "Sorry, I can not found the word\n";
            exit(1);
        }
    }
    void gameSolution(){
        Graph g(dictionary);
        // Get shortest path
        list<string> lePath = g.shortestPath(initialWord, finalWord);
        cout << "This is my answer: " << endl;
        for (list<string>::iterator it = lePath.begin(); it != lePath.end(); ++it) {
            cout << *it << endl;
        }
    }
    void gameStart(){
        getWords();
        checkWords();
        //loadWords();
        gameSolution();
    }
};


int main() {
    cout << "-------Word Ladder Game-------"<<endl;
    int a;
    cout<<"Please input the number of letter you want"<<endl;
    cin>>a;
    if(a==4)
    {
        Wordladder game;
        game.gameStart();
    }
    if(a==3)
    {
        Wordladder5 game5;
        game5.gameStart();
    }
    cout<<"Thank you"<<endl;
    return 0;
}
