#ifndef GRAPHS_H
#define GRAPHS_H

#include <bits/stdc++.h>

#define adjacencyMap(type) unordered_map<type, vector<type>>
#define visitedMap(type) unordered_map<type, bool>

using namespace std;

// Acyclic digraph
unordered_map<string, vector<string>> G1 = {
    {"A", {"B", "E"}},
    {"B", {"E", "F"}},
    {"C", {"D"}},
    {"D", {}},
    {"E", {"C", "F"}},
    {"F", {"D", "G"}},
    {"G", {}},
};

// Simple graph (cyclic, not bipartite, three connected components)
unordered_map<string, vector<string>> G2 = {
    {"A", {"B"}},
    {"B", {"A", "D", "E"}},
    {"C", {}},
    {"D", {"B", "E"}},
    {"E", {"B", "D", "F"}},
    {"F", {"E"}},
    {"G", {"H"}},
    {"H", {"G"}},
};

// Digraph (cyclic)
unordered_map<string, vector<string>> G3 = {
    {"A", {"B", "E"}},
    {"B", {"E"}},
    {"C", {"D"}},
    {"D", {}},
    {"E", {"C", "F"}},
    {"F", {"B", "D", "G"}},
    {"G", {}},
};

// Digraph (cyclic, four strongly connected components)
unordered_map<int, vector<int>> G4 = {
    {1, {3}},
    {2, {4, 10}},
    {3, {5, 11}},
    {4, {7}},
    {5, {1, 7, 9}},
    {6, {10}},
    {7, {9}},
    {8, {6}},
    {9, {2, 4, 8}},
    {10, {8}},
    {11, {6, 8}},
};

// Digraph (acyclic)
unordered_map<string, vector<string>> G5 = {
    {"A", {"B"}},
    {"B", {"C", "F"}},
    {"C", {"D"}},
    {"D", {"E"}},
    {"E", {}},
    {"F", {"E"}},
    {"G", {"H", "I"}},
    {"H", {"I", "F"}},
    {"I", {}},
};

// Simple graph (cube, bipartite, connected)
unordered_map<string, vector<string>> G6 = {
    {"000", {"100", "010", "001"}},
    {"001", {"101", "011", "000"}},
    {"010", {"110", "000", "011"}},
    {"100", {"000", "110", "101"}},
    {"011", {"111", "001", "010"}},
    {"101", {"001", "111", "100"}},
    {"110", {"010", "100", "111"}},
    {"111", {"011", "101", "110"}},
};

// Digraph (cyclic)
unordered_map<string, vector<string>> G7 = {
    {"A", {"B"}},
    {"B", {"C", "F"}},
    {"C", {"D"}},
    {"D", {"E"}},
    {"E", {}},
    {"F", {"E"}},
    {"G", {"H"}},
    {"H", {"I", "F"}},
    {"I", {"G"}},
};
#endif
