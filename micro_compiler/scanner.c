/*************************************************************************
	> File Name: scanner.c
	> Author: kuanshn
	> Mail: [email protected] 
	> Created Time: Mon Feb 21 17:05:56 2022
 ************************************************************************/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXLEN 32
typedef enum token_types{
	BEGIN,END,READ,WRITE,ID,INTLITERAL,
	LPAREN,RPAREN,SEMICOLON,COMMA,ASSIGNOP,
	PLUSOP,MINUSOP,SCANEOF
}token;
token scanner(void);
typedef struct Buffer{
	char token_buffer[MAXLEN];
	int now_ptr;
}buffer;
buffer* buffer_ctor(){
	buffer *b = (buffer*)malloc(sizeof(buffer));
	b->now_ptr = 0;
	for(int i=0;i<MAXLEN;i++){
		b->token_buffer[i] = '\0';
	}
	return b;
}
void clear_buffer(buffer* b){
	for(int i=0;i<MAXLEN;i++){
		b->token_buffer[i] = '\0';
	}
}
void buffer_char(buffer* b,char c){
	if(b->now_ptr == MAXLEN){
		printf("buffer is full\n");
	}
	else{
		b->now_ptr++;
		b->token_buffer[b->now_ptr] = c;
	}
}
token check_reserved(buffer* b){
	/* if token is in reserved word table 
	 *	 return reserved word token
	 * else
	 *   return ID token
	 * */
}
void lexical_error(char c){
	printf("there is a lexical error with %c",c);
}
token scanner(void){
	/*
	 * when scanner be called return a token
	 * and next time scanner be called start from previous token to read
	 * */
	int in_char,c;
	buffer *tBuffer = buffer_ctor();
    clear_buffer(tBuffer);
	if(feof(stdin)){
		return SCANEOF;
	}
	while((in_char = getchar())!=EOF){
		if(isspace(in_char)){  //skip space
			continue;          
		}
		else if(isalpha(in_char)){   //maybe identifier
			buffer_char(tBuffer,in_char);
			for(c = getchar();isalnum(c) || c == '_';c = getchar()){
				buffer_char(tBuffer,in_char);
			} // lookahead
			ungetc(c,stdin);
			//return check_reserved(b); //see if the token is reserved word or identifier
			return ID;
		}
		else if(isdigit(in_char)){
			buffer_char(tBuffer,in_char);
			for(c = getchar();isdigit(c) || c == '_';c = getchar()){
				buffer_char(tBuffer,in_char);
			} // lookahead
			ungetc(c,stdin);
			return INTLITERAL; 
		}
		else if(in_char == '('){
			return LPAREN;
		}
		else if(in_char == ')'){
			return RPAREN;
		}
		else if(in_char == ';'){
			return SEMICOLON;
		}
		else if(in_char == ','){
			return COMMA;
		}
		else if(in_char =='+'){
			return PLUSOP;
		}
		else if(in_char == ':'){
			c = getchar();
			if(c == '='){
				return ASSIGNOP;
			}
			else{
				ungetc(c,stdin);
				lexical_error(in_char);
			}
		}
		else if(in_char == '-'){
			c = getchar();
			if(c == '-'){
				do{
					in_char = getchar();
				}while(in_char!='\n'); 
				
			}
			else{
				ungetc(c,stdin);
				return MINUSOP;
			}
		}
		else{
			lexical_error(in_char);
		}
		
	}
}
void print_result(token t){
	switch(t){
		case BEGIN:
			printf("begin token\n");
			break;
		case END:
			printf("end token\n");
			break;
		case ID:
			printf("ID token\n");
			break;
		case INTLITERAL:
			printf("INT literal token\n");
			break;
		case LPAREN:
			printf("Left paren token\n");
			break;
		case RPAREN:
			printf("Right paren token\n");
			break;
		case COMMA:
			printf("COMMA token\n");
			break;
		case SEMICOLON:
			printf("simicolon token\n");
			break;
		case PLUSOP:
			printf("plus operator\n");
			break;
		case MINUSOP:
			printf("minus operaton\n");
			break;
		case ASSIGNOP:
			printf("assign operator\n");
			break;
		case SCANEOF:
			printf("EOF token\n");
			break;
		default:
			printf("other token\n");
	}
}
int main(){
	token t;
	while((t=scanner())!=SCANEOF){
		print_result(t);
	}
	return 0;
}
