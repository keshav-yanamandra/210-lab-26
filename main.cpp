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
    const int NUM_SLICES = 2;

    string raceNames[NUM_RACES] = {
            "Read",
            "Sort",
            "Insert",
            "Delete"
    };

    // times[0] = current simulation
    // times[1] = running totals
    long long times[NUM_SLICES][NUM_RACES][NUM_CONTAINERS] = {};

    for (int sim = 0; sim < NUM_SIMS; sim++) {

        vector<string> vectorCodes;
        list<string> listCodes;
        set<string> setCodes;

        string code;

        // Race 1: READING
        // File is opened before timing so only the reading is timed.

        ifstream finVector("codes.txt");

        auto start = high_resolution_clock::now();

        while (getline(finVector, code)) {
            vectorCodes.push_back(code);
        }

        auto end = high_resolution_clock::now();

        times[0][0][0] =
            duration_cast<nanoseconds>(end - start).count();

        finVector.close();


        ifstream finList("codes.txt");

        start = high_resolution_clock::now();

        while (getline(finList, code)) {
            listCodes.push_back(code);
        }

        end = high_resolution_clock::now();

        times[0][0][1] =
            duration_cast<nanoseconds>(end - start).count();

        finList.close();


        ifstream finSet("codes.txt");

        start = high_resolution_clock::now();

        while (getline(finSet, code)) {
            setCodes.insert(code);
        }

        end = high_resolution_clock::now();

        times[0][0][2] =
            duration_cast<nanoseconds>(end - start).count();

        finSet.close();


        // Race 2: SORTING

        start = high_resolution_clock::now();

        sort(vectorCodes.begin(), vectorCodes.end());

        end = high_resolution_clock::now();

        times[0][1][0] =
            duration_cast<nanoseconds>(end - start).count();


        start = high_resolution_clock::now();

        listCodes.sort();

        end = high_resolution_clock::now();

        times[0][1][1] =
            duration_cast<nanoseconds>(end - start).count();


        // A set is already sorted
        times[0][1][2] = 0;


        // Race 3: INSERTING

        start = high_resolution_clock::now();

        vector<string>::iterator vectorIt =
            vectorCodes.begin() + vectorCodes.size() / 2;

        vectorCodes.insert(vectorIt, "TESTCODE");

        end = high_resolution_clock::now();

        times[0][2][0] =
            duration_cast<nanoseconds>(end - start).count();


        start = high_resolution_clock::now();

        // The time includes finding the middle, not just the insert
        list<string>::iterator listIt = listCodes.begin();

        for (int i = 0; i < (int)listCodes.size() / 2; i++) {
            listIt++;
        }

        listCodes.insert(listIt, "TESTCODE");

        end = high_resolution_clock::now();

        times[0][2][1] =
            duration_cast<nanoseconds>(end - start).count();


        start = high_resolution_clock::now();

        setCodes.insert("TESTCODE");

        end = high_resolution_clock::now();

        times[0][2][2] =
            duration_cast<nanoseconds>(end - start).count();


        // Race 4: DELETING

        start = high_resolution_clock::now();

        vector<string>::iterator vectorDeleteIt =
            vectorCodes.begin() + vectorCodes.size() / 2;

        vectorCodes.erase(vectorDeleteIt);

        end = high_resolution_clock::now();

        times[0][3][0] =
            duration_cast<nanoseconds>(end - start).count();


        start = high_resolution_clock::now();

        list<string>::iterator listDeleteIt = listCodes.begin();

        // Casting to int to fix the warning
        for (int i = 0; i < (int)listCodes.size() / 2; i++) {
            listDeleteIt++;
        }

        listCodes.erase(listDeleteIt);

        end = high_resolution_clock::now();

        times[0][3][1] =
            duration_cast<nanoseconds>(end - start).count();


        start = high_resolution_clock::now();

        // A set has no random access, so walk to the middle
        set<string>::iterator setDeleteIt = setCodes.begin();

        for (int i = 0; i < (int)setCodes.size() / 2; i++) {
            setDeleteIt++;
        }

        setCodes.erase(setDeleteIt);

        end = high_resolution_clock::now();

        times[0][3][2] =
            duration_cast<nanoseconds>(end - start).count();


        // Add this simulation's times to the running totals
        for (int i = 0; i < NUM_RACES; i++) {
            for (int j = 0; j < NUM_CONTAINERS; j++) {
                times[1][i][j] += times[0][i][j];
            }
        }
    }

    cout << "Number of simulations: " << NUM_SIMS << endl;

    cout << setw(10) << "Operation"
        << setw(10) << "Vector"
        << setw(10) << "List"
        << setw(10) << "Set" << endl;


    for (int i = 0; i < NUM_RACES; i++) {
        cout << setw(10) << raceNames[i];

        for (int j = 0; j < NUM_CONTAINERS; j++) {
            cout << setw(10) << times[1][i][j] / NUM_SIMS;
        }

        cout << endl;
    }

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/