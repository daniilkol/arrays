#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
int read_array (const char *name, double *a,int maxn);
void init_array (double *a, int n, int key);
void print_array (double *a,int n);
void zadanie7 (double *a, int n,int (*cmp)(double,double));
int zadanie1(double *a,int n,double x,int (*cmp)(double,double));
int f(double a,double b);
int f(double a,double b)
{
    return (a<b);
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
    int m=(n >NMAX ? NMAX:n);
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
void zadanie7 (double *a, int n,int (*cmp)(double,double))
{
  int i,j,k;
  double p;
  for (i=1;i<n;i++)
  {   p=a[i];
      k=zadanie1(a,i,a[i],cmp);
      for (j=i;j>k;j--)
      a[j]=a[j-1];
      a[k]=p;
  }
}
int main (void)
{
    const char *name="a.txt";
    int n,key;
    double *a,t;
    int res;
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
       zadanie7(a,n,ptr);
       t=(clock()-t)/CLOCKS_PER_SEC;
       printf("Array after sort: \n");
       print_array(a,n);
       printf("Elapsed: %lf",t);
       free(a);
       return 0;
}
