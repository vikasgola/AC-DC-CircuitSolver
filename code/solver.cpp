#include <iostream>
#include<fstream>
#include <vector>
#include<complex>
#include<cmath>
#include <cstring>
#include<iomanip>
#include<eigen3/Eigen/Dense>
using Eigen::MatrixXcd;
using namespace std;

ofstream f;
MatrixXcd m(2,2);
complex<float> a;
MatrixXcd c(1,1);    
MatrixXcd b(1,1); 
MatrixXcd rhs(1,1); 
MatrixXcd lhs(1,1);  
int nodes=0;
int tt=0;

struct st
{
int net1;
int net2;
string n;
string freq;
double amplitude;
double angle;

};
vector<st> angar[1000];
vector<st> angar2[1000];
vector<st> rlc;
int nofreq=0;
struct my
{
    vector<st>vector1[1001];
};

vector<st>yu1;
vector<st>yu2;
int curf=0;
double freq2[1000];
my my2[1000];
vector<st>::iterator it;
double freq[1000];
string freqs[1000];
string freq2s[1000];
my my1[1000];

void   ifunc(int ,int);

void onlyc(int l)
{  
    rhs.resize(nodes+yu1.size(),1);
     rhs.setZero(nodes+yu1.size(),1);
      ifunc(l,1);
      MatrixXcd mm=lhs.colPivHouseholderQr().solve(rhs);
      cout<<endl<<lhs<<endl<<rhs;
       f.precision(3);
  double w=freq2[l]*6.28318530718;
  f<<endl<<"FREQ"<<"="<<freq2s[l]<<endl<<endl<<"VOLTAGES"<<endl;
                     for (  int i=0;i<rlc.size() ;i++)
                              {  
                               
                                if(rlc[i].n.at(0)!='V' && rlc[i].n.at(0)!='I' )
                                {   
                                    complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                    if(rlc[i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))<<" "<<arg(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(aa-mm(rlc[i].net2-1,0))<<" "<<arg(aa-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-aa)<<" "<<arg(mm(rlc[i].net1-1,0)-aa)*57.2957795131<<endl;
                                    
                                    
                                 }
                                 else if(freq2[l]==rlc[i].angle)    
                                {  
                                    
                                 if(rlc[i].n.at(0)!='V')
                                     {  
                                       
                                      complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                    if(rlc[i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))<<" "<<arg(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(aa-mm(rlc[i].net2-1,0))<<" "<<arg(aa-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-aa)<<" "<<arg(mm(rlc[i].net1-1,0)-aa)*57.2957795131<<endl;
                                   
                                     }
                                 else
                                   { 
                                        complex<double> aa;
                                     f<<rlc[i].n<<" "<<fixed<<"0.0"<<" "<<"0.0"<<endl;
                                    }
                                  }   
                                  else
                                    {
                                     f<<rlc[i].n<<fixed<<" "<<0.000<<" "<<"0.000"<<endl;
                                      }      
                             
                            
                               
                              }
    f<<endl<<"CURRENTS"<<endl;                            
             for (  int i=0;i<rlc.size() ;i++)
             {
                 if(rlc[i].n.at(0)!='V' && rlc[i].n.at(0)!='I' )
                                {    complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                      complex<double> imp;
                                      imp.real(0);
                                       imp.imag(0);
                                      if(rlc[i].n.at(0)=='R')
                                       imp.real(rlc[i].amplitude);
                                      if(rlc[i].n.at(0)=='C')
                                       imp.imag(-1/(rlc[i].amplitude*w));
                                      if(rlc[i].n.at(0)=='L')
                                       imp.imag(rlc[i].amplitude*w);                                                                                   
                                    if(rlc[i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs((mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))/imp)<<" "<<arg((mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))/imp)*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs((aa-mm(rlc[i].net2-1,0))/imp)<<" "<<arg((aa-mm(rlc[i].net2-1,0))/imp)*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs((mm(rlc[i].net1-1,0)-aa)/imp)<<" "<<arg((mm(rlc[i].net1-1,0)-aa)/imp)*57.2957795131<<endl;
                                    
                                    
                                 }
                                else if(freq2[l]==rlc[i].angle)  
                                 { 
                                     if(rlc[i].n.at(0)=='V')    
                                     {
                                          f<<rlc[i].n<<" "<<fixed<<"0.0"<<" "<<"0.0"<<endl;
                                     }
                                     else
                                        f<<rlc[i].n<<" "<<fixed<<rlc[i].amplitude<<" "<<0.0<<endl;
                                 }
                                else
                                     f<<rlc[i].n<<fixed<<" "<<0.000<<" "<<"0.000"<<endl;
                                                                                                        
             
             }


}
void freqcol()
{
    for(int i=0;i<yu2.size();i++)
         {  int tttt=0;
           for(int j=0;j<curf;j++)
                if(freq2[j]==yu2[i].angle)
                    {angar2[j].push_back(yu2[i]);
                       tttt=1;
                    }        
             if(tttt==0)
             {                    
             freq2[curf]=yu2[i].angle;
             freq2s[curf++]=yu2[i].freq;             
             angar2[curf-1].push_back(yu2[i]);                                    
             }
         }
}
void currentnf()
{
      for(int i=0;i<nodes;i++)
            for(int j=0;j<nodes+1;j++)
                 {
                     int ll=0;
                          for (it=my2[i].vector1[j].begin();it!=my2[i].vector1[j].end();it++)
                                {  
                                   int flag=1;
                                    for(int k=0;k<nofreq;k++)
                                      {
                                             if(freq[k]==my2[i].vector1[j][ll].angle) 
                                               flag=0;              
                                      }
                                   if(flag==1) 
                                         yu2.push_back(my2[i].vector1[j][ll]);  
                                       ll++;
                               
                                }
    
                }     
          freqcol();      


}
void vfunc(int l)
{          
     for(int  i=0;i<yu1.size();i++)
        {   if(angar[l][0].angle==yu1[i].angle)
            rhs(nodes+i,0)= yu1[i].amplitude;      
        }            
}
void ifunc(int  l,int tr)
{   
   double angle;
   if(tr==0)
     angle=angar[l][0].angle;
   else
      angle=angar2[l][0].angle;
      
   for(int i=0;i<nodes;i++)
        for(int j=0;j<nodes+1;j++)
             {
                  int ll=0;
                     for (it=my2[i].vector1[j].begin();it!=my2[i].vector1[j].end();it++)
                              {   
                                   
                                   if(my2[i].vector1[j][ll].angle==angle)
                                          {   
                                               int net1=my2[i].vector1[j][ll].net1;
                                               int net2=my2[i].vector1[j][ll].net2;
                                               if(net1!=0)
                                                    {
                                                    
                                                   rhs(net1-1,0)+= my2[i].vector1[j][ll].amplitude; 
                                                    }
                                                if(net2!=0)
                                                    {    
                                                      rhs(net2-1,0)-= my2[i].vector1[j][ll].amplitude;
                                                    }               
                                          }            
                            ll++; } 
              }
}
void filepaster(int l)
{ f.precision(3);
  double w=freq[l]*6.28318530718;
  MatrixXcd mm= lhs.colPivHouseholderQr().solve(rhs);
  f<<endl<<"FREQ"<<"="<<freqs[l]<<endl<<endl<<"VOLTAGES"<<endl;
                     for (  int i=0;i<rlc.size() ;i++)
                              {
                                if(rlc[i].n.at(0)!='V' && rlc[i].n.at(0)!='I' )
                                {    complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                    if(rlc[i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))<<" "<<arg(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(aa-mm(rlc[i].net2-1,0))<<" "<<arg(aa-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-aa)<<" "<<arg(mm(rlc[i].net1-1,0)-aa)*57.2957795131<<endl;
                                    
                                    
                                 }else if(freq[l]==rlc[i].angle)   
                                    
                                       {
                                 if(rlc[i].n.at(0)!='V')
                                     {
                                       complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                    if(rlc[i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))<<" "<<arg(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(aa-mm(rlc[i].net2-1,0))<<" "<<arg(aa-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-aa)<<" "<<arg(mm(rlc[i].net1-1,0)-aa)*57.2957795131<<endl;
                                     
                                     
                                     }
                                 else
                                   {   
                                       complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                    if(rlc [i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))<<" "<<arg(mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(aa-mm(rlc[i].net2-1,0))<<" "<<arg(aa-mm(rlc[i].net2-1,0))*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs(mm(rlc[i].net1-1,0)-aa)<<" "<<arg(mm(rlc[i].net1-1,0)-aa)*57.2957795131<<endl;
                                        }
                                  }   
                                  else
                                     f<<rlc[i].n<<fixed<<" "<<0.000<<" "<<"0.000"<<endl;
                                             
                             
                            
                               
                              }
    f<<endl<<"CURRENTS"<<endl;                            
             for (  int i=0;i<rlc.size() ;i++)
             {
                 if(rlc[i].n.at(0)!='V' && rlc[i].n.at(0)!='I' )
                                {    complex<double> aa;
                                     aa.real(0);
                                     aa.imag(0); 
                                      complex<double> imp;
                                      imp.real(0);
                                       imp.imag(0);
                                      if(rlc[i].n.at(0)=='R')
                                       imp.real(rlc[i].amplitude);
                                      if(rlc[i].n.at(0)=='C')
                                       imp.imag(-1/(rlc[i].amplitude*w));
                                      if(rlc[i].n.at(0)=='L')
                                       imp.imag(rlc[i].amplitude*w);                                                                                   
                                    if(rlc[i].net1!=0 && rlc[i].net2!=0)
                                    f<<rlc[i].n<<" "<<fixed<<abs((mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))/imp)<<" "<<arg((mm(rlc[i].net1-1,0)-mm(rlc[i].net2-1,0))/imp)*57.2957795131<<endl;
                                   else if(rlc[i].net1==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs((aa-mm(rlc[i].net2-1,0))/imp)<<" "<<arg((aa-mm(rlc[i].net2-1,0))/imp)*57.2957795131<<endl;
                                    else if(rlc[i].net2==0)
                                    f<<rlc[i].n<<" "<<fixed<<abs((mm(rlc[i].net1-1,0)-aa)/imp)<<" "<<arg((mm(rlc[i].net1-1,0)-aa)/imp)*57.2957795131<<endl;
                                    
                                    
                                 }
                                else if(freq[l]==rlc[i].angle)  
                                 { 
                                     if(rlc[i].n.at(0)=='V')    
                                     {
                                          f<<rlc[i].n<<" "<<fixed<<abs(mm(nodes+(tt),0))<<" "<<arg(-mm(nodes+(tt),0))*57.2957795131<<endl;
                                     }
                                     else
                                        f<<rlc[i].n<<" "<<fixed<<rlc[i].amplitude <<" "<<0.0<<endl;
                                 }
                                else
                                     f<<rlc[i].n<<fixed<<" "<<0.000<<" "<<"0.000"<<endl;
                                                                                                        
             
             }
                              
             }

void rightside(int l)
{   rhs.resize(nodes+yu1.size(),1);
     rhs.setZero(nodes+yu1.size(),1);
    ifunc(l,0);
    vfunc(l);
    filepaster(l);
}
void cm()
{  
   MatrixXcd mn=b.transpose();
   MatrixXcd h(mn.rows(),mn.rows());
   h.setZero(mn.rows(),mn.rows());
   c.resize(mn.rows(),mn.cols()+mn.rows());
   c<<mn , h ;
   
} 
void restmatrix(int rl,int tr)
{           
      b.resize(nodes,yu1.size());
      b.setZero(nodes,yu1.size());  
       for(int i =0;i<yu1.size();i++)           
         {
            int net1= yu1[i].net1 ; 
            int net2= yu1[i].net2 ;
            if(net1==0)
                 b(net2-1,i)=-1;
           else 
            {
                 b(net1-1,i)=1;
              if(net2!=0)
                 b(net2-1,i)=-1; 
            }            
           
        }
        cm();
      lhs.resize(nodes,nodes+yu1.size());
      lhs<<m, b;

      MatrixXcd temp=lhs;
      lhs.resize(nodes+yu1.size(),nodes+yu1.size());
      lhs<<temp,
               c;
       if(tr==0)                   
      rightside(rl);
      else
         onlyc(rl);
                
} 
void matrixmaker()
{
           
    for(int i=0;i<yu1.size();i++)
         {  int ytt=0;
           for(int j=0;j<nofreq;j++)
                if(freq[j]==yu1[i].angle)
                   { angar[j].push_back(yu1[i]);
                    ytt=1;}
            if(ytt==0)                        
             {freq[nofreq]=yu1[i].angle;
             freqs[nofreq++]=yu1[i].freq;             
             angar[nofreq-1].push_back(yu1[i]);                                    
         }}
   

}   
void matrixb(int ddl,int tr)
{   m.setZero(nodes,nodes);
    tt=0;
   double w;
    if(tr==0)
     w=freq[ddl]*6.28318530718 ;
   else
    w=freq2[ddl]*6.28318530718 ;
 //It is same for all
    for (int i = 1; i <=nodes ; ++i)
    {
               for(int b=0;b<nodes;b++)
                for(int bb=b+1;bb<nodes+1;bb++)
                         {  int l=0;
                           
                              if(b==i || bb==i)
                              {    
                               for (it=my1[b].vector1[bb].begin();it!=my1[b].vector1[bb].end();it++)
                                 {      
                                       if(my1[b].vector1[bb][l].n.at(0)=='C' )
                                              {  
                                                double val= my1[b].vector1[bb][l].amplitude;
                                                 a.real(0);
                                                 a.imag(1*w*val);
                                                 m(i-1,i-1)+=a;
                                                 
                                              }
                                     else if( my1[b].vector1[bb][l].n.at(0)=='L' )
                                                { a.real(0);
                                
                                              double val= my1[b].vector1[bb][l].amplitude;
                                                 a.imag(-1/(w*val));
                                                 m(i-1,i-1)+=a;
                                              }   
                                     else
                                       { 
                                        double val= my1[b].vector1[bb][l].amplitude;  
                                         a.real(1/val);
                                          a.imag(0);
                                       
                                         m(i-1,i-1)+=a;
                              
                                        }
                                                                             
                              l++;  }
                         }
                      
                                                                   
                                    
                 }    
        for (int j = i+1; j <= nodes; ++j)
        {   
                   int  l=0;
                               for (it=my1[i].vector1[j].begin();it!=my1[i].vector1[j].end();it++)
                                 {    
                                      if(my1[i].vector1[j][l].n.at(0)=='C' )
                                              {double val= my1[i].vector1[j][l].amplitude;
                                                 a.real(0);
                                                
                                                 a.imag(-1*w*val);
                                                 m(i-1,j-1)+=a;
                                              }
                                     else if( my1[i].vector1[j][l].n.at(0)=='L' )
                                                { a.real(0);
                                                double val= my1[i].vector1[j][l].amplitude;
                                                 a.imag(1*1/(w*val));
                                                 m(i-1,j-1)+=a;
                                              }   
                                     else
                                       {  
                                          double val= my1[i].vector1[j][l].amplitude;
                                                                                   
                                          a.real(-1*1/val);
                                          a.imag(0);
                                         m(i-1,j-1)+=a;
                                       
                                        }
                                        
               l++;
           }
           m(j-1,i-1)=m(i-1,j-1);
                 
       }  
   }
   if(tr==0)
       restmatrix(ddl,0);
   else 
        restmatrix(ddl,1);
      
    
} 
double value(string s)
{  
  string temp="";
   int  i;
   for( i=0;i<s.size();i++)
    {    
         if(isalpha(s.at(i)))
             break;
         else
            temp+=s.at(i);   
    }
    double val=stod(temp);
    if(i==s.size())
        return val;
     else  if(s.at(i)=='K')
       { 
       return val*1000;
       }   
    else if(s.at(i)=='N')
        return val*0.000000001;
   else if(s.at(i)=='U')
        return val*0.000001;
    else if(s.at(i)=='m')
        return val*0.001;
    else if(s.at(i)=='M')
        return val*1000000;  
    else
     return val;                          
}
int main() {
  //  init();
    int max=0;
    ifstream file;
    file.open("in.txt.dup");
    int count=0;
    string string1[1000];
    while (getline(file,string1[count++]))
    {
        //do nothing
    }

    for (int i = 0; i <count-1 ; ++i) {
        int words=0;
        string string2[10];
        char str[string1[i].length()];
        strcpy(str,string1[i].c_str());
        char *pch;
        pch = strtok (str," ,-\t()");
        while (pch != NULL)
        {
            string string3(pch);
            string2[words++]=string3;
            pch = strtok (NULL, " ,-\t()");
        }
        int net1=stoi(string2[1]);
        int net2=stoi(string2[2]);       
        if(string2[0].at(0)=='R' || string2[0].at(0)=='C' || string2[0].at(0)=='L')      
        {     
               st s;
              s.net1=net1;
              s.net2=net2;
              s.n=string2[0];
              s.angle=0; 
              s.freq="0";
              s.amplitude=value(string2[3]);
              rlc.push_back(s);               
              if(net1>net2)
              { 
                   net1=net1+net2;
                   net2=net1-net2;
                   net1=net1-net2;
              }
              
                s.net1=net1;
                s.net2=net2;                  
              my1[net1].vector1[net2].push_back(s); 
        }
        else  if(string2[0].at(0)=='V')
        {         
            st s;
            s.net1=net1;
            s.net2=net2;
            s.n=string2[0];
            s.freq= string2[6];
            s.amplitude=stod(string2[5]);
            s.angle=value(string2[6]);  
             rlc.push_back(s)      ;
             
            yu1.push_back(s);
            
       }
       else
       {
            st s;
            s.net1=net1;
            s.net2=net2;
            s.n=string2[0];
            s.freq= string2[6];
            s.amplitude=stod(string2[5]);
            s.angle=value(string2[6]);           
           
             rlc.push_back(s) ;
             
             if(net1>net2)
              { 
                net1=net1+net2;
                 net2=net1-net2;
                 net1=net1-net2;
              }
            my2[net1].vector1[net2].push_back(s);                          
       }  
       
      if(max<net1)
           max=net1;         
      if(max<net2)
              max=net2;
      
    }  
   file.close();

    f.open("results.txt",ios::out);
    nodes=max; 
    matrixmaker();    
    currentnf();  
        for(int f=0;f<nofreq;f++)
  {  
     matrixb(f,0);  
  }
   for(int f=0;f<curf;f++)
  {  
     matrixb(f,1);  
     
  }   
  
    return 0;
}
