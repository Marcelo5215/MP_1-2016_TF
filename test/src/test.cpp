/**
* @file teste.cpp
* @brief Modulo que contem o Roteiro de Testes utilizado pelo programa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "gerenciador.h"
#include "gtest/gtest.h"

TEST(List_Tests, Creating){
	TipoLista* lista = criaLista();
	TipoLista* null = NULL;
	ASSERT_NE(null, lista);

	EXPECT_EQ(1, estaVazia(lista));
	EXPECT_EQ(0, tamanhoLista(lista));

	EXPECT_EQ(LISTA_OK, limpaLista(lista));
}

TEST(List_Tests, Inserting){
	TipoLista* lista = criaLista();
	TipoLista* null = NULL;
	Celula* null2 = NULL;
	ASSERT_NE(null, lista);

	//elemento auxiliar a ser inserido
	t_item AUX;
	AUX.ID = 1;

	//inserindo elementos, pode haver elementos repetidos
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	AUX.ID = 2;	
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	AUX.ID = 3;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));

	//buscando os elementos na lista
	EXPECT_NE(null2, buscaLista(lista, 1));
	EXPECT_NE(null2, buscaLista(lista, 2));
	//busca
	t_item test= buscaListaInd(lista, 0);
	EXPECT_EQ(1, test.ID);
	test= buscaListaInd(lista, 1);
	EXPECT_EQ(1, test.ID);
	test= buscaListaInd(lista, 2);
	EXPECT_EQ(2, test.ID);
	test= buscaListaInd(lista, 3);
	EXPECT_EQ(3, test.ID);
	//busca de um indice maior que o tamanho
	test= buscaListaInd(lista, 4);
	EXPECT_EQ(-1, test.ID);

	//verificando o tamanho
	EXPECT_EQ(4, tamanhoLista(lista));

	EXPECT_EQ(0, estaVazia(lista));	

	EXPECT_EQ(LISTA_OK, limpaLista(lista));
}

TEST(List_Tests, Removing){
	TipoLista* lista = criaLista();
	TipoLista* null = NULL;
	Celula* null2 = NULL;
	ASSERT_NE(null, lista);

	//elemento auxiliar a ser inserido
	t_item AUX;
	AUX.ID = 1;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	AUX.ID = 2;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	AUX.ID = 3;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	EXPECT_EQ(3, tamanhoLista(lista));

	//removendo e verificando se foi realemnte removido
	EXPECT_EQ(LISTA_OK, retiraLista(lista, buscaLista(lista, 1)));
	EXPECT_EQ(null2, buscaLista(lista, 1));
	EXPECT_EQ(2, tamanhoLista(lista));
	EXPECT_EQ(LISTA_ERR, retiraLista(lista, buscaLista(lista, 1)));


	EXPECT_EQ(LISTA_OK, retiraLista(lista, buscaLista(lista, 2)));
	EXPECT_EQ(null2, buscaLista(lista, 2));
	EXPECT_EQ(1, tamanhoLista(lista));
	EXPECT_EQ(LISTA_ERR, retiraLista(lista, buscaLista(lista, 2)));


	EXPECT_EQ(LISTA_OK, limpaLista(lista));
}

TEST(List_Tests, Editing){
	TipoLista* lista = criaLista();
	TipoLista* null = NULL;
	ASSERT_NE(null, lista);

	//elemento auxiliar a ser inserido
	t_item AUX;
	AUX.ID = 1;
	AUX.peso = 0;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	AUX.ID = 2;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));
	AUX.ID = 3;
	EXPECT_EQ(LISTA_OK, insereLista(lista, AUX));

	EXPECT_EQ(LISTA_OK, editaCelulaPeso(lista, 1, 9));
	EXPECT_EQ( 9, buscaListaInd(lista, 0).peso);
	EXPECT_EQ(LISTA_OK, editaCelulaPeso(lista, 2, 3));
	EXPECT_EQ( 3, buscaListaInd(lista, 1).peso);
	EXPECT_EQ(LISTA_OK, editaCelulaPeso(lista, 3, 4));
	EXPECT_EQ( 4, buscaListaInd(lista, 2).peso);


	EXPECT_EQ(LISTA_ERR, editaCelulaPeso(lista, 131, 0));
	EXPECT_EQ(LISTA_ERR, editaCelulaPeso(lista, 131, -1));


	EXPECT_EQ(LISTA_OK, limpaLista(lista));
}

void montaGrafoTeste(t_grafo* g);

TEST(Graph_Tests, Creating){
	t_grafo* g = criaGrafo();
	t_grafo* test = NULL;
	//verifica a criacao do grafo
	ASSERT_NE(test, g);

	//verifica a deslocacao
	EXPECT_EQ(GRAFO_ERR , limpaGrafo(test));
	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
}

TEST(Graph_Tests, Inserting){
	t_grafo* g = criaGrafo();
	t_grafo* test = NULL;
	ASSERT_NE(test, g);

	t_prop prop;
	prop.ID = 1;

	//vertices
	EXPECT_EQ(GRAFO_OK, insereVertice(g, prop));          //inserindo um vertice qualquer
	EXPECT_EQ(GRAFO_ERR, insereVertice(test, prop));      //inserindo um vertice qualquer em um grafo nulo
	EXPECT_EQ(GRAFO_ERR, insereVertice(test, prop));      //inserindo um vertice já existente
	//inserindo mais vertices
	prop.ID = 3;
	EXPECT_EQ(GRAFO_OK, insereVertice(g, prop));
	prop.ID = 4;
	EXPECT_EQ(GRAFO_OK, insereVertice(g, prop));
	prop.ID = 5;
	EXPECT_EQ(GRAFO_OK, insereVertice(g, prop));          

	//origens
	EXPECT_EQ(GRAFO_OK, insereOrigem(g, prop.ID));       //inserindo uma origem
	EXPECT_EQ(GRAFO_ERR, insereOrigem(g, prop.ID));       //inserindo uma origem que já existe
	prop.ID = 9;
	EXPECT_EQ(GRAFO_ERR, insereOrigem(g, prop.ID));      //inserindo uma origem que não existe como vertice
	EXPECT_EQ(GRAFO_ERR, insereOrigem(test, prop.ID));   //inserindo uma origem em um grafo nulo
	//arestas
	EXPECT_EQ(GRAFO_OK, insereAresta(g, 3, 4, 6));    //inserindo uma aresta normal
	EXPECT_EQ(GRAFO_ERR, insereAresta(g, 9, 4, 1));	  //inserindo uma aresta que não possui o vertice com ID 9 como origem
	EXPECT_EQ(GRAFO_ERR, insereAresta(g, 3, 9, 3));   //inserindo uma aresta que não possui o vertice 9 como dest
	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
}

TEST(Graph_Tests, Removing){
	t_grafo* g = criaGrafo();
	t_grafo* test = NULL;
	ASSERT_NE(test, g);

	montaGrafoTeste(g);

	//a partir do grafo de exemplo removeremos seus elementos
	EXPECT_EQ(GRAFO_ERR,retiraOrigem(test, 1));     //retira uma origem de um grafo nulo
	EXPECT_EQ(GRAFO_OK, retiraOrigem(g, 1));         //retira uma origem existente
	EXPECT_EQ(GRAFO_ERR,retiraOrigem(g, 9));        //retira uma origem inexistente 
	EXPECT_EQ(GRAFO_ERR,retiraOrigem(g, 6));        //retira uma origem inexistente mas é um vértice
	//arestas
	EXPECT_EQ(GRAFO_OK,retiraAresta(g, 1, 2));    //retira uma aresta existente
	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, 1, 9));   //retira uma aresta com um dos vertices inexistentes
	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, 9, 7));   //retira uma aresta completamente inexistente

	//vertices
	EXPECT_EQ(GRAFO_ERR,retiraVertice(test, 1));     //retira um vertice de um grafo nulo
	EXPECT_EQ(GRAFO_ERR,retiraVertice(g, 8));        //retira um vertice inexistente
	EXPECT_EQ(GRAFO_OK,retiraVertice(g, 1));         // retira um vertice existente
	EXPECT_EQ(GRAFO_OK,retiraVertice(g, 4));         // retira um vertice existente
    // ao retirar esse vertice, as arestas com ele presente também sao retiradas, assim se quisermos retirar alguma aresta ou origem com ele deve ser encontrado um erro
	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, 1, 3));      // verifica se a aresta 1 nao existe
	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, 3, 1));
	EXPECT_EQ(GRAFO_ERR,retiraOrigem(g, 1));         // retira origem 1 nao existe

	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
}

TEST(Graph_Tests, Tracks){
	t_grafo* g = criaGrafo();
	t_grafo* null = NULL;
	ASSERT_NE(null, g);

	montaGrafoTeste(g);

	//menores caminhos
	EXPECT_EQ(1, menorCaminho(g, 1, 3));
	EXPECT_EQ(1, menorCaminho(g, 1, 2));
	EXPECT_EQ(2, menorCaminho(g, 1, 4));
	EXPECT_EQ(3, menorCaminho(g, 5, 1));
	//vertices que nao sao conectados
	EXPECT_EQ(-1, menorCaminho(g, 6, 1));
	//vertices que n existam
	EXPECT_EQ(-1, menorCaminho(g, 9, 1));
	EXPECT_EQ(-1, menorCaminho(g, 1, 9));
	EXPECT_EQ(-1, menorCaminho(null, 6, 1));

	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
}

TEST(File_Tests, Reading){
	t_grafo *g = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;

	//testa a consistencia da funcao para uma string valida
	ASSERT_EQ(g0, leitura_arquivo((char*)NULL));
	ASSERT_NE(g0, g);
	EXPECT_EQ(GRAFO_OK, limpaGrafo(g));
}

TEST(File_Tests, Writing){
	t_grafo *g = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;

	//testa a consistencia da funcao para um grafo vazio
	ASSERT_EQ(MAN_ERR, escrita_arquivo(g0, (char*)"../test/src/saida.txt"));
	//testa a consistencia da funcao para uma string valida
	ASSERT_EQ(MAN_ERR, escrita_arquivo(g,(char*)NULL));
	//testa a funcao com casos validos
	ASSERT_NE(MAN_ERR, escrita_arquivo(g, (char*)"../test/src/saida.txt"));
	EXPECT_EQ(GRAFO_OK, limpaGrafo(g));
}

TEST(Manager, Inserting){
	t_grafo* tarefa = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;
	ASSERT_NE(g0, tarefa);

	EXPECT_EQ(MAN_ERR, insereTarefa(tarefa, (char*)"100 'oitava tarefa' 0 0 1 0"));  // inserindo tarefa com ID repetido
	EXPECT_EQ(MAN_OK, insereTarefa(tarefa, (char*)"103 'quarta tarefa' 1 1 1 1 105"));  // inserindo tarefa
	EXPECT_EQ(MAN_ERR, insereTarefa(g0, (char*)"103 'quarta tarefa' 1 1 1 1 105"));  // inserindo tarefa em um grafo nulo
	EXPECT_EQ(MAN_ERR, insereTarefa(tarefa, (char*)NULL));  // inserindo tarefa em uma string nula

	ASSERT_NE(MAN_ERR, escrita_arquivo(tarefa, (char*)"../test/src/saida.txt"));

	EXPECT_EQ(GRAFO_OK, limpaGrafo(tarefa));
}

TEST(Manager, Removing){
	t_grafo* tarefa = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;
	ASSERT_NE(g0, tarefa);

	EXPECT_EQ(MAN_OK, retiraTarefa(tarefa, 100));  // retirando tarefa
	EXPECT_EQ(MAN_ERR, retiraTarefa(tarefa, 100));  // retirando tarefa inexistente
	EXPECT_EQ(MAN_ERR, retiraTarefa(g0, 101));  // inserindo tarefa em uma string nula

	ASSERT_NE(MAN_ERR, escrita_arquivo(tarefa, (char*)"../test/src/saida.txt"));

	EXPECT_EQ(GRAFO_OK, limpaGrafo(tarefa));
}

TEST(Manager, Editing){
	t_grafo* tarefa = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;
	ASSERT_NE(g0, tarefa);

	EXPECT_EQ(MAN_OK, editaTarefa(tarefa, 101, (char*)"120 'vigesima tarefa' 20 0 8 0"));
	EXPECT_EQ(MAN_OK, editaTarefa(tarefa, 105, (char*)"112 'ola tarefa' 20 0 8 0"));
	EXPECT_EQ(MAN_ERR, editaTarefa(tarefa, 89, (char*)"100 'vigesima tarefa' 20 0 8 0")); // tentando modificar uma tarefa que nao existe
	EXPECT_EQ(MAN_ERR, editaTarefa(tarefa, 112, (char*)"120 'vigesima tarefa' 20 0 8 0"));  // tentando modificar a tarefa para uma ja existente
	

	ASSERT_NE(MAN_ERR, escrita_arquivo(tarefa, (char*)"../test/src/saida.txt"));

	EXPECT_EQ(GRAFO_OK, limpaGrafo(tarefa));
}

TEST(Manager, First_Born){
	t_grafo* g = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;

	TipoLista *l_atual, *l_concluidas;
    l_atual = criaLista();
    l_concluidas = criaLista();


	ASSERT_NE(g0, g);

	EXPECT_EQ(MAN_ERR, manager(g0, 5, l_atual, l_concluidas)); //grafo null
	EXPECT_EQ(MAN_ERR, manager(g, -1, l_atual, l_concluidas)); //tempo invalido
	EXPECT_EQ(MAN_ERR, manager(g, 5, (TipoLista*)NULL, l_concluidas)); //primeira lista null
	EXPECT_EQ(MAN_ERR, manager(g, 5, l_atual, (TipoLista*)NULL)); //segunda lista null
	EXPECT_EQ(MAN_OK, manager(g, 0, l_atual, l_concluidas)); //a partir de 0 eh valido
	limpaLista(l_atual); limpaLista(l_concluidas);
	l_atual = criaLista();
    l_concluidas = criaLista();
	EXPECT_EQ(MAN_OK, manager(g, 12, l_atual, l_concluidas)); //tempo normal
	limpaLista(l_atual); limpaLista(l_concluidas);
	EXPECT_EQ(GRAFO_OK, limpaGrafo(g));

}

TEST(Manager, Start_Man){
	EXPECT_EQ(MAN_OK, startMan());
}

TEST(Manager, Peso){
	t_grafo* g = leitura_arquivo((char*)"../test/src/entrada.txt");
	t_grafo *g0 = NULL;

	TipoLista *lista_concluida;
    lista_concluida = criaLista();
    ASSERT_NE(g0, g);
	EXPECT_EQ(0, get_maior_peso(g0, lista_concluida, 105));
	EXPECT_EQ(0, get_maior_peso(g, (TipoLista*)NULL, 105));
	EXPECT_EQ(0, get_maior_peso(g, lista_concluida, 109));
	EXPECT_EQ(0, get_maior_peso(g, lista_concluida, 100));
	EXPECT_EQ(7, get_maior_peso(g, lista_concluida, 105));

	EXPECT_EQ(LISTA_OK, limpaLista(lista_concluida));
	EXPECT_EQ(GRAFO_OK, limpaGrafo(g));

}

int main(int argc, char** argv){
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

//cria um grafo de teste
//como as funcoes utilizao o ID do vertice(tarefa), não usaremos outros campos para os testes além de ID
void montaGrafoTeste(t_grafo* g){
	t_prop prop;
	prop.ID = 1;
	//inserindo vertices 
	insereVertice(g, prop);
	prop.ID = 2;
	insereVertice(g, prop);
	prop.ID = 3;
	insereVertice(g, prop);
	prop.ID = 4;
	insereVertice(g, prop);
	prop.ID = 5;
	insereVertice(g, prop);
	prop.ID = 6;
	insereVertice(g, prop);
	//inserindo Origens
	insereOrigem(g, 1);
	insereOrigem(g, 2);
	insereOrigem(g, 5);  

	insereAresta(g, 1, 2, 1);
	insereAresta(g, 1, 3, 1);
	insereAresta(g, 3, 1, 1);
	insereAresta(g, 2, 4, 1);
	insereAresta(g, 3, 2, 1);
	insereAresta(g, 4, 3, 1);
	insereAresta(g, 5, 4, 1);
	insereAresta(g, 5, 6, 1);
	insereAresta(g, 6, 6, 1);
	insereArestaAnter(g, 1, 2, 1);
	insereArestaAnter(g, 1, 3, 1);
	insereArestaAnter(g, 3, 1, 1);
	insereArestaAnter(g, 2, 4, 1);
	insereArestaAnter(g, 3, 2, 1);
	insereArestaAnter(g, 4, 3, 1);
	insereArestaAnter(g, 5, 4, 1);
	insereArestaAnter(g, 5, 6, 1);
	insereArestaAnter(g, 6, 6, 1);
}