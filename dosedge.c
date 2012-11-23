#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define miu 0.5 //Chemical Potential in units of t: the hopping integral

#define N 150   // the number of points in the arrary of the density of states

#define M 8000  // the division of the Brouine zone M*M

#define Pi 3.1415926

double edgeenergy(double x){
double ene;
double ene1;
ene1 = sqrt(miu*miu+4.0*cos(sqrt(3)/2.0*x));

ene = 1-ene1;

return(ene);

}



int main()
{
   int i,j,l;
   FILE *fp;
   int count = 0;
   float sum = 0;
   double DOS[N];
   double Max = 1-sqrt(miu*miu);
   double Min = 1-sqrt(miu*miu+4);
   double delta = (Max - Min)/N;
   double range = delta/2.0;
   double energyindex[N];//this means that eneryindex[n] is the value of the nth energy 
   for(i=0;i<N;i++){
     DOS[i]=0;
     energyindex[i] = Min + i*delta;
   }
   double energyband[M];
   double kx[M];
   //double ky[M];
   double delta1 = 2*Pi/M;
   float miu1 = miu;
   for(i=0;i<M;i++){
     kx[i]=-Pi+i*delta1;
     //ky[i]=kx[i];
   }
   for(i=0;i<M;i++)
     //for(j=0;j<M;j++)
       {
          energyband[i]=edgeenergy(kx[i]);
       }
   for(i=0;i<N;i++){
     count = 0;
     for(j=0;j<M;j++)
       //for(l=0;l<M;l++)
         {
            if((energyband[j]>energyindex[i]-range)&&(energyband[j]<energyindex[i]+range))
		count++;
         }
     DOS[i]=count;
   }
   for(i=0;i<N;i++)
     {
       sum = sum + DOS[i];
     }
   for(i=0;i<N;i++){
     DOS[i] = DOS[i]/sum;
   }

   fp=fopen("densityofedgestates.dat","wt+");
   if(fp==NULL){
      printf("cannot open file densityofstates.dat\n");
      return ;
   }
   fprintf(fp,"------Density of Edge States of Grapene-----\n");
   fprintf(fp,"------Tight Binding Calculations-------\n");
   fprintf(fp,"------Chemical Potential:%f------------\n",miu1);
   for(i=0;i<N;i++)
     {
       fprintf(fp,"%f %f\n",energyindex[i],DOS[i]);
     }
   fclose(fp);
}
