#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//############################################  STRUCTS  #########################################################//


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


typedef struct fila{
int cod_prod;
char* tipo_prod;
char* descricao_prod;
int preco_prod;
int cod_fila;
char* nome_cliente;
char* cpf;
int cep;
char*nome_rua;
int numero_casa;
char* complemento;
struct fila* prox;
}fila_pedidos;

//###########################################   VARIAVEIS  GLOBAIS   ############################################/

NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;
int id_prod = 0;

fila_pedidos* inicio_fila = NULL;
int id_fila = 0;
int tam_fila = 0;

//###########################################  FUNÇÕES    ######################################################/

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
    if(lixo->cod_prod == id){
        inicio = lixo->prox; 
        inicio->ant = NULL;
        free(lixo);
    }
    else if(fim->cod_prod == id){
        lixo = fim;
        fim = fim->ant;
        fim->prox = NULL;
        free(lixo);
    }
    else{
        while(lixo->cod_prod != id && lixo != NULL){
            lixo = lixo->prox;
        }
        if(lixo != NULL){
            lixo->prox->ant = lixo->ant;
            lixo->ant->prox = lixo->prox;
        }
        else{
            printf("Nenhum valor com esse id foi encontrado na lista");
        }
    }
    tam--;
}

void imprimir_lista_prod(){
    NO* aux = inicio;
    while(aux !=NULL){
        printf("id: %d tipo: %s, descricao: %s, preco: %d",aux->cod_prod,aux->tipo,aux->descricao,aux->preco);
        aux= aux->prox;
    }
}

void imprimir_por_tipo(char* tipo){
    NO* aux = inicio;
    while(aux !=NULL){
        if(strcmp(aux->tipo,tipo) == 0){
            printf("(id: %d, tipo: %s, descricao: %s, preco%d)",aux->cod_prod,aux->tipo,aux->descricao,aux->preco);
        }
        aux = aux->prox;
    }
}

void imprimir_por_preco(int min,int max){
        NO* aux = inicio;
    while(aux !=NULL){
        if(aux->preco > min && aux->preco < max){
            printf("(id: %d, tipo: %s, descricao: %s, preco%d)",aux->cod_prod,aux->tipo,aux->descricao,aux->preco);
        }
        aux = aux->prox;
    }
}
        


void add_fila(int id_prod, char* nome, char*cpf, int cep, char* nome_rua, int num_casa, char* complemento){ 
    char* tipo_prod;
    char* descricao_prod;
    int preco_prod;
    NO* aux_i = inicio;
    while(aux_i != NULL && aux_i->cod_prod != id_prod){
        aux_i = aux_i->prox;
    }
    tipo_prod = aux_i->tipo;
    descricao_prod = aux_i->descricao;
    preco_prod = aux_i->preco;

    if(inicio_fila == NULL){
        inicio_fila = malloc(sizeof(fila_pedidos));
        inicio_fila->cod_prod = id_prod;
        inicio_fila->tipo_prod = tipo_prod;
        inicio_fila->descricao_prod = descricao_prod;
        inicio_fila->preco_prod = preco_prod;
        inicio_fila->cod_fila = id_fila;
        inicio_fila->cpf = cpf;    
        inicio_fila->cep = cep;
        inicio_fila->nome_rua = nome_rua;
        inicio_fila->numero_casa = num_casa;
        inicio_fila->complemento = complemento;
        inicio_fila->prox = NULL;
    }
    else{
        fila_pedidos* var_f = malloc(sizeof(fila_pedidos));
        fila_pedidos* aux_f = inicio_fila;
        var_f->cod_prod = id_prod;
        var_f->tipo_prod = tipo_prod;
        var_f->descricao_prod = descricao_prod;
        var_f->preco_prod = preco_prod;
        var_f->cod_fila = id_fila;
        var_f->cpf = cpf;    
        var_f->cep = cep;
        var_f->nome_rua = nome_rua;
        var_f->numero_casa = num_casa;
        var_f->complemento = complemento;
        var_f->prox = NULL;     
        while (aux_f->prox !=NULL){
            aux_f = aux_f->prox;
        }
        aux_f->prox = var_f;

        
    }
    tam_fila++;
    id_fila++;
    
}

void remover_fila(){
    fila_pedidos* lixo = inicio_fila;
    if(inicio_fila == NULL){
        printf("a fila não possui nenhum pedido pra ser removido");
    }
    else{
    inicio_fila = inicio_fila->prox;
    free(lixo);
    }
}


//###############################################   MAIN   #########################################################//

int main(){
    add_lista_prod("quilha", "quilha pro-max", 8);
    add_lista_prod("deck", "deck simples", 25);
    add_lista_prod("leash", "leash ultimate", 5);

    printf("Lista Original\n");
    imprimir_lista_prod();

    remove_lista_prod(2); 

    printf("\nLista apos remover o ID 2\n");
    imprimir_lista_prod();                             //teste lista prod 
    return(0);
}