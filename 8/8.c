#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
int read_array (const char *name, double *a,int maxn);
void init_array (double *a, int n, int key);
void print_array (double *a,int n);
int f(double a,double b);
void zadanie2(double *a,int n,double *b,int m,double *c,int (*cmp)(double,double));
void zadanie8 (double *a,double *b, int n,int (*cmp)(double,double));
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
    int m=(n>NMAX?NMAX:n);
    for (i=0;i<m;i++)
    printf("%lf\n",a[i]);
}
void zadanie2(double *a,int n,double *b,int m,double *c,int (*cmp)(double,double))
{
    int i=0,j=0,k=0;
    while((i<n)&&(j<m))
    {
        if ((*cmp)(a[i],b[j]))
            {
                c[k]=a[i];
                i++;
            }
            else
            {
                c[k]=b[j];
                j++;
            }
            k++;
    }
    if (i==n)
    while (j<m)
    {
        c[k]=b[j];
        k++;
        j++;
    }
    else
        while (i<n)
    {
        c[k]=a[i];
        k++;
        i++;
    }
}
void zadanie8 (double *a,double *b, int n,int (*cmp)(double,double))
{
    double *c,*a_original=a;
  int i,j,k=1;

  while (k<=n-1)
  {
    for (i=0;i<n;i=i+2*k)
      if (i+2*k<=n)
	zadanie2 (a+i,k,a+i+k,k,b+i,cmp);
      else
      {
	for (j=i;j<n;j++)
	  b[j]=a[j];
	break;
      }
    c=a;
    a=b;
    b=c;
    k=2*k;
  }
  k=k/2;
  zadanie2(a,k,a+k,n-k,b,cmp);
  if (a==a_original)
    for (i=0;i<n;i++)
      a[i]=b[i];
}
int main (void)
{
    const char *name1="a.txt";
    const char *name2="b.txt";
    int n,key1,key2;
    double *a,*b;
    int res1,res2;
    double t;
    int (*ptr)(double,double);
    ptr=&f;
    printf ("Input n and key1,key2: ");
    if(scanf("%d%d%d",&n,&key1,&key2)!=3)
    {
        printf("Cannot read!\n");
        return 1;
    }
    if(!(a=(double*)malloc(n*sizeof(double))))
       {
           printf("Not enough memory!\n");
           return 2;
       }
    if(!(b=(double*)malloc(n*sizeof(double))))
       {
           printf("Not enough memory!\n");
           return 2;
       }
       if (key1==0)
       {
         res1=read_array(name1,a,n);
            if(res1<0)
            {
                switch (res1)
                {
                    case -1:
                        printf("Cannot open%s\n",name1);
                        break;
                    case -2:
                        printf("Cannot read%s\n",name1);
                        break;
                    default:
                        printf("Unknown error%s\n",name1);
                        break;
                }
                free(a);
                return 3;
            }
            n=res1;
       }
       else init_array(a,n,key1);
    if (key2==0)
       {
         res2=read_array(name2,b,n);
            if(res2<0)
            {
                switch (res2)
                {
                    case -1:
                        printf("Cannot open%s\n",name2);
                        break;
                    case -2:
                        printf("Cannot read%s\n",name2);
                        break;
                    default:
                        printf("Unknown error%s\n",name2);
                        break;
                }
                free(b);
                return 3;
            }
            n=res2;
       }
       else init_array(b,n,key2);
       printf("Array a: \n");
       print_array(a,n);
       t=clock();
       zadanie8(a,b,n,ptr);
       t=(clock()-t)/CLOCKS_PER_SEC;
       printf("Result array: \n");
       print_array(a,n);
       printf("Elapsed=%.2lf\n",t);
       free(a);
       free(b);
       return 0;
}
