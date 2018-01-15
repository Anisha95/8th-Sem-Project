#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

int main()
{
	int i,j,k,n,min_index,op1;
	float d,min;
	float pts[n][2];
	int flag = 0;
	
	printf("Press 1 for user-input \n :: Press 2 for file-input\n");
	scanf("%d",op1);
	
	if( op1 == 1 )
	{
		printf("Enter the number of elements you want to print :: \n");
		scanf("%d",&n);
		printf("Enter co_ordinates::\n");
		for(i=0;i<n;i++)
			scanf("%f%f",&pts[i][0],&pts[i][1]);	
	}
	if( op1 == 2)
	{
		FILE *fp;	
		char ch;
		int xx = 1,a,j,r,t=0,flag=0,arr[100],tp=-1;
		fp = fopen("abc.txt","r");
		if(fp)
		{
			while((ch = getc(fp))!= EOF )
			{		 
				if(ch != 32)
				{		
					a = atoi (&ch);
					t = t * 10;
					t = a + t;		
				}
				if(ch == 32)
				{
					xx++;
					tp++;
					arr[tp] = t; 	
					t = 0;	
				}		
			}
		}
		tp++;
		arr[tp] = t; 
		int count = 0;
		//puts("Printing the dataset");
		for(i=0;i<=tp;i++)
		{
			for(j=0;j<2;j++)
		{
			pts[i][j] = arr[count];
			count++;
			printf("%d\n",pts[i][j]);
		}
		}
		fclose(fp);
	}
	printf("Enter the number of clusters you want to have ::\n");
	scanf("%d",&k);		
		
	int	c[k][n] = {0}, b[k][n] = {0}; 
	float mean[k][2];
	int top[k];
	
	memset(b, 0, sizeof b);
	memset(c, 0, sizeof c);
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
		
		for(i=0;i<k;i++)
			top[i] = -1;			
			
		for(i=0;i<n;i++)
		{
			min = 5000000.00;
			for(j=0;j<k;j++)
			{
				d = sqrt(pow((mean[j][0] - pts[i][0]),2) + pow((mean[j][1] - pts[i][1]),2));
				// printf("%f\n",d);
				// getch();
				if(d < min)
				{
					min = d;
					min_index = j;
				}							
			}
	
			top[min_index]++;	
			c[min_index][top[min_index]] = i;
		}
		
		
		
		
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
	
printf("CLUSTER#\tCLUSTER MEAN\t\tCLUSTER ELEMENT\n");
printf("--------\t------------\t\t---------------\n");

for(i=0;i<k;i++)
{
	printf("%i\t\t%.2f,%.2f\t\t",i+1,mean[i][0],mean[i][1]);
	printf("%d",c[i][0]+1);
	for(j=1;j<=top[i];j++)
		printf(", %d",c[i][j]+1);
	printf("\n");
}
getch();
	
}
