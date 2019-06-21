#include <stdio.h>
#include <stdlib.h>

int toHex(char*, int);
int crke(char);
int stopnja(int);
int toBin(int, char*);
void izpisPrvoObmocje(char*, int);
void izpisDrugoObmocje(char*, int);
void izpisTretjoObmocje(char*, int);

int main(int argv, char* argc[]){
	//X'221A
	int vel=1;
	while(argc[1][vel-1]!='\0'){
		vel++;
	}
	char *st=argc[1];
	printf("vel: %d\n", vel);
	//printf("%d", toHex(st, vel-4));
	char* bin=(char*)malloc(100*sizeof(char));//(char*) malloc(((vel-2)*sizeof(char)*4));
	int n = toBin(toHex(st, vel-4), bin);
	//UTF8(bin, st, n, (vel-3)*4);
	if(toHex(st, vel-4)>=toHex((char*)"X'00", 1) && toHex(st, vel-4)<=toHex((char*)"X'7F", 1)){
		izpisPrvoObmocje(bin, n);
	}else if(toHex(st, vel-4)>=toHex((char*)"X'80", 1) && toHex(st, vel-4)<=toHex((char*)"X'7FF", 2)){
		izpisDrugoObmocje(bin, n);
	}else if(toHex(st, vel-4)>=toHex((char*)"X'800", 2) && toHex(st, vel-4)<=toHex((char*)"X'FFFF", 3)){
		izpisTretjoObmocje(bin, n);
	}
	free(bin);
	
	return 0;
}

int toHex(char st[], int vel){
	int rez=0;

	for(int x=2; st[x]!='\0'; vel--, x++) {
		if(st[x]=='A' || st[x]=='B' || st[x]=='C' || st[x]=='D' || st[x]=='E' || st[x]=='F') rez+=crke(st[x])*stopnja(vel);
		else if(st[x]=='a' || st[x]=='b' || st[x]=='c' || st[x]=='d' || st[x]=='e' || st[x]=='f') rez+=crke(st[x])*stopnja(vel);
		else rez+=(((int)st[x])-48)*stopnja(vel);
	}
	//printf("rez: %d\n", rez);
	return rez;
}

int crke(char st){
	if(st=='A' || st=='a')return 10;
	if(st=='B' || st=='b')return 11;
	if(st=='C' || st=='c')return 12;
	if(st=='D' || st=='d')return 13;
	if(st=='E' || st=='e')return 14;
	if(st=='F' || st=='f')return 15;
}

int stopnja(int vel){
	if(vel>0){
		int rez=16;
		for(int i=vel-1; i>0; i--)rez*=16;
		return rez;
	}
	return 1;
}

int toBin(int st, char* vred){
	if(st/2==0){
		vred[0]=(char)(st%2)+48;
		return 1;
	}
	int tr=toBin(st/2, vred);
	vred[tr]=(char)(st%2)+48;
	//printf("%c : %d\n", vred[tr], tr);
	vred[++tr]='\0';
	return tr;
}

void izpisPrvoObmocje(char* bin, int tr){
	printf("\n%d\n", tr);
	printf("0");
	for(int x=tr; x<7; x++){
		printf("0");
	}
	for(int x=0; bin[x]!='\0'; x++){
		printf("%c", bin[x]);	
	}
}

void izpisDrugoObmocje(char* bin, int tr){
	printf("110");
	int stej=0;
	for(int x=tr; x<11; x++, stej++){
		if(stej==3){
			printf("10");
			printf("0");
		}
		else printf("0");
	}
	for(int x=0; bin[x]!='\0'; x++, stej++){
		if(stej==3){
			printf("10");
			printf("%c", bin[x]);	
		}
		else printf("%c", bin[x]);	
	}
}

void izpisTretjoObmocje(char* bin, int tr){
	printf("1110");
	int stej=0;
	for(int x=tr; x<16; x++, stej++){
		if(stej==4 || stej==10){
			printf("10");
			printf("0");
		}
		else printf("0");
	}
	for(int x=0; bin[x]!='\0'; x++, stej++){
		if(stej==4 || stej==10){
			printf("10");
			printf("%c", bin[x]);	
		}
		else printf("%c", bin[x]);	
	}
}
