#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define POS_LABEL 1
#define NEG_LABEL 2
float svm_classify(float** data, float** svectors,float* shift, float* scale, float bias,float* alphas ,int m);


int main()
{

//--------------------------------------------------------------------------------------------------------------------------------------------//
// Initialization
int svsize = 5996;
int testsize = 1025;
int numof_vectors = 5;
int i,j,k,count;
float accuracy;
float dot_product,dot_product1[5996],dot_product2,result;
float model_bias = -0.20454;
int label;
float predictlabel[1025];
float* shift = (float*)malloc(4*sizeof(float*));
float* scale = (float*)malloc(4*sizeof(float*));

shift[0] = -0.036086;
shift[1]= -0.014269;
shift[2]= 0.0012401;
shift[3] = 0.022425;
scale[0] = 78.483;
scale[1]= 28.187;
scale[2]= 26.074;
scale[3] = 32.258;
float test_data1[4];

float** testData = (float**)malloc(testsize*sizeof(float*));
    	for( i = 0; i < testsize ; ++i)
		{
        	testData[i] = (float*)malloc(numof_vectors*sizeof(float));
    	}
float** supportVectors = (float**)malloc(svsize*sizeof(float*));
    	for( i = 0; i < svsize ; ++i)
		{
        	supportVectors[i] = (float*)malloc(4*sizeof(float));
    	}
//============================================================================================================================================//
//Read test input data
FILE *inputFile;
inputFile = fopen("testing.txt","r+");
for (i = 0; i<testsize; i++)
        {
            fscanf(inputFile, "%f,%f,%f,%f,%f",&testData[i][0],&testData[i][1],&testData[i][2],&testData[i][3],&testData[i][4] );
        }
fclose(inputFile);
//============================================================================================================================================//
//Read support vectors
FILE *inputFile1;
inputFile1 = fopen("supportvect.txt","r+");
for (i = 0; i<svsize; i++)
        {
            fscanf(inputFile1, "%f,%f,%f,%f",&supportVectors[i][0],&supportVectors[i][1],&supportVectors[i][2],&supportVectors[i][3]);
        }
fclose(inputFile1);
//============================================================================================================================================//      
// Read alpha values

float* alphas = (float*)malloc(svsize*sizeof(float*));
FILE *ip1;
ip1 = fopen ("alpha.txt","r+");   
for (i = 0; i<svsize; i++)
        {
            fscanf(ip1, "%f",&alphas[i] );
        }
//============================================================================================================================================//
//Predict the labels for each test vector
for (i = 0; i<testsize;i++)
 {   predictlabel[i] = svm_classify(testData,supportVectors,shift,scale,model_bias,alphas,i);
    if (predictlabel[i]==testData[i][4])
        {
            count++;
        } 
 }
//============================================================================================================================================//
//Calculate accuracy 
accuracy = ((float)count/testsize) *100;
printf("%f", accuracy);

return 0;
}


//============================================================================================================================================//
// Function to compute the predicted labels
float svm_classify(float** data, float** svectors,float* shift, float* scale, float bias ,float* alphas,int m)
{
    float result = 0;
    int svsize = 5996;
    int testsize = 1025;
    int i,j,k,accuracy,count=0;
    float dot_product=0 ,dot_product1[5996],dot_product2=0;
     float test_datanew[4];

    for (i = 0;i<4;i++)
            {
                // Compute the addition and scaling of the input data 
                test_datanew[i] = (data[m][i] + shift[i])*scale[i];
            }

    for (i = 0;i<svsize;i++)
            {   
            for (j= 0;j<4;j++)
                {   
                    //Compute the dot product of test data and support vectors 
                    dot_product =dot_product+ (test_datanew[j] * svectors[i][j]);
                }
                dot_product1[i] = dot_product;
                dot_product = 0;
            }

    for (i= 0;i<svsize;i++)
            {
                //multiply the dot products with the alphas 
                dot_product2 =dot_product2+ (dot_product1[i]*alphas[i]);
            }
            result = dot_product2 + bias;
    return (result > 0) ? POS_LABEL : NEG_LABEL;

} 






