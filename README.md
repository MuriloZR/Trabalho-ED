# 🌳 Segment Tree - Generic Implementation

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/status-in%20development-yellow.svg?style=for-the-badge)

## 📋 Sobre o Projeto

Implementação robusta e genérica de **Árvore de Segmentos (Segment Tree)** em C++ usando templates, permitindo operações eficientes em qualquer tipo de dados numérico.

### ✨ Características

- 🎯 **Template Genérico**: Funciona com `int`, `long long`, `double`, etc.
- ⚡ **Alta Performance**: Complexidade O(log n) para consultas e atualizações
- 🔧 **Operações Múltiplas**: Soma, Mínimo, Máximo, Maior divisor comum (com possibilidade de extensão)
- 📚 **Código Educativo**: Bem comentado e estruturado para aprendizado
- 🤝 **Colaborativo**: Desenvolvido em equipe para disciplina de Estruturas de Dados

## 🚀 Funcionalidades

### ✅ Implementado
- [x] Template genérico para qualquer tipo numérico
- [x] Operação de **Soma** (Range Sum Query)
- [x] Operação de **Mínimo** (Range Minimum Query)
- [x] Operação de **Máximo** (Range Maximum Query)
- [x] Construção da árvore O(n)
- [x] Função `update()` - Atualização de elementos
- [x] Função `query()` - Consultas por intervalo

### 🔄 Em Desenvolvimento
- [ ] Lazy Propagation (para atualizações em intervalo)
- [ ] Testes unitários

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

## 📊 Complexidade

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Construção | O(n) | Constrói a árvore inicial |
| Consulta | O(log n) | Query em intervalo [l, r] |
| Atualização | O(log n) | Update de um elemento |
| Espaço | O(4n) | Espaço necessário para a árvore |

## 📚 Referências

- [Segment Tree - CP-Algorithms](https://cp-algorithms.com/data_structures/segment_tree.html)
- [Introduction to Data Structures](https://www.geeksforgeeks.org/segment-tree-data-structure/)

---

**🎓 Disciplina**: Estruturas de Dados | **🏫 Universidade**: Universidade Federal de Santa Maria (UFSM)
