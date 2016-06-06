#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
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

	//buscando os elementos na lista
	EXPECT_NE(null2, buscaLista(lista, 1));
	EXPECT_NE(null2, buscaLista(lista, 2));

	//verificando o tamanho
	EXPECT_EQ(3, tamanhoLista(lista));

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

// TEST(Graph_Tests, Tracks){
// 	t_grafo* g = criaGrafoArq((char*)"entrada.txt");
// 	t_grafo* test = NULL;
// 	ASSERT_NE(test, g);

// 	//caminhos possiveis com origens
// 	EXPECT_EQ(3.0, percursoEntre(g, (char*)"U", (char*)"X"));
// 	EXPECT_EQ(2.0, percursoEntre(g, (char*)"U", (char*)"Y"));
// 	EXPECT_EQ(1.0, percursoEntre(g, (char*)"U", (char*)"V"));
// 	EXPECT_EQ(2.0, percursoEntre(g, (char*)"V", (char*)"X"));
// 	EXPECT_EQ(1.0, percursoEntre(g, (char*)"V", (char*)"Y"));
// 	EXPECT_EQ(1.0, percursoEntre(g, (char*)"W", (char*)"Z"));
// 	EXPECT_EQ(3.0, percursoEntre(g, (char*)"W", (char*)"V"));
// 	//caminhos que devem falhar
// 	//não é possivel chegar em U a partir de outro vertices
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"W", (char*)"U"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"V", (char*)"U"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"X", (char*)"U"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"Y", (char*)"U"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"Z", (char*)"U"));
// 	//não é possivel chegar em X a partir de outro vertices
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"X", (char*)"W"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"U", (char*)"W"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"Z", (char*)"W"));
// 	//caminhos com vertices inexistentes
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"G", (char*)"X"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"Y", (char*)"P"));
// 	EXPECT_EQ(-1.0, percursoEntre(g, (char*)"HJK", (char*)"9"));

// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));

// 	t_grafo* g1 = criaGrafoArq((char*)"entrada1.txt");
// 	ASSERT_NE(test, g1);
// 	EXPECT_EQ(7.0, percursoEntre(g, (char*)"A", (char*)"C"));
// 	EXPECT_EQ(4.0, percursoEntre(g, (char*)"A", (char*)"B"));
// 	EXPECT_EQ(3.0, percursoEntre(g, (char*)"B", (char*)"C"));
// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g1));
// }

// TEST(Graph_Tests, Writing){
// 	t_grafo* g = criaGrafoArq((char*)"entrada.txt");
// 	t_grafo* test = NULL;
// 	ASSERT_NE(test, g);
// 	ASSERT_EQ(GRAFO_OK, imprimeGrafoArq(g, (char*)"saida.txt"));
// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
// }

// TEST(Graph_Tests, Connected){
// 	t_grafo* g = criaGrafoArq((char*)"entrada.txt");
// 	t_grafo* test = NULL;
// 	ASSERT_NE(test, g);
// 	EXPECT_EQ(false, eConexo(g));
// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));

// 	t_grafo* g1 = criaGrafoArq((char*)"entrada1.txt");
// 	ASSERT_NE(test, g1);
// 	EXPECT_EQ(true, eConexo(g1));
// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g1));
// }

int main(int argc, char** argv){
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}



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
}