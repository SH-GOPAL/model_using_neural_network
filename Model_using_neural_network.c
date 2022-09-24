#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main()
{    
   
    
    for (int r = 0; r <=1; r++)
    {
    
     int i , j ,k,m,n,p, l,o;
    
    l=2;//number of inputs neurons
    p=7;//number of training patterns
    p=p-r;
    float in[l][p]; 
        FILE *fp3 ;
    fp3 = fopen("training.txt","r");
    if(fp3==NULL)
    {
        printf("file can't be opened\n");
        exit(1);
    }
    for ( i = 0; i < l; i++)
    {
        for ( j = 0; j < p; j++)
        {
            fscanf(fp3,"%f",&in[i][j]); }
            fscanf(fp3,"\n");
        
    }
    fclose(fp3);
    float t[i][p];   
    FILE *fp2 ;
    fp2 = fopen("output.txt","r");
    if(fp2==NULL)
    {
        printf("file can't be opened\n");
        exit(2);
    }
    
        for ( j = 0; j < 1; j++)
        {
            for ( i = 0; i < p; i++){
            fscanf(fp2,"%f",&t[j][i]); }
            fscanf(fp2,"\n");
             }
            
       
         fclose(fp2); 
    if(p=6){
    float in[l][p]; 
        FILE *fp1 ;
    fp1 = fopen("testing.txt","r");
    if(fp1==NULL)
    {
        printf("file can't be opened\n");
        exit(1);
    }
    for ( i = 0; i < l; i++)
    {
        for ( j = 0; j < p; j++)
        {
            fscanf(fp1,"%f",&in[i][j]); }
            fscanf(fp1,"\n");
        
    }
    fclose(fp1);
     float t[i][p];  
    FILE *fp2 ;
    fp2 = fopen("output1.txt","r");// output of testing patterns
    if(fp2==NULL)
    {
        printf("file can't be opened\n");
        exit(2);
    }
    
        for ( j = 0; j < 1; j++)
        {
            for ( i = 0; i < p; i++){
            fscanf(fp2,"%f",&t[j][i]); }
            fscanf(fp2,"\n");
             }
            
       

    }
   
     
      m =4 ;//number of hidden layer neuron
    int V[l+1][m];
     for ( i = 0; i < l+1; i++)
    {
        for ( j = 0; j < m; j++)
        { 
            int lower=-1 , upper=1,number  ;
            srand(time(NULL));
            V[i][j]= (rand() % (upper-lower +1))+lower;
                  }
              
            }
          
    n=1;//number of output layer neurons
    float W[m+1][n];
     for ( j = 0; j < m+1; j++)
    {
        for ( k = 0; k < n; k++)
        { 
            int lower=-1 , upper=1,number  ;
            srand(time(NULL));
            W[j][k]= (rand() % (upper-lower +1))+lower;
                  }
                 
    }
    FILE *out ;
    out = fopen("iterations.txt","w");
   float e=1;
   int q=1 ;
    while(e> 0.0001)
    {
    float IH[m][p];
    float OH[m][p];
    

    fprintf(out,"Iteration %d\n",q);
    //Output of hidden layer neurons
    for ( o = 0; o < p; o++)
    {
       
        for ( j = 0; j < m; j++)
        {     
            IH[j][o]=0;
            for ( i = 0; i < l; i++)
            {
              
                IH[j][o]=IH[j][o]+in[i][o]*V[i][j];
           
            }
           
            IH[j][o]=IH[j][o]+V[0][j];
            
             OH[j][o]= 1.0/(1+exp(-IH[j][o])); 
          
             
            
        }
     
      
    }
 
   
       // OUTPUT OF OUTPUT LAYER
        float error,mse;
        float OIH[m][p];
    float OOH[m][p],output;
    float delW[m][n],delV[l][m], a2=1,a1=10,eta =0.5;
    e=0 ;
    fprintf(out,"Output\t error \n");
    for ( o = 0; o < p; o++)
    {
       
        for ( j = 0; j < m; j++)
        {
            OIH[j][o]=0,mse=0;
            for ( k =0; k < n; k++)
            {
                OIH[j][o]=OIH[j][o]+OH[j][o]*W[j][k];
                
            }
            OIH[j][o]=OIH[j][o]+W[0][0];
            
             
             OOH[j][o]= 1.0/(1+exp(-OIH[j][o]));
               output = OOH[j][o]; 
            
             error =0;
               error =error+ (t[0][o]-OOH[j][o]);
           
           delW[j][o]=0;
           delW[j][o] = delW[j][o]+ (eta)*error*a2*OOH[j][o]*(1-OOH[j][o])*OH[j][o];
           W[j][o]=W[j][o]+delW[j][o];
          
      
            delW[j][o]=0;
            for(k=0;k<n+1;k++){
                delV[j][k]=0;
            delV[j][k] = delV[j][k] + (eta)/(n)*(t[0][o]-OOH[j][o])*a2*OOH[j][o]*(1-OOH[j][o])*W[j][k]*a1*OH[j][o]*(1-OH[j][o])*in[k][o];
       
            V[j][k]=V[j][k]+delV[j][k];
           
            }
           
           }
         mse = mse + 0.5*error*error ;
        fprintf(out,"%0.2f\t", output);
             fprintf(out,"%0.2f\n",error);

       
    }
       e=mse/p ;
         fprintf(out,"mean square error at iteration %d is %f\n",q,e);
         q=q+1;
    }
    
    }
  return 0;
}