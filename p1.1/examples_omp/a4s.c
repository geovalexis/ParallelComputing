#define N 100000000

int a[N],b[N],c[N];
long long s=0;

main()
{
int i;

for(i=0;i<N;i++)
{
 a[i]=1;
 b[i]=2;
 c[i]=0;
}

    for (i=0;i<N;i++)
     b[i] += a[i];

    for (i=0;i<N;i++)
     c[i] += b[i];

/* checksum */
s=0;
for (i=0;i<N;i++)
 s+=b[i];

 printf("Valor %d, de b %d suma total: %ld\n",i-1,b[i-1],s);

/* checksum */
s=0;
for (i=0;i<N;i++)
 s+=c[i];

 printf("Valor %d, de c %d suma total: %ld\n",i-1,c[i-1],s);
}


