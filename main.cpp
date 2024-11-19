#include <iostream>
#include <time.h>
#include <memory.h>

#include "pmm.h"

#define MAX(X,Y) ((X > Y) ? X : Y)


using namespace std;

int main()
{
    //srand(time(NULL));


    char arq[50];
    //testar_alocacao();


    ler_dados("pmm3.txt");
    //testar_dados("");

    //SolucaoBIN sBIN;
    //criar_solucaoBIN(sBIN);

    //sBIN.mat_sol[0][3] = 1;

    //calc_fo_solucaoBIN(sBIN);
    //escrever_solucaoBIN(sBIN);

    //testar_estruturas();


    ordenar_objetos();

    testar_construtivas();

    //printf("\n");
    //for (int j = 0; j < num_obj; j++)
    //    printf("%d  ", vet_ind_ord_obj[j]);



    return 0;
}


void testar_construtivas()
{
    Solucao sa, sg;

    heu_cons_aleatoria(sa);
    calc_fo_solucao(sa);
    escrever_solucao(sa);

    heu_cons_gulosa(sg);
    calc_fo_solucao(sg);
    escrever_solucao(sg);

}


void heu_cons_gulosa(Solucao& s)
{
    memset(&vet_uso_moc, 0, sizeof(vet_uso_moc));
    memset(&s.vet_sol, -1, sizeof(s.vet_sol));
    for (int j = 0; j < num_obj; j++)
        for (int i = 0; i < num_moc; i++)
            if (vet_uso_moc[i] + vet_pes_obj[vet_ind_ord_obj[j]] <= vet_cap_moc[i])
            {
                s.vet_sol[vet_ind_ord_obj[j]] = i;
                vet_uso_moc[i] += vet_pes_obj[vet_ind_ord_obj[j]];
                break;
            }
}


void ordenar_objetos()
{
    int flag, aux;
    for (int i = 0; i < num_obj; i++)
        vet_ind_ord_obj[i] = i;
    flag = 1;
    while(flag)
    {
        flag = 0;
        for (int i = 0; i < num_obj - 1; i++)
        {
            if ((double)vet_val_obj[vet_ind_ord_obj[i]]/vet_pes_obj[vet_ind_ord_obj[i]] <
                (double)vet_val_obj[vet_ind_ord_obj[i+1]]/vet_pes_obj[vet_ind_ord_obj[i+1]])
            {
                flag = 1;
                aux = vet_ind_ord_obj[i];
                vet_ind_ord_obj[i] = vet_ind_ord_obj[i+1];
                vet_ind_ord_obj[i+1] = aux;
            }
        }
    }
}





void testar_estruturas()
{
    clock_t h;
    SolucaoBIN sb;
    Solucao s;
    double tempo;

    const int repeticoes = 100000;

    h = clock();
    for (int r = 0; r < repeticoes; r++)
        criar_solucaoBIN(sb);
    h = clock() - h;
    tempo = (double)h/CLOCKS_PER_SEC;
    printf("\nCriar solucao BIN: %.5f", tempo);

    h = clock();
    for (int r = 0; r < repeticoes; r++)
        heu_cons_aleatoria(s);
    h = clock() - h;
    tempo = (double)h/CLOCKS_PER_SEC;
    printf("\nCriar solucao: %.5f", tempo);


    h = clock();
    for (int r = 0; r < repeticoes; r++)
        calc_fo_solucaoBIN(sb);
    h = clock() - h;
    tempo = (double)h/CLOCKS_PER_SEC;
    printf("\ncalcular FO BIN: %.5f", tempo);

    h = clock();
    for (int r = 0; r < repeticoes; r++)
        calc_fo_solucao(s);
    h = clock() - h;
    tempo = (double)h/CLOCKS_PER_SEC;
    printf("\nCalcular FO: %.5f", tempo);

}



void calc_fo_solucao(Solucao& s)
{
    memset(&vet_uso_moc, 0, sizeof(vet_uso_moc));
    s.fo = 0;
    for (int j = 0; j < num_obj; j++)
    {
        if (s.vet_sol[j] != -1)
        {
            s.fo += vet_val_obj[j];
            vet_uso_moc[s.vet_sol[j]] += vet_pes_obj[j];
        }
    }
    for (int i = 0; i < num_moc; i++)
        s.fo -= ALFA * MAX(0, vet_uso_moc[i] - vet_cap_moc[i]);
}

void escrever_solucao(Solucao& s)
{
    printf("\nFO: %d\n", s.fo);
    for (int j = 0; j < num_obj; j++)
        printf("%d ", s.vet_sol[j]);
}

void heu_cons_aleatoria(Solucao& s)
{
    for (int j = 0; j < num_obj; j++)
        s.vet_sol[j] = (rand() % (num_moc+1)) - 1;
}


void calc_fo_solucaoBIN(SolucaoBIN& s)
{
    memset(&vet_uso_moc, 0, sizeof(vet_uso_moc));
    memset(&vet_qtd_obj, 0, sizeof(vet_qtd_obj));
    s.fo = 0;
    for (int i = 0; i < num_moc; i++)
        for (int j = 0; j < num_obj; j++)
        {
            //if (s.mat_sol[i][j] == 1)
            //    s.fo += vet_val_obj[j];
            s.fo += vet_val_obj[j] * s.mat_sol[i][j];
            vet_uso_moc[i] += vet_pes_obj[j] * s.mat_sol[i][j];
            vet_qtd_obj[j] += s.mat_sol[i][j];
        }
    for (int i = 0; i < num_moc; i++)
        //if (vet_uso_moc[i] > vet_cap_moc[i])
        //    s.fo -= ALFA * (vet_uso_moc[i] - vet_cap_moc[i]);
        s.fo -= ALFA * MAX(0, vet_uso_moc[i] - vet_cap_moc[i]);
    for (int i = 0; i < num_obj; i++)
        //if (vet_qtd_obj[i] > 1)
        //    s.fo -= BETA * (vet_qtd_obj[i] - 1);
        s.fo -= BETA * MAX(0, vet_qtd_obj[i] - 1);

       /*
    printf("\n\n");
    for (int i = 0; i < num_moc; i++)
        printf("%d  ", vet_uso_moc[i]);

    printf("\n\n");
    for (int i = 0; i < num_obj; i++)
        printf("%d  ", vet_qtd_obj[i]);*/

}


void escrever_solucaoBIN(SolucaoBIN& s)
{
    printf("FO: %d\n", s.fo);
    for (int i = 0; i < num_moc; i++)
    {
        for (int j = 0; j < num_obj; j++)
            printf("%d ", s.mat_sol[i][j]);
        printf("\n");
    }
}

void criar_solucaoBIN(SolucaoBIN& s)
{
    for (int i = 0; i < num_moc; i++)
        for (int j = 0; j < num_obj; j++)
            s.mat_sol[i][j] = rand() % 2;
}












void testar_dados(char* arq)
{
    FILE* f;
    if (arq == "")
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d %d\n", num_obj, num_moc);
    for (int i = 0; i < num_obj; i++)
        fprintf(f, "%d ", vet_val_obj[i]);
    fprintf(f, "\n");
    for (int i = 0; i < num_obj; i++)
        fprintf(f, "%d ", vet_pes_obj[i]);
    fprintf(f, "\n");
    for (int i = 0; i < num_moc; i++)
        fprintf(f, "%d ", vet_cap_moc[i]);
    if (arq != "")
        fclose(f);
}


void ler_dados(char* arq)
{
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_obj, &num_moc);
    for (int i = 0; i < num_obj; i++)
        fscanf(f, "%d", &vet_val_obj[i]);
    for (int i = 0; i < num_obj; i++)
        fscanf(f, "%d", &vet_pes_obj[i]);
    for (int i = 0; i < num_moc; i++)
        fscanf(f, "%d", &vet_cap_moc[i]);
    fclose(f);
}



void testar_alocacao()
{
    const int tamanho = 5;
    const int repeticoes = 1000;

    clock_t h;
    double tempo;

    int** mat_dinamica;
    int mat_estatica[tamanho][tamanho];

    h = clock();
    for (int r = 0; r < repeticoes; r++)
    {
        mat_dinamica = (int**)malloc(sizeof(int*)*tamanho);
        for (int i = 0; i < tamanho; i++)
            mat_dinamica[i] = (int*)malloc(sizeof(int)*tamanho);
        for (int i = 0; i < tamanho; i++)
            free(mat_dinamica[i]);
        free(mat_dinamica);
    }
    h = clock() - h;
    tempo = (double)h / CLOCKS_PER_SEC;
    printf("Tempo malloc %.5f segundos!\n", tempo);


    h = clock();
    for (int r = 0; r < repeticoes; r++)
    {
        mat_dinamica = new int*[tamanho];
        for (int i = 0; i < tamanho; i++)
            mat_dinamica[i] = new int[tamanho];
        for (int i = 0; i < tamanho; i++)
            delete[] mat_dinamica[i];
        delete[] mat_dinamica;
    }
    h = clock() - h;
    tempo = (double)h / CLOCKS_PER_SEC;
    printf("Tempo new %.5f segundos!\n", tempo);



    h = clock();
    for (int r = 0; r < repeticoes; r++)
    {
        for (int i = 0; i < tamanho; i++)
            for (int j = 0; j < tamanho; j++)
                mat_estatica[i][j] = 0;
    }
    h = clock() - h;
    tempo = (double)h / CLOCKS_PER_SEC;
    printf("Tempo zerar for %.5f segundos!\n", tempo);


    h = clock();
    for (int r = 0; r < repeticoes; r++)
        memset(&mat_estatica, 0, sizeof(mat_estatica));
    h = clock() - h;
    tempo = (double)h / CLOCKS_PER_SEC;
    printf("Tempo memset for %.5f segundos!\n", tempo);


    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
            printf("%d  ", mat_estatica[i][j]);
        printf("\n");
    }

}
