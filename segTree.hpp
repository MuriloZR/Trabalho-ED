#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

enum TreeType {
    SUM,
    MAX,
    MIN,
    GCD,
    XOR
};

template<typename T>
class segTree
{
private:
    enum LazyType {
        NO_LAZY,    // Nenhuma operação lazy pendente
        LAZY_ADD,   // Operação de soma pendente
        LAZY_ASSIGN // Operação de assign pendente
    };
    
    TreeType type; //controla se é uma arvore de min,max, sum ou gcd
    int size; //tamanho do vetor usado pra construir a árvore
    std::vector<T> tree;  // Vetor de tipo genérico T, o vetor padrão da árvore
    std::vector<T> lazy;  // Vetor de tipo genérico T, guarda os valores pendentes para a lazy propagation
    std::vector<bool> marked; // Para operações de assign
    std::vector<LazyType> lazy_type; // Tipo da operação lazy pendente
    
    T operacao(T a, T b) {
      switch (type) {
        case SUM: return a + b;
        case MAX: return std::max(a, b);
        case MIN: return std::min(a, b);
        case GCD: return std::gcd(a, b);
        case XOR: return a ^ b;
      }

      return T();
    }

    T valorPadrao() {
      switch (type) {
        case SUM: return 0;
        case MAX: return std::numeric_limits<T>::lowest();
        case MIN: return std::numeric_limits<T>::max();
        case GCD: return 0;
        case XOR: return 0;
      }

      return T();
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

    T _query(int node, int L, int R, int l, int r)
    {
        //retorna valor padrão se for pra
        //fora dos limites
        if (r < L or R < l) {
            return valorPadrao();
        }

        // Se o no contém o range buscado
        // retorna o valor desse no
        if (l <= L and R <= r) {
            return tree[node];
        }

        // Aplica lazy propagation antes de descer na árvore
        push(node, L, R);

        // Achar o elemento do meio para
        // dividir o vetor em duas metades
        int mid = (L + R) / 2;

        // Percorre recursivamente direita e 
        // esquerda e encontra o no
        return operacao(_query(2 * node, L, mid, l, r), _query(2 * node + 1, mid + 1, R, l, r));
    }
    //daqui pra baixo tem os negocios de lazy propagation
    //não sei se eles vão estar funcionando, esse negócio
    //é uma loucura

    //tão funcionando

    void push_assign(int node, int L, int R) {
        if (marked[node]) {
            int mid = (L + R) / 2;

            tree[node*2] = lazy[node] * (mid - L + 1);
            tree[node*2+1] = lazy[node] * (R - mid);

            lazy[node*2] = lazy[node*2+1] = lazy[node];
            marked[node*2] = marked[node*2+1] = true;
            lazy_type[node*2] = lazy_type[node*2+1] = LAZY_ASSIGN;

            marked[node] = false;
            lazy_type[node] = NO_LAZY;
        }
    }

    void push_add(int node, int L, int R) {
        if (lazy_type[node] == LAZY_ADD) {
            int mid = (L + R) / 2;

            tree[node*2] += lazy[node] * (mid - L + 1);
            tree[node*2+1] += lazy[node] * (R - mid);

            if (lazy_type[node*2] == LAZY_ASSIGN) {
                // ADD sobre ASSIGN: soma tanto no tree quanto no lazy
                lazy[node*2] += lazy[node];
                // tree[filho] já foi atualizado acima
            } else if (lazy_type[node*2] == LAZY_ADD) {
                // ADD sobre ADD: apenas acumula no lazy
                lazy[node*2] += lazy[node];
            } else {
                // NO_LAZY: define como ADD
                lazy[node*2] = lazy[node];
                lazy_type[node*2] = LAZY_ADD;
            }

            if (lazy_type[node*2+1] == LAZY_ASSIGN) {
                // ADD sobre ASSIGN: soma tanto no tree quanto no lazy
                lazy[node*2+1] += lazy[node];
                // tree[filho] já foi atualizado acima
            } else if (lazy_type[node*2+1] == LAZY_ADD) {
                // ADD sobre ADD: apenas acumula no lazy
                lazy[node*2+1] += lazy[node];
            } else {
                // NO_LAZY: define como ADD
                lazy[node*2+1] = lazy[node];
                lazy_type[node*2+1] = LAZY_ADD;
            }

            lazy[node] = 0;
            lazy_type[node] = NO_LAZY;
        }
    }
    
    // Função unificada que decide qual push chamar
    void push(int node, int L, int R) {
        switch (lazy_type[node]) {
            case LAZY_ADD: push_add(node, L, R); break;
            case LAZY_ASSIGN: push_assign(node, L, R); break;
            case NO_LAZY: break;
        }
    }

    //adidiona 'add' a todos os valores entre v[l] e v[r]
    //L e R são os limites do vetor
    void _range_update_add(int node, int L, int R, int l, int r, T add) {
        if (l > r) return;
        
        if (l == L && r == R) {
            tree[node] += add * (R - L + 1);

            if (lazy_type[node] == LAZY_ASSIGN) {
                // Se já tem ASSIGN pendente, ADD se aplica sobre o valor ASSIGN
                lazy[node] += add;  // Novo valor = assign_value + add_value
                // Mantém LAZY_ASSIGN
            } else {
                // Se NO_LAZY ou LAZY_ADD, apenas acumula
                lazy[node] += add;
                lazy_type[node] = LAZY_ADD;
            }
        } else {
            push(node, L, R);
            int mid = (L + R) / 2;
            _range_update_add(node*2, L, mid, l, std::min(r, mid), add);
            _range_update_add(node*2+1, mid+1, R, std::max(l, mid+1), r, add);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }

    void _range_update_assign(int node, int L, int R, int l, int r, T new_val) {
        if (l > r) return;
        
        if (l == L && R == r) {
            tree[node] = new_val * (R - L + 1);

            lazy[node] = new_val;
            marked[node] = true;
            lazy_type[node] = LAZY_ASSIGN;
        } else {
            push(node, L, R);
            int mid = (L + R) / 2;
            _range_update_assign(node*2, L, mid, l, std::min(r, mid), new_val);
            _range_update_assign(node*2+1, mid+1, R, std::max(l, mid+1), r, new_val);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }

public:
    segTree(const std::vector<T>& arr, TreeType type) : 
        type(type), 
        size(arr.size()), 
        tree(4 * arr.size()), 
        lazy(4 * arr.size()),
        marked(4 * arr.size(), false),
        lazy_type(4 * arr.size(), NO_LAZY) 
    {
        build(arr, 1, 0, size - 1);
    }; //construtor da classe

    ~segTree() = default;
    
    //retorna a consulta entre left e right
    T query(int left, int right) {
        return _query(1, 0, size-1, left, right);
    };
    
    //soma 'value' a todos os elementos no intervalo [left, right]
    void add(int left, int right, T value) {
        _range_update_add(1, 0, size-1, left, right, value);
    };
    
    //atribui 'value' a todos os elementos no intervalo [left, right]
    void assign(int left, int right, T value) {
        _range_update_assign(1, 0, size-1, left, right, value);
    };
};
