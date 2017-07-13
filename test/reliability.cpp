// Modify as you please. Let me know if it makes no sense at all. 

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


// Function Prototypes
float R(float p, int e, const float S);
void d_comparison(int n, int e, vector <float> S_1, vector <float> S_2);

// Formula
float R(float p, int e, const float S) 
{
    int i;
    float Sum = 0.0;    
            
    for (i = 0; i <= e; i++)
    {
        Sum += S*pow(p,i)*pow((1.0 - p), (e-i)); 
    }

    return Sum;
}

// To compare between normal reliability and swing surgery, looking for d0
void d_comparison(int n, int e, vector <float> S_1, vector <float> S_2)
{
    int p_counter, d, i;
    float p;
    // Diameter constraint is to be used as at the most the number of (vertices(n) - 1). Thus, d = n - 1. 
    float R1[1001][n-1];
    float R2[1001][n-1];

    for (p_counter = 0; p_counter <= 1000; p_counter++)
    {
        for (d = 0; d <= n-1; d++)
        {
            // Getting the p value from 0 to 1. Increasing by 0.001
            p = p_counter/1000.0;

            R1[p_counter][d] = R(p, e, S_1[d]);

            R2[p_counter][d] = R(p, e, S_2[d]); 

            // Comparison
            if (R2[p_counter][d] >= R1[p_counter][d])
            {
                // Really long. I have not fixed this part yet to show us exactly the d0. 
                cout << "Starting with: " << endl;
                cout << d << ": "<< R2[p_counter][d] << endl;
            }                    
        } 
    }

}

int main()
{
    int vert, edg;   
    vector<float> S_1;
    vector<float> S_2; 

    // Testing values from Dr. Petingi's code
    S_1.push_back(0.0); // 0
    S_1.push_back(0.0);
    S_1.push_back(0.0);
    S_1.push_back(0.0169373); 
    S_1.push_back(0.074234);
    S_1.push_back(0.111145);
    S_1.push_back(0.120186);
    S_1.push_back(0.121613);
    S_1.push_back(0.121704); //8

    S_2.push_back(0.0);
    S_2.push_back(0.0);
    S_2.push_back(0.0);
    S_2.push_back(0.0122833);
    S_2.push_back(0.0698318);
    S_2.push_back(0.110283);
    S_2.push_back(0.121117);
    S_2.push_back(0.122711);
    S_2.push_back(0.122803);
    
    cout << "Enter the number of vertices: " << endl;
    cin >> vert;
    cout << "Enter the number of edges: " << endl;
    cin >> edg;

    d_comparison(vert, edg, S_1, S_2); 

    return 0;
}
