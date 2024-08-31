#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> keyid(3, vector<int> (5,-1));//pid,sec,min vector
int stdevceil;

int reversenum(int x)
{
    int r=0,rev=0;
    while(x>0)
    {
        rev=rev*10+x%10;
        x=x/10;
    }
    return rev;
}

void key_matrix(vector<int> keym)
{
    int j;
    int pid=keym[0];
    int minute = keym[2];
    int second = keym[1];
    int v=0;
       int w=reversenum(pid);
       for(j=0;j<5;j++)
       {
         keyid[v][j]=w%10;
         w=w/10;
         if(w==0)
        {
            v++;
           break;
        }
     }
    w=reversenum(minute);
    for(j=0;j<5;j++)
    {
        keyid[v][j]=w%10;
        w=w/10;
        if(w==0)
        {
            v++;
           break;
        }
    }
     w=reversenum(second);
    for(j=0;j<5;j++)
    {
        keyid[v][j]=w%10;
        w=w/10;
        if(w==0)
        {
            v++;
           break;
        }
    }
}

string encrypt(string str, vector<int> keym)
{
    
    key_matrix(keym);
    int row=str.length(),i=0,j;
   vector<vector<int>> asc(row, vector<int> (3,-1));//ascii vector
   if(row>3)
    keyid.resize(row,vector<int> (5,-1));
    for(int k=0;k<row;k++)
    {
        int t=0;
        int y=int(str[k]);
        int reversed_number=0;
        int f=0;
        if(y%10==0)
            f++;
        if(y%100==0)
            f++;
        if(y%1000==0)
            f++;
        while(y > 0) 
        {
            reversed_number = reversed_number * 10 + y % 10;
            y/=10;
        }
        while(reversed_number>0)
        {
            
            asc[i][t]=reversed_number%10;
            reversed_number/=10;
            t++;
        }
        if(t==2&&f==0)
            asc[i][t]=-1;
        if(f>0)
        {
            for(int q=0;q<f;q++)
            {
                
                asc[i][t++]=0;
            }
                
                
        }
        i++;
    }
    vector<vector<int>> res(row, vector<int> (3,-1));//ascii vector
    for(i=0;i<row;i++)//printing ascii matrix
        {
        for(j=0;j<3;j++)
            res[i][j]=asc[i][j]+keyid[i][j];
        cout<<endl;
        }
    //standard deviation
    double sum=0;
    for( i=0;i<row;i++)
    {
        for(j=0;j<3;j++)
        {
            sum=sum+res[i][j];
        }
    }
    double mean = sum /(row*5);
    sum=0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<3;j++)
        {
            sum=sum+res[i][j]*res[i][j];
        }
    }
    double stdev=sqrt(sum / (row*3) - mean * mean);
    stdevceil=ceil(stdev);

    vector<vector<int>> mul1(row, vector<int> (3));
    
    for(i=0;i<row;i++)
    {
        for(j=0;j<3;j++)
            mul1[i][j]=res[i][j]-stdevceil;

    }
    vector<vector<int>> final(row, vector<int> (3));
    for(i=0;i<row;i++)
    {
        for(j=0;j<3;j++)
        {
            if(mul1[i][j]>=0)
                final[i][j]=2*(mul1[i][j]);
            else
                final[i][j]=1-(2*(mul1[i][j]));
        }
    }
    string crypt;
    int k=0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<3;j++)
        {
            crypt.push_back(final[i][j]+'0');
        }
        
    }
    return crypt;
}

string matrix_decrypt(string crypt)
{
    int i, j;
    int n_row=crypt.length()/3;
    vector<vector<int>> revmul1(n_row, vector<int> (5));
    vector<vector<int>> rev_final(n_row, vector<int> (3));
    float temp;
    for(int i=0;i<crypt.length();i++)
    {
        rev_final[i/3][i%3]=crypt[i]-'0';
    }
    for(i=0;i<n_row;i++)  //yaha row dalna hoga
    {
        for(j=0;j<3;j++)
        {
            if((rev_final[i][j])%2==0)
            {
                revmul1[i][j]=(rev_final[i][j])/2;
                
            }
            else
            {
                revmul1[i][j]=(1-(rev_final[i][j]))/2;
            }
        }
    }
    //sub standard deviation
    //here stdevceil is a key
    for(i=0;i<n_row;i++)
    {
        for(j=0;j<3;j++)
        {
            revmul1[i][j]=revmul1[i][j]+stdevceil;
        }
    }
    vector<vector<int>> decrypt(n_row, vector<int> (3));
    for(i=0;i<n_row;i++)
    {
        for(j=0;j<3;j++)
            decrypt[i][j]=revmul1[i][j]-keyid[i][j];
    }
    vector<int> vec(n_row);
    int k=0;
    for(i=0;i<n_row;i++)
    {
        int result=0;
        for(j=0;j<3;j++)
        {
            if(decrypt[i][j]!=-1)
                result = result * 10 + decrypt[i][j];
            
        }
        vec[k++]=result;
    }
    string text;
    for(int i=0;i<k;i++)
    {
        //cout<<vec[i];
        char c=vec[i];
        text.push_back(c);
    }   
    return text;
    
}

