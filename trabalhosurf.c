#include <stdio.h>
#include <stdlib.h>

typedef struct lista_prod{
    int cod_prod;
    char* tipo;
    char* descricao;
    int preco; 
    NO* prox;
    NO* ant;
}NO;


NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;
int id_prod = 0;

typedef struct lista_caixa_prod{
    int cod_prod;
    lista_caixa_prod* prox;
}lista_caixa_prod;

typedef struct caixa{
    int cod_caixa;
    lista_caixa_prod lista_prod;
    int qtd;
}caixa;

typedef






void add_lista_prod(tipo,descricao,preco){
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
            novo->prox = inicio;
            inicio = novo;
            tam++;
        }   
        else{  // passar por toda a lista até achar a posição que se encaixa
            NO* aux = malloc(sizeof(NO));
            aux = inicio;
            while(aux->preco < novo->preco){
                aux = aux->prox;
            }
            aux = aux->ant;
            novo->prox = aux->prox;
            novo->ant = aux;
            aux->prox = novo;
            tam++;
        }
    }
}

void remove_lista_prod(id){
    NO* lixo = malloc(sizeof(NO));
    if(inicio->cod_prod == id){        
    lixo = inicio;
    inicio = inicio->prox;
    free(lixo);
    }
}

void imprimir_lista_prod(){
    NO* aux = malloc(sizeof(NO));
    while(aux !=NULL){
        printf("tipo: %s, descricao: %s, preco: %d",aux->tipo,aux->descricao,aux->preco);
        aux= aux->prox;
    }
}

