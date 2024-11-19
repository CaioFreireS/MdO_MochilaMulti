#ifndef PMM_H_INCLUDED
#define PMM_H_INCLUDED

#define MAX_OBJ 500
#define MAX_MOC 50

const int ALFA = 10;
const int BETA = 100;


typedef struct tSolucao
{
    int vet_sol[MAX_OBJ];
    int fo;
}Solucao;


typedef struct tSolucaoBIN
{
    int mat_sol[MAX_MOC][MAX_OBJ];
    int fo;
}SolucaoBIN;


// Dados de entrada
int num_obj;
int num_moc;
int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];
// Estruturas auxiliares
int vet_uso_moc[MAX_MOC];
int vet_qtd_obj[MAX_OBJ];
int vet_ind_ord_obj[MAX_OBJ];


void testar_construtivas();


void ordenar_objetos();
void heu_cons_gulosa(Solucao& s);
void testar_estruturas();

void calc_fo_solucao(Solucao& s);
void escrever_solucao(Solucao& s);
void heu_cons_aleatoria(Solucao& s);

void calc_fo_solucaoBIN(SolucaoBIN& s);
void escrever_solucaoBIN(SolucaoBIN& s);
void criar_solucaoBIN(SolucaoBIN& s);

void testar_dados(char* arq);
void ler_dados(char* arq);
void testar_alocacao();

#endif // PMM_H_INCLUDED
