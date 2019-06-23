#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int read_array (const char *name,double *a,int maxn);
void print_array(double *a, int n);
int zadanie1(double *a,int n,double x,int (*cmp)(double,double));
int f(double a,double b);
int f(double a,double b)
{
    return (a<b);
}
int read_array (const char *name,double *a,int maxn)
{
    FILE *fp;
    int i;
    if(!(fp=fopen(name,"r"))) return -1;
    for (i=0;i<maxn;i++)
    {
        if (fscanf(fp,"%lf",a+i)!=1)
        {
            if(!feof(fp))
            {
                fclose(fp);
                return -2;
            }
        }
    }
    fclose (fp);
    return i;
}
#define NMAX 20
void print_array(double *a, int n)
{
    int i;
    int m=(n>NMAX?NMAX:n);
    for (i=0;i<m;i++)
        printf("%lf\n",a[i]);
}
int zadanie1(double *a,int n,double x,int (*cmp)(double,double))
{
    int s,l=0,r=n;
    while (l!=r)
      {
       s=(l+r)/2;
    if ((*cmp)(a[s],x))
        l=s+1;
    else r=s;
      }
return l;
}
int main (void)
{
    const char *name="a.txt";
    int n,key=0;
    double *a,x;
    int res;
    int result;
    int (*ptr)(double,double);
    ptr=&f;
    printf ("Input n and x:");
    if(scanf("%d%lf",&n,&x)!=2)
    {
        printf("Cannot read!\n");
        return 1;
    }
    if(!(a=(double*)malloc(n*sizeof(double))))
    {
        printf ("Not enough memory!\n");
        return 2;
    }
    if(key==0)
    {
        res=read_array(name,a,n);
        if(res<0)
        {
            switch (res)
            {
                case -1: printf("Cannot open %s\n",name);
                case -2: printf("Cannot read %s\n",name);
                default: printf("Unknown error \n");
            }
            free (a);
            return 3;
        }
        n=res;
    }
    print_array (a,n);
    result=zadanie1 (a,n,x,ptr);
    printf ("Otvet %d\n",result);
    free(a);
    return 0;
}
