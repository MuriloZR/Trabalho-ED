/*
 * Segment Tree Implementation - Generic Template
 * 
 * ✅ IMPLEMENTED:
 * - Sum, Min, Max operations
 * - Generic template for any data type
 * - Build functions for all three operations
 * 
 * 🔄 TODO (for collaboration):
 * - Implement update() function
 * - Implement query() function  
 * - Add GCD operations (optional)
 * - Add range update with lazy propagation (advanced)
 */

#include <vector>
#include <algorithm>
#include <numeric>

enum TreeType {
    SUM,
    MAX,
    MIN,
    GCD 
};

template<typename T>
class segTree
{
private:
    TreeType type; //controla se é uma arvore de min,max, sum ou gcd
    int size; //tamanho do vetor usado pra construir a árvore
    std::vector<T> tree;  // Vetor de tipo genérico T
    
    T operacao(T a, T b) {
      switch (type) {
        case SUM: return a + b;
        case MAX: return std::max(a, b);
        case MIN: return std::min(a, b);
        case GCD: return std::gcd(a, b);
      }
    }

    void build(const std::vector<T>& arr,int node, int L, int R)
    {
        // Nó folha em L == R
        if (L == R) {
            tree[node] = arr[L];
        }
        else {

            // Achar o elemento do meio para
            // dividir o vetor em duas metades
            int mid = (L + R) / 2;

        
            // Percorrer a metade 
            // à esquerda recursivamente
            build(arr, 2 * node, L, mid);

            // Percorrer a metade
            // à direita recursivamente
            build(arr, 2 * node + 1, mid + 1, R);

            // Guardar a soma de ambas as
            // crianças no nó pai
            tree[node] = operacao(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void _update(int node, int L, int R, int pos, T new_val) {
        if (L == R) {
            tree[node] = new_val;
        }
        else {

            // Achar o elemento do meio para
            // dividir o vetor em duas metades
            int mid = (L + R) / 2;

            // Precisa atualizar apenas a metade da árvore
            // que vai ter algum valor modificado
            if (pos <= mid) {
                // Percorre recursivamente 
                // a metade à esquerda
                _update(node*2, L, mid, pos, new_val);
            }
            else {
                // Percorre recursivamente 
                // a metade à direita
                _update(node*2+1, mid+1, R, pos, new_val);
            }
            tree[node] = operacao(tree[node*2], tree[node*2+1]);
        }
    }
    T _query_sum(int node, int tl, int tr, int l, int r)
    {

        //retorna 0 se for pra
        //fora dos limites
        if (r < tl or tr < l) {
            return 0;
        }

        // Se o no contém o range buscado
        // retorna o valor desse no
        if (l <= tl and tr <= r) {
            return tree[node];
        }

        // Achar o elemento do meio para
        // dividir o vetor em duas metades
        int mid = (tl + tr) / 2;

        // Percorre recursivamente direita e 
        // esquerda e encontra o no
        return operacao(_query_sum(2 * node + 1, mid + 1, tr, l, r), _query_sum(2 * node + 1, mid + 1, tr, l, r));
    }
public:
    segTree(const std::vector<T>& arr, TreeType type) : type(type), size(arr.size()), tree(4 * arr.size()){
      build(arr, 1, 0, size - 1);
    }; //construtor da classe

    ~segTree() = default;

    void update(int pos, T value) {
        _update(1, 0, size-1, pos, value);
    }; //atualiza a arvore
    
    T query(int left, int right) {
        return _query_sum(1, 0, size-1, left, right);
    }; //retorna a consulta entre left e right
};