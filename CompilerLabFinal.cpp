#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define KEYWORDS "(double|int|long|char|return|void|do|float|unsigned)"
#define IDENTIFIERS "[a-zA-Z_][a-zA-Z0-9_]*"
#define SPECIAL_CHARS "[\?|;|:\$|\||,|\!]"
#define STRINGS "\"[^\"]*\"?"
#define NUMBERS "[\\+\\-]?([1-9][0-9]*|[1-9])?\\.?[0-9]*"
#define CHARACTER_CONSTANT "'[\\\\]?.'"

bool error=false;
string input_buffer="";

void Parser(string InputString){
    map<string ,map<string,string>>m;
    //cout<<InputString<<endl;
    string NonTerms[]={"J", "S","A","C", "B","E","P", "T","Q","F", "N"};
    string Terms[]={";", "(",")","id", "=","{","}", "+","-","while", "if","||", "*","/","&&", "const","print","$"};

            m[NonTerms[0]][Terms[3]]="S;J"; m[NonTerms[0]][Terms[6]]="?"; m[NonTerms[0]][Terms[9]]="S;J";
            m[NonTerms[0]][Terms[10]]="S;J"; m[NonTerms[0]][Terms[16]]="S;J"; m[NonTerms[0]][Terms[17]]="?"; //For S'

            m[NonTerms[1]][Terms[3]]="A"; m[NonTerms[1]][Terms[9]]="C"; m[NonTerms[1]][Terms[10]]="C";
            m[NonTerms[1]][Terms[16]]="print(E)"; //For S

            m[NonTerms[2]][Terms[3]]="id=E"; //For A

            m[NonTerms[3]][Terms[9]]="whileB"; m[NonTerms[3]][Terms[10]]="ifB"; //For C

            m[NonTerms[4]][Terms[1]]="(E){J}";  //For B

            m[NonTerms[5]][Terms[1]]="TP"; m[NonTerms[5]][Terms[3]]="TP"; m[NonTerms[5]][Terms[15]]="TP"; // For E

            m[NonTerms[6]][Terms[0]]="?"; m[NonTerms[6]][Terms[2]]="?"; m[NonTerms[6]][Terms[7]]="+TP";
            m[NonTerms[6]][Terms[8]]="-TP"; m[NonTerms[6]][Terms[11]]="||TP";   //For E'

            m[NonTerms[7]][Terms[1]]="FQ"; m[NonTerms[7]][Terms[3]]="FQ"; m[NonTerms[7]][Terms[15]]="FQ";  //For T

            m[NonTerms[8]][Terms[0]]="?"; m[NonTerms[8]][Terms[2]]="?";m[NonTerms[8]][Terms[7]]="?";
            m[NonTerms[8]][Terms[8]]="?"; m[NonTerms[8]][Terms[11]]="?"; m[NonTerms[8]][Terms[12]]="*FQ";
            m[NonTerms[8]][Terms[13]]="/FQ"; m[NonTerms[8]][Terms[14]]="&&FQ"; //For T'

            m[NonTerms[9]][Terms[1]]="(E)"; m[NonTerms[9]][Terms[3]]="N"; m[NonTerms[9]][Terms[15]]="N"; //For F

            m[NonTerms[10]][Terms[3]]="id"; m[NonTerms[10]][Terms[15]]="const";  //For N

            cout<<InputString<<endl;
            stack<char>stk;
            stk.push('$');
            stk.push('J');

            int l=InputString.length();
           // cout<<l<<endl;
            int j=0;
            string temp="";

            if(InputString[j]=='i' && InputString[j+1]=='d' ){
                        temp="id"; j+=2;
                    }
            else if(InputString[j]=='i' && InputString[j+1]=='f' ){
                        temp="if"; j+=2;
                    }
                    else if(InputString[j]=='c' && InputString[j+1]=='o' && InputString[j+2]=='n' && InputString[j+3]=='s' && InputString[j+4]=='t'){
                    temp="const"; j+=5;
                }
                else if(InputString[j]=='w' && InputString[j+1]=='h' && InputString[j+2]=='i' && InputString[j+3]=='l' && InputString[j+4]=='e'){
                    temp="while"; j+=5;
                }
                else if(InputString[j]=='p' && InputString[j+1]=='r' && InputString[j+2]=='i' && InputString[j+3]=='n' && InputString[j+4]=='t'){
                    temp="print"; j+=5;
                }
                else{
                    temp+=InputString[j]; j++;
                }



                // start parsing
           while(j<l){
                string c=""; c+=stk.top();
                int tmplnt=temp.length();

                if(stk.top()>='A' && stk.top()<='Z'){
                    //cout<<"In while stk top and temp "<<c<<" "<<temp<<endl;
                    stk.pop();
                    if(m[c][temp]==""){
                        cout<<"Parsing error for invalid syntax! "<<endl;
                        error=true;
                        return ;
                    }
                    string st=m[c][temp];
                  //cout<<"In second while map's string "<<st<<endl;
                    int lst=st.length();
                    while(lst--){
                        stk.push(st[lst]);
                    }
                }
                else if(m[c][temp]=="?"|| stk.top()=='?'){
                        // ? means epsilon
                    stk.pop(); }
                else{ //cout<<"In else Nonterminal "<<endl;
                        int flag=0;  //cout<<"In else temp skt top "<<temp<<" "<<stk.top()<<endl;
                    int lt=temp.length(); string stemp="";
                    for(int i=0;i<lt;i++){
                        if(temp[i]==stk.top()){
                            stemp+=stk.top();
                            stk.pop();
                        }
                        else
                            flag++;
                        }
                       // cout<<" In else stemp: "<<stemp<<endl;
                        if(flag){ /*stk.pop();
                            int sst=stemp.length();
                            while(sst--){
                            stk.push(stemp[sst]);
                            }*/
                            error=true;
                            cout<<"Syntax error, as expected "<<stk.top()<<endl; return ;
                        }
                        else
                        {   temp="";

                            if(InputString[j]=='i' && InputString[j+1]=='d' ){
                            temp="id"; j+=2;
                            }
                            else if(InputString[j]=='i' && InputString[j+1]=='f' ){
                            temp="if"; j+=2;
                            }
                            else if(InputString[j]=='c' && InputString[j+1]=='o' && InputString[j+2]=='n' && InputString[j+3]=='s' && InputString[j+4]=='t'){
                            temp="const"; j+=5;
                            }
                            else if(InputString[j]=='w' && InputString[j+1]=='h' && InputString[j+2]=='i' && InputString[j+3]=='l' && InputString[j+4]=='e'){
                            temp="while"; j+=5;   //changing lookahead

                            }
                            else if(InputString[j]=='p' && InputString[j+1]=='r' && InputString[j+2]=='i' && InputString[j+3]=='n' && InputString[j+4]=='t'){
                            temp="print"; j+=5;
                            }
                            else{
                            temp+=InputString[j]; j++;
                            }

                            if(temp=="$" &&  stk.top()!='J'){
                                    error=true;
                                cout<<"Parsing Error!  Error occurred as "<<stk.top()<<" expected."<<endl;
                                error=true;
                                return ;
                                break ;
                            }
                            if(stk.top()=='J' && temp=="$"){
                            stk.pop();
                            }
                        }
                }
           }

        cout<<"Final: stktop and tmp "<<stk.top()<<  temp<<endl;
        if(stk.top()=='$' && temp=="$"){
                    cout<<"Parsing Successfully"<<endl;
                    return ;
                }
        else {
                error=true;
                cout<<"Parsing Error! Error occurred as expected "<<stk.top()<<endl; return ;
            }
}

bool isSeparator(char c){
    string separator = " ;,#<>(){}[].";
    for(int i=0;i<separator.length();i++){
        if(c == separator[i])
          return true;
    }
    return false;
}

bool isSpecialCharacter(char c){
   string s_char = ";#{(})$@\".";
    for(int i=0;i<s_char.length();i++){
        if(c == s_char[i])
          return true;
    }
    return false;
}

bool isOperator(char c){
    string oparator = "+-*/<>=!&|";
    for(int i=0;i<oparator.length();i++){
        if(c == oparator[i])
          return true;
    }
    return false;
}

bool isKeyword(string s1){
    string keyWords[10]={"int","print","float","if","while","do","string","struct","const"};


    for(auto a: keyWords){
        if(a==s1)
            return true;
    }

    return false;
}
bool isIdentifier(string s1){

    bool ident = true;
    if(isKeyword(s1))
        ident = false;
    if(ident){
        if((s1[0] >= '0')&&(s1[0] <= '9'))
            ident = false;
    }
    if(ident){
            vector<char>s; for(auto a: s1){
                if(a!=' '){
                    s.push_back(a);
                }
            }
        for(int i=0;i<s.size();i++){
            if(((s[i] >= 'a')&&(s[i] <= 'z')) || ((s[i] >= 'A')&&(s[i]<='Z')) || ((s[i] >= '0')&&(s[i]<='9')) || s[i] =='_')
                continue;
            else{
                ident = false;
                break;
            }
        }
    }
    return ident;
}
bool isNumber(char s){
    bool number = true;

    if((s >= '0')&&(s <= '9') || (s =='.')){
             return number;
         }
         else{
            number = false;

         }

   /* for(int i=0;i<s.length();i++){
         if((s[0] >= '0')&&(s[0] <= '9') || (s[i] =='.') || s[i]==' '){
             continue;
         }
         else{
            number = false;
            break;
         }
    }*/
    return number;
}
bool is_Literal(string s){
    int len = s.length();
         if((s[0] == '"')&&(s[len-1] == '"'))
             return true;
         else
            return false;
}

//Token Name

stack<char>st;
void Lexer(string s, int line){

    int l=s.length(),j=0;

    for(int i=0;i<l;i++){

    if(s[i]=='{' || s[i]=='(')
        st.push(s[i]);

    else if((s[i]=='}' && st.top()=='{' && !st.empty())||(s[i]==')' && st.top()=='('&& !st.empty())){
            st.pop();}
    else if((s[i]=='}'||s[i]==')') && !st.empty()){
        cout<<"\nExpected openning bracket } "<<endl<<endl;
    }

     if(isNumber(s[i])){
                cout<<"< "<<s[i]<<" >"<<" NUMBER"<<endl;
                input_buffer+="const";
            }

        if(isSeparator(s[i])){
            string s1="";
            int k;
            if(s[0]=='#'){
                k=j+1;
            }
            else if(j==0)
                k=0;
            else{k=j+1;}
            for(k;k<i;k++){
                s1+=s[k];
            }

        if(s1!=""){
            if(isIdentifier(s1)){
                cout<<"< "<<s1<<" >"<<" IDENTIFIER"<<endl;
                input_buffer+="id";
            }

            else if(isKeyword(s1)){
               cout<<"< "<<s1<<" >"<<" KEYWORD"<<endl;
                input_buffer+=s1;
            }
            else if(isNumber('@')){
                cout<<"< "<<s1<<" >"<<" NUMBER"<<endl;
                input_buffer+="const";
            }

        }
         j=i;
        if(isSpecialCharacter(s[i])){
                cout<<"< "<<s[i]<<" >"<<" SPECIAL_CHARACTER"<<endl;
                input_buffer+=s[i];
            }
        }
        if(isOperator(s[i])){
                cout<<"< "<<s[i]<<" >"<<" OERATOR"<<endl;
                input_buffer+=s[i];
            }
    }
}
class regex_design {
public:
    regex checkFrontTab(){
        return regex("^[ /t]*");
    }
    regex checkEndTab(){
        return regex("[ /t]*$");
    }
    regex checkSingleComment(){
        return regex("[ /t]*//");
    }
    regex checkHeader(){
        return regex("#( )*include( )*(<)(stdio|conio|math|).h( )*>");
    }
    regex checkMain(){
        return regex("(int|void)( )*main( )*()( )*");
    }
    regex checkReturn() {
        return regex("return[ \t]*0[ \t]*;");
    }
    regex checkClose() {
        return regex("}");
    }

    regex checkOpen() {
        return regex("[{]");
    }
};

regex_design obj;
int main(){


    string str;
    ifstream file("samplecode.txt");
    vector<string>maincode;
    while(getline(file, str)){
        maincode.push_back(str);
    }

    vector<pair<string,int>>stringwithline;
    regex rg("^[\t]");
    smatch match;

    for(int i=0;i<maincode.size();i++){
        if(regex_search(maincode[i],match,obj.checkFrontTab()))  {
        string noSpace="";
        noSpace = match.suffix().str();
        if(regex_search(noSpace,match,obj.checkEndTab())){
            noSpace=match.prefix().str();
        }
        if(regex_search(noSpace,match,obj.checkSingleComment())){
            noSpace= match.prefix().str();
        }
        if(!noSpace.empty() ){
            stringwithline.push_back({noSpace,i+1});
        }
        }
    }

    cout<<"              Lexical Analysis:Tokenization \n\n";

    for(auto x: stringwithline){
        cout<<x.first<<endl;
        Lexer(x.first, x.second);
    }

    if(!st.empty()){
            if(st.top()=='{')
                cout<<"\nExpected bracket } "<<endl;
            else
                cout<<"\nExpected bracket ) "<<endl;
    }

    bool Headerfile=false;
    for(auto a: stringwithline){
        if(a.first[0]=='#'){
            string suffixAfterHeader="";
            if(regex_search(a.first, match, obj.checkHeader())){
                suffixAfterHeader=match.suffix().str();
                if(suffixAfterHeader.empty()){
                       Headerfile=true;
                }
                else{
                    cout<<"Header file "<<a.first<<" is not correct in line number "<<a.second<<endl;

                }
            }
            else {
                cout<<"Header file "<<a.first<<" is not correct in line number "<<a.second<<endl;

            }
        }
    }

    bool Main=false;
    int mainline;
    for(auto a:stringwithline){

        if(regex_search(a.first,match,obj.checkMain())){
            mainline=a.second;
            Main=true;
        }
    }
    if(!Main){
        //cout<<"Error in main function.. "<<endl;
    }

    bool Return=false;
    for(auto a:stringwithline){

        if(regex_search(a.first,match,obj.checkReturn())){
            Return=true;
        }
    }
    if(!Return){
       // cout<<"Error in return.. "<<endl;
    }

    input_buffer+='$';

    cout<<"\n\n                  Syntax Analysis : \n"<<endl;

    //cout<<input_buffer<<endl;

    int line =1;
    Parser(input_buffer);


        if(error==false)
            cout<<"\nBuild finished: 0 error, 0 warning"<<endl;
        else
            cout<<"Build finished: 1 error, 0 warning"<<endl;

    return 0;
}
