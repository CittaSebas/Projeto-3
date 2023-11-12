#include "proj.h"
#include <stdio.h>


int criarTarefa(ListaDeTarefas *lt){

    // Variáveis locais em formato struct
    char categoria[100];
    char descricao[300];
    int prioridade;
    //

    // Abrindo o arquivo
    FILE *f = fopen("arquivo.bin", "ab");
    //

    // Se o Arquivo não é encontrado retorna um código de erro
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    //

    Tarefa novatarefa;


    if (lt->qtd >= 100){
        printf("Limite maximo de tarefas atingido, delete uma antes de continuar\n");
        fclose(f);
        return 1;
    }


    // Pedindo Categoria, Descrição e Prioriade ao usuário
    printf("Escreva sua tarefa: \n");
    scanf("%s",novatarefa.categoria);

    printf("Descreva sua tarefa: \n");
    scanf("%s",novatarefa.descricao);

    printf("Qual a prioridade: \n");
    scanf("%d",&novatarefa.prioriade);
    //

    // Contando o número de tarefas
    lt->tarefas[lt->qtd] = novatarefa;
    lt->qtd++;
    //

    // Indicação de Sucesso
    return 0;
    //
}



int deletarTarefa(ListaDeTarefas *lt){

    int resposta;

    // Mensagem para o usuário
    printf("Qual tarefa deseja deletar?\n");
    //

    // Scan para ver a resposta do usuario
    scanf("%d",&resposta);
    //

    // Verificar se o número fornecido é válido
    if (resposta >= 0 && resposta < lt->qtd) {
        // Remover a tarefa da lista
        for (int i = resposta; i < lt->qtd - 1; i++) {
            lt->tarefas[i] = lt->tarefas[i + 1];
        }
        lt->qtd--;
        printf("Tarefa excluida com sucesso!\n");
    } if (resposta == 221){
        lt->qtd=0;
    } else {
        printf("Numero de tarefa invalido. Nenhuma tarefa foi excluida.\n");
    }
    // Código para deletar todas as tarefas de uma vez


    // Indicação de Sucesso
    return 0;
    //
}
int listarTarefas(ListaDeTarefas lt){
    int i = 0;

    // Mensagem para o usuário
    printf("Tarefas cadastradas: \n");
    //

    printf("lt.qtd: %d\n", lt.qtd);


    //Loop de repetição para leitura de cada Tarefa dentro da ListaDeTarefas no endereço lt
    while (i<lt.qtd){
        printf("%d. Categoria: %s\n",i, lt.tarefas[i].categoria);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Prioridade: %d\n", lt.tarefas[i].prioriade);

        i++;
    }
    //

    // Indicação de Sucesso
    return 0;
    //
}

void printMenu(){
    printf("Menu:\n ");
    printf("1. Criar Tarefa\n ");
    printf("2. Deletar Tarefa\n ");
    printf("3. Listar Tarefas\n ");

}
int salvarLista(ListaDeTarefas lt, char nome[]){

    // Abrindo o arquivo como write
    FILE *f= fopen("arquivo.bin", "wb");
    //

    if(f==NULL){
        return 1;
    }
    // Escrevendo a lista atualizada no arquivo
    fwrite(&lt, sizeof(ListaDeTarefas), 1, f);
    //

    // Fechando o arquivo
    fclose(f);
    //

    // Indicação de Sucesso
    return 0;}
//

int carregarLista(ListaDeTarefas *lt,char nome[]){

    // Abrindo o arquivo como read
    FILE *f = fopen("arquivo.bin", "rb");
    //

    if(f==NULL)
        return 1;

    //Loop de repetição para leitura de cada Tarefa dentro da ListaDeTarefas no endereço de tarefalida
    fread(lt,sizeof(ListaDeTarefas),1,f);
    //

    //Fecha o arquivo
    fclose(f);
    //

    // Indicação de Sucesso
    return 0;}
//