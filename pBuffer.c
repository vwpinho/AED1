#include <stdio.h>
#include <stdlib.h>

struct pessoa{
	int idade;
	char nome[20];
};
typedef struct pessoa P;

struct variaveis{
	int i;
	};
typedef struct variaveis var;

void menu(var *p);
void incluiP(void *pB);
void apagaP();
void buscaP();
void listaP(void *pB);

int main(){
	void *pBuffer;
	var *p;
	pBuffer= malloc(1*sizeof(var));
	if(!pBuffer){
		printf("Problema ao aloca memoria!");
		exit(1);
	}
	p=pBuffer;
	while(1){
		menu(p);
		switch (p->i) {
			case 1:
				incluiP(pBuffer);
				break; 
			case 2:
				printf("apagaP()");
				break;
			case 3:
				printf("buscaP()");
				break;
			case 4:
				listaP(pBuffer);
				break;
			default:
				printf("Erro no menu!\n");
				free(pBuffer);
				exit(1);
				break;
		}
	}
}

void menu(var *p){
	printf("1.Incluir pessoa\n2.Apagar pessoa\n3.Buscar pessoa\n4.Listar");
	scanf("%d",&(p->i));
}

void incluiP(void *pB){
	P *aux;
	pB=realloc(pB,1*sizeof(var)+1*sizeof(P));
	aux=(pB+sizeof(int));
	printf("Nome e idade:\n");
	scanf("%s %d",aux->nome,&(aux->idade));	
	}

void listaP(void *pB){
	P *aux;
	aux=(pB+sizeof(int));
	printf("Nome:%s\nIdade:%d\n",aux->nome,aux->idade);
	}
