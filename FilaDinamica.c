#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct elemento{
	int val;
	struct elemento *proximo;
}elemento;

typedef struct{
	elemento *inicio;
	elemento *final;
}fila;

fila* criar();
void liberar(fila *p);
int inserir(fila *p,int x);
int retirar(fila *p,int *x);
int vazia(fila *p);
int cheio(elemento *novo);
void menu();

int main() {	//fila dinamica
	setlocale(LC_ALL,"Portuguese");
	
	menu();
	
	return 0;
}

fila* criar(){
	fila *p=(fila*)malloc(sizeof(fila));
	p->inicio=NULL;
	p->final=NULL;
	
	return p;
}

void liberar(fila *p){
	elemento *aux;
	while(p->inicio!=NULL){
		aux=p->inicio;
		p->inicio=p->inicio->proximo;
		free(aux);
	}
	free(p);
}

int inserir(fila *p,int x){
	elemento *novo=(elemento*)malloc(sizeof(elemento));
	if(cheio(novo)==1){
		novo->val=x;
		if(p->inicio==NULL){
			p->inicio=novo;
			novo->proximo=NULL;
			p->final=novo;
		}
		else{
			p->final->proximo=novo;
			p->final=novo;
		}
		return 1;
	}
	return 0;
}

int retirar(fila *p,int *x){
	if(vazia(p)==0){
		elemento *aux;
		*x=p->inicio->val;
		aux=p->inicio;
		p->inicio=p->inicio->proximo;
		free(aux);
		return 1;
	}
	return 0;
}

int vazia(fila *p){
	if(p->final==NULL){
		return 1;
	}
	return 0;
}

int cheio(elemento *novo){
	if(novo!=NULL){
		return 1;
	}
	return 0;
}

void menu(){
	int check=-1,x,b,sv;
	fila *p;
	
	while(check!=0){
		printf("Digite:\n\t1 para criar fila;\n\t2 para enfileirar;\n\t3 para desenfileirar;\n\t4 para verificar se está vazia;\n\t5 para imprimir final;\n\t6 para imprimir inicio;\n\t7 para liberar fila;\n\t0 para sair;\n\n");
		scanf("%d",&check);
		
		switch(check){
			case 1:
				p=criar();
				printf("Fila criada!\n");
			break;
				
			case 2:
				printf("Digite valor a ser enfileirado: ");
				scanf("%d",&x);
				printf("\n");
				b=inserir(p,x);
				if(b){
					printf("Enfileirado!\n");
				}
				else{
					printf("Não foi possível enfileirar\n");
				}
			break;
			
			case 3:
				b=retirar(p,&sv);
				if(b){
					printf("Desenfileirado!\n");
				}
				else{
					printf("Não foi possível desenfileirar\n");
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
				printf("Final = %d\n",p->final->val);
			break;
			
			case 6:
				printf("Início = %d\n",p->inicio->val);
			break;
			
			case 7:
				liberar(p);
				printf("Fila liberada\n");
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
