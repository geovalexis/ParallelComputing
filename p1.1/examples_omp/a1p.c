#define N 200000000

int a[N],b[N];
long long s=0;

main()
{
int i,j;

/* inicialitzacio, no en paral.lel */

#pragma omp parallel

{

#pragma omp for
for(i=0;i<N;i++)
{
 a[i]=1;
 b[i]=2;
}

#pragma omp for
for (i=0;i<N;i++)
 b[i] += a[i];

 printf("Valor i %d, de b[i] %d \n",i-1,b[i-1]);
 
}

for (i=0;i<N;i++)
 s+=b[i];


printf("Valor %d, de b %d suma total: %ld\n",i-1,b[i-1],s);

}


