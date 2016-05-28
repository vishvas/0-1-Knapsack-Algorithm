#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int sizeOfArray=0;
int pointer=0;  //To check the line number 
int capacity=0; //maximum capacity 
int maximumProfit=0;
int numbest=0;
int maximumWeight=0;
int * resultArray;
struct item{
	int itemIndex;
	int weight;
	int profit;
	int status;
	int originalIndex;
}item;


int * profitArray;
int * weightArray;
int * bestSetArray;
int * includeArray;
int * originalIndexArray;
int * indexArray;
int finalSize=0;



int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


int struct_cmp_by_profit_divide_weight(const void *a, const void *b) 
{ 	int ratioA, ratioB;
    struct item *ia = (struct item *)a;
    struct item *ib = (struct item *)b;
    if( (ia->profit==0) && (ia->weight==0)){
    	ratioA =0;
    }
    else{
    	ratioA = (ia->profit)/(ia->weight);
    }
	if((ib->profit==0) && (ib->weight==0)){
    	ratioB=0;
    }else{
    	ratioB = (ib->profit)/(ib->weight);
    }
    int i = (int)(100.f*ratioB - 100.f*ratioA);
    
    return i;
} 


int promising(int i, int currentWeight, int currentProfit){
	int index;
	if( currentWeight>=capacity ){
		return 0;
	}else{
		float bound = currentProfit;
		index =i;
		while((currentWeight<capacity) && (i<=finalSize)){

			if( ( weightArray[i]+currentWeight ) <=capacity){
				currentWeight = currentWeight + weightArray[i];
				bound = bound + profitArray[i];
			}else{
				float fractionWeight = (capacity - currentWeight);
				currentWeight = capacity; 
				bound = bound + ( (profitArray[i]/weightArray[i]) * fractionWeight);
			}
			i++;
		}
		if(bound>maximumProfit){
			
		return 1;
		}
	}
	return 0;	
}


void knapsack(int index, int currentProfit, int currentWeight){
	
	if((currentWeight<=capacity) && (currentProfit > maximumProfit)) {
		
		maximumProfit = currentProfit;
		
		maximumWeight = currentWeight;
		
		numbest = index;
		
		int i;
		
		for ( i = 0; i < finalSize; ++i)
		{
			bestSetArray[i]=(-1);
			
		}

		for ( i = 0; i < index+1; ++i)
		{
			if(includeArray[i]==1){
				bestSetArray[i]= originalIndexArray[i];
			}
		}
		
	}
	
	float i = promising(index, currentWeight, currentProfit); // checking if the node is promising or not
	
	if((i>0)&&((index+1)<= finalSize)){
		includeArray[index+1]=1;
		knapsack(index+1, currentProfit+profitArray[index+1], currentWeight+weightArray[index+1]);
		includeArray[index+1]=0;
		knapsack(index+1,currentProfit,currentWeight);		
	}


	
}
int main(int argc, char *args[]){
	FILE * file_ptr = fopen(args[1], "r");
  	char * line = NULL;  	const char *s = ",";
  	size_t len = 0;
  	ssize_t read;
  	char *token=NULL; 
  	int i=0,j=0,k=0;
  	char *value;
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
	    		totalItem = malloc(sizeof(item)*(sizeOfArray));
	    		
	    	}
	    	else if(pointer==1){
	    		i=0,j=0;
	    		for(value=strtok(line,",");value;value=strtok(NULL,",")){
     					totalItem[i].weight=atoi(value);
     					totalItem[i].itemIndex=i;
     					totalItem[i].originalIndex=i;
     				
     				i++;
     			}
     			pointer++;

	    	}
	    	else if(pointer==2){
	    		i=0,j=0;
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
	

	qsort(totalItem, sizeOfArray, sizeof(struct item), struct_cmp_by_profit_divide_weight);
	finalSize = sizeOfArray+1;
	profitArray = malloc(sizeof(int)*finalSize);
	weightArray = malloc(sizeof(int)*finalSize);
	bestSetArray = malloc(sizeof(int)*finalSize);
	includeArray = malloc(sizeof(int)*finalSize);
	originalIndexArray = malloc(sizeof(int)*finalSize);
	indexArray = malloc(sizeof(int)*finalSize);

	profitArray[0]=0;
	weightArray[0]=0;
	indexArray[0]=0;
	originalIndexArray[0]=-1;
	bestSetArray[0]=(-1);
	includeArray[0]=0;
	

	for (i = 1; i < finalSize; ++i)
	{	
		originalIndexArray[i]= totalItem[i-1].originalIndex;
		indexArray[i]=i;
		profitArray[i]=totalItem[i-1].profit;
		weightArray[i]=totalItem[i-1].weight;
		bestSetArray[i]=(-1);
		includeArray[i]=0;
	}
	

	knapsack(0,0,0); // index, current weight and current profit 
	FILE *fw;
	fw=fopen("backtrack_output.txt", "w");
	fprintf(fw,"%d\n%d\n",maximumWeight,maximumProfit);
	
	qsort(bestSetArray, finalSize, sizeof(int), cmpfunc);
	for (i = 0; i < finalSize; ++i)
	{
		//printf("%d,",finalArray[i]);
		if(bestSetArray[i]!=(-1)){
			fprintf(fw,"%d",bestSetArray[i]);
			if(i!=(finalSize-1)){
			fprintf(fw, ", ");
			}
		}
		
	}

	fclose(fw);
	return 0;
	 // free(line);  // no error while freeing the memory
	 // free(token);
	 // free(value);
	 // free(profitArray);
	 // free(weightArray);
	 //free(totalItem);

	 //free(includeArray);
	 //free(bestSetArray);	
	 //free(originalIndexArray);
	 //free(indexArray);
	 
	
	
}