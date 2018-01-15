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


int main()
{
	int i, j, k, n, min_index, op1, flag = 0;
	float d, min, pts[1000][2];

	FILE *fp1;

	fp1 = fopen("threek.csv","w");
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
				scanf("%f%f",&pts[i][0],&pts[i][1]);
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
				sscanf(line,"%f,%f",&pts[n][0],&pts[n][1]);
				n++;
			}
			for(i=0;i<n;i++)
				printf("%f, %f\n",pts[i][0],pts[i][1]);
		}

		if(op1 == 3)
			exit(0);
		// The main code starts here
		//printf("Enter the number of clusters you want to have ::\n");
		//scanf("%d",&k);

		// Knowing the method to form clusters
		int op2;
		printf("Press 1 for Eucledian Method :: Press 2 for Manhattan Method :: \n");
		scanf("%d",&op2);

		float SV[n] = {0};
		float ratio[n] = {0};
		for(k=1;k<n;k++)
		{
			//puts("PASS 0 ::");
			//int	c[k][n] = {0}, b[k][n] = {0};
			int* c = new int[k*k];
			int b;
			
			 for (int u = 0; u < n; u++)
			 {
			 	for (int v = 0; v < n; v++)
			 	{
			 		 b = u * n + v; // or whatever value it is you want to store
	             	c[u * n + v] = b;
	
	             		// Or to read a value...
	             	b = c[u * n + v];
				
			
			/*for(int z=0;z<k;z++)
			{
				c[z] = new int[n];
				b[z] = new int[n];
			}*/

			//puts("PASS 00 ::");
			float mean[k][2];
			//puts("PASS 000 ::");
			int top[k];

			//puts("PASS 1 ::");

			//memset(b, 0, sizeof b);
			//memset(c, 0, sizeof c);
			clear(b,k,n);
			clear(c,k,n);
			//puts("PASS 2 ::");

			// initializing the first means
			for(i=0;i<k;i++)
			{
				mean[i][0] = pts[i][0];
				mean[i][1] = pts[i][1];
			}

			while(1)
			{
				flag = 0;
				//getch();
				//memset(b, 0, sizeof(b[0][0])*k*n);
				clear(b,k,n);
				// copying the values to check if elements are same
				for(i=0;i<k;i++)
				{
					for(j=0;j<n;j++)
					{
						b[i][j] = c[i][j];
					}
				}
				//getch();
				//memset(c, 0, sizeof c);
				clear(c,k,n);
				// finding the last element location in the clusters
				for(i=0;i<k;i++)
					top[i] = -1;

				for(i=0;i<=n-1;i++)
				{
					min = 5000000.00;
					for(j=0;j<k;j++)
					{
						// finding the element nearest to mean by Euclidean distance
						// formula: sqrt((a1 - b1)^2 + (a2 - b2)^2)
						if(op2 == 1)
							d = sqrt(pow((mean[j][0] - pts[i][0]),2) + pow((mean[j][1] - pts[i][1]),2));


						// finding the element nearest to mean by Manhattan distance
						// formula: |a1 - b1| + |a2 - b2|
						if(op2 == 2)
							d = fabs(mean[j][0] - pts[i][0]) + fabs(mean[j][1] - pts[i][1]);

						if(d < min)
						{
							min = d;
							min_index = j;
						}
					}
					top[min_index]++;
					c[min_index][top[min_index]] = i;
				}


				// mean calculation
				for(i=0;i<k;i++)
				{
					if (top[i]==-1)
						break;
					float sum_x = 0;
					float sum_y = 0;
					for(j=0;j<=top[i];j++)
					{
						sum_x += pts[c[i][j]][0];
						sum_y += pts[c[i][j]][1];
					}
					mean[i][0] = sum_x/j;
					mean[i][1] = sum_y/j;
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
				printf("%i\t\t%.2f,%.2f\t\t",i+1,mean[i][0],mean[i][1]);
				printf("(%.2f,%.2f)",pts[c[i][0]][0],pts[c[i][0]][1]);
				for(j=1;j<=top[i];j++)
					printf(", (%.2f,%.2f)", pts[c[i][j]][0],pts[c[i][j]][1] );
				printf("\n");
			}
			//getch();

			// Finding Elbow
			float volume[k], rangex,rangey,mxx,mxy,mnx,mny,sumvol = 0;
			memset(volume, 0, sizeof volume);
			//memset(elb_sum, 0, sizeof elb_sum);
			int x,y,z;
			// Selecting cluster
			for(x=0;x<k;x++)
			{
			    mxx = 0;
				mxy = 0;
				mnx = 5000000;
				mny = 5000000;
				//printf("k = %d\n",k);
				if (top[x]==-1)
					break;


				// Selecting point from cluster
			   	for(y=0;y<=top[x];y++)
				{

					if( mxx < pts[c[x][y]][0])

						mxx = pts[c[x][y]][0];



					if( mnx > pts[c[x][y]][0])

						mnx = pts[c[x][y]][0];




					if( mxy < pts[c[x][y]][1])

						mxy = pts[c[x][y]][1];


					if( mny > pts[c[x][y]][1])

						mny = pts[c[x][y]][1];

				}

				rangex = mxx - mnx ;
				rangey = mxy - mny ;
				//printf("The rangex is  %f\n",rangex);
				//printf("The rangey is  %f\n",rangey);
				//getch();
				volume[x] =  rangex * rangey ;
				//printf("The volume is  %f\n", volume[x]);
				//getch();
				sumvol = sumvol + volume[x]	;
				//elb[x] = elb[x] + d;

				/* testing */

				//getch();
			}
			printf("The sum of volume is  %f\n",sumvol);

			// If eligibale for finding elbow percentage
			/*if(x>0)
			{
				puts("here!");
				float percentage = ((elb[x] - elb[x-1])/elb[x]) * 100;
				printf("The elbow percentage is %f\n", percentage);
			}*/
			SV[k] = sumvol ;

			if(k==1)
				continue;
			else
				ratio[k] = SV[k]/SV[k-1];

			printf("Ratio %d :: %f\n",k, ratio[k]);
			if(ratio == 0)
				break;
			if( k == 20)
			getch();
			//puts("test1");

		}
		
	}
	     	delete [] c;

	     	fprintf(fp1,"Ratio %d :: %f\n",k, ratio[k]);
		}



		getch();

	}


}
