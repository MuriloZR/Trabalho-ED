
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

template<typename T>
class segTree
{
private:
    std::vector<T> tree;  // Vetor de tipo genérico T
    void segTree<T>::build_sum(const std::vector<T>& arr,int node, int L, int R)
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
    void segTree<T>::build_min(const std::vector<T> &arr, int node, int L, int R)
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
    void segTree<T>::build_max(const std::vector<T> &arr, int node, int L, int R)
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
public:
    segTree(const std::vector<T>& arr, std::string tree_type); //construtor da classe
    ~segTree();
    
    void update(int pos, T value); //atualiza a arvore
    T query(int left, int right);
};

template<typename T>
segTree<T>::segTree(const std::vector<T>& arr, std::string tree_type)
{
    tree.resize(4 * arr.size());
    if (tree_type == "soma" || tree_type == "sum") {
        build_sum(arr, 1, 0, arr.size() - 1);
    }
    else if (tree_type == "min")
    {
        build_min(arr, 1, 0, arr.size() - 1);
    }
    else if (tree_type == "max")
    {
        build_max(arr, 1, 0, arr.size() - 1);
    }
}

template<typename T>
segTree<T>::~segTree()
{
    // Destrutor (vector se limpa automaticamente)
}

template <typename T>
void segTree<T>::update(int pos, T value)
{
    //atualizar a árvore aqui
}

template <typename T>
T segTree<T>::query(int left, int right)
{
    return T(); //retorna o dado buscado entre left e right
}
