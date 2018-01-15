/*
 * Title: K-Means Clustering
 * Author: Anisha Pal
 * Credits : Prof. Subrata Bose
 * Maintainer : Anisha Pal (pal.anisha26@outlook.com)
 * Descritption: Can be used for both user input or file input 
 * Method : Eucledian Distance and manhattan distance
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int main()
{
	int i, j, k, n, min_index, op1, flag = 0 ,count = 0;
	float d, min, pts[1000][2];
		
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
			char line[1000];
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
		printf("Enter the number of clusters you want to have ::\n");
		scanf("%d",&k);		
			
		// Knowing the method to form clusters
		int op2;
		printf("Press 1 for Eucledian Method :: Press 2 for Manhattan Method :: \n");
		scanf("%d",&op2);	
		
		int	c[k][n] = {0}, b[k][n] = {0}; 
		float mean[k][2];
		int top[k];
		
		memset(b, 0, sizeof b);
		memset(c, 0, sizeof c);
		
		// initializing the first means
		for(i=0;i<k;i++)
		{
			mean[i][0] = pts[i][0];
			mean[i][1] = pts[i][1];
		}
		
		while(1)
		{				
			flag = 0;			
			memset(b, 0, sizeof b);	     
			for(i=0;i<k;i++)
			{
				for(j=0;j<n;j++)
				{
					b[i][j] = c[i][j];
				}
			}
			
			memset(c, 0, sizeof c);			
			
			// finding the last element location in the clusters
			for(i=0;i<k;i++)
				top[i] = -1;			
			                                                  	
			for(i=0;i<n;i++)							
			{
				min = 5000000.00;
				for(j=0;j<k;j++)
				{
					// finding the element nearest to mean by euclidean distance
					// formula: sqrt((a1 - b1)^2 + (a2 - b2)^2)
					if(op2 == 1)
						d = sqrt(pow((mean[j][0] - pts[i][0]),2) + pow((mean[j][1] - pts[i][1]),2)); 
						
					// finding the element nearest to mean by manhattan distance
					// formula: |a1 - b1| + |a2 - b2|
					if(op2 == 2)
						d = abs(mean[j][0] - pts[i][0]) + abs(mean[j][1] - pts[i][1]);
						
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
			 count++;
		}
		
		// display of the final cluster elements with their respective means
		printf("---------- %d no. iterations----------\n",count);	
		printf("CLUSTER#\tCLUSTER MEAN\t\tCLUSTER \n");
		printf("--------\t------------\t\t------------\n");
		
		for(i=0;i<k;i++)
		{
			
			printf("%i\t\t%.2f,%.2f\t\t",i+1,mean[i][0],mean[i][1]);
			printf("{");
			printf("(%.2f,%.2f)",pts[c[i][0]][0],pts[c[i][0]][1]);                                             
			for(j=1;j<=top[i];j++)
				printf(", (%.2f,%.2f)", pts[c[i][j]][0],pts[c[i][j]][1] );
			printf("}\t");
			printf("\n");
		}
		getch();
		
	}
}
