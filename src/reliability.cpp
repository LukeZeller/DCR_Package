
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>

#include "reliability.h"

using namespace std;

// Calculating R for each probability starting at p = 0 until p = 1
// d is being passed from d_comparison to use the vector of vector of ints
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

// To find the maximum value for which R2 > R1. It receives a vector of all d0's and then finds max.
// Then, that is the d0 for the whole graph.
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

// To compare and find our d0's for each probability
void d_comparison(int n, int e, vector< vector<int> > S_1, vector< vector<int> > S_2)
{
    // For the 2 for-loops
    int p_counter, d;
    // To hold all d0's and send to Max
    vector<int> d0;
    // To hold the final d0_value for the whole graph
    int d0_value;
    // Our probabilty
    long double p;
    // Diameter constraint is to be used as at the most the number of (vertices(n) - 1). Thus, d = n - 1. 
    long double R1[1001][n-1];
    long double R2[1001][n-1];

    // Saving values in 2 files
    ofstream d0values;
    ofstream all;
    
    d0values.open("d0values.txt");
    all.open("all.txt");
    

    for (p_counter = 0; p_counter <= 1000; p_counter++)
    {
        for (d = 0; d <= n-1; d++)
        {
            // Getting the p value from 0 to 1. Increasing by 0.001
            p = p_counter/1000.0;
            
            // R1 and R2 holds reliability before and after
            R1[p_counter][d] = R(p, e, d, S_1);

            R2[p_counter][d] = R(p, e, d, S_2); 
   
            // File for all probabilities and all d's for reference purposes
            if (all.is_open())
               all << "For probability: " << p << " this is its d value: " << d << ". With 1st Re: " << R1[p_counter][d] << " and 2nd Re: " << R2[p_counter][d] << "\n";

            // Looking for values of d for which R2 is GREATER than R1
            if (R2[p_counter][d] > R1[p_counter][d])
            { 
                // Pushing the values of d for which R2 > R1. It works using a break statement because it takes the first instance for which d R2 > R1.
                d0.push_back(d);

                // Looking at the values for which R2 > R1
                if (d0values.is_open())
                    d0values << "For probability: " << p << " for d value " << d << " R2 " << R2[p_counter][d]  << " than R1 " << R1[p_counter][d] << "\n";
                 
                // This statement must be uncommented if you want the result of d0 for the max function. If it is commented out, the d0 will be 10 because all values starting at 6
                // or 7 go up to 10 and 10 being passed to the max of course it will the biggest one.
                // Need to fix for this type of case: [4, 6, 7, 8, 9 ,10] For which d0 is 6.
                // When running the code for 11 17 AND using the break statements, the d0's are 7's.... and 4's.... (-4- which in reality should be 6)
                // In the all file you can see.

                //break;  

                // I was thinkig on making a function to see when it is consecutive until the end and then the first instance will be the result. So for example: [4, 6, 7, 8, 9, 10]
                // since 5 does not go after 4, then it is not consecutive. But starting at 6 it starts being consecutive until the end, therefore 6 will be our d0 and the value the 
                // function will return. (Just an idea, but there might be a quicker way to do this)   
            } 
         }
    }
    
    // Looking for the max.
    max(d0_resuls, 1001);
    // Final d0 value for the whole graph
    d0_value = max(d0, 1001);

    cout << "The d0 for this graph is: " << d0_value << endl;

    d0values.close();
    all.close();
}
