#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
int inputs[6675][195];
int testInput[3335][195];
/* ------------------Read train data -------------*/
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
/* ------------------Read test data -------------*/
void readTest(int testInput[][195]){
        FILE* fp = fopen("pp_tes.txt", "r");
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
// Calculating probabilities
void threeD(int inputs[][195],double pro[10][192][5],int cp[]){
    int i,j,k;
    /* pro matrix first dimension is the class second is the total feature dimensions and the last one is the 0 to 4 values dimensions */
    for(i=0;i<6670;i++){
        for(j=0;j<193;j++){
            pro[inputs[i][192]][j][inputs[i][j]]++;
        }
        cp[inputs[i][192]]++;
    }
    for(i=0;i<10;i++){
        for(j=0;j<192;j++){
            for(k=0;k<5;k++){
                pro[i][j][k]=pro[i][j][k]/667;
            }
        }
    }
}
void testing(int testInput[][195],double pro[10][192][5]){
    	int i,j,k;
	double acc=0;
    	double tpro[10];
    	for(i=0;i<3333;i++){
	for(j=0;j<10;j++){
		tpro[j]=0;
	}
	//Calculating probabilities 
	for(j=0;j<10;j++){
		for(k=0;k<192;k++){
				tpro[j]+=log(pro[j][k][testInput[i][k]]);
			}
		}
	int ind=0;
	double max=tpro[0];
	// Finding which class it belongs to using the probabilities calculated in train set
	for(j=1;j<10;j++){
		if(max<tpro[j]){
			max=tpro[j];
			ind=j;
		}
	}
	if(testInput[i][192]==ind)
		acc++;
	}
	printf("Accuracy: %lf\n",(acc*100)/3333);
}
int main(){
    int i, j, k,cp[10];
    double pro[10][192][5];
    // READING TRAIN DATA
    readTraining(inputs);
    // READING TEST DATA
    readTest(testInput);
   
    // GENERATING 3D MATRIX
    for(i=0;i<10;i++){
        for(j=0;j<192;j++){
            for(k=0;k<5;k++){
                pro[i][j][k]=0;
            }
        }
    }
    for(k=0;k<10;k++){
        cp[k]=0;
    }
    threeD(inputs,pro,cp);
    testing(testInput,pro);
    return 0;
}
