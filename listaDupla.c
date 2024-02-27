#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

typedef struct noAluno{

    int matricula;
    char nome[50];
    struct noAluno *proxNo;
    struct noAluno *antNo;

}aluno;

typedef struct noMateria{

    int codigo;
    char nome[15];
    int quantAluno;
    int quantMax;
    struct noMateria* proxNo;
    aluno *inicio;
    aluno *fim;

} materia;


typedef struct lista{
    materia *inicio;
    materia *fim;
    int quantidade;
} listaMaterias;

void inicializarMateria(materia *Materia){
    Materia->fim = NULL;
    Materia->inicio = NULL;
    Materia->quantAluno = 0;
}

void inicializarAluno(aluno *Aluno){
    Aluno -> proxNo = NULL;
    Aluno -> antNo = NULL;
}

void inicializarListaMaterias(listaMaterias *ListaMaterias){
    ListaMaterias -> fim = NULL;
    ListaMaterias -> inicio = NULL;
    ListaMaterias -> quantidade = 0;
}

int inserirMateria(listaMaterias *lista){

    materia *novaMat = malloc(sizeof(materia));

    if(novaMat==NULL)
    {
        printf("Erro de memória!");
        return 1;
    }

    inicializarMateria(novaMat);

    printf("Digite o código da turma: ");
    fflush(stdin);
    scanf("%d",&novaMat -> codigo);
    fflush(stdin);

    printf("Digite o nome da turma: ");
    fflush(stdin);
    gets(novaMat -> nome);
    fflush(stdin);

    printf("Digite a quantidade máxima de alunos da turma: ");
    fflush(stdin);
    scanf("%d",&novaMat -> quantMax);
    fflush(stdin);

    novaMat->proxNo = lista -> inicio;
    lista -> inicio = novaMat;
    lista -> quantidade++;
    if(lista->inicio!=NULL){
        lista->fim = novaMat;
    }
    printf("Disciplina adicionada com sucesso");

    return 0;
}

int inserirAluno(listaMaterias *lista, materia *Materia){

    if(Materia->quantAluno < Materia->quantMax){

        aluno *novoAluno = malloc(sizeof(aluno));

        if(novoAluno==NULL)
        {
            printf("Erro de memória!");
            return 0;
        }

        inicializarAluno(novoAluno);

        printf("Digite a matrícula do aluno: ");
        fflush(stdin);
        scanf("%d",&novoAluno -> matricula);
        fflush(stdin);

        printf("Digite o nome do aluno: ");
        fflush(stdin);
        gets(novoAluno -> nome);
        fflush(stdin);

        novoAluno->antNo = NULL;
        if(Materia->inicio!=NULL){
            novoAluno->proxNo = Materia->inicio;
            Materia->inicio->antNo = novoAluno;
        }else{
            Materia->fim = novoAluno;
        }
        Materia->inicio = novoAluno;
        Materia->quantAluno++;
        printf("Aluno adicionado com sucesso\n");
        return 1;

    }else{
        printf("Turma cheia");
        return 0;
    }
}

void removerDisciplinaDoInicio(listaMaterias *lista){
    if(lista->quantidade > 0){
        materia *disciplinaRemovida = lista->inicio;
        lista->inicio = disciplinaRemovida->proxNo;
        free(disciplinaRemovida);
        disciplinaRemovida = NULL;
        lista->quantidade--;
    } else{
        printf("Lista vazia");
    }
}

void destruirListaDeDisciplinas(listaMaterias *lista){
    while(lista-> inicio != NULL){
        removerDisciplinaDoInicio(lista);
    }
}

void removerAlunoDisciplina(materia *Materia,int matriculaAluno){
    aluno *aluno = Materia-> inicio;

    while(aluno != NULL ){

        if(aluno->matricula != matriculaAluno)
            aluno = aluno->proxNo;
        else{
            if(aluno==Materia->inicio){

                Materia->inicio= aluno->proxNo;
                aluno->proxNo->antNo=NULL;

            }else
                if(aluno==Materia->fim){

                    Materia->fim = aluno->antNo;
                    aluno->antNo->proxNo=NULL;

                }else{

                    aluno->antNo->proxNo = aluno->proxNo;
                    aluno->proxNo->antNo= aluno->antNo;

                }
                Materia->quantAluno--;
                free(aluno);
                aluno=NULL;
                printf("Aluno removido com sucesso\n");
                return;

            }
        }

        printf("Não achamos o aluno");
}

void listarMaterias(listaMaterias *lista){
    if(lista -> quantidade > 0){
        materia *materia = lista -> inicio;
        while(materia != NULL){
            printf("\nCodigo: %d\n", materia->codigo);
            printf("Nome: %s\n", materia->nome);
            printf("Quantidade de alunos: %d\n", materia->quantAluno);
            printf("Quantidade maxima de alunos: %d\n", materia->quantMax);
            printf("-----------------------\n");
            materia = materia->proxNo;
        }
    }else{
        printf("Lista vazia");
    }
}

materia* materiaEscolhida(listaMaterias *lista, int codigo){
    if(lista -> quantidade > 0){
        materia *materia = lista -> inicio;
        while(materia != NULL){

            if(materia->codigo == codigo){


                return materia;

            }

            materia=materia->proxNo;

        }
        return NULL;
    }else{
        printf("Lista vazia");
        return NULL;
    }
}

void listarAlunosMateria(materia *Materia){
    if(Materia->quantAluno > 0){
        aluno *aluno = Materia->inicio;
        while(aluno != NULL){
            printf("\nMatrícula: %d", aluno->matricula);
            printf("\nNome: %s", aluno->nome);
            printf("\n-----------------------");
            aluno = aluno->proxNo;
        }
    }else{
        printf("Nenhum aluno cadastrado na matéria");
    }
}



int main(){

    setlocale(LC_ALL,"portuguese");

    listaMaterias listaMat;
    int aux,op;
    inicializarListaMaterias(&listaMat);

    do{

        printf("\n---------Menu--------");
        printf("\n\n1 - Adicionar matéria\n");
        printf("2 - Adicionar aluno na matéria\n");
        printf("3 - Remover aluno da matéria\n");
        printf("4 - Remover matéria do início\n");
        printf("5 - Destruir a lista de matéria\n");
        printf("6 - Listar matérias \n");
        printf("7 - Listar a lista de alunos de uma matéria\n");
        printf("0 - Sair do programa\n");
        printf("\nEscolha uma opção:");

        fflush(stdin);
        scanf("%d",&op);
        fflush(stdin);
        system("cls");

        switch(op){

            case 0:

                printf("Obrigado por usar nosso programa!");

            break;

            case 1:

                inserirMateria(&listaMat);

            break;

            case 2:
            {
                int cod;
                listarMaterias(&listaMat);
                printf("Digite o código da matéria que você deseja adicionar o aluno:");
                fflush(stdin);
                scanf("%d",&cod);
                materia *matEsc = materiaEscolhida(&listaMat,cod);
                if(matEsc==NULL){

                    printf("Código inválido");

                }else{

                    inserirAluno(&listaMat,matEsc);
                    fflush(stdin);

                }
            }
            break;

            case 3:
            {
                int cod,matricula;
                listarMaterias(&listaMat);
                printf("Digite o código da matéria que você deseja remover o aluno:");
                fflush(stdin);
                scanf("%d",&cod);
                fflush(stdin);
                materia *matEsc = materiaEscolhida(&listaMat,cod);
                if(matEsc==NULL){

                    printf("Código inválido");

                }else{

                    printf("Digite a matrícula do aluno:");
                    fflush(stdin);
                    scanf("%d",&matricula);
                    fflush(stdin);

                    removerAlunoDisciplina(matEsc,matricula);

                }
            }
            break;

            case 4:
                removerDisciplinaDoInicio(&listaMat);
                fflush(stdin);

            break;

            case 5:
                destruirListaDeDisciplinas(&listaMat);
                fflush(stdin);
            break;

            case 6:

                listarMaterias(&listaMat);
            break;

            case 7:

            {
                int cod;
                listarMaterias(&listaMat);
                printf("Digite o código da matéria que você deseja listar os alunos:");
                fflush(stdin);
                scanf("%d",&cod);
                fflush(stdin);
                materia *matEsc = materiaEscolhida(&listaMat,cod);
                if(matEsc==NULL){

                    printf("Código inválido");

                }else{

                    listarAlunosMateria(matEsc);

                }
            }

            break;

            default:

                printf("Opção inválida");

            break;

        }

    }while (op!=0);
}
