#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct elemento{
	int val;
	struct elemento *prox;
}elemento;

typedef struct{
	elemento *inicio;
}lista;

lista* criar();
void liberar(lista *p);
int vazia(lista *p);
int cheia(elemento *novo);
int inserir(lista *p,int x,int pos);
int inserir_ult(lista *p,int x);
int remover(lista *p,int *x,int pos);
int remover_ult(lista *p,int *x);
int recuperar_key(lista *p,int x,int *y);
int recuperar_pos(lista *p,int x,int *y);
void imprimir(lista *p,int pos);
void imprimir_all(lista *p);
void menu();


int main(){
	setlocale(LC_ALL,"Portuguese");
	
	menu();
	
	return 0;
}

lista* criar(){
	lista *p=(lista*)malloc(sizeof(lista));
	p->inicio=NULL;
	
	return p;
}

void liberar(lista *p){
	elemento *aux,*aux_ant;
	
	while(p->inicio!=NULL){
		aux=p->inicio;
		while(aux->prox!=NULL){
			aux_ant=aux;
			aux=aux->prox;
		}
		free(aux);
		aux_ant->prox=NULL;
		if(p->inicio->prox==NULL){
			aux=p->inicio;
			free(aux);
			free(p);
			//return 1;
			break;
		}
	}
	//return 0;
}

int vazia(lista *p){
	if(p->inicio==NULL){
		return 1;
	}
	return 0;
}

int cheia(elemento *novo){
	if(novo!=NULL){
		return 1; //elemento alocado com sucesso
	}
	return 0;
}

int inserir(lista *p,int x,int pos){
	int i;
	elemento *novo,*aux,*aux_ant;
	novo=(elemento*)malloc(sizeof(elemento));
	
	if(cheia(novo)==1){
		novo->val=x;
		novo->prox=NULL;
		aux=p->inicio;
		if(pos==1){
			p->inicio=novo;
			novo->prox=aux;
		}
		
		else{
			for(i=1;i<pos;i++){
				aux_ant=aux;
				aux=aux->prox;
			}
			aux_ant->prox=novo;
			novo->prox=aux;
		}
		return 1;
	}
	return 0;
}

int inserir_ult(lista *p,int x){
	elemento *novo,*aux;
	novo=(elemento*)malloc(sizeof(elemento));
	
	if(cheia(novo)==1){
		if(p->inicio==NULL){
			p->inicio=novo;
			novo->prox=NULL;
			novo->val=x;
			return 1;
		}
		else{
			aux=p->inicio;
			while(aux->prox!=NULL){
					aux=aux->prox;
			}
			aux->prox=novo;
			novo->prox=NULL;
			novo->val=x;
			return 1;
		}
		
	}
	return 0;
}

int remover(lista *p,int *x,int pos){
	int i;
	elemento *aux,*aux_ant;
	
	if(vazia(p)==0){
		if(pos==1){
			aux=p->inicio;
			if(p->inicio->prox!=NULL){
				aux_ant=p->inicio->prox;
				p->inicio=aux_ant;
			}
			else{
				p->inicio=NULL;
			}
			free(aux);
			return 1;
		}
		aux=p->inicio;
		for(i=1;i<pos;i++){
			aux_ant=aux;
			aux=aux->prox;
		}
		aux_ant->prox=aux->prox;
		free(aux);
		return 1;
	}
	return 0;
}

int remover_ult(lista *p,int *x){
	elemento *aux,*aux_ant;
	int check=-1;
	
	if(vazia(p)==0){
		aux=p->inicio;
		while(aux->prox!=NULL){
			aux_ant=aux;
			aux=aux->prox;
			check++;
		}
		*x=aux->val;
		free(aux);
		aux_ant->prox=NULL;
		if(check==-1){
			p->inicio=NULL;
		}
		return 1;
	}
	return 0;
}

int recuperar_key(lista *p,int x,int *y){
	elemento *aux;
	aux=p->inicio;
	*y=1;
	if(aux->val==x){
		return 1;
	}
		while(aux->prox!=NULL){
			aux=aux->prox;
			*y++;
			if(aux->val==x){
				return 1;
			}
		}
		return 0;
}

int recuperar_pos(lista *p,int x,int *y){
	int i;
	elemento *aux;
	aux=p->inicio;
	
	for(i=1;i<x;i++){
		aux=aux->prox;
	}
	*y=aux->val;
	return 1;
}

void imprimir(lista *p,int pos){
	int i;
	elemento *aux=(elemento*)malloc(sizeof(elemento));
	
	aux->prox=p->inicio;
	for(i=1;i<pos;i++){
		aux->prox=aux->prox->prox;
	}
	printf("Elemento da posição %d: %d\n",pos,aux->prox->val);
}

void imprimir_all(lista *p){
	elemento *aux=(elemento*)malloc(sizeof(elemento));
	
	aux->prox=p->inicio;
	printf("\n");
	while(aux->prox!=NULL){
		printf("%d\t",aux->prox->val);
		aux->prox=aux->prox->prox;
	}
	printf("\n");
}

void menu(){
	int x,pos,b,check=-1,save;
	lista *p;
	printf("**************************************************\n\t\tLista Dinamica\n**************************************************\n\n");
	while(check!=0){
		printf("Digite:\n\t1 para criar lista;\n\t2 para inserir na ultima posição;\n\t3 para remover da ultima posição;\n\t4 para inserir em qualquer posição;\n\t5 para remover em qualquer posição;\n\t6 para imprimir lista;\n\t7 para recuperar por chave;\n\t8 para recuperar por posição;\n\t9 para liberar lista;\n\t0 para sair;\n\n");
		scanf("%d",&check);
		
		switch(check){
			case 1:
				p=criar();
				printf("Lista criada!\n");
			break;
			
			case 2:
				printf("Digite valor: ");
				scanf("%d",&x);
				
				b=inserir_ult(p,x);
				
				if(b){
					printf("Valor inserido com sucesso!\n");
				}
				else{
					printf("Não foi possível inserir valor!\n");
				}
			break;
				
			case 3:
				b=remover_ult(p,&save);
				
				if(b){
					printf("Valor removido com sucesso!\n");
				}
				else{
					printf("Não foi possível remover valor!\n");
				}
			break;
			
			case 4:
				printf("Digite valor: ");
				scanf("%d",&x);
				
				printf("Digite posição: ");
				scanf("%d",&pos);
				
				b=inserir(p,x,pos);
				
				if(b){
					printf("Valor inserido com sucesso!\n");
				}
				else{
					printf("Não foi possível inserir valor!\n");
				}
			break;
			
			case 5:
				printf("Digite posição: ");
				scanf("%d",&pos);
				
				b=remover(p,&save,pos);
				
				if(b){
					printf("Valor removido com sucesso!\n");
				}
				else{
					printf("Não foi possível remover valor!\n");
				}
			break;
			
			case 6:
				imprimir_all(p);
			break;
			
			case 7:
				printf("Digite a chave: ");
				scanf("%d",&x);
				b=recuperar_key(p,x,&save);
				if(b){
					printf("Valor encontrado na posição %d.\n",save);
				}
				else{
					printf("Não foi possível encontrar este valor.\n");
				}
			break;
			
			case 8:
				printf("Digite a posição: ");
				scanf("%d",&pos);
				b=recuperar_pos(p,pos,&save);
				if(b){
					printf("Valor encontrado: %d\n",save);
				}
				else{
					printf("Não foi possível encontrar esta pósição.\n");
				}
			break;
				
			case 9:
				liberar(p);
				printf("Lista liberada!\n");
			break;
			
			case 0:
				printf("Fechando...");
			break;
			
			default:
				printf("Opção inválida!\n");
			break;
		}
		printf("\n");
	}
}
