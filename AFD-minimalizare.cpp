#include <iostream>
#include<vector>

using namespace std;
int n,nrl,f,*F;
std::vector <int> **A ;
int **s;
vector <int> functie1(int q,int contor1,int contor2)
{  int i;
   vector <int> v;
   int siz,j;
   for(int k=0;k<nrl;k++)
   {int a=s[q][k];
    for(i=0;i<contor2+1;i++)
        { siz=A[contor1][i].size();
          for( j=0;j<siz;j++)
            if(a==A[contor1][i][j])
               v.push_back(i);}}
return v;
}
int functie2(int contor1,int contor2)
{ int p=1,j,k1,k2,i;
    for(i=0;i<contor2+1;i++)
    {   int siz=A[contor1][i].size();
        vector <int> v[20];
        //cout<<"size="<<siz<<"\n";
        for( j=0;j<siz;j++)
          { int q=A[contor1][i][j];
            v[j]=functie1(q,contor1,contor2);
            }
        for(k1=0;k1<siz;k1++)
            for(k2=0;k2<siz;k2++)
                   if(v[k1]!=v[k2])
                       p=0;

    }

  return p;
}
int main()
{   //stari totale

    cout<<"cate stari are automatul?\n"; cin>>n;
    int Q[n],i,q0;
    for(i=0;i<n;i++) Q[i]=i;



    //alfabet
    cout<<"cate litere are alfabetul?\n"; cin>>nrl;
    char AA[nrl],c;
    for(i=0;i<nrl;i++)
        {cin>>c;
          AA[i]=c;}
    //starea initiala
    cout<<"care este starea initiala?"; cin>>q0;

    //starile finale

    cout<<"cate stari finale are automatul?\n"; cin>>f;
    F=new int[f];
    cout<<"care sunt acestea?\n";
    for(i=0;i<f;i++)
    {
        cin>>F[i];
    }
   int z,y;
    //functia de tranzitie
   s=new int* [n];
   for(i=0;i<n;i++)
    s[i]=new int [nrl];
   cout<<"functia de tranzitie:\n";
   for(i=0;i<n;i++)
        for(int j=0;j<nrl;j++){
           cout<<Q[i]<<"->"<<AA[j]<<"\n";
           cout<<"introduceti numarul de stari in care ajunge:\n";
           cin>>z;
           if(z==1)
            {cout<<"in ce stare ajunge?\n";
             cin>>y;
             s[i][j]=y;}
            else if(z==0) s[i][j]=-1;
                 }


    y=0;
    int j,ok=1;
    A=new vector <int> *[20];
    for(i=0;i<n;i++)
        A[i]=new vector <int> [20];
    for(i=0;i<n;i++)
     {ok=1;
      for(j=0;j<f;j++)

        {if(Q[i]==F[j])
               ok=0;}
      if(ok==1) {A[0][0].push_back(Q[i]); y++;}
     }
    for(i=0;i<f;i++)
        A[0][1].push_back(F[i]);
cout<<"a[0]=\n";
for(i=0;i<2;i++)
{ int siz=A[0][i].size();
    for(j=0;j<siz;j++)
      cout<<A[0][i][j]<<" ";
 cout<<"\n";}

 int contor1=0, contor2=1, contor1curent, contor2curent,l1;
 int W;
 W=functie2(contor1,contor2);

 if(W!=0) {cout<<"Automatul este deja minimal!\n"; return 0;}
 while(W==0)
 {
     contor1curent=contor1+1;
     contor2curent=0;
     for(int k1=0;k1<contor2+1;k1++)
     {
         int m=contor2curent;
         A[contor1curent][contor2curent].push_back(A[contor1][k1][0]);
         int siz=A[contor1][k1].size();
         for(i=1;i<siz;i++)
         {  vector <int> l;
             l=functie1(A[contor1][k1][i],contor1,contor2);
             ok=0;
             for(int i1=m;i1<contor2curent+1;i1++)
             {   vector <int> l1;
                 l1=functie1(A[contor1curent][i1][0],contor1,contor2);
                 if(l==l1)
                 {
                     ok=1;
                     A[contor1curent][i1].push_back(A[contor1][k1][i]);
                     break;
                 }
             }
             if(ok==0)
             {
                 contor2curent++;
                 A[contor1curent][contor2curent].push_back(A[contor1][k1][i]);
             }
         }
         if(k1+1<contor2+1) contor2curent++;
     }
     contor1=contor1curent;
     contor2=contor2curent;
     W=functie2(contor1,contor2);
     cout<<"a["<<contor1<<"]=\n";
     for(i=0;i<contor2+1;i++)
     {int siz=A[contor1][i].size();
         for(j=0;j<siz;j++)
          cout<<A[contor1][i][j]<<" ";
      cout<<"\n";}
 }




int k;
 //afisare automat
 cout<<"NUMARUL DE STARI AL AUTOMATULUI MINIMAL ESTE "<<contor2+1<<"\n";
 for(i=0;i<contor2+1;i++)
    for(j=0;j<A[contor1][i].size();j++)
      if(A[contor1][i][j]==q0)
        cout<<"STAREA INITIALA ESTE q"<<i<<"\n";
 cout<<"STARILE FINALE SUNT: ";
 for(k=0;k<f;k++)
   for(i=0;i<contor2+1;i++)
    for(j=0;j<A[contor1][i].size();j++)
     if(F[k]==A[contor1][i][j])
       cout<<"q"<<i<<" ";
 cout<<"\n";


 for(i=0;i<contor2+1;i++)
 {
     cout<<"q"<<i<<" merge prin\n";
        { vector <int> v;
            v=functie1(A[contor1][i][0],contor1,contor2);
            for(int t=0;t<v.size();t++)
                cout<<char(97+t)<<" in q"<<v[t]<<"\n";}
 }
   return 0;
}
