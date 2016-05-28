#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int sizeOfArray=0;
int sizeOfWeight=0;
int sizeOfProfit=0;
int pointer=0;
int capacity=0;

struct item{
	int number;
	int weight;
	int profit;
}item;
int main(int argc, char *args[]){
	
	FILE * file_ptr = fopen(args[1], "r");
  	char * line = NULL;  	const char *s = ",";
  	size_t len = 0;
  	ssize_t read;
  	char *token=NULL; 
  	int i=0,j=0,k=0;
  	struct item * totalItem;
	if (file_ptr == NULL)
    {
    	printf("\nError opening\n");
    	
    	exit(EXIT_FAILURE);
    }else{
	    while ((read=getline(&line, &len, file_ptr)) != -1){
	    	if(pointer==0){
	    		sizeOfArray=atoi(line);
	    		pointer++;
	    		totalItem = malloc(sizeof(item)*sizeOfArray);
	    	}
	    	else if(pointer==1){
	    		i=0,j=0;
	    		char *value;
     			for(value=strtok(line,",");value;value=strtok(NULL,",")){
     					totalItem[i].weight=atoi(value);
     					totalItem[i].number=i;
     				
     				i++;
     			}
     			pointer++;	
	    	}
	    	else if(pointer==2){
	    		i=0,j=0;
	    		char *value;
     			for(value=strtok(line,",");value;value=strtok(NULL,",")){
     		
     				totalItem[i].profit=atoi(value);
     				
     				i++;
				}
				pointer++;
	    	}else if(pointer==3){
	    		capacity=atoi(line);
	    	}else{
	    		printf("Not valid entry\n");
	    	}
	     	
	    }
	}
	fclose(file_ptr); // closing the file


	FILE *fw;
	fw=fopen("brute_output.txt", "w");
	
	unsigned int power_size= pow(2,sizeOfArray);

	int weightSum=0;
	int totalProfit=0;
	int maximumProfit=0;
	int maximumWeight=0;
	int maxItemArraySize=0;
	
	int maxItemArray[power_size];
	
	memset(maxItemArray,-1,power_size);
	
	for ( i = 0; i <power_size; ++i)
	{	
		weightSum=0;
		totalProfit=0;
		int itemArray[sizeOfArray];

		int itemArrayIncremental=0;
		
		for ( j = 0; j < sizeOfArray; ++j)
		{
			if(i & (1<<j)){
				if((weightSum+totalItem[j].weight)<=capacity){
					itemArray[itemArrayIncremental]=j;
					itemArrayIncremental++;
					totalProfit= totalProfit+totalItem[j].profit;  // calculating the total profit for each iteration 
					weightSum= weightSum+totalItem[j].weight;  // calculating the total weight sum
				}
			}
            
		}

		if( (totalProfit>maximumProfit) && (maximumWeight<=capacity)){
			maximumProfit= totalProfit;	 // assign the current profit if it is maximum 
			maximumWeight=weightSum;	// assign the weight if still less than the capacity 
			int i;
			maxItemArraySize = itemArrayIncremental-1;
			memset(maxItemArray,-1,power_size);
			for (i = 0; i < itemArrayIncremental; ++i)
			{
				maxItemArray[i]=itemArray[i];
			}
		}
		
	}


	fprintf(fw,"%d\n",maximumWeight);
	fprintf(fw,"%d\n",maximumProfit);
	if(maximumProfit>0){
		for (i = 0; i <= maxItemArraySize; ++i)
		{
			if(maxItemArray[i]!=(-1)){
				if(i!=0){
				fprintf(fw,", ");
				}
			fprintf(fw,"%d",totalItem[maxItemArray[i]].number);
			}
			
		}
		fprintf(fw,"\n");
		return; 
	}
	else{
		fprintf(fw,"There is no such element.\n");
		return;
	}
	fclose(fw);
	//free(totalItem);
	
}