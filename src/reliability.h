#ifndef _RELIABILITY_H
#define _RELIABILITY_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


// Function Prototypes
double R(double p, int e, vector< vector<int> > S);
int max(vector<int> d0, int size);
void d_comparison(int n, int e, vector< vector<int> > S_1, vector< vector<int> > S_2);

#endif
