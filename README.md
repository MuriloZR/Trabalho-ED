# 🌳 Segment Tree - Generic Implementation

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Status](https://img.shields.io/badge/status-in%20development-yellow.svg?style=for-the-badge)

## 📋 Sobre o Projeto

Implementação robusta e genérica de **Árvore de Segmentos (Segment Tree)** em C++ usando templates, permitindo operações eficientes em qualquer tipo de dados numérico.

### ✨ Características

- 🎯 **Template Genérico**: Funciona com `int`, `long long`, `double`, etc.
- ⚡ **Alta Performance**: Complexidade O(log n) para consultas e atualizações
- 🔧 **Operações Múltiplas**: Soma, Mínimo, Máximo (com possibilidade de extensão)
- 📚 **Código Educativo**: Bem comentado e estruturado para aprendizado
- 🤝 **Colaborativo**: Desenvolvido em equipe para disciplina de Estruturas de Dados

## 🚀 Funcionalidades

### ✅ Implementado
- [x] Template genérico para qualquer tipo numérico
- [x] Operação de **Soma** (Range Sum Query)
- [x] Operação de **Mínimo** (Range Minimum Query)
- [x] Operação de **Máximo** (Range Maximum Query)
- [x] Construção da árvore O(n)

### 🔄 Em Desenvolvimento
- [ ] Função `update()` - Atualização de elementos
- [ ] Função `query()` - Consultas por intervalo
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
    segTree<int> sum_tree(arr, sum);    // Árvore de soma
    segTree<int> min_tree(arr, min);    // Árvore de mínimo
    segTree<int> max_tree(arr, max);    // Árvore de máximo
    
    // TODO: Exemplos de uso das funções query() e update()
    // quando estiverem implementadas
    
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

<!-- ## 🏗️ Estrutura do Projeto -->
<!---->
<!-- ``` -->
<!-- Trabalho-ED/ -->
<!-- ├── segTree.cpp          # Implementação principal -->
<!-- ├── README.md             # Este arquivo -->
<!-- └── examples/             # Exemplos de uso (futuro) -->
<!-- ``` -->

## 🛠️ Compilação

```bash
# Compilar exemplo básico
c++ -std=c++20 -o SegTree segTree.cpp
```

## 📊 Complexidade

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Construção | O(n) | Constrói a árvore inicial |
| Consulta | O(log n) | Query em intervalo [l, r] |
| Atualização | O(log n) | Update de um elemento |
| Espaço | O(4n) | Espaço necessário para a árvore |

## 🤝 Como Contribuir

Este é um projeto colaborativo! Para contribuir:

1. **Fork** o repositório
2. **Clone** para sua máquina local
3. **Crie uma branch** para sua feature: `git checkout -b feature/nova-funcionalidade`
4. **Commit** suas mudanças: `git commit -m 'Adiciona nova funcionalidade'`
5. **Push** para a branch: `git push origin feature/nova-funcionalidade`
6. Abra um **Pull Request**

### 🎯 Tarefas Disponíveis

- **Implementar função `update()`**: Atualização de elementos individuais
- **Implementar função `query()`**: Consultas por intervalo
- **Criar testes**: Casos de teste para validar implementação
- **Documentação**: Melhorar comentários e exemplos

## 📚 Referências

- [Segment Tree - CP-Algorithms](https://cp-algorithms.com/data_structures/segment_tree.html)
- [Introduction to Data Structures](https://www.geeksforgeeks.org/segment-tree-data-structure/)

---

**📌 Status**: Em desenvolvimento | **🎓 Disciplina**: Estruturas de Dados | **🏫 Universidade**: Universidade Federal de Santa Maria (UFSM)
