#include "proj.h"
#include <stdio.h>
#include <string.h>


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

    int posicaoInserir = lt->qtd;

    // Ajuda do ChatGPT pq a categoria tava sendo pulada na hora do Input
    // Consumir o caractere de nova linha deixado no buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Pedindo Categoria, Descrição e Prioriade ao usuário e no Proj 3 andamento.
    printf("De uma Categoria a sua tarefa: \n");
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

    // Função para que as tarefas ja sejam colocadas em ordem de prioridade automaticamente
    // Para simplificar função de listar tarefas e export
    while (posicaoInserir > 0 && lt->tarefas[posicaoInserir - 1].prioridade < novatarefa.prioridade) {
        lt->tarefas[posicaoInserir] = lt->tarefas[posicaoInserir - 1];
        posicaoInserir--;
    }
    //

    // Contando o número de tarefas
    lt->tarefas[posicaoInserir] = novatarefa;
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
    int prioridadeescolhida;
    int estadoescolhido;
    int i = 0;
    int escolha;
    char categoriaescolhida[100];

    // Mensagem para o usuario
    printf("Deseja listar as tarefas com qual filtro?\n");
    printf("1 para filtrar por prioridade. \n");
    printf("2 para filtrar por estado. \n");
    printf("3 para filtrar por categoria. \n");
    printf("4 para filtrar por prioridade e categoria. \n");
    printf("5 para listar todas. \n");
    scanf("%d", &escolha);
    //

    // Switch para uma das 4 escolhas
    // Funciona pedindo a prioridade/categoria/estado e comparando se há alguma dessas dentro da lista
    // se houver, da print nas informações dessa tarefa.
    switch (escolha) {
        case 1:
            printf("Digite a prioridade que deve ser listada: ");
            scanf("%d", &prioridadeescolhida);
            while(i<lt.qtd){
                if(lt.tarefas[i].prioridade == prioridadeescolhida){
                    printf("Numero da Tarefa: %d\n", i);
                    printf("Categoria: %s", lt.tarefas[i].categoria);
                    printf("Descricao: %s", lt.tarefas[i].descricao);
                    printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                    printf("Estado: %d\n",lt.tarefas[i].estado);

                }
                i++;
            }
            break;
        case 2:
            printf("Digite o estado que deve ser listado: ");
            scanf("%d", &estadoescolhido);
            while(i<lt.qtd){
                if(lt.tarefas[i].estado == estadoescolhido){
                    printf("Numero da Tarefa: %d\n", i);
                    printf("Categoria: %s", lt.tarefas[i].categoria);
                    printf("Descricao: %s", lt.tarefas[i].descricao);
                    printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                    printf("Estado: %d\n",lt.tarefas[i].estado);
                }
                i++;
            }
            break;
        case 3:
            printf("Digite a categoria que deve ser listada: ");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            fgets(categoriaescolhida, sizeof (categoriaescolhida),stdin);
            while(i<lt.qtd){
                if (strcmp(lt.tarefas[i].categoria, categoriaescolhida) == 0){
                    printf("Numero da Tarefa: %d\n", i);
                    printf("Categoria: %s", lt.tarefas[i].categoria);
                    printf("Descricao: %s", lt.tarefas[i].descricao);
                    printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                    printf("Estado: %d\n",lt.tarefas[i].estado);
                }
                i++;
            }
            break;
        case 4:
            printf("Digite a categoria e prioridade que devem ser listados: ");
            printf("Categoria: \n");
            scanf("%s", &categoriaescolhida);
            printf("Prioridade: \n");
            scanf("%d", &prioridadeescolhida);
            while(i<lt.qtd){
                if (strcmp(lt.tarefas[i].categoria, categoriaescolhida) == 0 && lt.tarefas[i].prioridade == prioridadeescolhida){
                    printf("Numero da Tarefa: %d\n", i);
                    printf("Categoria: %s", lt.tarefas[i].categoria);
                    printf("Descricao: %s", lt.tarefas[i].descricao);
                    printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                    printf("Estado: %d\n",lt.tarefas[i].estado);
                }
                i++;
            }
            break;
        case 5:
            while(i<lt.qtd){
                    printf("Numero da Tarefa: %d\n", i);
                    printf("Categoria: %s", lt.tarefas[i].categoria);
                    printf("Descricao: %s", lt.tarefas[i].descricao);
                    printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                    printf("Estado: %d\n",lt.tarefas[i].estado);

                i++;
            }
            break;
    }
    return 0;
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

                    printf("Digite a nova prioridade (entre 0 e 10): ");
                    if (scanf("%d", &novaPrioridade) == 1 && novaPrioridade >= 0 && novaPrioridade <= 10) {
                        lt->tarefas[resposta].prioridade = novaPrioridade;
                        break; // Se a prioridade for válida, saia do loop
                    } else {
                        printf("Prioridade invalida. Deve ser um numero entre 0 e 10.\n");
                    }
                    break;
                }
                case 4: {
                    int novoandamento;

                    printf("Digite o novo andamento (1: completa, 2: em andamento, 3: nao iniciada): ");
                    if (scanf("%d", &novoandamento) == 1 && (novoandamento == 1 || novoandamento == 2 || novoandamento == 3)) {
                        lt->tarefas[resposta].estado = novoandamento;
                        break;
                    } else {
                        printf("Estado invalido. \n");
                    }
                    break;

                }

            }
        } while (escolha != 5); // Código de saída do do-while é 5
    } else {
        printf("Escolha uma opcao valida.\n");
    }

    return 1;
}

int exportarTarefa(ListaDeTarefas *lt) {
    int escolha;
    int prioridade;
    char categoria[100];

    printf("Como deseja exportar os arquivos: \n");
    printf("1. Por Prioridade\n");
    printf("2. Por Categoria\n");
    printf("3. Por Ambos\n");
    scanf("%d", &escolha);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);


    switch (escolha) {
        case 1:
            printf("Digite a Prioridade que deseja: \n");
            scanf("%d", &prioridade);
            exportarPorPrioridade(*lt, prioridade);
            break;
        case 2:
            printf("Digite a Categoria que deseja: \n");
            fgets(categoria,sizeof (categoria),stdin);
            exportarPorCategoria(*lt, categoria);
            break;
        case 3:
            printf("Digite a Categoria que deseja: \n");
            fgets(categoria,sizeof (categoria),stdin);
            printf("Digite a Prioridade que deseja: \n");
            scanf("%d", &prioridade);
            exportarPorPrioridadeECategoria(*lt, prioridade, categoria);
            break;
        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    return 0;
}




void printMenu(){
    printf("Menu:\n ");
    printf("1. Criar Tarefa\n ");
    printf("2. Deletar Tarefa\n ");
    printf("3. Listar Tarefas\n ");
    printf("4. Alterar Tarefa\n ");
    printf("5. Exportar Tarefas\n ");

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

void removerQuebrasDeLinha(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';  // Substitui a quebra de linha por terminador nulo
    }
}

void exportarPorPrioridade(ListaDeTarefas lt, int prioridade) {
    char nomeArquivo[] = "export_prioridade.txt";

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para exportacao");
        return;
    }

    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridade) {
            removerQuebrasDeLinha(lt.tarefas[i].categoria);
            removerQuebrasDeLinha(lt.tarefas[i].descricao);
            fprintf(arquivo, "Prioridade: %d; Categoria: %s; Estado: %d; Descricao: %s;\n", lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].estado, lt.tarefas[i].descricao);
        }
    }

    fclose(arquivo);
}


void exportarPorCategoria(ListaDeTarefas lt, char categoria[]) {
    char nomeArquivo[] = "export_categoria.txt";

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para exportacao");
        return;
    }

    // Escrevendo as tarefas com a categoria escolhida no arquivo
    for (int i = 0; i < lt.qtd; i++) {
        if (strcmp(lt.tarefas[i].categoria, categoria) == 0){
            removerQuebrasDeLinha(lt.tarefas[i].categoria);
            removerQuebrasDeLinha(lt.tarefas[i].descricao);
            fprintf(arquivo, "Prioridade: %d; Categoria: %s; Estado: %d; Descricao: %s;\n", lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].estado, lt.tarefas[i].descricao);
        }
    }

    // Fechando o arquivo
    fclose(arquivo);
}

void exportarPorPrioridadeECategoria(ListaDeTarefas lt, int prioridade, char categoria[]) {
    char nomeArquivo[] = "export_categoria_e_prioridade.txt";

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para exportacao");
        return;
    }

    // Escrevendo as tarefas com a prioridade e categoria escolhidas no arquivo
    for (int i = 0; i < lt.qtd; i++) {
        if (lt.tarefas[i].prioridade == prioridade && strcmp(lt.tarefas[i].categoria, categoria) == 0) {
            removerQuebrasDeLinha(lt.tarefas[i].categoria);
            removerQuebrasDeLinha(lt.tarefas[i].descricao);
            fprintf(arquivo, "Prioridade: %d; Categoria: %s; Estado: %d; Descricao: %s;\n", lt.tarefas[i].prioridade, lt.tarefas[i].categoria, lt.tarefas[i].estado, lt.tarefas[i].descricao);
        }
    }

    // Fechando o arquivo
    fclose(arquivo);
}