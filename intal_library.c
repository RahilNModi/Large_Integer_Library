#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "intal.h"

static char *trimmer(char *str, const char *str1)
{
    size_t len;
    if (str1 == NULL) {
        str1 = "\t\n\v\f\r ";
    }
    len = strspn(str, str1);
    if (len > 0) {
        size_t length = strlen(str);
        if (len == length) {
            str = "0";
        }
        else {
            memmove(str, str + len, length + 1 - len);
        }
    }
    return str;
}

char* intal_add(const char* intal1, const char* intal2)
{
    int length1 = strlen(intal1);
    int length2 = strlen(intal2);
    int max = length1;
    int i,sum=0,c=0;
    if(length2 > length1)
        max = length2;
    char *final_intal = (char *)calloc((max+2),sizeof(char));
    final_intal[max+1]='\0';
    for(i=1; i<=max; i++)
    {
        if(i<=length1 && i<=length2)
            sum = c + (intal1[length1-i]-'0') + (intal2[length2-i]-'0');
        else if(i > length1)
            sum = c + (intal2[length2-i]-'0');
        else
            sum = c + (intal1[length1-i]-'0');
        c = sum / 10;
        final_intal[max+1-i] = (sum % 10)+'0';
    }
    final_intal[max+1-i]='0';
    if(c)
    {
        final_intal[max+1-i] = c + '0';
    }
    return trimmer(final_intal,"0");
}

int intal_compare(const char* intal1, const char* intal2)
{
    int result;
    if(strlen(intal1) > strlen(intal2))
        result = 1;
    else if(strlen(intal1) < strlen(intal2))
        result = -1;
    else
        result = strcmp(intal1,intal2);
    return result;
}

char* intal_diff(const char* intal1, const char* intal2)
{
    int length1 = strlen(intal1);
    int length2 = strlen(intal2);
    int max = length1;
    int i,diff=0,b=0;
    if(length2 > length1)
        max = length2;
    char *final_intal = (char *)calloc((max+1),sizeof(char));
    final_intal[max]='\0';
    if(intal_compare(intal1, intal2) == 1)
    {
        for(i=1; i<=max; i++)
        {
            if(i<=length1 && i<=length2)
            {
                if(intal1[length1-i]-b < intal2[length2-i])
                {
                    diff = (10+(intal1[length1-i]-'0')) - (intal2[length2-i]-'0') - b;
                    b=1;
                }
                else
                {
                    diff = (intal1[length1-i]-'0') - (intal2[length2-i]-'0') - b;
                    b=0;
                }
            }
            else
            {
                if(intal1[length1-i]-b < '0')
                {
                    diff = 10+(intal1[length1-i]-'0') - b;
                    b=1;
                }
                else
                {
                    diff = (intal1[length1-i]-'0') - b;
                    b=0;    
                }
            }
            final_intal[max-i] = diff + '0';
        }
    }
    else
    {
        for(i=1; i<=max; i++)
        {
            if(i<=length2 && i<=length1)
            {
                if(intal2[length2-i]-b < intal1[length1-i])
                {
                    diff = (10+(intal2[length2-i]-'0')) - (intal1[length1-i]-'0') - b;
                    b=1;
                }
                else
                {
                    diff = (intal2[length2-i]-'0') - (intal1[length1-i]-'0') - b;
                    b=0;
                }
            }
            else
            {
                if(intal2[length2-i]-b < '0')
                {
                    diff = 10+(intal2[length2-i]-'0') - b;
                    b=1;
                }
                else
                {
                    diff = (intal2[length2-i]-'0') - b;
                    b=0;    
                }
            }
            final_intal[max-i] = diff + '0';
        }
    }   
    return trimmer(final_intal,"0");  
}


char* intal_multiply(const char* intal1, const char* intal2)
{
    int length1 = strlen(intal1);
    int length2 = strlen(intal2);
    int i,j, product=0, c1=0, c2=0, sum=0;
    char *final_intal = (char *)calloc((length1+length2+1),sizeof(char));
    final_intal[length1+length2]='\0';
    memset(final_intal, '0', length1+length2);
    if(intal_compare(intal1,"0")==0 || intal_compare(intal2,"0")==0)
        return trimmer(final_intal,"0");
    else
    {
    for(i=1; i<=length2; i++)
    {
        for(j=1; j<=length1; j++)
        {
            product = c1 + ((intal1[length1-j]-'0') * (intal2[length2-i]-'0'));
            c1 = product / 10;
            sum = c2 +(final_intal[length1+length2+1-i-j]-'0') + (product % 10);
            c2 = sum / 10;
            final_intal[length1+length2+1-i-j] = (sum % 10) + '0';
        }
        if(c1)
        {
            sum = c2 +(final_intal[length1+length2+1-i-j]-'0') + c1;
            c2 = sum / 10;
            final_intal[length1+length2+1-i-j] = (sum % 10) + '0';
            c1=0;
            j++;
        }
        if(c2)
        {
            final_intal[length1+length2+1-i-j] = ((final_intal[length1+length2+1-i-j]-'0') + c2) +'0';
            c2=0;
        } 
    }
    return trimmer(final_intal,"0");
    }  
}

char* intal_mod(const char* intal1, const char* intal2)
{
    int len1 = strlen(intal1);
    char *final_intal = (char *)calloc(len1+1,sizeof(char));
    final_intal[len1]='\0';
    if(strcmp(intal2,"1")==0)
    {
        final_intal = "0";
        return final_intal;
    }
    else
    {
        char *p;
        char *temp = (char *)calloc(len1+2,sizeof(char));
        strcpy(final_intal,intal1);
        while(intal_compare(final_intal,intal2) !=- 1)
        {
            strcpy(temp,intal2);
            while(intal_compare(temp,final_intal) != 1)
            {
                p = temp;
                temp = intal_multiply(temp,"10");
                free(p);
            }
            temp[strlen(temp)-1]='\0';
            while(intal_compare(final_intal,temp) != -1)
            {
                p = final_intal;
                final_intal = intal_diff(final_intal,temp);
                free(p);
            }
        }
        return trimmer(final_intal,"0");
    } 
}

char* intal_pow(const char* intal1, unsigned int n)
{
    char *final_intal = (char *)calloc(1002,sizeof(char));
    final_intal[1001]='\0';
    if(intal_compare(intal1, "0") == 0)
    {
        strcpy(final_intal,"0");
        return final_intal;
    }
    else if(n == 0)
    {
        strcpy(final_intal,"1");
        return final_intal;
    }
    else
    {
        char *temp = final_intal;
        final_intal = intal_pow(intal1, n/2);
        free(temp);
        temp = final_intal;
        final_intal = intal_multiply(final_intal,final_intal);
        free(temp);
        if(n%2 == 1)
        {
            temp = final_intal;
            final_intal = intal_multiply(final_intal,intal1);
            free(temp);
        }
        return trimmer(final_intal,"0"); 
    }
}

char* intal_gcd(const char* intal1, const char* intal2)
{
    char *final_intal = (char *)calloc(1002,sizeof(char));
    char *temp1 = (char *)calloc(1002,sizeof(char));
    char *temp,*p;
    final_intal[1001]='\0';
    if(intal1 == 0 || intal2 == 0)
    {
        strcpy(final_intal,"0");
        return final_intal;
    }
    else if (intal_compare(intal1,intal2) == -1)
    {
        strcpy(temp1,intal1);
        strcpy(final_intal,intal2);
    }
    else
    {
        strcpy(final_intal,intal1);
        strcpy(temp1,intal2);   
    }
    while(intal_compare(temp = intal_mod(final_intal,temp1),"0")!=0)
    {
        p = final_intal;
        final_intal = temp1;
        free(p);
        temp1 = temp;   
    }
    free(temp);
    free(final_intal);
    return trimmer(temp1,"0");
    
}

char* intal_fibonacci(unsigned int n)
{
    char *final_intal;
    char *temp1 = (char *)calloc(1002,sizeof(char));
    char *temp2 = (char *)calloc(1002,sizeof(char));
    temp1[1001] = '\0';
    temp2[1001] = '\0';
    strcpy(temp1,"0");
    strcpy(temp2,"1");
    int count = 2;
    if(n == 0)
    {
        free(temp2);
        return temp1;
    }
    else if(n == 1)
    {
        free(temp1);
        return temp2;
    }
    else
    {
        while(count <= n)
        {
            final_intal = intal_add(temp1,temp2);
            strcpy(temp1,temp2);
            strcpy(temp2,final_intal);
            free(final_intal);
            count++;
        }
        free(temp1);
        return temp2;
    }
}

char* intal_factorial(unsigned int n)
{
    char *temp = (char *)calloc(1002,sizeof(char));
    char *final_intal;
    char *number = (char *)calloc(502,sizeof(char));
    int i;
    temp[1001] = '\0';
    number[501] ='\0';
    strcpy(temp,"1");
    for(i = n; i>0; i--)
    {
        sprintf(number,"%d",i);
        final_intal = intal_multiply(temp,number);
        strcpy(temp,final_intal);
        free(final_intal);
    }
    free(number);
    return(temp);
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    char *final_intal = (char*)malloc(1002*sizeof(char));
    char *temp;
    final_intal[1001] = '\0';
    if(k > n/2)
            k = n-k;
    if(n==0 && k==0)
    {
        strcpy(final_intal,"0");
        return final_intal;
    }
    else if(k==0)
    {
        strcpy(final_intal,"1");
        return final_intal;
    }
    else if(k==1)
    {
        sprintf(final_intal,"%d",n);
        return final_intal;
    }
    else
    {
        int i,j;
        char **DPcol1 = (char**)malloc((k+1)*sizeof(char *));
        char **DPcol2 = (char **)malloc((k+1)*sizeof(char *));
        for(i = 0; i < (k+1); i++) {
		    DPcol1[i] = (char*) malloc(1001 * sizeof(char));
	    }
        for(i = 0; i < (k+1); i++) {
		    DPcol2[i] = (char*) malloc(1001 * sizeof(char));
	    }
        strcpy(DPcol1[0],"1");
        strcpy(DPcol1[1],"1");
        for(i = 2; i<=n; i++)
        {
            strcpy(DPcol2[0],"1");
            if(i<=k)
            {
                strcpy(DPcol2[i],"1");
                for(j = 1; j < i; j++)
                {
                    temp = DPcol2[j];
                    DPcol2[j] = intal_add(DPcol1[j],DPcol1[j-1]);
                    free(temp);
                }
            }
            else
            {
                for(j = 1; j <= k; j++)
                {
                    temp = DPcol2[j];
                    DPcol2[j] = intal_add(DPcol1[j],DPcol1[j-1]);
                    free(temp);
                }
            }
            for(j = 0; j < k+1; j++)
            {
                strcpy(DPcol1[j],DPcol2[j]);
            }
        }
        strcpy(final_intal,DPcol1[k]);
        for(i=0; i<(k+1); i++)
        {
            free(DPcol1[i]);
            free(DPcol2[i]);
        }
        free(DPcol1);
        free(DPcol2);
        return trimmer(final_intal,"0");
    }
}

int intal_max(char **arr, int n)
{
    int offset = 0;
    for(int i=1; i < n; i++)
    {
        if(intal_compare(arr[offset],arr[i]) == -1)
            offset = i;
    }
    return offset;
}

int intal_min(char **arr, int n)
{
    
    int offset = 0;
    for(int i=1; i < n; i++)
    {
        if(intal_compare(arr[offset],arr[i]) == 1)
            offset = i;
    }
    return offset;
}

int intal_search(char **arr, int n, const char* key)
{
    for(int i=0; i < n; i++)
    {
        if(intal_compare(arr[i],key)==0)
            return i;
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    int low = 0, high = n-1, mid;
    while(low <= high)
    {
        mid = low + (high - low)/2;
        if((mid == 0 || intal_compare(key,arr[mid -1]) == 1) && intal_compare(arr[mid],key) == 0)
            return mid;
        else if(intal_compare(arr[mid],key) == -1)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

static void heapify(char **arr,int n)
{
    int i,j,k;
    char *key;
    for(k=(n-1)/2; k>=0; k--)
    {
        j = k;
        key = arr[j];
        i = 2*j+1;
        while(i<n)
        {
            if(i+1<n)
                if(intal_compare(arr[i+1],arr[i]) == 1)
                    i++;
            if(intal_compare(arr[i],key) == 1)
            {
                arr[j] = arr[i];
                j = i;
                i = 2*j+1;
            }
            else
                break;
        }
        arr[j] = key;
    }
}

void intal_sort(char **arr, int n)
{
    char *temp;
    int i;
    for(i=n; i>0; i--)
    {
        heapify(arr,i);
        temp = arr[i-1];
        arr[i-1] = arr[0];
        arr[0] = temp;
    }
}

char* coin_row_problem(char **arr, int n)
{
    char *final_intal;
    char *temp1 = (char *)calloc(1002,sizeof(char));
    char *temp2 = (char *)calloc(1002,sizeof(char));
    strcpy(temp1,"0");
    strcpy(temp2,arr[0]);
    int i;
    for(i = 2; i<=n; i++)
    {
        final_intal = intal_add(temp1,arr[i-1]);
        if(intal_compare(final_intal,temp2) == -1)
            strcpy(final_intal,temp2);
        strcpy(temp1,temp2);
        strcpy(temp2,final_intal);
        free(final_intal);
    }
    free(temp1);
    return trimmer(temp2, "0");
}