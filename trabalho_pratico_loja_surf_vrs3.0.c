#include<stdio.h>
#include<stdlib.h>

////////////////////// LISTA DUPLAMENTE ENCADEADA DE PRODUTOS A VENDA ///////////////
typedef struct NO{
    //dados 
    int codigo;
    char* tipo;
    char* descricao;
    float preco;
    //mecanismo de uniao de nos
    struct NO * prox;
    struct NO * ant;

}NO;

//como a lista de produtos para vendas é unica precisamos de apenas uma, logo podemos deixar o inicio e fim delas globais
NO * inicio = NULL;
NO * fim = NULL;
int tam = 0;

void add_lista_produtos_a_venda(int codigo, char* tipo, char* descricao, float preco){
    
    //paso 1: criar o NO novo!
    NO *novo = malloc(sizeof(NO));
    novo->codigo = codigo;
    novo->tipo = tipo;
    novo->descricao = descricao;
    novo->preco = preco;
    novo->prox = NULL;
    novo->ant = NULL;

    //passo 2: onde este NO novo irá ser  colocado na lista?
    if(inicio == NULL){ //lista vazia
        inicio = novo;
        fim = novo;
    }else{ //lista nao esta vazia 
        if(novo->preco < inicio->preco){ // add no inicio!
            novo->prox = inicio;
            inicio->ant = novo;
            inicio = novo;
        }else if(novo->preco > fim->preco){ // add no fim! :D
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
        }else{ //entre 1 e tam -1 (depois do inicio, antes do fim - "meio")
            NO * aux = inicio;
            while(aux->preco <= novo->preco){
                aux = aux->prox;
            }
            aux->ant->prox = novo;
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant = novo;
        }
    }
    tam++;
}

void imprimir_lista_produtos_a_venda(){
    NO * aux = inicio;
    for(int i=0; i<tam; i++){
        printf("\nPRODUTO A VENDA! Dados:\n");
        printf("Codigo = %d\n", aux->codigo);
        printf("Tipo = %s\n", aux->tipo);
        printf("Descricao = %s\n", aux->descricao);
        printf("Preco = %f\n", aux->preco);
        aux = aux->prox;
    } 
}


//////////////////// REPRESENTACAO DA LISTA ENCADEADA DE PRODUTOS /////////////

typedef struct NO_DA_LISTA_ENC{
    int codigo_produto;
    NO_DA_LISTA_ENC *prox;
}

typedef struct LISTA_ENC_PROD{
    NO_DA_LISTA_ENC *inicio;
    NO_DA_LISTA_ENC *fim;
    int tam;
}

void add_lista(LISTA_ENC_PROD *l, int codigo_produto){

    NO_DA_LISTA_ENC *novo = malloc(sizeof(NO_DA_LISTA_ENC));
    novo->codigo_produto = codigo_produto;
    novo->prox = NULL;

    if(l->tam == 0){
        l->inicio = novo;
        l->fim = novo;
        l->tam++;
    }else{
        l->fim->prox = novo;
        l->fim = novo;
        l->tam++;

    }
}

typedef struct CAIXA{
    int codigo_caixa;
    //lista encadeada de codigos dos produtos que estao a venda de um dos 4 tipos
    LISTA_ENC_PROD *lista_prod;

}CAIXA;

////////////////////////// REPRESENTACAO DA PILHA ////////////////////////

typedef struct NO_DA_PILHA{
    //dados (depende da aplicação)
    CAIXA *caixa;
    //mecanismo de uniao de nos
    struct NO_DA_PILHA * prox;
}NO_DA_PILHA;


typedef struct PILHA{
    NO_DA_PILHA * topo;
    int tam;
}PILHA;

void add_pilha(PILHA *p, CAIXA *caixa){
    
        //passo 1: criar o NO novo!
        NO_PILHA *novo = malloc(sizeof(NO_PILHA));
        novo->caixa = caixa;
        novo->prox = NULL;

        //passo 2: onde este NO novo irá ser  colocado na pilha?
        if(p->topo == NULL){ //pilha vazia
            p->topo = novo;
        }else{ //pilha nao esta vazia
        // add no topo!
            novo->prox = p->topo;
            p->topo = novo;
        }
        p->tam++;
}

PILHA * construir_pilha(){
    PILHA *p = malloc(sizeof(PILHA));
    p->topo = NULL;
    p->tam = 0;   
    return p; 
}
LISTA_ENC_PROD * construir_lista(){
    LISTA_ENC_PROD *nova_lista = malloc(sizeof(LISTA_ENC_PROD));
    nova_lista->inicio = NULL;
    nova_lista->fim = NULL;
    nova_lista->tam = 0;
    return nova_lista;

}

CAIXA * construir_caixa(int codigo_caixa, LISTA_ENC_PROD *l){
    CAIXA *nova_caixa = malloc(sizeof(CAIXA));
    nova_caixa->codigo_caixa = codigo_caixa;
    nova_caixa->lista_prod = l;
    return nova_caixa;
}


int main(){
    PILHA *pilha_leash = construir_pilha()
    PILHA *pilha_parafina = construir_pilha()
    PILHA *pilha_quilha = construir_pilha()
    PILHA *pilha_deck = construir_pilha()

    //suponha que chegou um LEASH para venda
    //codigo 11111
    //tipo leash
    //descricao: ...
    //preco: 80

    //1 - coloco o produto a venda:
    add_lista_produtos_a_venda(1111, "leash", "...", 80.0);
    if(pilha_leash->topo == NULL){ //estoque de leash tá vazio?
        LISTA_ENC_PROD *lista_nova = construir_lista();
        add_lista(lista_nova, 1111);
        CAIXA *caixa = construir_caixa(1917282, lista_nova);
        add_pilha(pilha_leash, caixa);

    }else{ // e se o estoque nao esta vazio
        if(pilha_leash->topo->caixa->lista_prod->tam == 25){

        }else{ //caso pilha_leash->topo->caixa->lista_prod->tam < 25
            
        }
    }



}

