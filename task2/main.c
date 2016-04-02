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

int main(){
	char filename[15] = "ink.txt";
	char  *command, *nname, *nnumber, c;
	int id, i = 0;
//	struct Note work;
		while(true){
		foundflag = false;
		read_file(filename);
		command = read(stdin);
		if(!strcmp(command, "exit")){
			write_to_file(filename);
			return 0;
		}else if(!strcmp(command, "find")){
			nname = read(stdin);
			if(checkNum(nname)){
				nnumber = makeNiceNumber(nname);
				struct Note *work1 = Mybook.head;
				int k;
				for(k = 0; k < Mybook.size; k++, work1 = work1->next){
					if(!strcmp(work1->number, nnumber)){
						foundflag = true;
						printf("%d %s %s\n", work1->id, work1->name, work1->number);
					}
				}
			}else if (checkName(nname)){
				nname = makeNiceName(nname);
				struct Note *work2 = Mybook.head;
				int j;
				for(j = 0; j < Mybook.size; j++, work2 = work2->next){
					if(strstr(work2->name, nname) != NULL){
						foundflag = true;
						printf("%d %s %s\n", work2->id, work2->name, work2->number);
					}
				}
			}else{
				perror("Please, try again wrong format ");
			}
			if(foundflag){
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
			scanf(" %d ", &id);
			command = read(stdin);
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
			}else if(number[i] == '('){
				if(one){
					return false;
				}else{
					one = true;
				}
			}else if(number[i] == ')'){
				if(!one){
					return false;
				}else{
					if(two){
						return false;
					}else{
						two = true;
					}
				}
			}else if(number[i] == '-'){
				if(prev != '-'){
				}else{return false;}
			}else{return false;}
			prev = number[i];
			i++;
		}
		return true;
	}else{return false;}
}

bool checkName(char *name){						//check input name(only letters a-z, A-Z)
	int i = 0;
	if(strlen(name) != 0){
		while(i < strlen(name)){
			if(isalpha(name[i]) > 0){
			}else{return false;}
			i++;
		}
		return true;
	}else{return false;}
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
	if(stream == NULL){
		stream = fopen(filename, "w+");
	}
	int id, maxid = Mybook.last_id;
	char *name, *number;
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
	buf = (char*)realloc(buf, sizeof(char) * (buf_length + 1));
	buf[size] = '\0';
	return buf;
}

void change(bool flag, int id, char *str){
	struct Note *newnote = Mybook.head;
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
		Mybook.tail = newnote;
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

