#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct elemento{
	int val;
	struct elemento *anterior;
}elemento;

typedef struct{
	elemento *top;
}pilha;

pilha* criar();
void liberar(pilha *p);
int empilhar(pilha *p,int x);
int desempilhar(pilha *p,int *x);
int vazia(pilha *p);
int cheia(elemento *novo);
void menu();

int main() {	//pilha dinamica
	setlocale(LC_ALL,"Portuguese");
	
	menu();
	
	return 0;
}

pilha* criar(){
	pilha *p;
	p=(pilha*)malloc(sizeof(pilha));
	
	p->top=NULL;
	
	return p;
}

void liberar(pilha *p){
	while(p->top!=NULL){
		elemento *aux=p->top;
		p->top=p->top->anterior;
		free(aux);
	}
	free(p);
}

int empilhar(pilha *p,int x){
	elemento *novo;
	novo=(elemento*)malloc(sizeof(elemento));
	novo->anterior=p->top;
	p->top=novo;
	novo->val=x;
	
	return cheio(novo);
}

int desempilhar(pilha *p,int *x){
	
	if(vazia(p)==0){
		*x=p->top->val;
		elemento *aux=p->top;
		p->top=p->top->anterior;
		free(aux);
		return 1;
	}
	return 0;
}

int vazia(pilha *p){
	if(p->top!=NULL){
		return 0;
	}
	return 1;
}

int cheio(elemento *novo){
	if(novo!=NULL){
		return 1;
	}
	return 0;
}

void menu(){
	int check=-1,x,b,sv;
	pilha *p;
	
	while(check!=0){
		printf("Digite:\n\t1 para criar pilha;\n\t2 para empilhar;\n\t3 para desempilhar;\n\t4 para verificar se está vazia;\n\t5 para imprimir topo;\n\t6 para imprimir desempilhado;\n\t7 para liberar pilha;\n\t0 para sair;\n\n");
		scanf("%d",&check);
		
		switch(check){
			case 1:
				p=criar();
				printf("Pilha criada!\n");
			break;
				
			case 2:
				printf("Digite valor a ser empilhado: ");
				scanf("%d",&x);
				printf("\n");
				b=empilhar(p,x);
				if(b){
					printf("Empilhado!\n");
				}
				else{
					printf("Não foi possível empilhar\n");
				}
			break;
			
			case 3:
				b=desempilhar(p,&sv);
				if(b){
					printf("Desempilhado!\n");
				}
				else{
					printf("Não foi possível desempilhar\n");
				}
			break;
			
			case 4:
				if(vazia(p)==1){
					printf("Vazia!\n");
				}
				else{
					printf("Não está vazia.\n");
				}
			break;
			
			case 5:
				printf("Topo = %d\n",p->top->val);
			break;
			
			case 6:
				printf("Desempilhado = %d\n",sv);
			break;
			
			case 7:
				liberar(p);
				printf("Pilha liberada\n");
			break;
			
			case 0:
				printf("Fechando...\n");
			break;
			
			default:
				printf("Tente outra opção.\n");
			break;
		}
		printf("\n");	
	}
}
