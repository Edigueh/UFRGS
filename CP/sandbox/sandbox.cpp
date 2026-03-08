#include <bits/stdc++.h>
using namespace std;

int main(void) {
    map<string, vector<string>> propPrefs = {
        {"Atlanta", {"Wayne", "Val", "Yolanda", "Zeus", "Xavier"}},
        {"Boston", {"Yolanda", "Wayne", "Val", "Xavier", "Zeus"}},
        {"Chicago", {"Wayne", "Zeus", "Xavier", "Yolanda", "Val"}},
        {"Detroit", {"Val", "Yolanda", "Xavier", "Wayne", "Zeus"}},
        {"El Paso", {"Wayne", "Yolanda", "Val", "Zeus", "Xavier"}}
    };

    map<string, vector<string>> recPrefs = {
        {"Val", {"El Paso", "Atlanta", "Boston", "Detroit", "Chicago"}},
        {"Wayne", {"Chicago", "Boston", "Detroit", "Atlanta", "El Paso"}},
        {"Xavier", {"Boston", "Chicago", "Detroit", "El Paso", "Atlanta"}},
        {"Yolanda", {"Atlanta", "El Paso", "Detroit", "Chicago", "Boston"}},
        {"Zeus", {"Detroit", "Boston", "El Paso", "Chicago", "Atlanta"}}
    };
}
