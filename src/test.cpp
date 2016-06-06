#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "gtest/gtest.h"

TEST(Graph_Tests, Creating){
	t_grafo* g = criaGrafo();
	t_grafo* test = NULL;
	//verifica a criacao do grafo
	ASSERT_NE(test, g);

	//verifica a deslocacao
	EXPECT_EQ(GRAFO_ERR , limpaGrafo(test));
	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
}

// TEST(Graph_Tests, Inserting){
// 	t_grafo* g = criaGrafoArq((char*)"entrada.txt");
// 	t_grafo* test = NULL;
// 	ASSERT_NE(test, g);
// 	//vertices
// 	EXPECT_EQ(GRAFO_OK, insereVertice(g, (char*)"L"));          //inserindo um vertice qualquer
// 	EXPECT_EQ(GRAFO_ERR, insereVertice(test, (char*)"GA"));     //inserindo um vertice qualquer em um grafo nulo
// 	EXPECT_EQ(GRAFO_ERR, insereVertice(test, (char*)"L"));      //inserindo um vertice já existente
// 	//origens
// 	EXPECT_EQ(GRAFO_OK, insereOrigem(g, (char*)"L"));       //inserindo uma origem
// 	EXPECT_EQ(GRAFO_ERR, insereOrigem(g, (char*)"P"));      //inserindo uma origem que não existe como vertice
// 	EXPECT_EQ(GRAFO_ERR, insereOrigem(test, (char*)"L"));   //inserindo uma origem em um grafo nulo
// 	//arestas
// 	EXPECT_EQ(GRAFO_OK, insereAresta(g, (char*)"Z", (char*)"L", 6));    //inserindo uma aresta normal
// 	EXPECT_EQ(GRAFO_ERR, insereAresta(g, (char*)"P", (char*)"L", 1));	//inserindo uma aresta que não possui o vertice P como origem
// 	EXPECT_EQ(GRAFO_ERR, insereAresta(g, (char*)"Z", (char*)"P", 3));   //inserindo uma aresta que não possui o vertice P como dest
// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
// }

// TEST(Graph_Tests, Removing){
// 	t_grafo* g = criaGrafoArq((char*)"entrada.txt");
// 	t_grafo* test = NULL;
// 	ASSERT_NE(test, g);
// 	//a partir do grafo de exemplo removeremos seus elementos
// 	EXPECT_EQ(GRAFO_ERR,retiraOrigem(test, (char*)"V"));     //retira uma origem de um grafo nulo
// 	EXPECT_EQ(GRAFO_OK, retiraOrigem(g, (char*)"V"));         //retira uma origem existente
// 	EXPECT_EQ(GRAFO_ERR,retiraOrigem(g, (char*)"L"));        //retira uma origem inexistente 
// 	EXPECT_EQ(GRAFO_ERR,retiraOrigem(g, (char*)"Z"));        //retira uma origem inexistente mas é um vértice
// 	//arestas
// 	EXPECT_EQ(GRAFO_OK,retiraAresta(g, (char*)"Z",(char*)"Z"));    //retira uma aresta existente
// 	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, (char*)"Z",(char*)"P"));   //retira uma aresta com um dos vertices inexistentes
// 	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, (char*)"P",(char*)"A"));   //retira uma aresta completamente inexistente
// 	//vertices
// 	EXPECT_EQ(GRAFO_ERR,retiraVertice(test, (char*)"U"));     //retira um vertice de um grafo nulo
// 	EXPECT_EQ(GRAFO_ERR,retiraVertice(g, (char*)"P"));        //retira um vertice inexistente
// 	EXPECT_EQ(GRAFO_OK,retiraVertice(g, (char*)"U"));         // retira um vertice existente
//     // ao retirar esse vertice, as arestas com ele presente também sao retiradas, assim se quisermos retirar alguma aresta ou origem com ele deve ser encontrado um erro
// 	EXPECT_EQ(GRAFO_ERR,retiraAresta(g, (char*)"U", (char*)"V"));    // verifica de a aresta U nao existe
// 	EXPECT_EQ(GRAFO_ERR,retiraOrigem(g, (char*)"U"));                // retira origem U nao existe

// 	EXPECT_EQ(GRAFO_OK , limpaGrafo(g));
// }

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