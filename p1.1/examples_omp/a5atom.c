#define N 100000000
#define MAX 4

int a[N],b[N],ind[N];
long long s=0;

main()
{
int i;

/* inicialitzacio, no en paral.lel */

for(i=0;i<N;i++)
{
 a[i]=1;
 b[i]=2;
 ind[i]=i%MAX;
}

#pragma omp parallel for
for (i=0;i<N;i++)
 #pragma omp atomic 
 b[ind[i]] += a[i];

for (i=0;i<MAX;i++)
{
 printf("Valor %d, de b %d \n",i,b[i]);
 s+=b[i];
}


 printf("Suma total de b: %ld\n",s);


}


