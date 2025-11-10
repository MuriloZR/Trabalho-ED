# Segment Tree - Generic Implementation

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/status-in%20development-yellow.svg?style=for-the-badge)

## Sobre o Projeto

Implementação genérica de **Árvore de Segmentos (Segment Tree)** em C++ usando templates, permitindo operações eficientes em qualquer tipo de dados numérico.

### Características

- **Template Genérico**: Funciona com `int`, `long long`, `double`, etc.
- **Alta Performance**: Complexidade O(log n) para consultas e atualizações
- **Operações Múltiplas**: Soma, Mínimo, Máximo, Maior divisor comum (com possibilidade de extensão)
- **Código Educativo**: Bem comentado e estruturado para aprendizado
- **Colaborativo**: Desenvolvido em equipe para disciplina de Estruturas de Dados

## Funcionalidades

### Implementado
- [x] Template genérico para qualquer tipo numérico
- [x] Operação de **Soma** (Range Sum Query)
- [x] Operação de **Mínimo** (Range Minimum Query)
- [x] Operação de **Máximo** (Range Maximum Query)
- [x] Construção da árvore O(n)
- [x] Função `update()` - Atualização de elementos
- [x] Função `query()` - Consultas por intervalo
- [x] Lazy Propagation (para atualizações em intervalo)
- [x] Testes unitários

## 📖 Como Usar

### Exemplo Básico

```cpp
#include "segTree.hpp"
#include <vector>
#include <iostream>

int main() {
    // Criando um array de exemplo
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};
    
    // Criando árvores de segmentos para diferentes operações
    segTree<int> sum_tree(arr, SUM);    // Árvore de soma
    segTree<int> max_tree(arr, MAX);    // Árvore de máximo
    segTree<int> min_tree(arr, MIN);    // Árvore de mínimo
    segTree<int> gcd_tree(arr, GCD);    // Árvore de maior divisor comum
    
    // os parâmetros da função query são o intervalo que quer se buscar
    // exemplo: a soma total é do arr[0] até arr[size - 1]
    // a soma de arr[0] até arr[3] seria sum_tree.query(0, 3);
    int soma = sum_tree.query(0, arr.size() - 1);
    int maior = max_tree.query(0, arr.size() - 1);
    int menor = min_tree.query(0, arr.size() - 1);
    int mdc = gcd_tree.query(0, arr.size() - 1);
    
    return 0;
}
```

### Tipos Suportados

```cpp
// Inteiros
segTree<int> tree_int(arr_int, sum);

// Long Long (para números grandes)
segTree<long long> tree_ll(arr_ll, sum);

// Ponto flutuante
segTree<double> tree_double(arr_double, min);

```
## 🛠️ Compilação

```bash
# Compilar exemplo básico
c++ -std=c++20 -o SegTree segTree_teste.cpp
```

## Complexidade

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Construção | O(n) | Constrói a árvore inicial |
| Consulta | O(log n) | Query em intervalo [l, r] |
| Atualização | O(log n) | Update de um elemento |
| Espaço | O(4n) | Espaço necessário para a árvore |

## Porquê o espaço é O(4n)?
Para um vetor de tamanho N, o número de nós folha será N.
Como a Segment Tree possui a estrutura de uma árvore binária completa,
o número de nós pode ser até 2N - 1, quando N é uma potência de 2.
Se N não for uma potência de 2, o número de nós folha na Segment Tree será
o próximo número maior que N que é potência de 2, isso pode levar a um número de nós
maior que o necessário. Ao usar um tamanho de 4N, é garantido que haverá espaço
suficiente para todos os nós, mesmo se N não for uma potência de 2.  
Cálculo da potência de 2 maior que N: $\lfloor \log _{2}\left(N\right) \rfloor + 1$  
Cálculo matemático:  
$4N > 2(\lfloor \log _{2}\left(N\right) \rfloor + 1) - 1$  
$2N > \lfloor \log _{2}\left(N\right) \rfloor + 1 - 1$  
$2N > \lfloor \log _{2}\left(N\right) \rfloor$ Isso é verdade?  
Prova por indução:  
A desigualdade pode ser provada mostrando que $n < 2^n \quad \forall n \ge 1 \in \mathbb{N}$  
n = 1, $1 < 2^1$  
Assumimos que a inequação é verdadeira para algum $k \in \mathbb{N}$, $k < 2^k$  
$k+1 < 2^{k+1}$  
$\forall k \ge 1,\quad 2k \ge k+1$  
$k+1 \le 2k < 2^{k+1}$  
Como o logaritmo é a função inversa da exponenciação, $2N > \lfloor \log _{2}\left(N\right) \rfloor \quad \forall N \ge 1$

## Referências

- [Segment Tree - CP-Algorithms](https://cp-algorithms.com/data_structures/segment_tree.html)
- [Introduction to Data Structures](https://www.geeksforgeeks.org/segment-tree-data-structure/)

---

**Disciplina**: Estruturas de Dados | **Universidade**: Universidade Federal de Santa Maria (UFSM)
