
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
#include <string>
#include <algorithm>

enum TreeType {
    sum,
    max,
    min,
    gcd
};

template<typename T>
class segTree
{
private:
    TreeType type; //controla se é uma arvore de min,max, sum ou gcd
    int size; //tamanho do vetor usado pra construir a árvore
    std::vector<T> tree;  // Vetor de tipo genérico T

    void build_sum(const std::vector<T>& arr,int node, int L, int R)
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
            build_sum(arr, 2 * node, L, mid);

            // Percorrer a metade
            // à direita recursivamente
            build_sum(arr, 2 * node + 1, mid + 1, R);

            // Guardar a soma de ambas as
            // crianças no nó pai
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void build_min(const std::vector<T> &arr, int node, int L, int R)
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
            build_min(arr, 2 * node, L, mid);

            // Percorrer a metade 
            // à direita recursivamente
            build_min(arr, 2 * node + 1, mid + 1, R);

            // Guardar a soma de ambas as
            // crianças no nó pai
            tree[node] = std::min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void build_max(const std::vector<T> &arr, int node, int L, int R)
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
            build_max(arr, 2 * node, L, mid);

            // Percorrer a metade 
            // à diretita recursivamente
            build_max(arr, 2 * node + 1, mid + 1, R);

            // Guardar a soma de ambas as
            // crianças no nó pai
            tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void build_gcd(const std::vector<T> &arr, int node, int L, int R)
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
            build_gcd(arr, 2 * node, L, mid);

            // Percorrer a metade 
            // à diretita recursivamente
            build_gcd(arr, 2 * node + 1, mid + 1, R);

            // Guardar a soma de ambas as
            // crianças no nó pai
            tree[node] = std::__gcd(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update_sum(int node, int L, int R, int pos, T new_val) {
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
                update_sum(node*2, L, mid, pos, new_val);
            }
            else {
                // Percorre recursivamente 
                // a metade à direita
                update_sum(node*2+1, mid+1, R, pos, new_val);
            }
            tree[node] = tree[node*2] + tree[node*2+1];
        }
    }
    T query_sum(int node, int tl, int tr, int l, int r)
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
        return query_sum(2 * node, tl, mid, l, r) + query_sum(2 * node + 1, mid + 1, tr, l, r);
    }
public:
    segTree(const std::vector<T>& arr, TreeType type); //construtor da classe
    ~segTree() = default;
    void update(int pos, T value); //atualiza a arvore
    T query(int left, int right);
};

template<typename T>
segTree<T>::segTree(const std::vector<T>& arr, TreeType type) : type(type), size(arr.size())
{
    tree.resize(4 * size);
    if (type == sum) {
        build_sum(arr, 1, 0, size - 1);
    }
    else if (type == min) {
        build_min(arr, 1, 0, size - 1);
    }
    else if (type == max) {
        build_max(arr, 1, 0, size - 1);
    }
    else if (type == gcd) {
        build_gcd(arr, 1, 0, size - 1);
    }
}

template <typename T>
void segTree<T>::update(int pos, T value)
{
    if (type == sum) {
        update_sum(1, 0, size-1, pos, value);
    }
    else if (type == max) {
        //TODO
    }
    else if (type == min) {
        //TODO
    }
    else if (type == gcd) {
        //TODO
    }
    
}

template <typename T>
T segTree<T>::query(int left, int right)
{
    if (type == sum) {
        return query_sum(1, 0, size-1, left, right);
    }
    else if (type == max) {
        //TODO
    }
    else if (type == min) {
        //TODO
    }
    else if (type == gcd) {
        //TODO
    }
}