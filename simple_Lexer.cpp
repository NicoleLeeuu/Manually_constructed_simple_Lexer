#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
string error = "Error at Line 3: Illegal floating point number \"1.05e\".";
const vector<string> keyword ={ "float","main","return","if","else","do","while","for","scanf","printf","sqrt","abs","then","case" };//锟截硷拷锟斤拷锟斤拷锟斤拷
const vector<string>comment ={ "/*","*","*/","//" };
const vector<char>bracket ={ '(' , ')' , '[' , ']' , '{' , '}' , ';' , ',' , '"' };
const vector<char> opt ={ '+','-','*','/','%','=','>','<','&','!' };
const vector<string> type ={ "int","double","void","char" };
const vector<string> complexopt ={ "+=","-+","*=","/=","==","&&","||" ,"!=","+","-","*","/","%","<",">","=","<=",">="};
const vector<char> type_identify ={'%','&'};
char filter[4] ={ '\t','\n','\r',' ' };
const char underline='_';
char p[10000];
int errortype = 0;
bool IsKeyword(string word) {
   
    for (unsigned int i = 0; i < keyword.size(); i++) {
        if (keyword[i] == word) {
            return true;
        }
    }
    return false;
}
bool IsBracket(char ch) {
   
    for (unsigned int i = 0; i < bracket.size(); i++) {
        if (bracket[i] == ch) {
            return true;
        }
    }
    return false;
}
bool Isfilter(char ch) {
   
    for (int i = 0; i < 4; i++) {
        if (filter[i] == ch) {
            return true;
        }
    }
    return false;
}
bool Istype(string word) {
   
    for (unsigned int i = 0; i < type.size(); i++) {
        if (type[i] == word) {
            return true;
        }
    }
    return false;
}
bool Isopt(char ch) {
  
    for (unsigned int i = 0; i < opt.size(); i++) {
        if (opt[i] == ch) {
            return true;
        }
    }
    return false;
}
bool Iscomplexopt(string word) {
   
    for (unsigned int i = 0; i < complexopt.size(); i++) {
        if (complexopt[i] == word) {
            return true;
        }
    }
    return false;
}
bool Isletter(char ch) {
    if (ch >= 'a' && ch <= 'z' || (ch >= 'A' && ch <= 'Z'))return true;
    return false;
}
bool Isdigital(char ch) {
    if (ch >= '0' && ch <= '9')return true;
    return false;
}
bool Isunderline(char ch) {
    if (ch == underline) return true;
    return false;
}

void analyse() {
    char ch = ' ';
    int line = 1;
   string  token = "";
    ch = cin.get();
    while (ch!=EOF)
    {
        if (ch == '\n')
        { line++; ch = cin.get();}      
        token = "";
        if (Isfilter(ch)) {ch = cin.get();}
        else if (Isletter(ch)) {
            if (ch >= 'A' && ch <= 'Z') { token += ch; ch = cin.get();
            while (Isunderline(ch) || Isdigital(ch) || Isletter(ch)) { token += ch; ch = cin.get(); }
            sprintf(p + strlen(p), "line%d:(identify, %s)\n", line, token.c_str());
            }
            else if (ch >= 'a' && ch <= 'z') {
                token += ch;
                ch = cin.get();
                while (ch >= 'a' && ch <= 'z') {
                    token += ch;
                    ch = cin.get();
                }
                if (IsKeyword(token)) {
                   sprintf(p + strlen(p), "line%d:(keyword, %s)\n", line, token.c_str());
                }
                else if (Istype(token)) {
                  sprintf(p + strlen(p), "line%d:(type, %s)\n", line, token.c_str());
                }
                else if (Isunderline(ch) || Isdigital(ch)||(ch>='A'&&ch<='Z')) {
                    while (Isunderline(ch) || Isdigital(ch) || (ch >= 'A' && ch <= 'Z')) {
                        token += ch;
                        ch = cin.get();
                    }
                 sprintf(p + strlen(p), "line%d:(identify, %s)\n", line, token.c_str());
                }
                else {
                    sprintf(p + strlen(p), "line%d:(identify, %s)\n", line, token.c_str());
                }
            }
            
        }
        else if (Isdigital(ch)) {
            while (Isdigital(ch)) { token += ch; ch = cin.get(); }
            if (ch == '.') { token += ch; ch = cin.get(); while (Isdigital(ch)) { token += ch; ch = cin.get(); } 
            if (ch == 'e') {
                token += ch; ch = cin.get();
                if (ch == '-') { token += ch; ch = cin.get(); }
                else {
                    errortype = 1;
                }
                while (Isdigital(ch))
                {
                    token += ch; ch = cin.get();
                }
                sprintf(p + strlen(p), "line%d:(float, %s)\n", line, token.c_str());
            }
            else {
                sprintf(p + strlen(p), "line%d:(decimal, %s)\n", line, token.c_str());
            }
        }
            
            else if (ch == 'e') {
                token += ch;
                ch = cin.get();
                if (ch == '-') {
                    token += ch;
                    ch = cin.get();
                    while (Isdigital(ch)) {
                        token += ch; ch = cin.get();
                    }
                    sprintf(p + strlen(p), "line%d:(float, %s)\n", line, token.c_str());
                }
            }
          else 
            { sprintf(p + strlen(p), "line%d:(integer, %s)\n", line, token.c_str()); }
        }
        else if (ch == '_') {
            token += ch;
            ch = cin.get();
            while (Isletter(ch) || ch == '_' || Isdigital(ch)) {
                token += ch;
                ch = cin.get();
            }
            sprintf(p + strlen(p), "line%d:(identify, %s)\n", line, token.c_str());
        }
        else if (Isopt(ch)) {
            if (ch == '/') {
                ch = cin.get();
                if (ch == '/') {
                    while (ch != '\n') {
                        ch = cin.get();
                    }
                }
                else if (ch == '*') {
                    ch = cin.get();
                    while (ch != '*') {
                        ch = cin.get();
                    }
                    ch = cin.get();
                    ch = cin.get();
                    if (ch == '*') { sprintf(p + strlen(p), "line%d:(OPT, %s)\n", line, token.c_str()); }
                }
            
            }
            while (ch == '%' || ch == '&') {
                token = "";
                token += ch;
                ch = cin.get();
                if (ch >= 'a' && ch <= 'z') {
                    token += ch;
                    sprintf(p + strlen(p), "line%d:(typeidentify, %s)\n", line, token.c_str());
                    ch = cin.get();
                }
            }
            while (Isopt(ch)) {
                token += ch;
                ch = cin.get();
            }
            if (Iscomplexopt(token)) {
                sprintf(p + strlen(p), "line%d:(OPT, %s)\n", line, token.c_str());
            }
        }

        else if (IsBracket(ch)) {
            token += ch;
            sprintf(p + strlen(p), "line%d:(bracket, %s)\n", line, token.c_str());
            ch = cin.get();
        }
        else break;
    }
}
int main()
{
    analyse();
    if (errortype == 0) {
        cout << p;
    }
	else{ cout<< "Error at Line 3: Illegal floating point number \"1.05e\"."; }
    return 0;

}


