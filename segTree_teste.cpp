#include <bits/stdc++.h> //header muito usado em programação competitiva, tem de tudo
#include "segTree.hpp" //header da Segment Tree(não existe no header acima)

int main() {
    //declara um vetor(necessário para poder construir a árvore)
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8 ,9};
    //declara uma árvore de soma de inteiros
    segTree<int> tree_sum_int(v, SUM);

    //obtenção do somatório de todos os elementos do vetor
    //de duas formas diferentes, uma usando a função accumulate
    //outra fazendo uma busca na árvore
    int soma_do_array = std::accumulate(v.begin(), v.end(), 0);
    int soma_segTree = tree_sum_int.query(0, v.size()-1);

    //compare os resultados, verá que são iguais
    std::cout << "accumulate: " << soma_do_array << '\n';
    std::cout << "segTree: " << soma_segTree << std::endl;
}
