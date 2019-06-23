#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int read_array (const char *name,double *a,int maxn);
void print_array(double *a, int n);
int zadanie3(double *a,int n,double *b,int m,double *c,int (*cmp)(double,double));
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
int zadanie3(double *a,int n,double *b,int m,double *c,int (*cmp)(double,double))
{
    int i=0,j=0,k=0;
    while((i<n)&&(j<m))
    {
        if ((*cmp)(a[i],b[j]))
            {
                c[k]=a[i];
                i++;
                k++;
            }
            else
             if ((*cmp)(b[j],a[i]))
                {
                    c[k]=b[j];
                    j++;
                    k++;
                }
                else  i++;


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
    return k;
}
int main (void)
{
    const char *name1="a.txt";
    const char *name2="b.txt";
    int n,m,key1=0,key2=0;
    double *a,*b,*c;
    int res1,res2,result;
    int (*ptr)(double,double);
    ptr=&f;
    printf ("Input n and m:");
    if(scanf("%d%d",&n,&m)!=2)
    {
        printf("Cannot read!\n");
        return 1;
    }
    if(!(a=(double*)malloc(n*sizeof(double))))
    {
        printf ("Not enough memory!\n");
        return 2;
    }
    if(!(b=(double*)malloc(m*sizeof(double))))
    {
        printf ("Not enough memory!\n");
        return 2;
    }
    if(!(c=(double*)malloc((n+m)*sizeof(double))))
    {
        printf ("Not enough memory!\n");
        return 2;
    }
    if(key1==0)
    {
        res1=read_array(name1,a,n);
        if(res1<0)
        {
            switch (res1)
            {
                case -1: printf("Cannot open %s\n",name1);
                case -2: printf("Cannot read %s\n",name1);
                default: printf("Unknown error \n");
            }
            free (a);
            return 3;
        }
        n=res1;
    }
    if(key2==0)
    {
        res2=read_array(name2,b,m);
        if(res2<0)
        {
            switch (res2)
            {
                case -1: printf("Cannot open %s\n",name2);
                case -2: printf("Cannot read %s\n",name2);
                default: printf("Unknown error \n");
            }
            free (b);
            return 3;
        }
        m=res2;
    }
    printf("Array a: \n");
    print_array (a,n);
    printf("Array b: \n");
    print_array (b,m);
    result=zadanie3 (a,n,b,m,c,ptr);
    printf("Result array: \n");
    print_array(c,result);
    printf("Otvet: %d",result);
    free(a);
    free(b);
    free(c);
    return 0;
}
