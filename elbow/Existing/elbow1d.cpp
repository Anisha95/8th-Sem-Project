/*
 * Title: K-Means Clustering
 * Author: Anisha Pal
 * Credits : Prof. Subrata Bose
 * Maintainer : Anisha Pal (pal.anisha26@outlook.com)
 * Descritption: Can be used for both user input or file input
 * Method : Eucledian Distance
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int clear(int **a, int x, int y)
{
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			a[i][j] = 0;
		}
	}
}

int clearf(double **a, int x, int y)
{
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			a[i][j] = 0;
		}
	}
}

int main()
{
	int i, j, k, n, min_index, op1, flag = 0;
	float d, min, pts[1000];
	float mean[k];
	double SSE;
	FILE *fp1;

	fp1 = fopen("Eucl.csv","w");
	if (fp1 == NULL)
        puts("Bad day..");

	while(1)
	{
        system("cls");
		// taking user-input to choose either user-input or file-input
		printf("Press 1 for user-input :: Press 2 for file-input :: Press 3 to exit ::\n");
		scanf("%d",&op1);
		// for user-input
		if(op1 == 1)
		{
			printf("Enter the number of elements you want to print :: \n");
			scanf("%d",&n);
			printf("Enter co_ordinates::\n");
			for(i=0;i<n;i++)
				scanf("%f",&pts[i]);
		}
		// for file-input
		if(op1 == 2)
		{
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
				getch();
				continue;
			}
			char line[1000000];
			n = 0;
			while(fgets(line, sizeof line, fp))
			{
				sscanf(line,"%f",&pts[n]);
				n++;
			}
			for(i=0;i<n;i++)
				printf("%f\n",pts[i]);
		}
		if(op1 == 3)
			exit(0);
		// The main code starts here
		// Knowing the method to form clusters
		int op2;
		printf("Press 1 for Eucledian Method :: Press 2 for Manhattan Method :: \n");
		scanf("%d",&op2);

		for(k=1;k<n;k++)
		{
			//puts("testing eee re\n");
			int** c = new int*[k];
			int** b = new int*[k];
			for(int z=0;z<k;z++)
			{
				c[z] = new int[n];
				b[z] = new int[n];
			}
			float mean[k];
			int top[k];
			SSE = 0;
			clear(b,k,n);
			clear(c,k,n);
			// initializing the first means
			
			for(i=0;i<k;i++)
			{
				mean[i] = pts[i];						// initially averages are set to as the elemnts of the given user arrray .. 
				
			}
						
			
			while(1)
			{
				flag = 0;
				clear(b,k,n);
				// copying the values to check if elements are same
				for(i=0;i<k;i++)
				{
					for(j=0;j<n;j++)
					{
						b[i][j] = c[i][j];
					}
				}
				clear(c,k,n);
				// finding the last element location in the clusters
				for(i=0;i<k;i++)
					top[i] = -1;

				for(i=0;i<=n-1;i++)
				{
					min = 5000000.00;
					for(j=0;j<k;j++)
					{
						if( pts[i] == pts[i+1])
							{
								printf("Sorry!");
								break;
							}
						// finding the element nearest to mean by Euclidean distance
						
						d = fabs(mean[j] - pts[i]);
						
						if(d < min)
						{
							min = d;
							min_index = j;
						}
					}
					top[min_index]++;
					c[min_index][top[min_index]] = pts[i];
				}
                // mean calculation
				
				
				
				
				for(i=0;i<k;i++)
				{
					if (top[i]==-1)
						break;
					float sum= 0;
				
					for(j=0;j<=top[i];j++)
					{
						sum += pts[c[i][j]];
						
					}
					mean[i] = sum/j;
					printf("%f\n",mean[i]);
				}
				
			
				// breaking out from the loop if the cluster elements remains the same as before..
				for(i=0;i<k;i++)
				{

					for(j=0;j<n;j++)
					{
							if(b[i][j] != c[i][j])
							{
								flag = 1;
								break;
							}
					}
				}
				if(flag == 0)
				break;
			}
			
			
					
			// display of the final cluster elements with their respective means
			printf("CLUSTER#\tCLUSTER MEAN\t\tCLUSTER ELEMENT\n");
			printf("--------\t------------\t\t---------------\n");

			
				for(i=0;i<k;i++)
				{
					printf("%i\t\t%d\t\t",i+1,mean[i]);
					printf("%d",c[i][0]);
					for(j=1;j<=top[i];j++)
						printf(", %d",c[i][j]);
						getch();
					printf("\n");
				}
			

			/* ********************* TEST ******************** */
			// Finding Elbow
			double elb[k];//elb_sum[k][n];
			double** elb_sum = new double*[k];
			for(int z=0;z<k;z++)
				elb_sum[z] = new double[n];

			memset(elb, 0, sizeof elb);
			clearf(elb_sum,k,n);
			int xx,yy;
			// Selecting cluster
			printf("k = %d\n",k);
			for(xx=0;xx<k;xx++)
			{
				if (top[xx]==-1)
					break;
				// Selecting point from cluster
				for(yy=0;yy<=top[xx];yy++)
				{
					d = fabs(mean[xx] - pts[c[xx][yy]]);
						
					// Elbow
					elb[xx] = elb[xx] + d;
				}
				SSE = SSE + elb[xx];
			}
			//SSE = SSE + elb[x];
			printf("SSE value for given k:  = %f\n",SSE);
			for(int z=0;z<k;z++)
			{
				delete [] c[z];
				delete [] b[z];
				delete [] elb_sum[z];
			}

			delete [] b;
	     	delete [] c;
	     	delete [] elb_sum;

	     	fprintf(fp1,"%d,%f\n",k,SSE);
	     	//puts("testing e  re\n");
	     	//getch();
		}



		getch();

	}


}
