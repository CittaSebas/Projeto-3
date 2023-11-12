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

    // Ajuda do ChatGPT pq a categoria tava sendo pulada na hora do Input
    // Consumir o caractere de nova linha deixado no buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Pedindo Categoria, Descrição e Prioriade ao usuário e no Proj 3 andamento.
    printf("De um Nome a sua tarefa: \n");
    fgets(novatarefa.categoria, sizeof(novatarefa.categoria), stdin);

    printf("Descreva sua tarefa: \n");
    fgets(novatarefa.descricao, sizeof(novatarefa.descricao), stdin);


    printf("Qual a prioridade (de 0 a 10): \n");
    scanf("%d",&novatarefa.prioridade);

    printf("Qual o estado da tarefa (1: pronta, 2: trabalhando, 3: nao comecou)? \n");
    scanf("%d", &novatarefa.estado);
    //

    // Consumir o caractere de nova linha deixado no buffer
    while ((c = getchar()) != '\n' && c != EOF);
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

    } else {
        printf("Numero de tarefa invalido. Nenhuma tarefa foi excluida.\n");
    }
    if (resposta == 221) {
        lt->qtd = 0;
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

    //Loop de repetição para leitura de cada Tarefa dentro da ListaDeTarefas no endereço lt
    while (i<lt.qtd){

        printf("%d. Categoria: %s\n",i, lt.tarefas[i].categoria);
        printf("Descricao: %s", lt.tarefas[i].descricao);
        printf("Estado: %d", lt.tarefas[i].estado);
        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
        i++;
    }
    //

    // Indicação de Sucesso
    return 0;
    //
}

int alterarTarefa(ListaDeTarefas *lt){
// Inicialização da variável do pedido do usuário
    int resposta;

    printf("Qual tarefa deseja alterar? ");
    scanf("%d", &resposta);

    // Verificar se o número fornecido é válido
    if (resposta >= 0 && resposta < lt->qtd) {
        int escolha;

        do {
            // Loop contínuo até o usuário escolher sair
            printf("O que deseja alterar na tarefa %d?\n", resposta);
            printf("1. Categoria\n");
            printf("2. Descricao\n");
            printf("3. Prioridade\n");
            printf("4. Andamento\n");
            printf("5. Concluir\n");
            scanf("%d", &escolha);

            switch (escolha) {
                // Cases para as escolhas que o usuário pode tomar
                case 1:
                    printf("Digite a nova categoria: ");
                    scanf("%s", lt->tarefas[resposta].categoria);
                    break;
                case 2:
                    printf("Digite a nova descricao: ");
                    scanf("%s", lt->tarefas[resposta].descricao);
                    break;
                case 3: {
                    int novaPrioridade;
                    do {
                        printf("Digite a nova prioridade (entre 0 e 10): ");
                        if (scanf("%d", &novaPrioridade) == 1 && novaPrioridade >= 0 && novaPrioridade <= 10) {
                            lt->tarefas[resposta].prioridade = novaPrioridade;
                            break; // Se a prioridade for válida, saia do loop
                        } else {
                            printf("Prioridade invalida. Deve ser um numero entre 0 e 10.\n");
                        }
                    } while (1); // Loop infinito, sairá apenas quando a prioridade for válida
                    break;
                }
                case 4: {
                    int novoandamento;
                    do {
                        printf("Digite o novo andamento (1: completa, 2: em andamento, 3: nao iniciada): ");
                        if (scanf("%d", &novoandamento) == 1 && (novoandamento == 1 || novoandamento == 2 || novoandamento == 3)) {
                            lt->tarefas[resposta].estado = novoandamento;
                            break;
                        } else {
                            printf("Estado invalido. \n");
                        }
                    } while (1);
                    break;
                }
                case 5:
                    printf("Alteracoes feitas.\n");
                    break;
                default:
                    printf("Opçao nao encontrada.\n");
            }
        } while (escolha != 5); // Código de saída do do-while é 5
    } else {
        printf("Escolha uma tarefa valida.\n");
    }

    return 1;
}



void printMenu(){
    printf("Menu:\n ");
    printf("1. Criar Tarefa\n ");
    printf("2. Deletar Tarefa\n ");
    printf("3. Listar Tarefas\n ");
    printf("4. Alterar Tarefa\n");

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