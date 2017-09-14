#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

#ifdef NAN
#endif
#define POS_LABEL 1
#define NEG_LABEL 0

//======================================================================================================================================//
//===========================================DECLARATIONS===============================================================================//
long NUM_FEATURES = 4;
long NUM_SUBJECTS = 15;
int KNN_K = 3;
float sq_euclid_dist(float *x, float *y, long len);
float knn_classify2(float *x, int k, float** model_data, long model_len, long feature_len);
//======================================================================================================================================//
//========================================MAIN FUNCTION=================================================================================//
int main()
{

	int start = 502904 ;
	int end = 614739;
	int start_n = 1282641;
	float predictlabel;
	float x;
	float accuracy;
	int diff;
	int num_of_windows1 = 187;
	int num_of_windows2 = 305;
	diff = (end - start);
	x = ceil((float)diff/600);
	int num_of_windows = num_of_windows1+ num_of_windows2;
	int numof_features = 4;
	int data_size = 1589959;	
	int i, j, k, z,count;
	float sum,mean;
	float channelLabel[num_of_windows];
	double time_spent=0;
//======================================================================================================================================//
//=========================================MEMORY ALLOCATIONS===========================================================================//
	float** inputData = (float**)malloc(data_size*sizeof(float*));
		for( i = 0; i < data_size ; ++i)
		{inputData[i] = (float*)malloc(numof_features*sizeof(float));}
	float** newfeature = (float**)malloc(data_size*sizeof(float*));
		for( i = 0; i < data_size ; ++i)
		{newfeature[i] = (float*)malloc(5*sizeof(float));}
	float** newfeature1 = (float**)malloc(data_size*sizeof(float*));
		for( i = 0; i < data_size ; ++i)
		{newfeature1[i] = (float*)malloc(numof_features*sizeof(float));}
	float** newfeature2 = (float**)malloc(data_size*sizeof(float*));
		for( i = 0; i < data_size ; ++i)
		{newfeature2[i] = (float*)malloc(numof_features*sizeof(float));}
	float*data = (float*)malloc(numof_features*sizeof(float));
//======================================================================================================================================//
//============================READING FROM INPUT FILE===================================================================================//

	FILE *inputFile;
    inputFile = fopen("Mymatrix.txt","r+");
	for (i = 0; i<data_size; i++)
		{for ( j=0 ; j<numof_features ; j++)
			{
			fscanf(inputFile, "%f",&inputData[i][j] );
			}
		}
	fclose(inputFile);
//======================================================================================================================================//
//============================FEATURE EXTRACTION========================================================================================//
	clock_t begin = clock();	
	int c=0;
	for (j = 0; j<4;j++)
		{
		int tempstart = start;
		int temppoint = tempstart +1200;
		for (z= 0; z<num_of_windows1;z++)
		{
			c = 0;
			float sum = 0;
			float mean = 0.00;
			float x = 0.0/0.0;
			for (k = tempstart; k< temppoint; k++)
				{
				if (!(inputData[k][j] != inputData[k][j]))
					{sum = sum + inputData[k][j];
					c++;
					}
				}
				mean = (float)sum /c;
				newfeature1[z][j] = mean;
			tempstart= tempstart +600;
			temppoint = tempstart +1200;	
			}
		}

	for (j = 0; j<4;j++)
		{		
		int tempstart1 = start_n;
		int temppoint1 = tempstart1 +1200;
		for (z= 0; z<num_of_windows2;z++)
		{
			c = 0;
			float sum = 0;
			float mean = 0.00;
			float x = 0.0/0.0;
			for (k = tempstart1; k< temppoint1; k++)
				{
				if (!(inputData[k][j] != inputData[k][j]))
					{	
					sum = sum + inputData[k][j];
					c++;
					}
				}
				mean = (float)sum /c;
				newfeature2[z][j] = mean;
			tempstart1= tempstart1 +600;
			temppoint1 = tempstart1 +1200;
			}
		}	
	for (z = 0; z<num_of_windows1;z++)
		{for (i = 0; i< numof_features; i++)
			{
				newfeature[z][i] = newfeature1[z][i];
			}
		newfeature[z][4] = 0;
		}
	for (z = 0; z<num_of_windows2;z++)
		{for (i = 0; i< numof_features; i++)
			{
				newfeature[z+num_of_windows1][i] = newfeature2[z][i];
			}
			newfeature[z][4] = 1;	
		}
	
//====================================================================================================================================//
//=============================CLASSIFICATION=========================================================================================//	
	
	for (i = 0;i<num_of_windows ; i++)
		{for ( j= 0; j< numof_features; j++)
			{
				data[j] = newfeature[i][j];
			}				
		channelLabel[i] = knn_classify2( data,3, newfeature , num_of_windows,4);
		
		FILE *fp1;
		fp1= fopen ("traindata.txt","a");
		fprintf(fp1,"%f %f %f %f %f\n", newfeature[i][0], newfeature[i][1],newfeature[i][2],newfeature[i][3],newfeature[i][4]);
		predictlabel += channelLabel[i];
		fclose(fp1);

		//printf(" %f   %d \n",channelLabel[i], i);
		if (channelLabel[i] == newfeature[i][4])
			{ 
			count++;
			}

	}
	clock_t t_end = clock();
	time_spent = (double) (t_end - begin)/CLOCKS_PER_SEC;
	printf("Execution time :%f",time_spent);
	//printf( "%f \n", predictlabel);
	//printf("%f \n", (float)num_of_windows);
	accuracy = count/(float)num_of_windows *100;
	//printf("%f", accuracy);
	return 0;
}

//========================================================================================================================================//
//============================CLASSIFICATION FUNCTION CALL================================================================================//
float knn_classify2(float *x, int k, float** model_data, long model_len, long feature_len){

    long i,j,found;

    float k_dist[k];
    float k_labels[k];
    float dist = 0, other_dist = 0;
    float sum_label = 0, label = 0, other_label = 0;

    //Set all distances to MAX
    for(i = 0; i < k; ++i){
        k_dist[i] = DBL_MAX;
        k_labels[i] = 0;
    }

    //Compute distance for each model entry and dynamically sort
    for(i = 0; i < model_len; ++i){
        dist = sq_euclid_dist(x,model_data[i],feature_len);
        label = model_data[i][feature_len];
        found = 0;
        for(j = 0; j < k; ++j){
            if( (!found && (dist <= k_dist[j])) || found ){
                other_dist = k_dist[j];
                other_label = k_labels[j];
                k_dist[j] = dist;
                k_labels[j] = label;
                dist = other_dist;
                label = other_label;
                found = 1;
            }
        }
    }
    //Sum closest labels
    for(i = 0; i < k; ++i){
        sum_label += k_labels[i];
    }
    // Return pos if greater than 0, else neg label
    return (sum_label > 0.5*k) ? POS_LABEL : NEG_LABEL;
}


float sq_euclid_dist(float *x, float *y, long len){
    long i;
    float dist = 0;
    for(i = 0; i < len; ++i){
        dist += pow(x[i]-y[i],2);
    }
    return pow(dist,0.5);
}
