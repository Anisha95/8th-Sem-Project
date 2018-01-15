#include <bits/stdc++.h>
#include <float.h>
# define MAX 10000
#include <conio.h>
#include <string>
using namespace std;

vector<int>medoids1;        // (n-1)th medoid
vector<int>medoids2;        // nth medoid
vector<int>temp_medoid;     // medoid formed with swapped non-medoid
float pts[MAX][2];          // stores the points from .csv file

// Calculates the cost of the medoid configuration
float calculateCost(vector<int> &medoid, int n, int k)
{
    float cost = 0;
    for(int i=0;i<n;i++)
    {
        float min = LONG_LONG_MAX;
        for(int j=0;j<k;j++)
        {
            // finding the minimum cost by Manhattan distance
            // formula: |a1 - b1| + |a2 - b2|
            float d = fabs(pts[medoid[j]][0] - pts[i][0]) + fabs(pts[medoid[j]][1] - pts[i][1]);
            if(d < min)
                min = d;
        }
        cost += min;
    }
    return cost;
}

// driver program
int main()
{
    int n = 0;
    // loading points from FILE
    FILE *fp;
    char loc[1000];
    n = 0;
    puts("Enter the file location :: ");
    fflush(stdin);
    gets(loc);
    fp = fopen(loc,"r");
    if(fp == NULL)
    {
        puts("File not found !");
        exit(1);
    }
    char line[1000000];
    n = 0;
    while(fgets(line, sizeof line, fp))
    {
        sscanf(line,"%f,%f",&pts[n][0],&pts[n][1]);
        n++;
    }
    for(int i=0;i<n;i++)
        printf("%d. (%.2f, %.2f)\n",i+1,pts[i][0],pts[i][1]);

    // Getting cluster details
    int k;
    cout << "Enter number of clusters" << endl;
    cin >> k;

    // Random choosing of K-Medoids and assigning them to nth medoid
    for(int i=0;i<k;i++)
    {
        int temp = rand()%n;
        medoids2.push_back(temp);
    }

    // loops till there's no change in medoid configuration
    while(medoids1 != medoids2)
    {
        medoids1 = medoids2;            // creating backup of nth medoid
        int i,j;
        for(i=0;i<k;i++)
        {
            int temp = medoids2[i];    // calculating the cost of current configuration
            bool flag = false;
            float c1 = calculateCost(medoids2, n, k);

            temp_medoid = medoids2;
            for(j=0;j<n;j++)
            {
                if(temp == j)
                    continue;
                temp_medoid[i] = j;     // calculating the cost of the new configuration
                float c2 = calculateCost(temp_medoid, n, k);

                if(c2<c1)               // on better results changing the configuration and re-computing
                {
                    medoids2[i] = j;
                    flag = true;
                    break;
                }
            }

            if(flag)
            {
                i--;
                continue;
            }

        }
    }

    // creating the output files

    ofstream fmout("out_medoid.csv", ios::out);

    // formatted display of the result
    cout << "MEET THE FINAL MEDOIDS" << endl;
    for(int xx=0; xx<k; xx++)
    {
        cout << "(" << pts[medoids2[xx]][0] << "," << pts[medoids2[xx]][1] << ") ";
        fmout << pts[medoids2[xx]][0] << "," << pts[medoids2[xx]][1] << endl;
    }
    cout << endl;

    int cluster[k][n-k], top[k];
    memset(top, -1, sizeof(top));
    memset(cluster, 0, sizeof(cluster));
    int i,j;
    for(i=0;i<n;i++)
    {
        int cluster_number;
        float min = LONG_LONG_MAX;
        for(j=0;j<k;j++)
        {
            // finding the minimum cost by Manhattan distance
            // formula: |a1 - b1| + |a2 - b2|
            cout << pts[medoids2[j]][0] << " - " << pts[i][0] << " + " << pts[medoids2[j]][1] << " - " << pts[i][1] << endl;
            float d = fabs(pts[medoids2[j]][0] - pts[i][0]) + fabs(pts[medoids2[j]][1] - pts[i][1]);
            if(d < min)
            {
                min = d;
                cluster_number = j;
            }
        }
        top[cluster_number] += 1;
        cluster[cluster_number][top[cluster_number]] = i;
        cout << pts[i][0] << "," << pts[i][1] << " is going to cluster " << cluster_number << endl;
        cout << cluster_number << " , " <<  top[cluster_number] << " = " << i << endl;
        cout << top[cluster_number] << endl;
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<n;j++)
                cout << cluster[i][j] << " ";
            cout << endl;
        }

        getch();
    }


    for(int i=0;i<k;i++)
    {
        // creating the dynamic files
        cout << "CLUSTER " << i+1 << " :: {";
        for(int j=0;j<=top[i];j++)
        {
            cout << "(" << pts[cluster[i][j]][0] << "," << pts[cluster[i][j]][1] << ") ";
        }
        cout << "\b}" << endl;
    }
	getch();
    return 0;
}
