#include <stdlib.h>
#include <stdio.h>
#include "carregar_grafo.h"
#define limite_peso 9999
typedef struct arestas_minimas
{
    int origen;
    int destino;
    int peso;
}arestas_minimas;

typedef struct rota
{
    int pesototal; // pesotal gasto para visitar os clientes
    int toltal_entregue; // toltal de produstos entrege durante essa rota
    int * clientes_visitados; // array de clientes que foram visitados durante essa rota
    int total_de_clientes_visitado;
}rota;

arestas_minimas * caminho(grafo_solucao grafo);
rota gerar_rotas(arestas_minimas * arestas,grafo_solucao grafo);
void remover_clientes_visitados_grafo(grafo_solucao grafo,rota rota1);

int main(){

    char nome_arquivo[] = "instancia1.txt";

    grafo_solucao grafo1 = carregar_grafo(nome_arquivo); // carrega os dados do arquivo

    rota * rotas = (rota*) malloc(grafo1.numero_veiculos*sizeof(rota)); // o numero de rotas se o numero de veiculos disponiveis    

    for(int i =0;i<grafo1.numero_veiculos;i++){
        arestas_minimas *arestas_minimas;
        arestas_minimas = caminho(grafo1);
        rotas[i] = gerar_rotas(arestas_minimas,grafo1);
        remover_clientes_visitados_grafo(grafo1,rotas[i]);
        
    }

}

rota gerar_rotas(arestas_minimas *arestas, grafo_solucao grafo) {
    int capacidade_maxima = grafo.capcacidade_carga_carro;
    int prox_vert;
    int peso_total_rota = 0;

    prox_vert = arestas[0].destino;
    peso_total_rota += arestas[0].peso;

    int soma_total_entregado = grafo.demanda_de_cliente[prox_vert - 1];

    int *clientes_visitados = (int *)malloc(sizeof(int));
    clientes_visitados[0] = prox_vert;
    int total_de_clientes_visitados = 1;

    for (int i = 1; i < grafo.n_entregra; i++) {
        if (arestas[i].origen == prox_vert) {
            prox_vert = arestas[i].destino;
            int demanda_cliente = grafo.demanda_de_cliente[prox_vert - 1];

            if (soma_total_entregado + demanda_cliente > capacidade_maxima) {
                break;
            }

            clientes_visitados = (int *)realloc(clientes_visitados, (total_de_clientes_visitados + 1) * sizeof(int));
            clientes_visitados[total_de_clientes_visitados] = prox_vert;
            total_de_clientes_visitados++;

            peso_total_rota += arestas[i].peso;
            soma_total_entregado += demanda_cliente;
        }
    }

    rota rota_atual;

    rota_atual.pesototal = peso_total_rota;
    rota_atual.toltal_entregue = soma_total_entregado;
    rota_atual.clientes_visitados = clientes_visitados;
    rota_atual.total_de_clientes_visitado = total_de_clientes_visitados;
    
    int ultimo_cliente = clientes_visitados[total_de_clientes_visitados-1];

    //rota_atual.pesototal += grafo.matriz_custo[ultimo_cliente][0]; // calcular peso do ultimo cliente visitado de volta para o deposito
    return rota_atual;
}
arestas_minimas * caminho(grafo_solucao grafo){
    int menor_peso = 0;
    int visitados[grafo.num_ver-1];
    arestas_minimas* lista_de_arestas = (arestas_minimas*)malloc(grafo.num_ver * sizeof(arestas_minimas));

    for (int i = 0; i < grafo.num_ver-1; i++){
        visitados[i] = 0; // preenche todo vetor marcando todos os vertices como nao visitados
        int count =0;
    }
    for (int i = 0; i < grafo.num_ver-1; i++) // i = origen , j detino
    {
        int passado;
        visitados[i]=1;
        menor_peso = limite_peso;
        int vertice_de_menor_peso;
        for (int j = 0; j < grafo.num_ver; j++)
        {
            if (grafo.matriz_custo[i][j] != 0 && grafo.matriz_custo[i][j]<menor_peso ){ 

                if (visitados[j]!=1) // verifica se o vertice atual ja foi visitado
                {
                    menor_peso = grafo.matriz_custo[i][j];
                    vertice_de_menor_peso = j;
                }
            }
        }
        if(menor_peso != limite_peso){
            lista_de_arestas[i].origen = i;
            lista_de_arestas[i].destino = vertice_de_menor_peso;
            lista_de_arestas[i].peso = menor_peso;
            /*printf("%d->",lista_de_arestas[i].origen);
            printf("%d",lista_de_arestas[i].destino);
            printf(" peso = %d \n",lista_de_arestas[i].peso);*/
        }
   }
   return lista_de_arestas;

}
void remover_clientes_visitados_grafo(grafo_solucao grafo,rota rota1){
    for(int i =0;i<rota1.total_de_clientes_visitado;i++){
        for(int j=0;j<grafo.num_ver;j++){
            int indice = rota1.clientes_visitados[i];
            grafo.matriz_custo[indice][j] = 0;
            grafo.matriz_custo[j][indice] = 0;
        }
    }

}
