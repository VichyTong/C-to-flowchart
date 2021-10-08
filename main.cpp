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
	RDIV,
	DOT,
	PUNCTUAL
};

bool isnumber(char ch){
	return (ch>='0' && ch<='9');
}
bool isletter(char ch){
	return ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || ch=='_');
}
bool isoperator(char ch){
	return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='=' || ch=='!' || ch=='>' || ch=='<' || ch=='&' || ch=='|' || ch=='^' || ch==',' || ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='[' || ch==']' || ch=='"' || ch=='/' || ch=='\\' || ch=='.' || ch=='\'');
}
bool isend(char ch){
	return (ch=='\n' || ch==' ' || ch=='\t');
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
		id_data[data.size()]=str;
	}
	data.push_back(tmp);
}
void trans_num(string str){
	TokenType tmp;
	tmp=NUM;
	num_data[data.size()]=str;
	data.push_back(tmp);
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
	else if(str=="."){
		tmp=DOT;
	}
	else if(str=="\'"){
		tmp=PUNCTUAL;
	}
	data.push_back(tmp);
}
void scanner(){
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
	string INFILE;
	char ch;
	while((ch=getchar())!=EOF){
		INFILE+=ch;
	}
	INFILE+='\n';
	for(int i=0; i<INFILE.size(); i++){
		ch=INFILE[i];
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
				if(ch=='#'){
					while(ch!='\n'){
						i++;
						ch=INFILE[i];
					}
					sta=0;
				}
				else if(isnumber(ch)){
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
						else{
							trans_opr(str);
							sta=3;
							str=ch;
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
	NODETYPE_RETURN,
	NODETYPE_ELSE,
	FUNCTION_USING,
	FUNCTION_DECLARE
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
			node r_else;
			r_else.type=NODETYPE_ELSE;
			r_else.l=nxt;
			AST.push_back(r_else);
			int r_else_index=AST.size()-1;
			int else_body_index=build(nxt+1, r);
			AST[r_else_index].r=AST[else_body_index].r;
			addedge(r_if_index, r_else_index);
			addedge(r_else_index, else_body_index);
			AST[r_if_index].r=AST[r_else_index].r;
		}
		return r_if_index;
	}
	else if(data[now]==SCANF){
		while(data[now]!=SEMI && now<=r){
			now++;
		}
		node command;
		command.type=INPUT;
		command.l=l;
		command.r=now;
		AST.push_back(command);
		return AST.size()-1;
	}
	else if(data[now]==PRINTF){
		while(data[now]!=SEMI && now<=r){
			now++;
		}
		node command;
		command.type=OUTPUT;
		command.l=l;
		command.r=now;
		AST.push_back(command);
		return AST.size()-1;
	}
	else if(data[now]==RETURN){
		while(data[now]!=SEMI && now<=r){
			now++;
		}
		node command;
		command.type=NODETYPE_RETURN;
		command.l=l;
		command.r=now;
		AST.push_back(command);
		return AST.size()-1;
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
map<string, int> Function_set;
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
				if(data[i+3]==NUM){
					int body_index=build(i, link[i+2]+1);
					addedge(0, body_index);
					i=link[i+2]+1;
				}
				else{
					if(Function_set.count(id_data[i+1])>0){
						AST[Function_set[id_data[i+1]]].type=FUNCTION_DECLARE;
					}
					node fun;
					fun.type=FUNCTION;
					fun.l=i;
					AST.push_back(fun);
					int fun_index=AST.size()-1;
					addedge(0, fun_index);
					int body_index=build(link[i+2]+1, data.size()-1);
					AST[fun_index].r=AST[body_index].r;
					addedge(fun_index, body_index);
					Function_set[id_data[i+1]]=fun_index;
					i=AST[fun_index].r;
				}
			}
		}
		else if(data[i]==VOID){
			if(Function_set.count(id_data[i+1])>0){
				AST[Function_set[id_data[i+1]]].type=FUNCTION_DECLARE;
			}
			node fun;
			fun.type=FUNCTION;
			fun.l=i;
			AST.push_back(fun);
			int fun_index=AST.size()-1;
			addedge(0, fun_index);
			int body_index=build(link[i+2]+1, data.size()-1);
			AST[fun_index].r=AST[body_index].r;
			addedge(fun_index, body_index);
			Function_set[id_data[i+1]]=fun_index;
			i=AST[fun_index].r;
		}
	}
}
void Function_set_init(){
//	for(int i=0; i<AST[0].son.size(); i++){
//		if(AST[AST[0].son[i]].type==FUNCTION){
//			Function_set[id_data[AST[AST[0].son[i]].l+1]]=AST[0].son[i];
//		}
//	}
	for(int i=0; i<AST.size(); i++){
		if(AST[i].type==COMMON && Function_set.count(id_data[AST[i].l])>0){
			AST[i].type=FUNCTION_USING;
		}
	}
}
map<int, pair<int, int>> if_lst;
map<int, int> lst;
void printedge(int index_a, int index_b, int sta){
	if(AST[index_a].type==NODETYPE_IF){
		printedge(if_lst[index_a].first, index_b, (if_lst[index_a].first==AST[index_a].son[0]) ? 1 : 0);
		printedge(if_lst[index_a].second, index_b, (if_lst[index_a].second==AST[index_a].son[0]) ? -1 : 0);
		return;
	}
	if(AST[index_a].type==NODETYPE_RETURN){
		return;
	}
	if(sta>0){
		printf("%d -> %d [label=\"Y\"];\n",index_a, index_b);
	}
	else if(sta<0){
		printf("%d -> %d [label=\"N\"];\n",index_a, index_b);
	}
	else{
		printf("%d -> %d;\n",index_a, index_b);
	}
}
void dfs(int last, int now, int sta){
	int type=AST[now].type;
	if(type==NODETYPE_FOR){
		printedge(last, AST[now].son[0], sta);
		printedge(AST[now].son[0], AST[now].son[1], 0);
		dfs(AST[now].son[1], AST[now].son[2], 1);
		printedge(lst[AST[now].son[2]], AST[now].son[3], (AST[lst[AST[now].son[2]]].type==JUDGE)?-1:0);
		printedge(AST[now].son[3], AST[now].son[1], 0);
		lst[now]=AST[now].son[1];
	}
	else if(type==NODETYPE_WHILE){
		printedge(last, AST[now].son[0], sta);
		dfs(AST[now].son[0], AST[now].son[1], 1);
		printedge(lst[AST[now].son[1]], AST[now].son[0], 0);
		lst[now]=AST[now].son[0];
	}
	else if(type==NODETYPE_IF){
		printedge(last, AST[now].son[0], sta);
		dfs(AST[now].son[0], AST[now].son[1], 1);
		if(AST[now].son.size()==3){
			dfs(AST[now].son[0], AST[now].son[2], -1);
			if_lst[now]=make_pair(lst[AST[now].son[1]], lst[AST[now].son[2]]);
		}
		else{
			if_lst[now]=make_pair(lst[AST[now].son[1]], AST[now].son[0]);
		}
		lst[now]=now;
	}
	else if(type==NODETYPE_ELSE){
		dfs(last, AST[now].son[0], sta);
		lst[now]=lst[AST[now].son[0]];
	}
	else if(type==COMPLEX){
		int siz=AST[now].son.size();
		int pre=last, nowsta=sta;
		for(int i=0; i<siz; i++){
			dfs(pre, AST[now].son[i], nowsta);
			int typ=AST[AST[now].son[i]].type;
			if(typ==NODETYPE_FOR || typ==NODETYPE_WHILE){
				pre=lst[AST[now].son[i]];
				nowsta=-1;
			}
			else if(typ==NODETYPE_IF){
				pre=AST[now].son[i];
				nowsta=0;
			}
			else{
				pre=lst[AST[now].son[i]];
				nowsta=0;
			}
		}
		lst[now]=lst[AST[now].son[siz-1]];
	}
	else if(type==FUNCTION){
		dfs(now, AST[now].son[0], 0);
	}
	else if(type==JUDGE){
		printf("DFSERROR\n");
	}
	else if(type==COMMON || type==INPUT || type==OUTPUT){
		if(last!=now){
			printedge(last, now, sta);
		}
		lst[now]=now;
	}
	else if(type==NODETYPE_RETURN){
		if(last!=now){
			printedge(last, now, sta);
		}
		lst[now]=now;
	}
	else if(type==FUNCTION_USING){
		int index=Function_set[id_data[AST[now].l]];
		lst[now]=lst[index];
	}
	else if(type==FUNCTION_DECLARE){
		return;
	}
//	else if(type==ROOT){
//		int siz=AST[now].son.size();
//		for(int i=0; i<siz; i++){
//			dfs(0, AST[now].son[i], 0);
//		}
//	}
}
void printname(){
	for(int i=0; i<AST.size(); i++){
		if(AST[i].type==COMMON){
			if(AST[i].l==AST[i].r){
				continue;
			}
			printf("%d [shape=box, label=\"", i);
			for(int j=AST[i].l; j<=AST[i].r; j++){
				if(data[j]==NUM){
					cout << num_data[j] << " ";
				}
				else if(data[j]==ID){
					cout << id_data[j] << " ";
				}
				else{
					cout << a[data[j]+1] << " ";
				}
			}
			printf("\"];\n");
		}
		else if(AST[i].type==JUDGE){
			printf("%d [shape=diamond, label=\"", i);
			for(int j=AST[i].l; j<=AST[i].r; j++){
				if(data[j]==NUM){
					cout << num_data[j] << " ";
				}
				else if(data[j]==ID){
					cout << id_data[j]<< " ";
				}
				else{
					cout << a[data[j]+1]<< " ";
				}
			}
			printf("\"];\n");
		}
		else if(AST[i].type==INPUT){
			printf("%d [shape=box, label=\"", i);
			for(int j=AST[i].l; j<=AST[i].r; j++){
				if(data[j]==NUM){
					cout << num_data[j] << " ";
				}
				else if(data[j]==ID){
					cout << id_data[j] << " ";
				}
				else{
					cout << a[data[j]+1] << " ";
				}
			}
			printf("\"];\n");
		}
		else if(AST[i].type==OUTPUT){
			printf("%d [shape=box, label=\"", i);
			for(int j=AST[i].l; j<=AST[i].r; j++){
				if(data[j]==NUM){
					cout << num_data[j] << " ";
				}
				else if(data[j]==ID){
					cout << id_data[j] << " ";
				}
				else{
					cout << a[data[j]+1] << " ";
				}
			}
			printf("\"];\n");
		}
		else if(AST[i].type==FUNCTION){
			printf("%d [shape=box, label=\"function:", i);
			cout << id_data[AST[i].l+1] << " ";
			printf("\"];\n");
		}
		else if(AST[i].type==ROOT){
			printf("%d [shape=ellipse, label=\"begin\"];\n", i);
		}
		else if(AST[i].type==NODETYPE_RETURN){
			printf("%d [shape=ellipse, label=\"", i);
			for(int j=AST[i].l; j<=AST[i].r; j++){
				if(data[j]==NUM){
					cout << num_data[j] << " ";
				}
				else if(data[j]==ID){
					cout << id_data[j] << " ";
				}
				else{
					cout << a[data[j]+1] << " ";
				}
			}
			printf("\"];\n");
		}
		else if(AST[i].type==FUNCTION_DECLARE){
			continue;
		}
	}
}
void initstr(){
	a[1]="auto";
	a[2]="break";
	a[3]="case";
	a[4]="char";
	a[5]="const";
	a[6]="continue";
	a[7]="defalt";
	a[8]="do";
	a[9]="double";
	a[10]="else";
	a[11]="enum";
	a[12]="extern";
	a[13]="float";
	a[14]="for";
	a[15]="goto";
	a[16]="if";
	a[17]="int";
	a[18]="long";
	a[19]="register";
	a[20]="return";
	a[21]="short";
	a[22]="signed";
	a[23]="sizeof";
	a[24]="static";
	a[25]="struct";
	a[26]="switch";
	a[27]="typedef";
	a[28]="union";
	a[29]="unsigned";
	a[30]="void";
	a[31]="volatile";
	a[32]="while";
	a[33]="+";
	a[34]="-";
	a[35]="*";
	a[36]="/";
	a[37]="%";
	a[38]="++";
	a[39]="--";
	a[40]="==";
	a[41]="!=";
	a[42]=">";
	a[43]="<";
	a[44]=">=";
	a[45]="<=";
	a[46]="&&";
	a[47]="||";
	a[48]="!";
	a[49]="&";
	a[50]="|";
	a[51]="^";
	a[52]="<<";
	a[53]=">>";
	a[54]="=";
	a[55]="+=";
	a[56]="-=";
	a[57]="*=";
	a[58]="/=";
	a[59]="%=";
	a[60]=",";
	a[61]=";";
	a[62]="(";
	a[63]=")";
	a[64]="[";
	a[65]="]";
	a[66]="{";
	a[67]="}";
	a[68]="\\\"";
	a[69]="//";
	a[70]="/*";
	a[71]="*/";
	a[72]="#";
	a[73]="ID";
	a[74]=" ";
	a[75]="scanf";
	a[76]="printf";
	a[77]="getchar";
	a[78]="NUM";
	a[79]="\\";
	a[80]=".";
	a[81]="\'";
}
int main(){
	freopen("test.in", "r", stdin);
	freopen("graph.dot", "w", stdout);
	initstr();
	scanner();
//	for(int i=0; i<data.size(); i++){
//		printf("%d %d ", i, data[i]+1);
//		cout << a[data[i]+1] << endl;
//	}
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
	Function_set_init();
	printf("digraph g {\n");
	int main_index=Function_set["main"];
	printedge(0, main_index, 0);
	for(int i=0; i<AST[0].son.size(); i++){
		if(AST[AST[0].son[i]].type==FUNCTION){
			dfs(AST[0].son[i], AST[0].son[i], 0);
		}
	}
	printname();
	printf("}\n");
	return 0;
}
