#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//############################################  STRUCTS  #########################################################//

typedef struct lista_caixa_prod {
    int cod_prod;
    struct lista_caixa_prod* prox;
} lista_caixa_prod;

typedef struct caixa {
    int cod_caixa;
    lista_caixa_prod* lista_prod;
    int qtd;
} caixa;

typedef struct NO {
    int cod_prod;
    char* tipo;
    char* descricao;
    int preco;
    struct NO* prox;
    struct NO* ant;
} NO;

typedef struct fila {
    int cod_prod;
    char* tipo_prod;
    char* descricao_prod;
    int preco_prod;
    int cod_fila;
    char* cpf;
    int cep;
    char* nome_rua;
    int numero_casa;
    char* complemento;
    struct fila* prox;
} fila_pedidos;

typedef struct pilha {
    int codigoDacaixa;
    struct pilha* prox;
} pilha;

//###########################################   VARIAVEIS  GLOBAIS   ############################################/

NO* inicio = NULL;
NO* fim = NULL;
int tam = 0;
int id_prod = 0;

pilha* topo = NULL;
int CodigoCaixa = 0;

fila_pedidos* inicio_fila = NULL;
int id_fila = 0;
int tam_fila = 0;

//###########################################  FUNÇÕES    ######################################################/

void criar_pilha() {
    pilha* novo_no = malloc(sizeof(pilha));
    if (!novo_no) return;

    CodigoCaixa++;
    novo_no->codigoDacaixa = CodigoCaixa;
    novo_no->prox = topo;
    topo = novo_no;

    printf("Caixa %d foi empilhada com sucesso.\n", CodigoCaixa);
}

int limite_por_tipo(char* tipo) {
    if (strcmp(tipo, "parafina") == 0) return 50;
    if (strcmp(tipo, "leash") == 0) return 25;
    if (strcmp(tipo, "quilha") == 0) return 10;
    if (strcmp(tipo, "deck") == 0) return 5;
    return 0;
}

int contar_por_tipo(char* tipo) {
    int cont = 0;
    NO* aux = inicio;

    while (aux != NULL) {
        if (strcmp(aux->tipo, tipo) == 0) {
            cont++;
        }
        aux = aux->prox;
    }
    return cont;
}

void add_lista_prod(char* tipo, char* descricao, int preco, int qnt) {
    int limite = limite_por_tipo(tipo);
    int qtd_atual = contar_por_tipo(tipo);

    for (int i = 0; i < qnt; i++) {
        // Verifica se precisa criar nova pilha
        if (limite > 0 && (qtd_atual + i + 1) % limite == 0) {
            printf("Limite de %s excedido. Criando nova pilha.\n", tipo);
            criar_pilha();
        }

        
        NO* novo = malloc(sizeof(NO));

        novo->cod_prod = ++id_prod;
        
        //Aloca memória para strings
        novo->tipo = malloc(strlen(tipo) + 1);
        if (novo->tipo) strcpy(novo->tipo, tipo);
        
        novo->descricao = malloc(strlen(descricao) + 1);
        if (novo->descricao) strcpy(novo->descricao, descricao);
        
        novo->preco = preco;
        novo->prox = NULL;
        novo->ant = NULL;

        
        if (inicio == NULL) { // caso a lista esteja vazia
            inicio = fim = novo;
        }
        else if (preco < inicio->preco) {
            novo->prox = inicio;
            inicio->ant = novo;
            inicio = novo;
        }
        else if (preco >= fim->preco) {  // caso o item add seja mais barato ou de mesmo valor 
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
        }
        else { // passar por toda a lista até achar a posição que se encaixa
            NO* aux = inicio;
            while (aux != NULL && aux->preco <= preco) {
                aux = aux->prox;
            }

            if (aux != NULL) {
                novo->prox = aux;
                novo->ant = aux->ant;
                aux->ant->prox = novo;
                aux->ant = novo;
            }
        }

        tam++;
    }
}

void remove_lista_prod(int id){
    NO* lixo = inicio;

    if (lixo == NULL) {
        printf("lista vazia\n");
        return;
    }
    while (lixo != NULL && lixo->cod_prod != id) {
        lixo = lixo->prox;
    }
    if (lixo == NULL) {
        printf("Nenhum valor com esse id foi encontrado na lista\n");
        return;
    }
    if (inicio == fim) {
        inicio = NULL;
        fim = NULL;
    }
    else if (lixo == inicio) {
        inicio = lixo->prox;
        inicio->ant = NULL;
    }
    else if (lixo == fim) {
        fim = lixo->ant;
        fim->prox = NULL;
    }
    else {
        lixo->ant->prox = lixo->prox;
        lixo->prox->ant = lixo->ant;
    }

    free(lixo->tipo);
    free(lixo->descricao);
    free(lixo);
    tam--;
}



void imprimir_lista_prod() {
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    NO* aux = inicio;
    printf("\n=== LISTA DE PRODUTOS ===\n");
    printf("Total: %d produtos\n\n", tam);
    
    while (aux != NULL) {
        printf("ID: %d\n", aux->cod_prod);
        printf("Tipo: %s\n", aux->tipo);
        printf("Descricao: %s\n", aux->descricao);
        printf("Preco: R$%d\n", aux->preco);
        printf("---------------------\n");
        aux = aux->prox;
    }
}

void imprimir_por_tipo(char* tipo) {
    NO* aux = inicio;
    int encontrados = 0;
    
    printf("\n=== PRODUTOS DO TIPO: %s ===\n", tipo);
    
    while (aux != NULL) {
        if (strcmp(aux->tipo, tipo) == 0) {
            printf("ID: %d, Descricao: %s, Preco: R$%d\n", 
                   aux->cod_prod, aux->descricao, aux->preco);
            encontrados++;
        }
        aux = aux->prox;
    }
    
    if (encontrados == 0) {
        printf("Nenhum produto encontrado deste tipo.\n");
    }
}

void imprimir_por_preco(int min, int max) {
    NO* aux = inicio;
    int encontrados = 0;
    
    printf("\n=== PRODUTOS ENTRE R$%d E R$%d ===\n", min, max);
    
    while (aux != NULL) {
        if (aux->preco >= min && aux->preco <= max) {
            printf("ID: %d, Tipo: %s, Descricao: %s, Preco: R$%d\n", 
                   aux->cod_prod, aux->tipo, aux->descricao, aux->preco);
            encontrados++;
        }
        aux = aux->prox;
    }
    
    if (encontrados == 0) {
        printf("Nenhum produto encontrado nesta faixa de preco.\n");
    }
}


void add_fila(int id_prod, char* nome, char* cpf, int cep, char* nome_rua, int num_casa, char* complemento) {
    int preco_prod = 0;
    NO* aux_i = inicio;
    while (aux_i != NULL && aux_i->cod_prod != id_prod) {
        aux_i = aux_i->prox;
    }
    
    if (aux_i == NULL) {
        printf("Produto com ID %d nao encontrado!\n", id_prod);
        return;
    }
    fila_pedidos* novo = malloc(sizeof(fila_pedidos));
    if (!novo) {
        printf("Erro ao alocar memoria para fila!\n");
        return;
    }
    novo->cod_prod = id_prod;
    preco_prod = aux_i->preco;
    novo->tipo_prod = malloc(strlen(aux_i->tipo) + 1);
    if(novo->tipo_prod != NULL){
        strcpy(novo->tipo_prod, aux_i->tipo);
    }
    novo->descricao_prod = malloc(strlen(aux_i->descricao) + 1);
    if(novo->descricao_prod != NULL){
    strcpy(novo->descricao_prod, aux_i->descricao);
    }
    novo->preco_prod = preco_prod;
    novo->cod_fila = id_fila++;
    novo->cep = cep;
    novo->numero_casa = num_casa;
    novo->prox = NULL;
    

    novo->cpf = malloc(strlen(cpf) + 1);
    if (novo->cpf) strcpy(novo->cpf, cpf);
    
    novo->nome_rua = malloc(strlen(nome_rua) + 1);
    if (novo->nome_rua) strcpy(novo->nome_rua, nome_rua);
    
    novo->complemento = malloc(strlen(complemento) + 1);
    if (novo->complemento) strcpy(novo->complemento, complemento);
    
    // Inserir na fila
    if (inicio_fila == NULL) {
        inicio_fila = novo;
    }
    else {
        fila_pedidos* aux_f = inicio_fila;
        while (aux_f->prox != NULL) {
            aux_f = aux_f->prox;
        }
        aux_f->prox = novo;
    }
    
    tam_fila++;
   
}

void remover_fila(){
    fila_pedidos* lixo = inicio_fila;
    if(inicio_fila == NULL){
        printf("a fila não possui nenhum pedido pra ser removido");
    }
    else{
    inicio_fila = inicio_fila->prox;
    free(lixo->tipo_prod);
    free(lixo->descricao_prod);
    free(lixo->cpf);
    free(lixo->nome_rua);
    free(lixo->complemento);
    free(lixo);
    }
}


//###############################################   MAIN   #########################################################//

int main() {
    for (int i = 0; i < 25; i++) add_lista_prod("deck", "deck premium", 50, 1);
    for (int i = 0; i < 25; i++) add_lista_prod("quilha", "quilha pro-max", 8, 1);
    for (int i = 0; i < 25; i++) add_lista_prod("leash", "leash ultimate", 5, 1);
    for (int i = 0; i < 25; i++) add_lista_prod("parafina", "parafina top", 20, 1);
    printf("\n=== ESTOQUE CRIADO COM 100 PRODUTOS ===\n");
    imprimir_lista_prod();
    printf("\n=== PILHAS NO ESTOQUE ===\n");
    pilha* aux_pilha = topo;
    while (aux_pilha != NULL) {
        printf("Caixa %d\n", aux_pilha->codigoDacaixa);
        aux_pilha = aux_pilha->prox;
    }
    printf("\n=== SIMULANDO COMPRAS DE 20 PRODUTOS ===\n");
    for (int id = 1; id <= 20; id++) {
        char cpf[20]; sprintf(cpf, "000.000.000-%02d", id);
        char rua[20]; sprintf(rua, "Rua %d", id);
        char comp[20]; sprintf(comp, "Apto %d", id);
        add_fila(id, "Cliente", cpf, 10000 + id, rua, id*10, comp);
    }
    printf("\n=== FILA DE PEDIDOS (20) ===\n");
    fila_pedidos* aux_f = inicio_fila;
    while (aux_f != NULL) {
        printf("Pedido ID %d - Produto: %s - Cliente CPF: %s\n", aux_f->cod_fila, aux_f->descricao_prod, aux_f->cpf);
        aux_f = aux_f->prox;
    }
    printf("\n=== ENTREGANDO 10 PRODUTOS ===\n");
    for (int i = 0; i < 10; i++) {
        remover_fila();
    }
    printf("\n=== FILA APOS ENTREGAS ===\n");
    aux_f = inicio_fila;
    while (aux_f != NULL) {
        printf("Pedido ID %d - Produto: %s - Cliente CPF: %s\n", aux_f->cod_fila, aux_f->descricao_prod, aux_f->cpf);
        aux_f = aux_f->prox;
    
    }
    printf("\nPrograma finalizado com sucesso!\n");
    return 0;

}