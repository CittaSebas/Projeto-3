typedef struct {
    int prioridade;
    char categoria[100];
    char descricao[300];
    int estado;
} Tarefa;

typedef struct {
    Tarefa tarefas[100];
    int qtd;
} ListaDeTarefas;

int criarTarefa(ListaDeTarefas *lt);
int deletarTarefa(ListaDeTarefas *lt);
int listarTarefas(ListaDeTarefas lt);
int alterarTarefa(ListaDeTarefas *lt);
int exportarTarefa(ListaDeTarefas *lt);
void exportarPorPrioridade(ListaDeTarefas lt, int prioridade);
void exportarPorCategoria(ListaDeTarefas lt, char categoria[]);
void exportarPorPrioridadeECategoria(ListaDeTarefas lt, int prioridade, char categoria[]);
void removerQuebrasDeLinha(char *str);

void printMenu();
int salvarLista(ListaDeTarefas lt,char nome[]);
int carregarLista(ListaDeTarefas *lt, char nome[]);