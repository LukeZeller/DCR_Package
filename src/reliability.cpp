
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>

#include "reliability.h"

using namespace std;

long double R(long double p, int e, int d, vector< vector<int> > S) 
{
    int i;
    long double Sum = 0.0;    
     
    for (i = 0; i <= e; i++)
    {       
       Sum += S[d][i]*pow(p,i)*pow((1.0 - p), (e-i)); 
    }

    return Sum;
}

int max(vector<int> d0, int size)
{
    int max = d0[0];

    for (int i = 1; i < size; i++) 
    {
        if (d0[i] > max) 
        {
            max = d0[i];
        }
    }

    return max;
}


/*void print(vector<int> d0, int size)
{
    ofstream d0values;
    d0values.open("d0values.txt");

    for (int i = 0; i < size; i++)
    {
        if (d0values.is_open())
            d0values << i << " " << d0[i] << "\n";   
    }

    d0values.close();
}
*/


void d_comparison(int n, int e, vector< vector<int> > S_1, vector< vector<int> > S_2)
{
    int p_counter, d, d0_value;
    vector<int> d0;
    long double p;
    // Diameter constraint is to be used as at the most the number of (vertices(n) - 1). Thus, d = n - 1. 
    long double R1[1001][n];
    long double R2[1001][n];

    ofstream all;
    all.open("all.txt");
    

    for (p_counter = 0; p_counter <= 1000; p_counter++)
    {
        for (d = n - 1; d >= 0; --d)
        {
            // Getting the p value from 0 to 1. Increasing by 0.001
            p = p_counter/1000.0;
            
            R1[p_counter][d] = R(p, e, d, S_1);

            R2[p_counter][d] = R(p, e, d, S_2); 
   
            if (all.is_open())
               all << "For probability: " << p << " this is its d value: " << d << ". With 1st Re: " << R1[p_counter][d] << " and 2nd Re: " << R2[p_counter][d] << "\n";

            if (R1[p_counter][d] > R2[p_counter][d])
            { 
                d0.push_back(d + 1);
                //break;
            } 
         }
    }
    
    d0_value = max(d0, 1001);

    cout << "The d0 for this graph is: " << d0_value << endl;

    //print(d0, 1001);

    all.close();
}
