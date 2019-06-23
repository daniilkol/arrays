#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
int read_array (const char *name, double *a,int maxn);
void init_array (double *a, int n, int key);
void print_array (double *a,int n);
int split (double*a,int n,int (*cmp)(double,double));
void zadanie9 (double *a,int n,int (*cmp)(double,double));
int f(double a,double b);
int f(double a,double b)
{
    return (a<=b);
}
int read_array (const char *name, double *a,int maxn)
{
    FILE *fp;
    int i;
    if(!(fp=fopen(name,"r")))
        return -1;
   for(i=0;i<maxn; i++)
    {
        if(fscanf(fp,"%lf", a+i)!=1)
        {
            if(!feof(fp))
            {
                fclose(fp);
                return -2;
            }
        }

        }
        fclose(fp);
        return i;
}
void init_array (double *a, int n, int key)
{
    int i;
    srand(key);
    for (i=0;i<n;i++)
        a[i]=rand();
}
#define NMAX 20
void print_array (double *a,int n)
{
    int i;
    int m=(n>NMAX?NMAX:n);
    for (i=0;i<m;i++)
    printf("%lf\n",a[i]);
}
int split (double*a,int n,int (*cmp)(double,double))
{
    double d,c=a[n/2];
    int i=0,j=n-1;
    while (i<=j)
    {
        while(a[i]<c) i++;
        while (a[j]>c) j--;
        if(i<=j)
        {
            d=a[i];
            a[i]=a[j];
            a[j]=d;
            i++;j--;
        }
    }
    if (i>=n) return n-1;
    if (j<0) return 1;
    return i;
}
void zadanie9 (double *a,int n,int (*cmp)(double,double))
{
    if (n<=1) return;
    int k,n1;
    double *a1;
    n1=n;
    a1=a;
    while (n1>1)
    {
        k=split(a1,n1,cmp);
        if(k>n1-k)
        {
            zadanie9(a1+k,n1-k,cmp);
            n1=k;
        }
        else
          {
              zadanie9(a1,k,cmp);
              a1=a1+k;
              n1=n1-k;
          }
    }
}
int main (void)
{
    const char *name="a.txt";
    int n,key;
    double *a;
    int res;
    double t;
    int (*ptr)(double,double);
    ptr=&f;
    printf ("Input n and key: ");
    if(scanf("%d%d",&n,&key)!=2)
    {
        printf("Cannot read!\n");
        return 1;
    }
    if(!(a=(double*)malloc(n*sizeof(double))))
       {
           printf("Not enough memory!\n");
           return 2;
       }
    if (key==0)
       {
         res=read_array(name,a,n);
            if(res<0)
            {
                switch (res)
                {
                    case -1:
                        printf("Cannot open%s\n",name);
                        break;
                    case -2:
                        printf("Cannot read%s\n",name);
                        break;
                    default:
                        printf("Unknown error%s\n",name);
                        break;
                }
                free(a);
                return 3;
            }
            n=res;
       }
       else init_array(a,n,key);
       printf("Array a: \n");
       print_array(a,n);
       t=clock();
       printf("Result array: \n");
       zadanie9(a,n,ptr);
       t=(clock()-t)/CLOCKS_PER_SEC;
       print_array(a,n);
       printf("Elapsed=%.2lf\n",t);
       free(a);
       return 0;
}
