#include <bits/stdc++.h>
#include "matrix.cpp"
#include "tree.cpp"
using namespace std;

vector<int> key(3);//key vector

void key1()
{
    pid_t pid = getpid();
    key[0]=pid;
    
}

void key2()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *ltm = localtime(&now);
    key[1]=ltm->tm_sec;
    key[2]=ltm->tm_min;
}

int main()
{
    key1();
    key2();
    int pidd=key[0];
    int p=0;
    while(pidd>0)
    {
        p+=(pidd%10);
        pidd/=10;
    }
    cout<<p<<endl;
    string s, s1, s2;
    cout<<"enter string"<<endl;
    getline(cin,s);
    int str_size = s.length();
    for (int i = 0; i < str_size/2; i++)
    {
        s1.push_back(s[i]);
    }
    for (int i = str_size/2; i < str_size; i++)
    {
        s2.push_back(s[i]);
    }
    string e1,e2;
    //cout<<"***ENCRYPTION***"<<endl;
    if(p%2==0)
    {
        e1=encrypt(s1,key);
        e2=tree_prep(s2,key);
    }
    else
    {
        e1=tree_prep(s1,key);
        e2=encrypt(s2,key);
    }
    string d1,d2;
    //cout<<"***DECRYPTION***"<<endl;
    if(p%2==0)
    {
        d1=matrix_decrypt(e1);
        d2=tree_end(e2,key);
        cout<<endl;
        cout<<"encrypted text:";
        cout<<e1;
       
        for(int i=0;i<cypher_text.length();i++)
        {
            if(cypher_text[i]==' ')
                continue;
            else
                cout<<cypher_text[i];
        }
        cout<<endl;
        cout<<"decrypted text:";
        //cout<<"matrix:"<<d1;
        cout<<d1<<d2<<endl;
    }
    else
    {
        d1=tree_end(e1,key);
        d2=matrix_decrypt(e2);
        cout<<"encrypted text:";
        
        for(int i=0;i<cypher_text.length();i++)
        {
            if(cypher_text[i]==' ')
                continue;
            else
                cout<<cypher_text[i];
        }
        cout<<e2;
        cout<<endl;
        cout<<"decrypted text:";
        
        cout<<d1<<d2<<endl;
        
    }
    
    return 0;
}