#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

int inputs[6675][195];
int testInput[3335][195];
int m1[4450][195],m2[4450][195],m3[4450][195];
/* Reading training data */
void readTraining(int inputs[][195]){
	FILE* fp = fopen("pp_tra.txt", "r");
	int i,j;

	while(getc(fp) != EOF){
		for(i=0;i<6670;i++){
			for(j=0;j<193;j++){
				fscanf(fp,"%d",&inputs[i][j]);

                    	}
        	}
    	}
    	fclose(fp);
}
/* Reading test data */
void readTest(int testInput[][195]){
    	FILE* fp = fopen("pp_tes.dat", "r");
    	int i,j;
    	while(getc(fp) != EOF){
		for(i=0;i<3333;i++){
			for(j=0;j<193;j++){
				fscanf(fp,"%d",&testInput[i][j]);
                    	}
        	}
    	}
    	fclose(fp);
}
/* Merging arrays in merge sort */
void merge(double arr[],int index[], int l, int m, int r)
{
    	int i, j, k;
    	int n1 = m - l + 1;
    	int n2 =  r - m;

    	/* create temp arrays */
    	int L[n1], R[n2],li[n1],ri[n2];

    	/* Copy data to temp arrays L[] and R[] */
    	for (i = 0; i < n1; i++){
        	L[i] = arr[l + i];
		li[i]=index[l+i];
	}
    	for (j = 0; j < n2; j++){
        	R[j] = arr[m + 1+ j];
		ri[j]=index[m+1+j];
	}
    	/* Merge the temp arrays back into arr[l..r]*/
    	i = 0; // Initial index of first subarray
    	j = 0; // Initial index of second subarray
    	k = l; // Initial index of merged subarray
    	while (i < n1 && j < n2)
    	{
    	    if (L[i] <= R[j])
    	    {
    	        arr[k] = L[i];
		index[k]=li[i];
    	        i++;
    	    }
    	    else
    	    {
    	        arr[k] = R[j];
		index[k]=ri[j];
            	j++;
            }
            k++;
    	}

    	/* Copy the remaining elements of L[], if there are any */
    	while (i < n1)
    	{
        	arr[k] = L[i];
		index[k]=li[i];
        	i++;
        	k++;
    	}

    	/* Copy the remaining elements of R[], if there are any */
    	while (j < n2)
    	{
        	arr[k] = R[j];
		index[k]=ri[j];
        	j++;
        	k++;
    	}
}

/* l is for left index and r is right index of the sub-array of arr to be sorted */
void mergeSort(double arr[],int index[], int l, int r)
{
	if (l < r)
    	{
        	// Same as (l+r)/2, but avoids overflow for
        	// large l and h
        	int m = l+(r-l)/2;

        	// Sort first and second halves
        	mergeSort(arr,index, l, m);
        	mergeSort(arr,index, m+1, r);

        	merge(arr,index, l, m, r);
    	}
}

/* Distance calculation: Euclidian distance */
double distance(int x[],int y[]) {
	int i,count=0;
	float sum=0;
	for(i=0;i<192;i++) {
		count++;
      		sum=sum+((x[i]-y[i])*(x[i]-y[i]));
      		//printf("%d %d\n",x[i],y[i]);
  	}
  	sum=sqrt(sum);
  	//printf("%f %d",sum,count);
  	return sum;
}
int train(){
	int i,j,k=1,t=0;
	int a1[2225][195],a2[2225][195],a3[2225][195];
	double te[3][25];
	/* Dividing the input array into three folds */
	for(i=0;i<6670;i++){
		for(j=0;j<193;j++){
			if(i>=0 && i<2224){
				a1[i][j]=inputs[i][j];
			}
			else if(i>=2224 && i<4447){
				a2[i-2224][j]=inputs[i][j];
			}
			else{
				a3[i-4447][j]=inputs[i][j];
			}
		}
	}
	/* Making the training folds in accordance with the test folds */
	
	for(i=0;i<4447;i++){
		for(j=0;j<193;j++){
			if(i<2224){
				m1[i][j]=a1[i][j];
			}
			else{
				m1[i][j]=a2[i-2224][j];
			}
		}
	}
	for(i=0;i<4447;i++){
		for(j=0;j<193;j++){
			if(i<2224){
				m2[i][j]=a2[i][j];
			}
			else{
				m2[i][j]=a3[i-2224][j];
			}
		}
	}
	for(i=0;i<4447;i++){
		for(j=0;j<193;j++){
			if(i<2224){
				m3[i][j]=a1[i][j];
			}
			else{
				m3[i][j]=a3[i-2224][j];
			}
		}
	}
	int mo,co=0;
	double dist[4450];
	int index[4450];
	/* Initialization of 3x25 matrix with 0's */
	for(i=0;i<3;i++){
		for(j=0;j<25;j++){
			te[i][j]=0;
		}
	}	
	for(k=1;k<=25;k++){
		printf("Calculating for k=%d\n",k);
		for(t=0;t<3;t++){
			for(i=0;i<2224;i++){
				/* Making the distance array */
				for(j=0;j<4447;j++){
					dist[j]=0;
				}
				for(j=0;j<4447;j++){
					if(t==0){ // Considering the first fold as test
						dist[j]=distance(a1[i],m2[j]);
						index[j]=j;
					}
					else if(t==1){ // Considering the second fold as test
						dist[j]=distance(a2[i],m3[j]);
						index[j]=j;
					}
					else if(t==2){ // Considering the third fold as test
						dist[j]=distance(a3[i],m1[j]);
						index[j]=j;
					}
				}
				/* Sorting the distance array */
				mergeSort(dist,index,0,4446);
				//printf("%d",t);
				//printf("%d,%d %d,%d %d,%d\n",dist[0],index[0],dist[100],index[100],dist[4446],index[4446]);
				/* Calculating the errors */
				if(t==0){
					for(mo=0;mo<k;mo++){
					//printf("************");
						//printf("%d %d",a1[i][192],m2[index[mo]][192]);
						if(a1[i][192]!=m2[index[mo]][192]){
							te[t][k-1]++;
						}
					}				
				}
				else if(t==1){
					for(mo=0;mo<k;mo++){
						if(a2[i][192]!=m3[index[mo]][192]){
							te[t][k-1]++;
						}
					}
				}
				else if(t==2){
					for(mo=0;mo<k;mo++){
						if(a3[i][192]!=m1[index[mo]][192]){
							te[t][k-1]++;
						}
					}
				}
			}			
		}
	}
	//printf("Total error: %d",te);
	double error[25];
	int va,z;
	for(va=0;va<3;va++){
		for(z=0;z<25;z++) {
			//printf("%d",te[va][z]);
			/* Dividing the error with no. of elements */
			if(va==0){
				te[va][z]=te[va][z]/2224;
			}
			else if(va==1){
				te[va][z]=te[va][z]/2223;
			}
			else{
				te[va][z]=te[va][z]/2223;
			}
		}
	}	
	/* error calculation */
	printf("Errors : \n");
	for(z=0;z<25;z++) {
			error[z]=(te[0][z]+te[1][z]+te[2][z])/3;
			printf("k=%d error=%lf\n",z+1,error[z]);
	}
	int min=error[0],ind=0;
	/* Calculating k which has min error */
	for(z=1;z<25;z++) {
		if(min>=error[z]){
			min=error[z];
			ind=z;
		}
	}	
	return ind+1;
}
void test(int testInput[][195],int inputs[][195],int k){
	int i,j,v;
	double err=0;
	double dist[6675];
	int index[6675];
	int vm[10];
	for(v=0;v<10;v++){
		vm[k]=0;
	}
	for(i=0;i<3333;i++){
		for(j=0;j<6670;j++){
			dist[j]=distance(testInput[i],inputs[j]);    /* Calculating distances */
			index[j]=j;
		}
		mergeSort(dist,index,0,6669);    //Sorting distances
		for(v=0;v<k;v++){
			vm[inputs[index[v]][192]]++;
		}
		int max=vm[0];
		int z,ind=0;
		//Max probability of the class to which the corresponding test input belongs to
		for(z=1;z<10;z++) {
			if(max<=vm[z]){
				max=vm[z];
				ind=z;
			}
		}
		//printf("%d %d %d\n",i,testInput[i][192],ind);
		if(testInput[i][192]==ind){ // Checking whether the class label matches or not
			err++;
		}
	}
	//printf("%lf\n",acc);
	printf("\nAccuracy : %lf \n",100-(err/3333)*100);
}
int main(){
	int i, j, k;
	readTraining(inputs);
	/*for(i=0;i<6670;i++){
		for(j=0;j<192;j++){
			printf("%d ",inputs[i][j]);
                }
		printf("\n");
        }*/
	readTest(testInput);
	//printf("@@2");
	k=train(inputs);
	//printf("@@66");
	/*for(i=0;i<3333;i++){
		for(j=0;j<193;j++){
			printf("%d ",testInput[i][j]);
                }
		printf("\n");
        }*/	
	//k=1;
	printf("k value: %d \n",k);
	test(testInput,inputs,k);
	return 0;
}
