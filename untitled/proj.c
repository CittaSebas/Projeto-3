#include "proj.h"
#include <stdio.h>

// Função de Criar Tarefas
// No Proj 3. Foi agregado estado da tarefa. Por isso também a mudança no Struct do Proj.h
//
int criarTarefa(ListaDeTarefas *lt){

    // Abrindo o arquivo
    FILE *f = fopen("arquivo.bin", "ab");
    //

    // Se o Arquivo não é encontrado retorna um código de erro
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    //

    // Struct
    Tarefa novatarefa;
    //

    // Verificação de Limite
    if (lt->qtd >= 100){
        printf("Limite maximo de tarefas atingido, delete uma antes de continuar\n");
        fclose(f);
        return 1;
    }
    //

    // Pedindo Categoria, Descrição e Prioriade ao usuário e no Proj 3 andamento.
    printf("Escreva sua tarefa: \n");
    fgets(novatarefa.categoria, sizeof(novatarefa.categoria), stdin);

    printf("Descreva sua tarefa: \n");
    fgets(novatarefa.descricao, sizeof(novatarefa.descricao), stdin);

    while(novatarefa.prioridade>10 || novatarefa.prioridade<0){

        printf("Qual a prioridade(de 0 a 10): \n");
        scanf("%d",&novatarefa.prioridade);
    }
    printf("Qual o andamento da tarefa (1: completa, 2: em andamento, 3: nao inciado)? \n");
    fflush(stdin);
    scanf("%d", &novatarefa.estado);
    //

    // Contando o número de tarefas
    lt->tarefas[lt->qtd] = novatarefa;
    lt->qtd++;
    //

    // Indicação de Sucesso
    return 0;
    //
}


// Função para deletar tarefas, não muda no Proj 3.
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

int alterarTarefa(ListaDeTarefas *lt){

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