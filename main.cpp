#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;
vector <int> data; 
map <int, string> id_data;
map <int, string> num_data;
string a[100];
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
	NUM,
	// tmp
	RDIV
};

bool isnumber(char ch){
	return (ch>='0' && ch<='9');
}
bool isletter(char ch){
	return ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || ch=='_');
}
bool isoperator(char ch){
	return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='=' || ch=='!' || ch=='>' || ch=='<' || ch=='&' || ch=='|' || ch=='^' || ch==',' || ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch=='"' || ch=='/' || ch=='\\');
}
bool isend(char ch){
	return (ch=='\n' || ch==' ');
}
bool istype(int a){
	return (a==INT || a==CHAR || a==DOUBLE || a==FLOAT || a==LONG || a==SHORT);
}
void trans_id_or_key(string str){
	TokenType tmp;
	if(str=="auto"){
		tmp=AUTO;
	}
	else if(str=="break"){
		tmp=BREAK;
	}
	else if(str=="case"){
		tmp=CASE;
	}
	else if(str=="char"){
		tmp=CHAR;
	}
	else if(str=="const"){
		tmp=CONST;
	}
	else if(str=="continue"){
		tmp=CONTINUE;
	}
	else if(str=="defalt"){
		tmp=DEFALT;
	}
	else if(str=="do"){
		tmp=DO;
	}
	else if(str=="double"){
		tmp=DOUBLE;
	}
	else if(str=="else"){
		tmp=ELSE;
	}
	else if(str=="enum"){
		tmp=ENUM;
	}
	else if(str=="extern"){
		tmp=EXTERN;
	}
	else if(str=="float"){
		tmp=FLOAT;
	}
	else if(str=="for"){
		tmp=FOR;
	}
	else if(str=="goto"){
		tmp=GOTO;
	}
	else if(str=="if"){
		tmp=IF;
	}
	else if(str=="int"){
		tmp=INT;
	}
	else if(str=="long"){
		tmp=LONG;
	}
	else if(str=="register"){
		tmp=REGISTER;
	}
	else if(str=="return"){
		tmp=RETURN;
	}
	else if(str=="short"){
		tmp=SHORT;
	}
	else if(str=="signed"){
		tmp=SIGNED;
	}
	else if(str=="sizeof"){
		tmp=SIZEOF;
	}
	else if(str=="static"){
		tmp=STATIC;
	}
	else if(str=="struct"){
		tmp=STRUCT;
	}
	else if(str=="switch"){
		tmp=SWITCH;
	}
	else if(str=="typedef"){
		tmp=TYPEDEF;
	}
	else if(str=="union"){
		tmp=UNION;
	}
	else if(str=="unsigned"){
		tmp=UNSIGNED;
	}
	else if(str=="void"){
		tmp=VOID;
	}
	else if(str=="volatile"){
		tmp=VOLATILE;
	}
	else if(str=="while"){
		tmp=WHILE;
	}
	else{
		tmp=ID;
		id_data[data.size()+1]=str;
	}
	data.push_back(tmp);
}
void trans_num(string str){
	TokenType tmp;
	tmp=NUM;
	data.push_back(tmp);
	num_data[data.size()]=str;
}
void trans_opr(string str){
	TokenType tmp;
	if(str=="+"){
		tmp=PLUS;
	}
	else if(str=="-"){
		tmp=MINUS;
	}
	else if(str=="*"){
		tmp=STAR;
	}
	else if(str=="/"){
		tmp=DIV;
	}
	else if(str=="%"){
		tmp=MOD;
	}
	else if(str=="++"){
		tmp=BIPLUS;
	}
	else if(str=="--"){
		tmp=BIMINUS;
	}
	else if(str=="=="){
		tmp=DO_EQL;
	}
	else if(str=="!="){
		tmp=NOT_EQL;
	}
	else if(str==">"){
		tmp=GREATER;
	}
	else if(str=="<"){
		tmp=LESS;
	}
	else if(str==">="){
		tmp=GREATER_EQL;
	}
	else if(str=="<="){
		tmp=LESS_EQL;
	}
	else if(str=="&&"){
		tmp=LGC_AND;
	}
	else if(str=="||"){
		tmp=LGC_OR;
	}
	else if(str=="!"){
		tmp=LGC_NOT;
	}
	else if(str=="&"){
		tmp=AND;
	}
	else if(str=="|"){
		tmp=OR;
	}
	else if(str=="^"){
		tmp=XOR;
	}
	else if(str=="<<"){
		tmp=LSHIFT;
	}
	else if(str==">>"){
		tmp=RSHIFT;
	}
	else if(str=="="){
		tmp=ASSIGN;
	}
	else if(str=="+="){
		tmp=ASSIGN_PLUS;
	}
	else if(str=="-="){
		tmp=ASSIGN_MINUS;
	}
	else if(str=="*="){
		tmp=ASSIGN_STAR;
	}
	else if(str=="/="){
		tmp=ASSIGN_DIV;
	}
	else if(str=="%="){
		tmp=ASSIGN_MOD;
	}
	else if(str==","){
		tmp=COMMA;
	}
	else if(str==";"){
		tmp=SEMI;
	}
	else if(str=="("){
		tmp=LP;
	}
	else if(str==")"){
		tmp=RP;
	}
	else if(str=="["){
		tmp=LS;
	}
	else if(str=="]"){
		tmp=RS;
	}
	else if(str=="{"){
		tmp=LC;
	}
	else if(str=="}"){
		tmp=RC;
	}
	else if(str=="\""){
		tmp=QUOT;
	}
	else if(str=="//"){
		tmp=NOTE;
	}
	else if(str=="/*"){
		tmp=LNOTE;
	}
	else if(str=="*/"){
		tmp=RNOTE;
	}
	else if(str=="#"){
		tmp=HASH;
	}
	else if(str==" "){
		tmp=SPACE;
	}
	else if(str=="\\"){
		tmp=RDIV;
	}
	data.push_back(tmp);
}
void scanner(){
	char ch;
	string str;
	int sta=0,note=0;
//  sta=0 first is null
//	sta=1 first is number
//	sta=2 first is letter
//	sta=3 first is operator
//  note=0 not note
//  note=1 in // note
//  note=2 in /* note & NOT detected '*'
//  note=3 in /* note & detected '*'
	while((ch=getchar())!=EOF){
		if(note==1){
			if(ch=='\n'){
				note=0;
			}
			continue;
		}
		else if(note==2){
			if(ch=='*'){
				note=3;
			}
			continue;
		}
		else if(note==3){
			if(ch=='/'){
				note=0;
			}
			else{
				note=2;
			}
			continue;
		}
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
							str.clear();
							sta=0;
						}
						else if(str=="!"){
							TokenType tmp;
							tmp=NOT_EQL;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str==">"){
							TokenType tmp;
							tmp=GREATER_EQL;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str=="<"){
							TokenType tmp;
							tmp=LESS_EQL;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str=="+"){
							TokenType tmp;
							tmp=ASSIGN_PLUS;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str=="-"){
							TokenType tmp;
							tmp=ASSIGN_MINUS;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str=="*"){
							TokenType tmp;
							tmp=ASSIGN_STAR;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str=="/"){
							TokenType tmp;
							tmp=ASSIGN_DIV;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
						else if(str=="%"){
							TokenType tmp;
							tmp=ASSIGN_MOD;
							data.push_back(tmp);
							str.clear();
							sta=0;
						}
					}
					else if(ch=='&' && str=="&"){
						TokenType tmp;
						tmp=LGC_AND;
						data.push_back(tmp);
						str.clear();
						sta=0;
					}
					else if(ch=='|' && str=="|"){
						TokenType tmp;
						tmp=LGC_OR;
						data.push_back(tmp);
						str.clear();
						sta=0;
					}
					else if(ch=='<' && str=="<"){
						TokenType tmp;
						tmp=LSHIFT;
						data.push_back(tmp);
						str.clear();
						sta=0;
					}
					else if(ch=='>' && str==">"){
						TokenType tmp;
						tmp=RSHIFT;
						data.push_back(tmp);
						str.clear();
						sta=0;
					}
					else if(ch=='+' && str=="+"){
						TokenType tmp;
						tmp=BIPLUS;
						data.push_back(tmp);
						str.clear();
						sta=0;
					}
					else if(ch=='-' && str=="-"){
						TokenType tmp;
						tmp=BIMINUS;
						data.push_back(tmp);
						str.clear();
						sta=0;
					}
					else if(ch=='/' && str=="*"){
						note=2;
						str.clear();
						sta=0;
					}
					else if(ch=='/' && str=="/"){
						note=1;
						str.clear();
						sta=0;
					}
					else{
						trans_opr(str);
						sta=3;
						str=ch;
					}
				}
				else{
					printf("ERROR3\n");
				}
				break;
			}
		}
	}
}
map <int, int> link;
void match(){
	stack <int> s_p;
	stack <int> s_s;
	stack <int> s_c;
	for(int i=0; i<data.size(); i++){
		switch (data[i]){
			case LP:{
				s_p.push(i);
				break;
			}
			case RP:{
				if(!s_p.empty()){
					link[s_p.top()]=i;
					s_p.pop();
				}
				break;
			}
			case LS:{
				s_s.push(i);
				break;
			}
			case RS:{
				if(!s_s.empty()){
					link[s_s.top()]=i;
					s_s.pop();
				}
				break;
			}
			case LC:{
				s_c.push(i);
				break;
			}
			case RC:{
				if(!s_c.empty()){
					link[s_c.top()]=i;
					s_c.pop();
				}
				break;
			}
		}
	}
}
enum nodetype{
	ROOT,
	FUNCTION,
	COMMON,
	JUDGE,
	COMPLEX,
	INPUT,
	OUTPUT,
	NODETYPE_FOR,
	NODETYPE_WHILE,
	NODETYPE_IF,
	NODETYPE_ELSE
};
struct node{
	int type;
	int l,r;
	int id_index;
	vector<int> son;
};
vector <node> AST;
void addedge(int u,int v){
	AST[u].son.push_back(v);
}
int build(int l, int r){
	int now=l;
	if(data[now]==LC){
		node r_complex;
		int nl=now+1, nr=link[now]-1;
		r_complex.type=COMPLEX;
		r_complex.l=now;
		r_complex.r=nr+1;
		AST.push_back(r_complex);
		int r_index=AST.size()-1;
		while(nl<=nr){
			int body_index=build(nl, nr);
			addedge(r_index, body_index);
			nl=AST[body_index].r+1;
		}
		return r_index;
	}
	else if(data[now]==FOR){
		node r_for,pre,jud,lst;
		int Lp=now+1,Rp=link[Lp];
		int semi1=now+2,semi2=now+2;
		while(data[semi1]!=SEMI){
			semi1++;
		}
		semi2=semi1+1;
		while(data[semi2]!=SEMI){
			semi2++;
		}
		pre.type=COMMON;
		pre.l=Lp+1;
		pre.r=semi1-1;
		jud.type=JUDGE;
		jud.l=semi1+1;
		jud.r=semi2-1;
		lst.type=COMMON;
		lst.l=semi2+1;
		lst.r=Rp-1;
		r_for.type=NODETYPE_FOR;
		r_for.l=now;
		AST.push_back(r_for);
		int r_for_index=AST.size()-1;
		int body_index=build(Rp+1, r);
		AST[r_for_index].r=AST[body_index].r;
		if(Lp+1<=semi1-1){
			AST.push_back(pre);
			addedge(r_for_index, AST.size()-1);
		}
		if(semi1+1<=semi2-1){
			AST.push_back(jud);
			addedge(r_for_index, AST.size()-1);
		}
		addedge(r_for_index, body_index);
		if(semi2+1<=Rp-1){
			AST.push_back(lst);
			addedge(r_for_index, AST.size()-1);
		}
		return r_for_index;
	}
	else if(data[now]==WHILE){
		node r_while, jud;
		int Rp=link[now+1];
		jud.type=JUDGE;
		jud.l=now+2;
		jud.r=Rp-1;
		r_while.type=NODETYPE_WHILE;
		r_while.l=now;
		AST.push_back(r_while);
		int r_while_index=AST.size()-1;
		int body_index=build(Rp+1, r);
		AST[r_while_index].r=AST[body_index].r;
		if(now+1<=Rp-1){
			AST.push_back(jud);
			addedge(r_while_index, AST.size()-1);
		}
		addedge(r_while_index, body_index);
		return r_while_index;
	}
	else if(data[now]==IF){
		node r_if, jud;
		int Rp=link[now+1];
		jud.type=JUDGE;
		jud.l=now+2;
		jud.r=Rp-1;
		r_if.type=NODETYPE_IF;
		r_if.l=now;
		AST.push_back(r_if);
		int r_if_index=AST.size()-1;
		int body_index=build(Rp+1, r);
		AST[r_if_index].r=AST[body_index].r;
		if(now+1<=Rp-1){
			AST.push_back(jud);
			addedge(r_if_index, AST.size()-1);
		}
		addedge(r_if_index, body_index);
		int nxt=AST[r_if_index].r+1;
		if(data[nxt]==ELSE){
			int else_body_index=build(nxt+1, r);
			addedge(r_if_index, else_body_index);
			AST[r_if_index].r=AST[else_body_index].r;
		}
		return r_if_index;
	}
	else{
		while(data[now]!=SEMI && now<=r){
			now++;
		}
		node command;
		command.type=COMMON;
		command.l=l;
		command.r=now;
		AST.push_back(command);
		return AST.size()-1;
	}
}
void init(){
	node root;
	root.type=ROOT;
	root.l=0;
	root.r=data.size()-1;
	AST.push_back(root);
	for(int i=0; i<data.size(); i++){
		if(istype(data[i])){
			if(data[i+2]!=LP){
				int r=i+2;
				while(data[r]!=SEMI){
					r++;
				}
				int body_index=build(i, r);
				addedge(0, body_index);
				i=r;
			}
			else{
				if(data[link[i+2]+1]==SEMI){
					int body_index=build(i, link[i+2]+1);
					addedge(0, body_index);
					i=link[i+2]+1;
				}
				else{
					node fun;
					fun.type=FUNCTION;
					fun.l=i;
					AST.push_back(fun);
					int fun_index=AST.size()-1;
					addedge(0, fun_index);
					int body_index=build(link[i+2]+1, data.size()-1);
					AST[fun_index].r=AST[body_index].r;
					addedge(fun_index, body_index);
					i=AST[fun_index].r;
				}
			}
		}
		else if(data[i]==VOID){
			node fun;
			fun.type=FUNCTION;
			fun.l=i;
			AST.push_back(fun);
			int fun_index=AST.size()-1;
			addedge(0, fun_index);
			int body_index=build(link[i+2]+1, data.size()-1);
			AST[fun_index].r=AST[body_index].r;
			addedge(fun_index, body_index);
			i=AST[fun_index].r;
		}
	}
}
void dfs(int now){
	if(AST[now].son.empty()){
		printf("CNT=%d TYPE=%d L=%d R=%d\n",now, AST[now].type, AST[now].l, AST[now].r);
		return;
	}
	else{
		for(int i=0; i<AST[now].son.size(); i++){
			dfs(AST[now].son[i]);
		}
		printf("CNT=%d TYPE=%d L=%d R=%d\n",now, AST[now].type, AST[now].l, AST[now].r);
	}
}
int main(){
	freopen("test.in", "r", stdin);
	scanner();
	a[1]="AUTO";
	a[2]="BREAK";
	a[3]="CASE";
	a[4]="CHAR";
	a[5]="CONST";
	a[6]="CONTINUE";
	a[7]="DEFALT";
	a[8]="DO";
	a[9]="DOUBLE";
	a[10]="ELSE";
	a[11]="ENUM";
	a[12]="EXTERN";
	a[13]="FLOAT";
	a[14]="FOR";
	a[15]="GOTO";
	a[16]="IF";
	a[17]="INT";
	a[18]="LONG";
	a[19]="REGISTER";
	a[20]="RETURN";
	a[21]="SHORT";
	a[22]="SIGNED";
	a[23]="SIZEOF";
	a[24]="STATIC";
	a[25]="STRUCT";
	a[26]="SWITCH";
	a[27]="TYPEDEF";
	a[28]="UNION";
	a[29]="UNSIGNED";
	a[30]="VOID";
	a[31]="VOLATILE";
	a[32]="WHILE";
	a[33]="PLUS";
	a[34]="MINUS";
	a[35]="STAR";
	a[36]="DIV";
	a[37]="MOD";
	a[38]="BIPLUS";
	a[39]="BIMINUS";
	a[40]="DO_EQL";
	a[41]="NOT_EQL";
	a[42]="GREATER";
	a[43]="LESS";
	a[44]="GREATER_EQL";
	a[45]="LESS_EQL";
	a[46]="LGC_AND";
	a[47]="LGC_OR";
	a[48]="LGC_NOT";
	a[49]="AND";
	a[50]="OR";
	a[51]="XOR";
	a[52]="LSHIFT";
	a[53]="RSHIFT";
	a[54]="ASSIGN";
	a[55]="ASSIGN_PLUS";
	a[56]="ASSIGN_MINUS";
	a[57]="ASSIGN_STAR";
	a[58]="ASSIGN_DIV";
	a[59]="ASSIGN_MOD";
	a[60]="COMMA";
	a[61]="SEMI";
	a[62]="LP";
	a[63]="RP";
	a[64]="LS";
	a[65]="RS";
	a[66]="LC";
	a[67]="RC";
	a[68]="QUOT";
	a[69]="NOTE";
	a[70]="LNOTE";
	a[71]="RNOTE";
	a[72]="HASH";
	a[73]="ID";
	a[74]="SPACE";
	a[75]="SCANF";
	a[76]="PRINTF";
	a[77]="GETCHAR";
	a[78]="NUM";
	a[79]="RDIV";
	for(int i=0; i<data.size(); i++){
		printf("%d %d ", i, data[i]+1);
		cout << a[data[i]+1] << endl;
	}
	match();
	init();
//	for(int i=0; i<AST.size(); i++){
//		printf("CNT=%d TYPE=%d L=%d R=%d\n", i, AST[i].type, AST[i].l, AST[i].r);
//		printf("Sons:");
//		for(int j=0; j<AST[i].son.size(); j++){
//			printf("%d ",AST[i].son[j]);
//		}
//		printf("\n");
//	}
	dfs(0);
	return 0;
}
