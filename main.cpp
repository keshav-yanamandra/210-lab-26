// Keshav Yanamandra
// COMSC-210-5293, Fall 2026
// Lab 26
// Started from my Lab 25 code

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int main() {

    const int NUM_RACES = 4;
    const int NUM_CONTAINERS = 3;
    const int NUM_SIMS = 15;

    string raceNames[NUM_RACES] = {
        "Read",
        "Sort",
        "Insert",
        "Delete"
    };

    string containerNames[NUM_CONTAINERS] = {
        "Vector",
        "List",
        "Set"
    };

    for (int sim = 0; sim < NUM_SIMS; sim++) {

        vector<string> vectorCodes;
        list<string> listCodes;
        set<string> setCodes;

        string code;

        long long vectorTimes[NUM_RACES] = {};
        long long listTimes[NUM_RACES] = {};
        long long setTimes[NUM_RACES] = {};

    // Race 1: READING
    // File is opened before timing so only the reading is timed.

    ifstream finVector("codes.txt");

    auto start = high_resolution_clock::now();

    while (getline(finVector, code)) {
        vectorCodes.push_back(code);
    }

    auto end = high_resolution_clock::now();

    vectorTimes[0] = duration_cast<nanoseconds>(end - start).count();
    finVector.close();


    ifstream finList("codes.txt");

    start = high_resolution_clock::now();

    while (getline(finList, code)) {
        listCodes.push_back(code);
    }

    end = high_resolution_clock::now();

    listTimes[0] = duration_cast<nanoseconds>(end - start).count();
    finList.close();


    ifstream finSet("codes.txt");

    start = high_resolution_clock::now();

    while (getline(finSet, code)) {
        setCodes.insert(code);
    }

    end = high_resolution_clock::now();

    setTimes[0] = duration_cast<nanoseconds>(end - start).count();
    
    finSet.close();

    // Race 2: SORTING

    start = high_resolution_clock::now();
    sort(vectorCodes.begin(), vectorCodes.end());
    end = high_resolution_clock::now();
    vectorTimes[1] = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    listCodes.sort();
    end = high_resolution_clock::now();
    listTimes[1] = duration_cast<nanoseconds>(end - start).count();


    // A set is already sorted
    setTimes[1] = -1;


    // Race 3: INSERTING
    start = high_resolution_clock::now();
    vector<string>::iterator vectorIt = vectorCodes.begin() + vectorCodes.size() / 2;

    vectorCodes.insert(vectorIt, "TESTCODE");
    end = high_resolution_clock::now();

    vectorTimes[2] = duration_cast<nanoseconds>(end - start).count();
    start = high_resolution_clock::now();

    // the time includes finding the middle, not just the insert    
    list<string>::iterator listIt = listCodes.begin();
    for (int i = 0; i < (int)listCodes.size() / 2; i++) {
        listIt++;
    }

    listCodes.insert(listIt, "TESTCODE");
    end = high_resolution_clock::now();

    listTimes[2] = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    setCodes.insert("TESTCODE");
    end = high_resolution_clock::now();

    setTimes[2] = duration_cast<nanoseconds>(end - start).count();


    // Race 4: DELETING

    start = high_resolution_clock::now();
    vector<string>::iterator vectorDeleteIt = vectorCodes.begin() + vectorCodes.size() / 2;
    vectorCodes.erase(vectorDeleteIt);
    end = high_resolution_clock::now();

    vectorTimes[3] = duration_cast<nanoseconds>(end - start).count();
    start = high_resolution_clock::now();
    
    list<string>::iterator listDeleteIt = listCodes.begin();

    //casting to int to fix the warning
    for (int i = 0; i < (int)listCodes.size() / 2; i++) {
        listDeleteIt++;
    }

    listCodes.erase(listDeleteIt);
    end = high_resolution_clock::now();
    listTimes[3] = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();

    // A set has no random access, so walk to the middle. this will take longer
    set<string>::iterator setDeleteIt = setCodes.begin();
    for (int i = 0; i < (int)setCodes.size() / 2; i++) {
        setDeleteIt++;
    }

    setCodes.erase(setDeleteIt);
    end = high_resolution_clock::now();

    setTimes[3] = duration_cast<nanoseconds>(end - start).count();
    
    cout << "Simulation " << sim + 1 << " complete." << endl;

    }
    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/