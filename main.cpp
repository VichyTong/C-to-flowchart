#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
vector <int> data; 
enum TokenType{
	//keywords
	AUTO,
	BREAK,
	CASE,
	CHAR,
	CONST,
	CONTINUE,
	DEFALT,
	DO,
	DOUBLE,
	ELSE,
	ENUM,
	EXTERN,
	FLOAT,
	FOR,
	GOTO,
	IF,
	INT,
	LONG,
	REGISTER,
	RETURN,
	SHORT,
	SIGNED,
	SIZEOF,
	STATIC,
	STRUCT,
	SWITCH,
	TYPEDEF,
	UNION,
	UNSIGNED,
	VOID,
	VOLATILE,
	WHILE,
	//operators
	PLUS,
	MINUS,
	STAR,
	DIV,
	MOD,
	BIPLUS,
	BIMINUS,
	DO_EQL, // ==
	NOT_EQL, // !=
	GREATER, // >
	LESS, // <
	GREATER_EQL, // >=
	LESS_EQL, // <=
	LGC_AND,
	LGC_OR,
	LGC_NOT,
	AND,
	OR,
	XOR,
	LSHIFT, // <<
	RSHIFT, // >>
	ASSIGN,
	ASSIGN_PLUS,
	ASSIGN_MINUS,
	ASSIGN_STAR,
	ASSIGN_DIV,
	ASSIGN_MOD,
	// others
	COMMA,
	SEMI,
	LP, // (
	RP, // )
	LS, // [ 
	RS, // ]
	LC, // {
	RC, // }
	QUOT, // "
	NOTE, // //
	LNOTE, // /*
	RNOTE, // */
	HASH, // #
	ID, 
	SPACE,
	// io
	SCANF,
	PRINTF,
	GETCHAR,
	// number
	NUM
};

bool isnumber(char ch){
	return (ch>='0' && ch<='9');
}
bool isletter(char ch){
	return ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || ch=='_');
}
bool isoperator(char ch){
	return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='=' || ch=='!' || ch=='>' || ch=='<' || ch=='&' || ch=='|' || ch=='^' || ch==',' || ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch=='"' || ch=='/');
}
bool isend(char ch){
	return (ch=='\n' || ch==' ');
}
void trans_id_or_key(string str){
	TokenType tmp;
	if(str=="int"){
		tmp=INT;
	}
	else if(str=="for"){
		tmp=FOR;
	}
	else if(str=="return"){
		tmp=RETURN;
	}
	else{
		tmp=ID;
	}
	data.push_back(tmp);
}
void trans_num(string str){
	TokenType tmp;
	tmp=NUM;
	data.push_back(tmp);
}
void trans_opr(string str){
	TokenType tmp;
	if(str=="("){
		tmp=LP;
	}
	else if(str==")"){
		tmp=RP;
	}
	else if(str=="{"){
		tmp=LC;
	}
	else if(str=="}"){
		tmp=RC;
	}
	else if(str=="="){
		tmp=ASSIGN;
	}
	else if(str==";"){
		tmp=SEMI;
	}
	else if(str=="<"){
		tmp=LESS;
	}
	else if(str=="+"){
		tmp=PLUS;
	}
	data.push_back(tmp);
}
void scanner(){
	char ch;
	string str;
	int sta=0;
//	sta=1 first is number
//	sta=2 first is letter
//	sta=3 first is operator
	while((ch=getchar())!=EOF){
		switch (sta){
			case 0:{
				if(isnumber(ch)){
					str+=ch;
					sta=1;
				}
				else if(isletter(ch)){
					str+=ch;
					sta=2;
				}
				else if(isoperator(ch)){
					str+=ch;
					sta=3;
				}
				break;
			}
			case 1:{
				if(isend(ch)){
					trans_num(str);
					str.clear();
					sta=0;
				}
				else if(isnumber(ch)){
					str+=ch;
				}
				else if(isletter(ch)){
					trans_num(str);
					sta=2;
					str=ch;
				}
				else if(isoperator(ch)){
					trans_num(str);
					sta=3;
					str=ch;
				}
				else{
					printf("ERROR1\n");
				}
				break;
			}
			case 2:{
				if(isend(ch)){
					trans_id_or_key(str);
					str.clear();
					sta=0;
				}
				else if(isnumber(ch)){
					str+=ch;
				}
				else if(isletter(ch)){
					str+=ch;
				}
				else if(isoperator(ch)){
					trans_id_or_key(str);
					sta=3;
					str=ch;
				}
				else{
					printf("ERROR2\n");
				}
				break;
			}
			case 3:{
				if(isend(ch)){
					trans_opr(str);
					str.clear();
					sta=0;
				}
				else if(isnumber(ch)){
					trans_opr(str);
					sta=1;
					str=ch;
				}
				else if(isletter(ch)){
					trans_opr(str);
					sta=2;
					str=ch;
				}
				else if(isoperator(ch)){
					if(ch=='='){
						if(str=="="){
							TokenType tmp;
							tmp=DO_EQL;
							data.push_back(tmp);
						}
						else if(str=="!"){
							TokenType tmp;
							tmp=NOT_EQL;
							data.push_back(tmp);
						}
						else if(str==">"){
							TokenType tmp;
							tmp=GREATER_EQL;
							data.push_back(tmp);
						}
						else if(str=="<"){
							TokenType tmp;
							tmp=LESS_EQL;
							data.push_back(tmp);
						}
						else if(str=="+"){
							TokenType tmp;
							tmp=ASSIGN_PLUS;
							data.push_back(tmp);
						}
						else if(str=="-"){
							TokenType tmp;
							tmp=ASSIGN_MINUS;
							data.push_back(tmp);
						}
						else if(str=="*"){
							TokenType tmp;
							tmp=ASSIGN_STAR;
							data.push_back(tmp);
						}
						else if(str=="/"){
							TokenType tmp;
							tmp=ASSIGN_DIV;
							data.push_back(tmp);
						}
						else if(str=="%"){
							TokenType tmp;
							tmp=ASSIGN_MOD;
							data.push_back(tmp);
						}
					}
					else if(ch=='&' && str=="&"){
						TokenType tmp;
						tmp=LGC_AND;
						data.push_back(tmp);
					}
					else if(ch=='|' && str=="|"){
						TokenType tmp;
						tmp=LGC_OR;
						data.push_back(tmp);
					}
					else if(ch=='<' && str=="<"){
						TokenType tmp;
						tmp=LSHIFT;
						data.push_back(tmp);
					}
					else if(ch=='>' && str==">"){
						TokenType tmp;
						tmp=RSHIFT;
						data.push_back(tmp);
					}
					else if(ch=='+' && str=="+"){
						TokenType tmp;
						tmp=BIPLUS;
						data.push_back(tmp);
					}
					else if(ch=='-' && str=="-"){
						TokenType tmp;
						tmp=BIMINUS;
						data.push_back(tmp);
					}
					else if(ch=='*' && str=="/"){
						TokenType tmp;
						tmp=LNOTE;
						data.push_back(tmp);
					}
					else if(ch=='/' && str=="*"){
						TokenType tmp;
						tmp=RNOTE;
						data.push_back(tmp);
					}
					else if(ch=='/' && str=="/"){
						TokenType tmp;
						tmp=NOTE;
						data.push_back(tmp);
					}
					else{
						trans_opr(str);
						sta=3;
						str=ch;
					}
				}
				else{
					printf("ERROR2\n");
				}
				break;
			}
		}
	}
}


int main(){
	freopen("test.in", "r", stdin);
	scanner();
	for(int i=0; i<data.size(); i++){
		printf("%d\n", data[i]+1);
	}
	return 0;
}