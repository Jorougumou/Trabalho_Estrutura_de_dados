#include <stdio.h>
#include <stdlib.h>






typedef struct lista_caixa_prod{
    int cod_prod;
    struct lista_caixa_prod* prox;
}lista_caixa_prod;

typedef struct caixa{
    int cod_caixa;
    lista_caixa_prod* lista_prod;
    int qtd;
}caixa;


typedef struct NO{
    int cod_prod;
    char* tipo;
    char* descricao;
    int preco; 
    struct NO* prox;
    struct  NO* ant;
}NO;

NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;
int id_prod = 0;

void add_lista_prod(char* tipo,char* descricao,int preco){
    NO * novo = malloc(sizeof(NO));
    id_prod++;
    novo->cod_prod = id_prod;
    novo->tipo = tipo;
    novo->descricao = descricao; 
    novo->preco = preco;
    novo->ant = NULL;
    novo->prox = NULL;

    if(inicio == NULL){ // caso a lista esteja vazia
        inicio = novo;
        fim = novo;
        tam++;
    }else{
        if(fim->preco < novo->preco){     // caso o item adicionado seja o item mais caro
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
            tam++;
        }

        else if(inicio->preco > novo->preco){ // caso o item adicionado seja mais barato
            inicio->ant = novo;
            novo->prox = inicio;
            inicio = novo;
            tam++;
        }   
        else{  // passar por toda a lista até achar a posição que se encaixa
            NO* aux = inicio;
            while(aux->preco <= novo->preco){
                aux = aux->prox;
            };
            aux->ant->prox = novo;
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant = novo;
            tam++;
        }
    }
}

void remove_lista_prod(int id){
    NO* lixo = inicio;
    while(lixo->cod_prod != id){        
        lixo = lixo->prox;                 //mt mal feito corrigir dps
    };
    free(lixo);
    
  
}

void imprimir_lista_prod(){
    NO* aux = inicio;
    while(aux !=NULL){
        printf("tipo: %s, descricao: %s, preco: %d",aux->tipo,aux->descricao,aux->preco);
        aux= aux->prox;
    }
}

main(){
    add_lista_prod("quilha", "qilha pro-max", 8);
        add_lista_prod("deck", "deck simples", 25);
        add_lista_prod("leash", "leash ultimate", 5);

        printf("Lista Original:");
        imprimir_lista_prod();

        remove_lista_prod(2); 

        printf("\nLista apos remover o ID 2:");
        imprimir_lista_prod();                             //teste lista prod 
        return(0);
}