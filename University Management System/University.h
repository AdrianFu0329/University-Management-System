#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <iostream>
using namespace std;

class University {
public:
    int rank;
    string name;
    string location;
    double ar; // academic reputation
    int arRank;
    double er; // employer reputation
    int erRank;
    double fsr; // faculty/student ratio
    int fsrRank;
    double cpf; // citations per faculty
    int cpfRank;
    double ifr; // international faculty ratio
    int ifrRank;
    double isr; // international student ratio
    int isrRank;
    double irn; // international research network
    int irnRank;
    double ger; // employment outcome
    int gerRank;

    friend ostream& operator<<(ostream& os, const University& uni);
};

#endif // UNIVERSITY_H