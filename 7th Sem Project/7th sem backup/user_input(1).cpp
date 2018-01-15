#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int main()
{
		int i,j,k,n,min_index, sig = 0;
		float sub,sum,min;
		int flag = 0;
		
		printf("Enter the number of elements you want to print :: \n");
		scanf("%d",&n);
		
		float a[n];
		printf("Enter the elements you want to give ::\n");
		
		for(i=0;i<n;i++)
			scanf("%f",&a[i]);
		
		printf("Enter the number of clusters you want to have ::\n");
		scanf("%d",&k);		
			
		float	c[k][n] = {0.0}, b[k][n] = {0.0}, avg[k], s;
		int top[k];
		
		memset(b, 0, sizeof b);
		memset(c, 0, sizeof c);
		for(i=0;i<k;i++)
				avg[i] = a[i];
		
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
			
			for(i=0;i<k;i++)
				top[i] = -1;			
				
			for(i=0;i<n;i++)
			{
				min = 5000000;
				for(j=0;j<k;j++)
				{
					sub = abs(avg[j] - a[i]);
					if(sub < min)
					{
						min = sub;
						min_index = j;
					}							
				}
		
				top[min_index]++;	
				c[min_index][top[min_index]] = a[i];
			}
			
			/*puts("New Cluster ::");
			for(i=0;i<k;i++)
			{
				
				for(j=0;j<=top[i];j++)
					printf("%f  ", c[i][j]);
				puts("");
			}
			puts("");
		
			printf("\n");
			printf("\n");*/
			
			for(i=0;i<k;i++)
			{
				if (top[i]==-1)
					break;
				sum = 0;
				for(j=0;j<=top[i];j++)
				{
					sum = sum +	c[i][j];
					 
				}
				avg[i] = sum/(top[i]+1);
			}
			
			/*puts("Updated avg");
			for(i=0;i<k;i++)
				printf("%f  ",avg[i]);
			printf("\n");*/		
			
			
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
		
	printf("CLUSTER#\tCLUSTER MEAN\tCLUSTER ELEMENT\n");
	printf("--------\t------------\t---------------\n");
	
	for(i=0;i<k;i++)
	{
		printf("%i\t\t%f\t",i+1,avg[i]);
		printf("%f",c[i][0]);
		for(j=1;j<=top[i];j++)
			printf(", %f",c[i][j]);
		printf("\n");
	}
	getch();
		
}
