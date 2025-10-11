#include <bits/stdc++.h> //header muito usado em programação competitiva, tem de tudo
#include "segTree.hpp" //header da Segment Tree(não existe no header acima)

int main() {
    //declara um vetor(necessário para poder construir a árvore)
    std::vector<int> v(10);

    srand(time(NULL));
    //poe 10 valores aleatorios entre 0 e 999 no vetor
    for (auto& i : v) i = rand()%1000;

    //declara uma árvore de soma de inteiros
    segTree<int> tree_sum(v, SUM);

    //obtenção do somatório de todos os elementos do vetor
    //de duas formas diferentes, uma usando a função accumulate
    //outra fazendo uma busca na árvore
    int array_sum = std::accumulate(v.begin(), v.end(), 0);
    int segTree_sum = tree_sum.query(0, v.size()-1);

    //compare os resultados, verá que são iguais
    std::cout << "accumulate: " << array_sum << '\n';
    std::cout << "segTree_sum: " << segTree_sum << std::endl;

    segTree<int> tree_max(v, MAX);

    //obtenção do maior número entre todos os elementos do vetor
    //de duas formas diferentes, uma usando a função max_element
    //outra fazendo uma busca na árvore
    int array_max = *std::max_element(v.begin(), v.end());
    int segTree_max = tree_max.query(0, v.size()-1);

    //compare os resultados, verá que são iguais
    std::cout << "max: " << array_max << '\n';
    std::cout << "segTree_max: " << segTree_max << std::endl;

    segTree<int> tree_min(v, MIN);

    //obtenção do menor número entre todos os elementos do vetor
    //de duas formas diferentes, uma usando a função min_element
    //outra fazendo uma busca na árvore
    int array_min = *std::min_element(v.begin(), v.end());
    int segTree_min = tree_min.query(0, v.size()-1);

    //compare os resultados, verá que são iguais
    std::cout << "min_element: " << array_min << '\n';
    std::cout << "segTree: " << segTree_min << std::endl;

    segTree<int> tree_gcd(v, GCD);

    //obtenção do maior divisor comum (mdc) de todos os elementos do vetor
    //de duas formas diferentes, uma usando a função gcd
    //outra fazendo uma busca na árvore
    int array_gcd = v[0];
    // itera entre todo o vetor para achar o mdc do vetor
    for (size_t i = 1; i < v.size(); ++i) {
        array_gcd = std::gcd(array_gcd, v[i]);
    }
    int segTree_gcd = tree_gcd.query(0, v.size()-1);

    //compare os resultados, verá que são iguais
    std::cout << "gcd: " << array_gcd << '\n';
    std::cout << "segTree: " << segTree_gcd << std::endl;
}
