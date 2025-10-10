
#include <vector>

template<typename T>
class seg_tree
{
private:
    std::vector<T> tree;  // Vetor de tipo genérico T
public:
    seg_tree(const std::vector<T>& arr); //construtor da classe
    ~seg_tree();
    
    void update(int pos, T value); //atualiza a arvore
    T query(int left, int right);
};

template<typename T>
seg_tree<T>::seg_tree(const std::vector<T>& arr) : size(arr.size())
{
    tree.resize(4 * size);
    // Construir a árvore aqui
}

template<typename T>
seg_tree<T>::~seg_tree()
{
    // Destrutor (vector se limpa automaticamente)
}

template <typename T>
void seg_tree<T>::update(int pos, T value)
{
    //atualizar a árvore aqui
}

template <typename T>
T seg_tree<T>::query(int left, int right)
{
    return T(); //retorna o dado buscado entre left e right
}
