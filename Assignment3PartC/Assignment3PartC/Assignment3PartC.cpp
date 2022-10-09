#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_map>
using namespace std;

vector<string> loadData(string);
string returnWord(string);
string getKey(string);
string getDefinitions(string);
vector<string> splitDefinitions(string);
tuple<string, string, int> createTuple(string);
int getTuplePosition(vector<tuple<string, string, int>>& v, string p, string d);
bool checkTuple(vector<tuple<string, string, int>>, string, string);
vector<tuple<string, string, int>> fillDefinitionsVector(vector<string>);
void fillMap(unordered_map <string, vector<tuple<string, string, int>>>&, vector<string>);

// filter functions
void sortVectorByDefinition(string, vector<tuple<string, string, int>>, vector<string>);
int findStart(string, vector<tuple<string, string, int>>, vector<string>);
int findEnd(string, vector<tuple<string, string, int>>, vector<string>);

// User interface Functions
void initiateInterface();
void help();
void notFound();
bool containsTerm(string);
bool isPartOfSpeech(string);
bool isReverse(string);
bool isDistinct(string);
void argument1Check(string);
void argument2Check(string);
void argument3Check(string);
void argument4Check(string);

// TODO
// - sort by part of speech
// - sort by definition in part of speech

int main()
{
    unordered_map <string, vector<tuple<string, string, int>>> book;
    vector<string> rawData = loadData("Data.CS.SFSU.txt");
    vector<string> partsOfSpeech = {
            "adjective",
            "adverb",
            "conjunction",
            "interjection",
            "noun",
            "preposition",
            "pronoun",
            "verb"
    };
    fillMap(book, rawData);

    for (auto x : book) {
        //cout << "hello" << endl;
        string pos, def;
        int n;
        cout << x.first << endl;
        for (tuple<string, string, int> v : x.second) {
            tie(pos, def, n) = v;
            cout << pos << " | " << def << " | " << n << endl;
        }
    }


    //vector<string> x = splitDefinitions(getDefinitions(rawData[8]));
    //vector<tuple<string, string, int>> defTest = fillDefinitionsVector(x);
    //int i = 0;
    //string tempDef, tempPos;
    //int n;
    //for (tuple<string, string, int> def : defTest) {
    //    i++;
    //    tie(tempPos, tempDef, n) = def;
    //    cout << i << ": " << tempPos << " | " << tempDef << " | " << n << endl;
    //}
}

vector<string> loadData(string a) {
    fstream ioFile;
    string line, fileName;
    vector<string> rawData = {};


    ioFile.open(a, ios::in);
    while (!ioFile.is_open()) {
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        cout << "<!>ERROR<!> ===> Provided file path: " << a << endl;
        cout << "<!>Enter the CORRECT data file path: ";
        cin >> fileName;
        ioFile.open(fileName, ios::in);
    }
    while (getline(ioFile, line)) {
        rawData.push_back(line);
    }
    ioFile.close();
    return rawData;
}

string returnWord(string str) {
    stringstream ss(str);
    string word;
    while (!ss.eof()) {
        ss >> word;
        cout << word << endl;
    }
    return word;
}

string getKey(string str) {
    int count = 0;

    while (str.at(count) != '|') {
        count++;
    }
    return str.substr(0, count);
}

string getDefinitions(string str) {
    int count = 0;

    while (str.at(count) != '|') {
        count++;
    }
    return str.substr(count, str.length());
}
vector<string> splitDefinitions(string str) {
    vector<string> definitions = {};
    stringstream ss(str);
    string def;
    while (getline(ss, def, '|')) {
        definitions.push_back(def);
    }
    // for (string d : definitions)
    // {
    //     cout << "Split definition: " << d << endl;
    // }
    return definitions;
}


// create a tuple
// add part of speech
// definition
// number of times it appears
tuple<string, string, int> createTuple(string str) {
    int arrowStart = str.find(' ');
    // cout << arrowStart << endl;
    string pos, def;


    pos = str.substr(0, arrowStart);
    def = str.substr(arrowStart + 6, str.length());

    return make_tuple(pos, def, 1);
}


int getTuplePosition(vector<tuple<string, string, int>>& v, string p, string d) {
    string pos, def;
    int n;
    for (int i = 0; i < v.size(); i++) {
        tie(pos, def, n) = v[i];
        // cout << pos << " " << def << " " << n << endl;
        if (pos == p && def == d) {
            return i;
        }
    }
    return -1;
}

vector<tuple<string, string, int>> fillDefinitionsVector(vector<string> v) {
    vector<tuple<string, string, int>> output = {};
    tuple<string, string, int> temp;
    string str, tempDef, tempPos;
    int position;
    for (int i = 1; i < v.size(); i++) {
        str = v[i];
        if (output.size() == 0) {
            output.push_back(createTuple(str));
        }
        else {
            temp = createTuple(str);
            tie(tempPos, tempDef, ignore) = temp;
            position = getTuplePosition(output, tempPos, tempDef);
            if (position > -1) {
                get<2>(output[position]) += 1;
            }
            else {
                output.push_back(createTuple(str));
            }
        }
    }
    sort(output.begin(), output.end());
    return output;
}

void fillMap(unordered_map <string, vector<tuple<string, string, int>>>& map, vector<string> data) {
    string key, definitions;
    vector<string> storeRawDefinitions;
    vector<tuple<string, string, int>> storeDefinitions;
    for (int i = 0; i < data.size(); i++) {
        key = getKey(data[i]);
        definitions = getDefinitions(data[i]);
        storeRawDefinitions = splitDefinitions(definitions);
        storeDefinitions = fillDefinitionsVector(storeRawDefinitions);
        //cout << key << endl;
        map[key] = storeDefinitions;
    }
}


void sortVectorByDefinition(string pos, vector<tuple<string, string, int>>& v, const vector<string>& vp) {
    int i, j= 0;
    while (j <= v.size()) {

    }
}
int findStart(string p, vector<tuple<string, string, int>>& v, const vector<string>& vp) {
    string partOfSpeech;
    for (int i = 0; i < v.size(); i++) {
        tie(partOfSpeech, ignore, ignore) = v.at(i);
        if (partOfSpeech == p) {
            return i;
        }
    }
    return -1;
}
int findEnd(string pos, vector<tuple<string, string, int>>& v, const vector<string>& vp) {
    string current, next;
    return -1;
}


/// ############################
/// ####  USER INTERFACE METHODS
/// ############################

//void initiateInterface();
void help() {
    cout << "    |" << endl;
    cout << "    PARAMETER HOW-TO, please enter:" << endl;
    cout << "    1. A search key -then 2. An optional part of speech -then" << endl;
    cout << "    3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
    cout << "    |" << endl;
}
void notFound() {
    cout << "    |" << endl;
    cout << "    <NOT FOUND> To be considered for the next release. Thank you." << endl;
    cout << "    |" << endl;
}
//bool containsTerm(string) {
//
//}
//bool isPartOfSpeech(string);
//bool isReverse(string);
//bool isDistinct(string);
//void argument1Check(string);
//void argument2Check(string);
//void argument3Check(string);
//void argument4Check(string);
