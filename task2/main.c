#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

typedef struct Note{
	int id;
	char *name, *number;
	struct Note *next, *prev;
}Note;

typedef struct Book{
	int size, last_id;
	struct Note *head, *tail;
}Book;

bool foundflag;

struct Book Mybook = {0, 0, NULL, NULL};

char* read(FILE *a);					
void read_file(char *filename);
void write_to_file(char *filename);
void add(int id, char *name, char *number);
char* makeNiceName(char *a);			
char* makeNiceNumber(char *a);				
bool checkNum(char *a);					
bool checkName(char *a);				
void exterminate(int id);				
struct Note seekNum(char *a);
struct Note seekName(char *a);  
void change(bool flag, int id, char *str);



int main(int argc, char *argv[]){
	char *filename = argv[1];
	char  command[10], *nname, *nnumber, c;
	int id, i = 0;
	FILE *in = fopen(filename, "r");
//	read_file(filename);


	struct Note work;
		while(true){
		foundflag = false;
		read_file(filename);
		scanf("%s", &command);
		scanf("%c", &c);
		if(!strcmp(command, "exit")){
			return 0;
		}else if(!strcmp(command, "find")){
			nname = read(stdin);
			if(checkNum(nname)){
				work = seekNum(makeNiceNumber(nname));
			}else if (checkName(nname)){
				work = seekName(makeNiceName(nname));
			}else{
				perror("Please, try again wrong format ");
			}
			if(foundflag){
				printf("%d %s %s\n", work.id, work.name, work.number);
			}else{
				printf("%s\n", "not found");
			}
		}else if(!strcmp(command, "create")){
			nname = read(stdin);
			nnumber = read(stdin);
			if((checkName(nname)) && (checkNum(nnumber))){
				nname = makeNiceName(nname);
				nnumber = makeNiceNumber(nnumber);
				add(++Mybook.last_id, nname, nnumber);
			}else{
				perror("bad input");
			}
		}else if(!strcmp(command, "delete")){
			scanf(" %d", &id);
			exterminate(id);
		}else if(!strcmp(command, "change")){
			scanf(" %d %s ", &id, &command);
			if(!strcmp(command, "name")){
				nname = read(stdin);
				if(checkName(nname)){
					nname = makeNiceName(nname);
					change(0, id, nname);						// 0 - we change name
				}else{	
					perror("Please, try again(name empty) ");
				}
			}else if(!strcmp(command, "number")){
				nnumber = read(stdin);
				if(checkNum(nnumber)){
					nnumber = makeNiceNumber(nnumber);		// 1 - we change name
					change(1, id, nnumber);
				}else{
					perror( "Please, try again (number empty)");
				}
			}
		}
		write_to_file(filename);
		fflush(stdout);
	}
	return 0;
	
}
char* makeNiceNumber(char *number){					//delete unimportant symbols(see checknum)
	char *b = (char *)malloc(sizeof(char) * strlen(number));
	int i = 0, j = 0;
	while(i < strlen(number)){
		if(isdigit(number[i]) > 0){
			b[j++] = number[i++];
		}else{
			i++;
		}
	}
	b[j] = '\0';
	free(number);
	return b;
}

bool checkNum(char *number){									//check the input number(no more than 2 '-' in a row and no more than 1 ())			
	bool flag = false, one = false, two = false;
	int i = 0;
	char prev;
	if(strlen(number) != 0){
		prev = 'a';
		if(number[i] == '+'){
			i++;
		}
		while(i < strlen(number)){
			if(isdigit(number[i]) > 0){
//				continue;
			}else if(number[i] == '('){
				if(one){
//					perror("Please, try again (number)");
					return false;
				}else{
					one = true;
				}
			}else if(number[i] == ')'){
				if(!one){
//					perror("Please, try again (number)");
					return false;
				}else{
					if(two){
//						perror("Please, try again (number)");
						return false;
					}else{
						two = true;
					}
				}
			}else if(number[i] == '-'){
				if(prev != '-'){
				}else{
//					perror("Please, try again (incorrect number :  2 adjacent \" - \")");
					return false;
				}
			}else{
//				perror("Please, try again (number)");
//				printf("%s\n", number);
//				system("pause");
				return false;
			}
			prev = number[i];
			i++;
		}
		return true;
	}else{
		return false;
	}
}

bool checkName(char *name){						//check input name(only letters a-z, A-Z)
	int i = 0;
	if(strlen(name) != 0){
		while(i < strlen(name)){
			if(isalpha(name[i]) > 0){
			}else{
//				perror("Please, try again(name) ");
				return false;
			}
			i++;
		}
		return true;
	}else{
		return false;
	}
}
char* makeNiceName(char *name){		
	int i;// to lower case
	for(i = 0; i <strlen(name); i++){
		name[i] = tolower(name[i]);
	}
	return name;
}

void read_file(char *filename){						//reads the file
	FILE *stream = fopen(filename, "r");
	int i, id, maxid = Mybook.last_id;
	char *name, *number, *check;
	while(!feof(stream)){
		fscanf(stream, "%d", &id);
		if(feof(stream)){
			Mybook.last_id = maxid;
			fclose(stream);
			return;
		}
		if(id > maxid){
			maxid = id;
		}
		char c = fgetc(stream);
		name = read(stream);
		number = read(stream);
		if(checkName(name) && checkNum(number)){
			add(id, makeNiceName(name), makeNiceNumber(number));
		}
	}
	Mybook.last_id = maxid;
	fclose(stream);
	return;
}

char* read(FILE *stream){								//reads 1 word from the stream
	int size = 0,  buf_length = 16;
	char c, *buf = (char*)malloc(sizeof(char) * 16);
	while(true){
		c = fgetc(stream); 
		if(size + 1 > buf_length){
			buf = (char*)realloc(buf, sizeof(char) * (buf_length * 2));
			buf_length *= 2;
		}
		if(c == EOF){
			break;
		}else{
			if(( c == ' ') || (c == '\0') || (c == '\n')){
				break;
			}else{
				buf[size ++] = c;
			}
		}
	}
	buf[size] = '\0';
	return buf;
}

void change(bool flag, int id, char *str){
	struct Note *newnote = Mybook.head;
	struct Note sample = flag ? seekNum(str) : seekName(str);
	int i = 0;
	while(i < Mybook.size){
		if(newnote->id == id){
			if(flag){
				newnote->number = str;
			}else{
				newnote->name = str;
			}
		}
		i++;
		newnote = newnote->next;
	}
}
void add( int id, char* name, char* number){			//add new note to our book
	Mybook.size++;
	struct Note *newnote = (struct Note*)malloc(sizeof(struct Note));
	newnote->id = id;
	newnote->name = name;
	newnote->number = number;
	newnote->prev = Mybook.tail;
	newnote->next = NULL;
	if(Mybook.size == 1){
		Mybook.head = newnote;
		Mybook.tail= newnote;
	}else{
		Mybook.tail->next = newnote;
		Mybook.tail = Mybook.tail->next;
	}
}

void exterminate(int id){
	int i = 0;
	struct Note *work = Mybook.head, *bf, *lf;
	while(i < Mybook.size){
		if(work->id == id){
			bf = work->prev;
			lf = work->next;
			if(bf != NULL){
				bf->next = lf;
			}else{
				Mybook.head = lf;
			}
			if(lf != NULL){
				lf->prev = bf;
			}else{
				Mybook.tail = bf;
			}
			free(work);
			Mybook.size --;
			return;
		}
		i++;
		work = work->next;
	}
	return;
}


void write_to_file(char *filename){
	FILE *out = fopen(filename, "w");
	struct Note *work = Mybook.tail;
	struct Note *mem;
	if(!out){
//		perror("failed to reopen");
	}else{
		while(Mybook.size > 0){
			fprintf(out, "%d %s %s\n", Mybook.tail->id, Mybook.tail->name, Mybook.tail->number);
			mem = Mybook.tail->prev;
			if(Mybook.tail != NULL){
				free(Mybook.tail);
			}
			Mybook.tail = mem;
			Mybook.size--;
		}
		Mybook.last_id = -1;
		fclose(out);
	}
}
struct Note seekName(char *name){
	struct Note *work = Mybook.head;
	int i;
	for(i = 0; i < Mybook.size; i++, work = work->next){
		if(strstr(work->name, name) != NULL){
			foundflag = true;
			return *work;
		}
	}
//	perror("No such name found");
	struct Note ans = {0, "", "", NULL, NULL};
	return ans;
}
struct Note seekNum(char *number){
	struct Note *work = Mybook.head;
	int i;
	for(i = 0; i < Mybook.size; i++, work = work->next){
		if(!strcmp(work->number, number)){
			foundflag = true;
			return *work;
		}
	}
//	perror("No such number found");
	struct Note ans = {0, "", "", NULL, NULL};
	return ans;
}
