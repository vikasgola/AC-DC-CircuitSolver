#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<map>
#include"duplicater.h"
using namespace std;

fstream input;
fstream output;
string edge[1000][1000];
int total_nets = 1,drawed=0;
vector <int> nets_position;
map <string, string> values;
int start = 50;
// resistor 5
// inductor 8


void start_svg()
{
	//out<<  "<svg width=\"1000\" height=\"1000\" viewBox=\"-1.25 -1.25 10 10\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" onload=\"init(evt)\">\n";
	output<<  "<style>\n";
	output<<  "\t.button{\n";
	output<<  "\t    fill:           \t#225EA8;\n";
	output<<  "\t\tstroke:   \t\t\t#0C2C84;\n";
	output<<  "\t\tstroke-miterlimit:\t6;\n";
	output<<  "\t\tstroke-linecap:\t\tround;\n";
	output<<  "\t}\n";
	output<<  "\t.button:hover{\n";
	output<<  "\t\tstroke-width:   \t2;\n";
	output<<  "\t}\n";
	output<<  "\t.plus-minus{\n";
	output<<  "\t\tfill:\t#fff;\n";
	output<<  "\t\tpointer-events: none;\n";
	output<<  "\t}\n";
	output<<  "</style>\n";
	output<<  "\n";
	output<<  "<script type=\"text/ecmascript\">\n";
	output<<  "<![CDATA[\n";
	output<<  "\tvar transMatrix = [1,0,0,1,0,0];\n";
	output<<  "    \n";
	output<<  "    function init(evt)\n";
	output<<  "    {\n";
	output<<  "        if ( window.svgDocument == null )\n";
	output<<  "        {\n";
	output<<  "            svgDoc = evt.target.ownerDocument;\n";
	output<<  "\n";
	output<<  "        }\n";
	output<<  "        mapMatrix = svgDoc.getElementById(\"map-matrix\");\n";
	output<<  "        width  = evt.target.getAttributeNS(null, \"width\");\n";
	output<<  "        height = evt.target.getAttributeNS(null, \"height\");\n";
	output<<  "    }\n";
	output<<  "    \n";
	output<<  "    function pan(dx, dy)\n";
	output<<  "    {\n";
	output<<  "    \t\n";
	output<<  "\t\ttransMatrix[4] += dx;\n";
	output<<  "\t\ttransMatrix[5] += dy;\n";
	output<<  "        \n";
	output<<  "\t\tnewMatrix = \"matrix(\" +  transMatrix.join(' ') + \")\";\n";
	output<<  "\t\tmapMatrix.setAttributeNS(null, \"transform\", newMatrix);\n";
	output<<  "    }\n";
	output<<  "    \n";
	output<<  "\tfunction zoom(scale)\n";
	output<<  "\t{\n";
	output<<  "\t\tfor (var i=0; i<transMatrix.length; i++)\n";
	output<<  "\t\t{\n";
	output<<  "\t\t\ttransMatrix[i] *= scale;\n";
	output<<  "\t\t}\n";
	output<<  "\t\t//transMatrix[4] += (1-scale)*width/2;\n";
	output<<  "\t\t//transMatrix[5] += (1-scale)*height/2;\n";
	output<<  "\t        \n";
	output<<  "\t\tnewMatrix = \"matrix(\" +  transMatrix.join(' ') + \")\";\n";
	output<<  "\t\tmapMatrix.setAttributeNS(null, \"transform\", newMatrix);\n";
	output<<  "    }\n";
	output<<  "]]>\n";
	output<<  "</script>\n";
	output<<  "<g id=\"map-matrix\" transform=\"matrix(1 0 0 1 0 0)\">\n";
	output<< " <g transform = \"translate(0,0) scale(0.011)\"> ";
}

	
void end_svg()
{
	output<< "</g>\n";
	output<< "</g>\n";
	output<< "\n";
	output<< "<g transform=\"matrix(0.01 0 0 0.01 -1 -1) translate(0,-280) scale(2)\">\n";
	output<< "<circle cx=\"50\" cy=\"50\" r=\"42\" fill=\"white\" opacity=\"0.75\"/>\n";
	output<< "<path class=\"button\" onclick=\"pan( 0, 0.3)\" d=\"M50 10 l12   20 a40, 70 0 0,0 -24,  0z\" />\n";
	output<< "<path class=\"button\" onclick=\"pan( 0.3, 0)\" d=\"M10 50 l20  -12 a70, 40 0 0,0   0, 24z\" />\n";
	output<< "<path class=\"button\" onclick=\"pan( 0,-0.3)\" d=\"M50 90 l12  -20 a40, 70 0 0,1 -24,  0z\" />\n";
	output<< "<path class=\"button\" onclick=\"pan(-0.3, 0)\" d=\"M90 50 l-20 -12 a70, 40 0 0,1   0, 24z\" />\n";
	output<< "  \n";
	output<< "<circle class=\"compass\" cx=\"50\" cy=\"50\" r=\"20\"/>\n";
	output<< "<circle class=\"button\"  cx=\"50\" cy=\"41\" r=\"8\" onclick=\"zoom(0.95)\"/>\n";
	output<< "<circle class=\"button\"  cx=\"50\" cy=\"59\" r=\"8\" onclick=\"zoom(1.05)\"/>\n";
	output<< "\n";
	output<< "<rect class=\"plus-minus\" x=\"46\" y=\"39.5\" width=\"8\" height=\"3\"/>\n";
	output<< "<rect class=\"plus-minus\" x=\"46\" y=\"57.5\" width=\"8\" height=\"3\"/>\n";
	output<< "<rect class=\"plus-minus\" x=\"48.5\" y=\"55\" width=\"3\" height=\"8\"/>\n";
	output<< "</g>\n";
	output<<  "</svg>\n";
}


void draw_resistor(int x,int y){
    x = x*10;
    y = y*10;

    output<<endl<<"<!-- resistor -->"<<endl;
    output<<"<line x1=\""<<x<<"\" y1=\""<<y<<"\" x2=\""<<x + 5<<"\" y2=\""<<y<<"\" style=\"stroke:rgb(0,0,0);stroke-width:1\"/>"<<endl<< "\
    <line x1=\""<<x + 5<<"\" y1=\""<<y<<"\" x2=\""<<x+10<<"\" y2=\""<<y+10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+10<<"\" y1=\""<<y+10<<"\" x2=\""<<x+15<<"\" y2=\""<<y-10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+15<<"\" y1=\""<<y-10<<"\" x2=\""<<x+20<<"\" y2=\""<<y+10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+20<<"\" y1=\""<<y+10<<"\" x2=\""<<x+25<<"\" y2=\""<<y-10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+25<<"\" y1=\""<<y-10<<"\" x2=\""<<x+30<<"\" y2=\""<<y+10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+30<<"\" y1=\""<<y+10<<"\" x2=\""<<x+35<<"\" y2=\""<<y-10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+35<<"\" y1=\""<<y-10<<"\" x2=\""<<x+40<<"\" y2=\""<<y+10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+40<<"\" y1=\""<<y+10<<"\" x2=\""<<x+45<<"\" y2=\""<<y-10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+45<<"\" y1=\""<<y-10<<"\" x2=\""<<x+50<<"\" y2=\""<<y<<"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>"<<endl<< " \
    <line x1=\""<<x+50<<"\" y1=\""<<y<<"\" x2=\""<<x +55<<"\" y2=\""<<y<<"\" style=\"stroke:rgb(0,0,0);stroke-width:1\"/>"<<endl;
    output<<"<!-- resistor finished -->"<<endl;
    
}

void draw_inductor(int x,int y)
{
    output<<endl;    
    output<<"<!-- inductor -->"<<endl;
    x=x*10;
    y=y*10;
    
    string s="<line x1=\""+ to_string(x)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+5)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
    s+="<path d=\"M "+to_string(x+5)+" "+to_string(y)+" q 5 -20 10 0\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />\n    "  ;
    s+="<path d=\"M "+to_string(x+5+10)+" "+to_string(y)+" q 5 -20 10 0\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />\n    ";  
    s+="<path d=\"M "+to_string(x+5+20)+" "+to_string(y)+" q 5 -20 10 0\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />\n    ";  
    s+="<path d=\"M "+to_string(x+5+30)+" "+to_string(y)+" q 8 -20 10 0\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />\n    ";
    s+= "<line x1=\""+to_string(x+5+40)+"\" y1=\""+to_string(y)+"\" x2=\""+to_string(x+5+45)+"\" y2=\""+to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\"/>     ";
    output<<s;
    output<<"<!-- inductor finished -->"<<endl;
    
}

void draw_capacitor(int x,int y){
    output<<endl;    
    output<<"<!-- capacitor -->"<<endl;
    y=y*10;
    x=x*10;

    string s="<line x1=\""+ to_string(x)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+18)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
    s+="<line x1=\""+ to_string(x+18)+"\" y1=\""+to_string(y-10)+"\" x2=\"" +to_string(x+18)+"\" y2=\"" +to_string(y+10)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
    s+="<line x1=\""+ to_string(x+30)+"\" y1=\""+to_string(y-10)+"\" x2=\"" +to_string(x+30)+"\" y2=\"" +to_string(y+10)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
    s+="<line x1=\""+ to_string(x+30)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+50)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
    output<<s;
    output<<"<!-- capcitor finished -->"<<endl;    

}

void draw_current(int x,int y)
{
   x=x*10;
   y=y*10;

   string s="<circle cx=\""+to_string(x+25)+"\" cy=\""+to_string(y)+ "\" r=\"20\" stroke=\"black\" stroke-width=\"2\" fill=\"white\" />\n";
    s+="<line x1=\""+ to_string(x+12)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+35)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
    s+="<path d=\"M "+to_string(x+35)+" "+to_string(y-5)+" L"+to_string(x+35)+" "+to_string(y+5)+ " L"+to_string(x+40)+" "+to_string(y) +" Z \"/> \n" ;
   s+="<line x1=\""+ to_string(x)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+5)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
   s+="<line x1=\""+ to_string(x+45)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+50)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
   output<<s;
}

void draw_voltage(int x,int y)
{
   x=x*10;
   y=y*10;

   string s="<circle cx=\""+to_string(x+25)+"\" cy=\""+to_string(y)+ "\" r=\"20\" stroke=\"black\" stroke-width=\"2\" fill=\"white\" />\n";   
   s+="<path d=\"M "+to_string(x+9)+" "+to_string(y)+" q 8 -20 16 0\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />\n    "  ;
   s+="<path d=\"M "+to_string(x+25)+" "+to_string(y)+" q 8 20 16 0\" stroke=\"black\" stroke-width=\"2\" fill=\"none\" />\n    "  ;
   s+="<line x1=\""+ to_string(x)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+5)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
   s+="<line x1=\""+ to_string(x+45)+"\" y1=\""+to_string(y)+"\" x2=\"" +to_string(x+50)+"\" y2=\"" +to_string(y)+"\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n    ";
   output<<s;
}

void draw_line(int x1,int y1,int x2,int y2){
    output<<endl;    
    output<<"<!-- line start-->"<<endl;
    output<<"<line x1=\""<<x1*10<<"\" y1=\""<<y1*10<<"\" x2=\""<<x2*10<<"\" y2=\""<<y2*10<<"\" style=\"stroke:rgb(0,0,0);stroke-width:1\"/>"<<endl;
    output<<"<!-- line finished-->"<<endl;
}

void draw_text(int x, int y,string text){
    output<<"<text x=\""<<x*10 - 20<<"\" y=\""<<y*10 + 30<<"\" >"<<text<<"</text>"<<endl;
}

void draw_ground(int x,int y){
    output<<endl;
    output<<"<!-- ground start -->"<<endl;
    draw_line(x-3,y,x+3,y);
    draw_line(x-2,y+1,x+2,y+1);
    draw_line(x-1,y+2,x+1,y+2);
    output<<"<!-- ground finished -->"<<endl;
}

void draw_circle(int cx,int cy,int r){
    output<<"<circle cx=\""<<cx*10<<"\" cy=\""<<cy*10<<"\" r=\""<<r<<"\" fill=\"black\" />"<<endl;
}

void draw_element(int n1,int n2,char e,string name){

    int tyd = drawed*3 + 30,tyu = -drawed*6 + start;
    draw_line(nets_position[n2],start,nets_position[n2],tyu);
    draw_line(nets_position[n1],start,nets_position[n1],tyu);


        if(n1>n2){  
            draw_line(nets_position[n2],tyu,nets_position[n2]+15,tyu);
            if(e == 'R'){
                draw_resistor(nets_position[n2]+15,tyu);        
                draw_text(nets_position[n2]+15,tyu,name + " "+ values.at(name));
            }else if(e == 'L'){
                draw_inductor(nets_position[n2]+15,tyu);    
                draw_text(nets_position[n2]+15,tyu,name+ " "+ values.at(name));                    
            }else if(e == 'C'){
                draw_capacitor(nets_position[n2]+15,tyu);      
                draw_text(nets_position[n2]+15,tyu,name+ " "+ values.at(name));                  
            }else if(e == 'I'){
                draw_current(nets_position[n2]+15,tyu);        
                draw_text(nets_position[n2]+13,tyu,name+ " "+ values.at(name));                
            }else if(e == 'V'){
                draw_voltage(nets_position[n2]+15,tyu);        
                draw_text(nets_position[n2]+13,tyu,name+ " "+ values.at(name));                
            }

            draw_line(nets_position[n2]+20,tyu,nets_position[n1],tyu);
        }else {
            draw_line(nets_position[n1],tyu,nets_position[n1]+15,tyu);
            if(e == 'L'){
                draw_inductor(nets_position[n1]+15,tyu);
                draw_text(nets_position[n1]+15,tyu,name+ " "+ values.at(name));                                    
            }else if(e == 'R'){
                draw_resistor(nets_position[n1]+15,tyu);
                draw_text(nets_position[n1]+15,tyu,name+ " "+ values.at(name));                
            }else if(e == 'V'){
                draw_voltage(nets_position[n1]+15,tyu);
                draw_text(nets_position[n1]+13,tyu,name+ " "+ values.at(name));                                
            }else if(e == 'I'){
                draw_current(nets_position[n1]+15,tyu);
                draw_text(nets_position[n1]+13,tyu,name+ " "+ values.at(name));                                
            }else if(e == 'C'){
                draw_capacitor(nets_position[n1]+15,tyu);
                draw_text(nets_position[n1]+15,tyu,name+ " "+ values.at(name));                                  
            }
            draw_line(nets_position[n1]+20,tyu,nets_position[n2],tyu);
        }

        drawed++;
}

void draw_start(int x,int y){
    draw_line(x,y,x,y+5);
    draw_line(x,y,x+6,y);
    draw_ground(x,y+5);
    output<<"<text x=\""<<550 - 20<<"\" y=\""<<(start+5)*10 + 30<<"\" font-size = \"32px \" font-weight=\"bold\" >"<<"AC_Circuit_Solver"<<"</text>"<<endl;
    
    output<<"<text transform=\"scale(1.7)\" x=\""<<20*10 - 100<<"\" y=\""<<-100 <<"\" >"<<"Developed by:"<<"</text>"<<endl;
        output<<"<text transform=\"scale(2)\" x=\""<<24*10 - 100<<"\" y=\""<<-70<<"\" >"<<"Vikas Gola, Deepak Rai"<<"</text>"<<endl;
    
}

int validator(string a){  
    regex b("^(( )|\t)*(R)[0-9]+(( )|\t)+(NET)[0-9]+(( )|\t)+((((NET)[1-9])[0-9]*)|0)(( )|\t)+[0-9]+((\\.[0-9]+)?([KUNMm]?))\\s*"); 
    if ( regex_match(a, b) )
        return 1;
    regex c("^(( )|\t)*(C)[0-9]+(( )|\t)+(NET)[0-9]+(( )|\t)+((((NET)[1-9])[0-9]*)|0)(( )|\t)+[0-9]+((\\.[0-9]+)?(([UNKMm]?)[F]))\\s*");     
    if(regex_match(a,c))
       return 2;
    regex d("^(( )|\t)*(L)[0-9]+(( )|\t)+(NET)[0-9]+(( )|\t)+((((NET)[1-9])[0-9]*)|0)(( )|\t)+[0-9]+((\\.[0-9]+)?(([UNKMm]?)[H]))\\s*");  
    if(regex_match(a,d))
      return 3;
    regex e("^(( )|\t)*(V)[0-9]+(( )|\t)+(NET)[0-9]+(( )|\t)+((((NET)[1-9])[0-9]*)|0)(( )|\t)+((SIN)|(COS))\\((( )|\t)*[0-9]+(\\.[0-9]+)?[((( )|\t)+[0-9]+(\\.[0-9]+)?(( )|\t)+[0-9]+(\\.[0-9]+)?(Khz)(( )|\t)+[0-9]+(\\.[0-9]+)?(( )|\t)+[0-9]+(\\.[0-9]+)?(( )|\t)*\\)\\s*");  
     if(regex_match(a,e))
      return 4;         
   regex f("^(( )|\t)*(I)[0-9]+(( )|\t)+(NET)[0-9]+(( )|\t)+((((NET)[1-9])[0-9]*)|0)(( )|\t)+((SIN)|(COS))\\((( )|\t)*[0-9]+(\\.[0-9]+)?(( )|\t)+[0-9]+(\\.[0-9]+)?(( )|\t)+[0-9]+(\\.[0-9]+)?(Khz)(( )|\t)+[0-9]+(\\.[0-9]+)?(( )|\t)+[0-9]+(\\.[0-9]+)?(( )|\t)*\\)\\s*");  
     if(regex_match(a,f))
      return 5;         
}

int main(){

	string in;
	
	in="in.txt";

    input.open(in,ios::in);
    output.open(in + ".svg" ,ios::out);

    for(int i =0;i <10;i++)
    for(int j =0;j <10;j++)
        edge[i][j] = "-";


    int t=0;
    string line;

    while(getline(input,line)){
        t++;    
            
        char * pch;
        char str[line.length()];  
        strcpy(str, line.c_str());   
        pch = strtok (str," ()");

        string s[10];
        int words=0;

        while (pch != NULL){
            string sls(pch);
            s[words++]=sls;
            pch = strtok (NULL, " ()");
        }

        if( s[1] =="0" || s[2] =="0"){
            cout<<"Please replace 0 with Net0"<<endl;
            exit(0);
        }

        if(stoi(s[1].substr(3,s[1].length()-3 )) > total_nets-1 ){
            total_nets=stoi(s[1].substr(3,s[1].length()-3 ))+1;   
        }else if(stoi(s[2].substr(3,s[2].length()-3 )) > total_nets-1 ){
            total_nets=stoi(s[2].substr(3,s[2].length()-3 ))+1;                        
        }

        if( s[0][0] != 'I' && s[0][0] != 'V'){
            values.insert(pair<string,string>(s[0],s[3]));
        }else{
            values.insert(pair<string,string>(s[0],s[3]+"( "+s[4]+" "+s[5]+ " "+s[6]+" "+s[7] +" "+s[8]+ " )"));            
        }

        if(edge[stoi(s[1].substr(3,s[1].length()-3 ))][stoi(s[2].substr(3,s[2].length()-3 ))] != "-")
            edge[stoi(s[1].substr(3,s[1].length()-3 ))][stoi(s[2].substr(3,s[2].length()-3 ))] = edge[stoi(s[1].substr(3,s[1].length()-3 ))][stoi(s[2].substr(3,s[2].length()-3 ))]+s[0];
        else
            edge[stoi(s[1].substr(3,s[1].length()-3 ))][stoi(s[2].substr(3,s[2].length()-3 ))] = s[0];
            
    }
    if(t>8)
        start = 50 + 4*(t-8);

    output<<"<svg width = \"screen.width\" height = \"screen.height\" style = \"border: 2px solid black;margin:10px\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"-1.25 -0.25 25 5\" version=\"1.1\" onload=\"init(evt)\" >"<<endl;

	start_svg();

    draw_start(4, start);
    // x = 10
    // each element 20 + 5

    output<<endl<<"<!-- Drawing all points  -->"<<endl;
    draw_text(10,start,"Ground");    
    for(int i = 0;i<total_nets;i++){
        nets_position.push_back(10 + i*25 );            
        draw_circle(nets_position.at(i),start,3);
        if(i!=0)
            draw_text(nets_position.at(i),start,"Net" + to_string(i) );            
    }
    output<<"<!-- Drawing all points finsihed  -->"<<endl;
    
    for(int i=0;i<total_nets;i++){
        for(int j=0;j<total_nets;j++){
            if(edge[i][j]!="-"){
                for(int k=0;k<edge[i][j].length();k+=2 ){
                        draw_element(i,j,edge[i][j][k],edge[i][j].substr(k,2));
                }
            }
        } 
    }

    cout<<total_nets<<endl;

    //output<<"</svg>";
    
    end_svg();
    
    output.close();

    duplicater("in.txt");
    
     
}
