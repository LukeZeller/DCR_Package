#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

bool swng = false;

struct edge {
     int v;
     int u;
     double prob;
};

class Graph {
  private:
      double Rel;
      int diameter;
      int term;
      //float unqprb;
      int nodes;
      int edges;
      edge* List;
      int* Vector;
      int C[80][1500];
	  int source;
	  int terminal;
	  //i//nt max=80;
      int Max;
	  int counter;
	  int counter2;
	  //bool swng = false;


public:
      Graph (int n, int e,int d, int so, int te)  
         {
         Rel=0.0;
		 double g1, g2;
		 Max=1500;
		 int g4;
		 source=so;
		 terminal=te;
		 counter = 0;
		 counter2 = 0;
		 ifstream infile;
		 //ofstream outfile;
		 infile.open("graph.in");
		 //outfile.open("C:/documents and settings/louis/desktop/dcrexact/NSFREL14.txt");
         nodes=n; edges = e;diameter=d;
         List=new edge[e];
         Vector=new int[e];
         for (int j=0;j< e; j++)
	    { 
              infile >> List[j].u >> List[j].v >> g4 >> g1 >> g2 >> List[j].prob;
			  if (swng   && (j==0) ) List[j].u = nodes-1; //swing an edge;
			  //cout << endl << List[j].u << " " <<List[j].v << List[j].prob;
			  //List[j].u=List[j].v=0;
              //List[j].prob=p;
              Vector[j]=1;
            }
		 infile.close();
        }
      void Create();
      bool Diam(int d, int so, int te);
      void Backtrack(int edgenum);
      void PrintRel(); 
	  void SetST(int s1, int t1){source=s1; terminal= t1;Rel=0.0;}
	  double getR(){return Rel;}
}; 

//void swing() {swng = true;}
void Graph::PrintRel()
{ cout << endl << "The total Reliability with diameter < = " << diameter << " is " << Rel;
  double nds = nodes;
  cout << endl << "arboles " << Rel/pow (List[0].prob, nds -1.0);

}
void Graph::Backtrack(int edgenum)
{
    int i,j;
    double Ri=1.0;
    for (i=0; i < nodes; i++)
        for (j=0 ; j < nodes; j++)
             if (i !=j)       
               C[i][j]=Max;
             else
               C[i][j]=0;
	//cout << "edges" << edges;
    for (i=0; i < edges; i++)
         if (Vector[i])
           {  C[List[i].u][List[i].v]=1;
              C[List[i].v][List[i].u]=1;
           }

   
        if (this->Diam(diameter,source,terminal)) {
         for (i=0; i < edges; i++)
              if (Vector[i])
                  Ri=Ri * List[i].prob;
              else Ri=Ri * (1.0 - List[i].prob);
          Rel=Rel + Ri;
		  //cout << endl << "counter: " << ++ counter << " > D " << counter2 << " - rel: " << Ri;
          for (j=edgenum+1; j < edges; j++) {
              Vector[j]=0;
              this->Backtrack(j);
              Vector[j]=1;
		  }
		} else counter2 ++;
}

        
bool Graph::Diam(int d, int so, int te)
{
   int i,j,k;
    
   for (k = 0 ; k < nodes; k++) 
      for (i = 0; i < nodes; i ++)
         for (j = 0 ; j < nodes; j++)
             if((C[i][k] + C[k][j]) < C[i][j])
                 C[i][j]= C[i][k] + C[k][j];
   for (i=0; i < (terminal - 1); i++){
	  for(j=i+1; j < terminal; j++){
	    if (C[i][j] > d)
                 return (false);
	  } 
   }
   
        return (true);
}
 

void Graph::Create()
{
        int j;
       
      for (j=0; j < edges; j++)
      {  
	cout << "Enter endpoint u: ";
        cin >> List[j].u;
        cout << endl;
        cout << "Enter endpoint v: ";
        cin >> List[j].v ;
        cout << endl;
       
      }
     cout << endl;
    
}

int main() {
   int j, nodes, edges, diameter, counter=0;
   //float unqprob;
   cout << endl << "Enter number of nodes: ";
   cin >> nodes;
   cout << endl << "Enter Diameter: ";
   cin >> diameter;
   cout << endl;

   ofstream outfile;
//infile.open("C:/documents and settings/louis/desktop/dcrexact/NSFNET.txt");
   outfile.open("C:/users/Petingi/desktop/dcrexact/swing-10-16-d9-rare-case.txt");


  // outfile << endl << "14 nodes, 21 edges, Diameter= "<< diameter << "  Diameter-Constrained Rel.";
  outfile << endl << "All Terminal Reliability";
  outfile << endl << "=========================";
  outfile << endl << "Diameter: " << diameter;

  outfile << endl;
   //cin >> terminal;
   cout << endl << "Enter number of edges: ";
   cin >> edges;
   //cout << endl << "Enter unique edge probability: "3
   //cin >> unqprob;
   
   
   swng=false;
   Graph G(nodes,edges,diameter,0,nodes);
   //for (int l=0; l < nodes - 1 ; l++)
	  // for (int k=l+1; k < nodes ; k++)
         //int l=0, k;
	     //G.SetST(0,1);
         G.Backtrack(-1);
         G.PrintRel();
		 outfile  << endl << "Reliability: "<< G.getR();
		 outfile << endl << "================= After Swing ===================";
         swng = true;
    Graph Gs(nodes,edges,diameter,0,nodes);
	      
   //for (int l=0; l < nodes - 1 ; l++)
	  // for (int k=l+1; k < nodes ; k++)
         //int l=0, k;
	     //G.SetST(0,1);
         Gs.Backtrack(-1);
         Gs.PrintRel();
		 outfile  << endl << " swing Reliability: "<< Gs.getR();
		 outfile << endl;
      // }
   cout << endl << "enter to finish: ";
   cin >> j;
   outfile.close();
}
