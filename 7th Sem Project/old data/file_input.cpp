#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>


int main()
{
	FILE *fp;
	
	char ch;
	int xx = 1,i,r,n=0,flag=0,arr[100],tp=-1,t;
	fp = fopen("abc.txt","r");
	
	if(fp)
	{
	
	while((ch = getc(fp))!= EOF )
	{		 
		
		
		if(ch != 32)
		{		
			i = atoi (&ch);
			n = n * 10;
			n = i + n;
			//printf("%d\n",n);			
		}
		if(ch == 32)
		{
			xx++;
			tp++;
			arr[tp] = n; 
			//printf("%d\n",arr[tp]);	
			n = 0;	
		}
		
		
	}

}
	tp++;
	arr[tp] = n; 
	
	
	
	int a[n];

	puts("Printing the dataset");
	for(t=0;t<=tp;t++)
	{
	
		a[t] = arr[t];
		printf("%d\n",a[t]);
	}
	
	fclose(fp);

	////////////////////////////////////////////
	
	int j,k,min,min_index,sub,sum;
		flag = 0;
		
		/*printf("Enter the number of elements you want to print\n");  // taking elements from user.....
		scanf("%d",&n);*/
		
		n = xx;
		
		/*int a[n];													// input array  of dynamic nature...
		
		printf("Enter the elements you want to give\n");
		
		for(i=0;i<n;i++)
		{
			scanf("%d",&a[i]);
		}*/
		
		
		
		printf("Enter the number of clusters you want to have ::\n");  // taking elements from user.....
		scanf("%d",&k);
		
		puts("");
		
			
		int	c[k][n] = {0}, b[k][n] = {0}, top[k],avg[k];
		
		
		for(i=0;i<k;i++)
		{
				avg[i] = a[i];						// initially averages are set to as the elemnts of the given user arrray .. 
				
		}
		
		
		
		
		
		while(1)
		{
			flag = 0;
			
			memset(b, 0, sizeof b);	
			for(i=0;i<k;i++)
			{
												// taking b to store the previous iteration value of c so that it can be used for comparisons later..
				for(j=0;j<n;j++)
				{
						b[i][j] = c[i][j];
					 
				}
			}
			
			
			
			
			
			memset(c, 0, sizeof c);
		
			
			for(i=0;i<k;i++)
			{
				top[i] = -1;
				//puts("top test");						//assigning the top variables to -1 for each cluster arrays
				//printf("%d\n",top[i]);
			}
			
			
			
				
			for(i=0;i<n;i++)
			{
				if( a[i] == a[i+1])
				{
					printf("Sorry!");
					break;
				}
				min = 5000000;						// at first assigning min to  5000000
				for(j=0;j<k;j++)
				{
					//printf("testing %d with %d and diff = %d\n",avg[j], a[i], abs(avg[j] - a[i]));						
					sub = abs(avg[j] - a[i]);
					if(sub < min)									//  forming cluster elements with respect to the corresponding means
					{
						min = sub;
						min_index = j;
					}							
				}
		
				top[min_index]++;	
				c[min_index][top[min_index]] = a[i];
				
				//printf("%d is going to cluster %d\n", a[i], min_index);
			}
			
			/*for(i=0;i<k;i++)
			{
				
				for(j=0;j<=top[i];j++)
					printf("%d  ", c[i][j]);		// formation of clusters..
				puts("");
			}
		
			printf("\n");
			printf("\n");*/
			
			for(i=0;i<k;i++)
			{
				sum = 0;
				for(j=0;j<=top[i];j++)
				{
					sum = sum +	c[i][j];				// then finding out the mean of the cluster elements..
					 
				}
					//printf("%d  ", sum);
						
				avg[i] = sum/(top[i]+1);
				
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
					
			}								// if the means of the clusters previous iteration is same for the present then leave the while loop 
			
			
			if(flag == 0)
			break;
			
			
		
		}
		
	printf("CLUSTER#\tCLUSTER MEAN\tCLUSTER ELEMENT\n");
	printf("--------\t------------\t---------------\n");
	
	for(i=0;i<k;i++)
	{
		printf("%i\t\t%d\t\t",i+1,avg[i]);
		printf("%d",c[i][0]);
		for(j=1;j<=top[i];j++)
			printf(", %d",c[i][j]);
		printf("\n");
	}
	getch();
		
}
