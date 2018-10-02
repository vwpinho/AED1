#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
    int dia,mes,ano;
};
typedef struct data D;
struct pessoa{
	D niver;
	char nome[20];
        char email[30];
        int telefone;
};
typedef struct pessoa P;

struct variaveis{
	int i,nPessoas,flag,j,min_id;
        char busca[20], cmp[20];
        P tmp,min;
	};
typedef struct variaveis var;

void menu(var *p);
void incluiP(void **pB);
void apagaP(void **pB, char *nome);
void buscaP(void **pB);
void listaP(void **pB);
void cortaString(char* s,int n,void **pB);
void Insertionsort (void **pB);
void Selectsort (void **pB);
void Bubblesort (void **pB);
void menuOrdem ();
int main(){
	void *pBuffer;
	var *p;
	pBuffer= malloc(1*sizeof(var));
	if(!pBuffer){
		printf("Problema ao aloca memoria!");
		exit(1);
	}
	p=pBuffer;
	p->nPessoas=0;
	//printf("sizeof(int)=%d\nsizeof(float)=%d\nsizeof(char)=%d\n",sizeof(int),sizeof(float),sizeof(char));
	while(1){
		menu(p);
		switch (p->i) {
			case 1:
				incluiP(&pBuffer);
				break;
			case 2:
				printf("Nome da pessoa:");
                                scanf("%s",p->busca);
                                apagaP(&pBuffer,p->busca);
				break;
			case 3:
				buscaP(&pBuffer);
				break;
			case 4:
				listaP(&pBuffer);
				break;
                        case 5:
                                printf("\n1.Insertion Sort\n2.Selection Sort\n3.Bubblesort\n");
                                scanf("%d",&(p->j));
                                if(p->j==1)
                                    Insertionsort(&pBuffer);
                                if(p->j==2)
                                    Selectsort(&pBuffer);
                                if(p->j==3)
                                    Bubblesort(&pBuffer);
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
	printf("1.Incluir pessoa\n2.Apagar pessoa\n3.Buscar pessoa\n4.Listar\n5.Ordenar\n");
	scanf("%d",&(p->i));
}

void incluiP(void **pB){
	P *aux;
	void *p;
	var *i;

	i = *pB;
	i->nPessoas++;
	*pB=realloc(*pB,1*sizeof(var)+i->nPessoas*sizeof(P));
	i=*pB;
	p=*pB + sizeof(var) + (i->nPessoas-1)*sizeof(P);
	aux=p;
	printf("\nNome, aniversario, email e telefone:\n");
	scanf("%s %d %d %d",aux->nome,&(aux->niver.dia),&(aux->niver.mes),&(aux->niver.ano));
        scanf("%s %d",aux->email,&(aux->telefone));
	}

void listaP(void **pB){
	P *aux;
	void *p;
	var *i;
	i=*pB;
	for(i->i=0;i->i < i->nPessoas;(i->i)++){
        p=*pB + sizeof(var) + i->i*sizeof(P);
        aux=p;
        printf("\nNome:%s\nAniversario:%d/%d/%d\nEmail:%s\nTelefone:%d\n",aux->nome,aux->niver.dia,aux->niver.mes,aux->niver.ano,aux->email,aux->telefone);
        }
	}
void buscaP(void **pB)
{
    P *aux;
    var *i;
    void *p;
    
    i=*pB;
    printf("\nDigite um nome para busca:");
    scanf("%s",i->busca);
    i->flag=0;
    for(i->i=0;i->i < i->nPessoas;(i->i)++)
    {
        p=*pB + sizeof(var) + i->i*sizeof(P);
        aux = p;
        
        cortaString(aux->nome,(int)strlen(i->busca),pB);
        printf("\nDEBUG:Sb:%s\tLen:%zd\tSb:%s\n",i->busca,strlen(i->busca),i->cmp);
        if(strcmp(i->busca,i->cmp) == 0)
        {
            printf("Pessoa encontrada!\n");
            printf("Nome:%s\nAniversario:%d/%d/%d\nEmail:%s\nTelefone:%d\n",aux->nome,aux->niver.dia,aux->niver.mes,aux->niver.ano,aux->email,aux->telefone);
            printf("Deseja exclui-la?[1.Sim / 2.Nao]\n");
            scanf("%d",&(i->flag));
            if(i->flag==1)
            {
                apagaP(pB,aux->nome);
            }
            break;
        }
    }
    if(!(i->flag))
    {
        printf("Pessoa não encontrada!\n");
    }

}
void cortaString(char* s,int n,void **pB)
{
    var *i;
    
    i=*pB;
    strcpy(i->cmp,"");
    printf("Funcao corta, n:%d\n",n);
    for(i->j=0; i->j < n;i->j++)
    {
        i->cmp[i->j]=s[i->j];
    }
    i->cmp[n]='\0';
}
void apagaP(void **pB, char *nome)
{
    P *aux,*anterior;
    var *i;
    void *p;
    
    i=*pB;
    i->flag=0;
    for(i->i=0;i->i < i->nPessoas;(i->i)++)
    {
        p=*pB + sizeof(var) + i->i*sizeof(P);
        aux = p;
        if(strcmp(aux->nome,nome)==0)
        {
            printf("Tem certeza que deseja excluir %s da agenda? [1.SIM / 2.NAO]?\n",nome);
            scanf("%d",&(i->flag));
            if(i->flag==1)
            {
               for(i->j=i->i; i->j < i->nPessoas-1; i->j++)
               {
                   p=*pB + sizeof(var) + i->j*sizeof(P);
                   anterior = p;
                   p=*pB + sizeof(var) + (i->j+1)*sizeof(P);
                   aux = p;
                   *anterior=*aux;
               }
               printf("Pessoa deletada!\n");
               i->nPessoas--;
               *pB=realloc(*pB,1*sizeof(var)+i->nPessoas*sizeof(P));
            }
            if(i->flag==2)
            {
                printf("Exclusao abortada!\n");
            }
        }
    }
    if(i->flag==0)
    {
        printf("Pessoa não encontrada!\n");
    }
}
void Insertionsort (void **pB) { 
        var *i;
        void *p;
        P *aux,*proximo;
        i = *pB;
        for (i->j=1; i->j < i->nPessoas; i->j++) { 
		i->i =i->j - 1;
                p = *pB + sizeof(var) + i->j*sizeof(P);
		aux = p;
                i->tmp = *aux;                      // Segunda pessoa
		p =  *pB + sizeof(var) + i->i*sizeof(P);
                aux = p;                            // Primeira pessoa
                while ( (i->i >= 0) && ((strcmp(i->tmp.nome,aux->nome)<0)) ) { 
                        p = *pB + sizeof(var) + (i->i+1)*sizeof(P);
                        proximo = p; 
                        *proximo = *aux;            // Segundo recebe primeiro
                        i->i--; 
                        p = *pB + sizeof(var) + i->i*sizeof(P);
                        aux = p;
		}//while
                p = *pB + sizeof(var) + (i->i+1)*sizeof(P);
		proximo = p;
                *proximo = i->tmp; 
	}//for
 }//Insertionsort
    void Selectsort (void **pB) {
       var *i;
       void *p;
       P *data,*aux;
       i = *pB;
       for (i->i=0; i->i < (i->nPessoas-1); i->i++) { 
            i->min_id = i->i;
            p = *pB + sizeof(var) + (i->i)*sizeof(P);
            data = p;
            i->min = *data; 
            for (i->j=(i->i+1); i->j<i->nPessoas; i->j++) {
                p = *pB + sizeof(var) + (i->j)*sizeof(P);
                data = p;
                if (strcmp(data->nome,i->min.nome)<0) { 
                    i->min = *data; 
                    i->min_id = i->j; 
                    } 
                }
            p = *pB + sizeof(var) + (i->i)*sizeof(P);
            data = p;
            i->tmp = *data; 
            p = *pB + sizeof(var) + (i->min_id)*sizeof(P);
            aux = p;
            *data = *aux; 
            *aux = i->tmp;
        } 
    }
    void Bubblesort (void **pB) { 
	var *i;
        void *p;
        P *data,*proximo;
        i = *pB;
	for (i->i=0; i->i < (i->nPessoas-1); i->i++) { 
                i->flag=0;
		for (i->j=0; i->j < (i->nPessoas - i->i - 1); i->j++) {
                        p = *pB + sizeof(var) + (i->j)*sizeof(P);
                        data = p;
			p = *pB + sizeof(var) + (i->j + 1)*sizeof(P);
                        proximo = p;
                        if (strcmp(proximo->nome,data->nome) < 0) { 					
                            i->tmp = *data; 
                            *data = *proximo;
                            *proximo = i->tmp; 
                            i->flag=1;
			} 
		}
            if(i->flag==0)
                break;
	} 
    }



/* Aprimoramentos futuro:
 * Na busca por pessoas, mostrar todas em que o nome começa com os caracteres 
 * digitados
 * Criar uma sequencia numerica para as pessoas, gerada automaticamente,
 * e mostra-la na lista para facilitar a exclusao de pessoas
 * Lista e Incluir pessoa por enquanto atendem suas funcoes
 */