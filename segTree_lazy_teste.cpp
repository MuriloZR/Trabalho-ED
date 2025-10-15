#include "segTree.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cassert>
#include <algorithm>
#include <numeric>

class TestFramework {
private:
    std::mt19937 gen;
    
public:
    TestFramework() : gen(std::random_device{}()) {}
    
    // Implementação naive usando vetores normais
    class NaiveSegTree {
    private:
        std::vector<int> arr;
        TreeType type;
        
    public:
        NaiveSegTree(const std::vector<int>& initial, TreeType t) : arr(initial), type(t) {}
        
        void rangeAdd(int l, int r, int val) {
            for (int i = l; i <= r && i < arr.size(); i++) {
                arr[i] += val;
            }
        }
        
        void rangeAssign(int l, int r, int val) {
            for (int i = l; i <= r && i < arr.size(); i++) {
                arr[i] = val;
            }
        }
        
        void assign(int pos, int val) {
            if (pos < arr.size()) arr[pos] = val;
        }
        
        void add(int pos, int val) {
            if (pos < arr.size()) arr[pos] += val;
        }
        
        int query(int l, int r) {
            if (l > r || l >= arr.size()) return getDefaultValue();
            
            r = std::min(r, (int)arr.size() - 1);
            int result = arr[l];
            
            for (int i = l + 1; i <= r; i++) {
                switch (type) {
                    case SUM: result += arr[i]; break;
                    case MAX: result = std::max(result, arr[i]); break;
                    case MIN: result = std::min(result, arr[i]); break;
                    case GCD: result = std::gcd(result, arr[i]); break;
                }
            }
            return result;
        }
        
        int getDefaultValue() {
            switch (type) {
                case SUM: return 0;
                case MAX: return std::numeric_limits<int>::lowest();
                case MIN: return std::numeric_limits<int>::max();
                case GCD: return 0;
            }
        }
        
        void print() {
            std::cout << "Array: ";
            for (int x : arr) std::cout << x << " ";
            std::cout << std::endl;
        }
    };
    
    // Testa operações básicas
    void testBasicOperations() {
        std::cout << "🧪 Testando operações básicas...\n";
        
        std::vector<int> arr = {1, 3, 5, 7, 9, 11};
        
        // Teste para SUM
        segTree<int> sum_tree(arr, SUM);
        NaiveSegTree naive_sum(arr, SUM);
        
        // Testes de query inicial
        assert(sum_tree.query(0, 2) == naive_sum.query(0, 2));
        assert(sum_tree.query(1, 4) == naive_sum.query(1, 4));
        assert(sum_tree.query(0, 5) == naive_sum.query(0, 5));
        
        // Teste para MIN
        segTree<int> min_tree(arr, MIN);
        NaiveSegTree naive_min(arr, MIN);
        
        assert(min_tree.query(0, 2) == naive_min.query(0, 2));
        assert(min_tree.query(1, 4) == naive_min.query(1, 4));
        
        // Teste para MAX
        segTree<int> max_tree(arr, MAX);
        NaiveSegTree naive_max(arr, MAX);
        
        assert(max_tree.query(0, 2) == naive_max.query(0, 2));
        assert(max_tree.query(1, 4) == naive_max.query(1, 4));
        
        std::cout << "✅ Operações básicas funcionando!\n";
    }
    
    // Testa range add com lazy propagation
    void testRangeAdd() {
        std::cout << "🧪 Testando Range Add com Lazy Propagation...\n";
        
        std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
        
        segTree<int> seg_tree(arr, SUM);
        NaiveSegTree naive(arr, SUM);
        
        // Teste 1: Range add simples
        seg_tree.rangeAdd(1, 4, 10);
        naive.rangeAdd(1, 4, 10);
        
        for (int l = 0; l < 8; l++) {
            for (int r = l; r < 8; r++) {
                int seg_result = seg_tree.query(l, r);
                int naive_result = naive.query(l, r);
                if (seg_result != naive_result) {
                    std::cout << "❌ ERRO Range Add: query(" << l << "," << r 
                              << ") seg=" << seg_result << " naive=" << naive_result << std::endl;
                    naive.print();
                    assert(false);
                }
            }
        }
        
        // Teste 2: Múltiplos range adds
        seg_tree.rangeAdd(0, 2, 5);
        naive.rangeAdd(0, 2, 5);
        
        seg_tree.rangeAdd(3, 7, -3);
        naive.rangeAdd(3, 7, -3);
        
        // Verificar todas as queries novamente
        for (int l = 0; l < 8; l++) {
            for (int r = l; r < 8; r++) {
                assert(seg_tree.query(l, r) == naive.query(l, r));
            }
        }
        
        std::cout << "✅ Range Add funcionando!\n";
    }
    
    // Testa range assign com lazy propagation
    void testRangeAssign() {
        std::cout << "🧪 Testando Range Assign com Lazy Propagation...\n";
        
        std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
        
        segTree<int> seg_tree(arr, SUM);
        NaiveSegTree naive(arr, SUM);
        
        // Teste 1: Range assign simples
        seg_tree.rangeAssign(1, 4, 100);
        naive.rangeAssign(1, 4, 100);
        
        for (int l = 0; l < 8; l++) {
            for (int r = l; r < 8; r++) {
                int seg_result = seg_tree.query(l, r);
                int naive_result = naive.query(l, r);
                if (seg_result != naive_result) {
                    std::cout << "❌ ERRO Range Assign: query(" << l << "," << r 
                              << ") seg=" << seg_result << " naive=" << naive_result << std::endl;
                    assert(false);
                }
            }
        }
        
        // Teste 2: Range assign sobreposto
        seg_tree.rangeAssign(0, 2, 50);
        naive.rangeAssign(0, 2, 50);
        
        seg_tree.rangeAssign(5, 7, 25);
        naive.rangeAssign(5, 7, 25);
        
        // Verificar todas as queries
        for (int l = 0; l < 8; l++) {
            for (int r = l; r < 8; r++) {
                assert(seg_tree.query(l, r) == naive.query(l, r));
            }
        }
        
        std::cout << "✅ Range Assign funcionando!\n";
    }
    
    // Testa operações mistas (add + assign)
    void testMixedOperations() {
        std::cout << "🧪 Testando operações mistas (Add + Assign)...\n";
        
        std::vector<int> arr = {10, 20, 30, 40, 50};
        
        segTree<int> seg_tree(arr, SUM);
        NaiveSegTree naive(arr, SUM);
        
        // Sequência de operações mistas
        seg_tree.rangeAdd(0, 2, 5);
        naive.rangeAdd(0, 2, 5);

        
        
        seg_tree.rangeAssign(1, 3, 100);
        naive.rangeAssign(1, 3, 100);
        
        
        seg_tree.rangeAdd(2, 4, -10);
        naive.rangeAdd(2, 4, -10);
        
        
        seg_tree.add(0, 1000);
        naive.add(0, 1000);
        
        
        seg_tree.assign(4, 777);
        naive.assign(4, 777);
        
        
        // Verificar todas as queries
        for (int l = 0; l < 5; l++) {
            for (int r = l; r < 5; r++) {
                int seg_result = seg_tree.query(l, r);
                int naive_result = naive.query(l, r);
                if (seg_result != naive_result) {
                    std::cout << "❌ ERRO Mixed Ops: query(" << l << "," << r 
                              << ") seg=" << seg_result << " naive=" << naive_result << std::endl;
                    naive.print();
                    assert(false);
                }
            }
        }
        
        std::cout << "✅ Operações mistas funcionando!\n";
    }
    
    // Teste de stress com operações aleatórias
    void testStress() {
        std::cout << "🧪 Teste de stress com 1000 operações aleatórias...\n";
        
        const int n = 20;
        std::vector<int> arr(n);
        std::uniform_int_distribution<int> val_dist(1, 100);
        
        for (int i = 0; i < n; i++) {
            arr[i] = val_dist(gen);
        }
        
        segTree<int> seg_tree(arr, SUM);
        NaiveSegTree naive(arr, SUM);
        
        std::uniform_int_distribution<int> op_dist(0, 4);
        std::uniform_int_distribution<int> pos_dist(0, n-1);
        std::uniform_int_distribution<int> val_small_dist(-50, 50);
        
        for (int test = 0; test < 1000; test++) {
            int op = op_dist(gen);
            int l = pos_dist(gen);
            int r = pos_dist(gen);
            if (l > r) std::swap(l, r);
            int val = val_small_dist(gen);
            
            switch (op) {
                case 0: // range add
                    seg_tree.rangeAdd(l, r, val);
                    naive.rangeAdd(l, r, val);
                    break;
                case 1: // range assign
                    seg_tree.rangeAssign(l, r, val);
                    naive.rangeAssign(l, r, val);
                    break;
                case 2: // single add
                    seg_tree.add(l, val);
                    naive.add(l, val);
                    break;
                case 3: // single assign
                    seg_tree.assign(l, val);
                    naive.assign(l, val);
                    break;
                case 4: // query (verificação)
                    int seg_result = seg_tree.query(l, r);
                    int naive_result = naive.query(l, r);
                    if (seg_result != naive_result) {
                        std::cout << "❌ ERRO no teste " << test << ": query(" << l << "," << r 
                                  << ") seg=" << seg_result << " naive=" << naive_result << std::endl;
                        assert(false);
                    }
                    break;
            }
        }
        
        // Verificação final completa
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                assert(seg_tree.query(l, r) == naive.query(l, r));
            }
        }
        
        std::cout << "✅ Teste de stress passou!\n";
    }
    
    // Benchmark de performance
    void benchmarkPerformance() {
        std::cout << "⚡ Benchmark de Performance...\n";
        
        const int n = 10000;
        std::vector<int> arr(n, 1);
        
        segTree<int> seg_tree(arr, SUM);
        NaiveSegTree naive(arr, SUM);
        
        const int operations = 10000;
        
        // Benchmark Segment Tree
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < operations; i++) {
            int l = i % n;
            int r = (i + 100) % n;
            if (l > r) std::swap(l, r);
            
            if (i % 2 == 0) {
                seg_tree.rangeAdd(l, r, 1);
            } else {
                seg_tree.query(l, r);
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto seg_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        // Benchmark implementação naive
        start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < operations; i++) {
            int l = i % n;
            int r = (i + 100) % n;
            if (l > r) std::swap(l, r);
            
            if (i % 2 == 0) {
                naive.rangeAdd(l, r, 1);
            } else {
                naive.query(l, r);
            }
        }
        
        end = std::chrono::high_resolution_clock::now();
        auto naive_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "🚀 Segment Tree: " << seg_time.count() << "ms\n";
        std::cout << "🐌 Implementação Naive: " << naive_time.count() << "ms\n";
        std::cout << "📈 Speedup: " << (double)naive_time.count() / seg_time.count() << "x\n";
    }
};

int main() {
    std::cout << "🌳 === TESTE DE LAZY PROPAGATION - SEGMENT TREE ===\n\n";
    
    TestFramework tester;
    
    try {
        tester.testBasicOperations();
        std::cout << std::endl;
        
        tester.testRangeAdd();
        std::cout << std::endl;
        
        tester.testRangeAssign();
        std::cout << std::endl;
        
        tester.testMixedOperations();
        std::cout << std::endl;
        
        tester.testStress();
        std::cout << std::endl;
        
        tester.benchmarkPerformance();
        
        std::cout << "\n🎉 TODOS OS TESTES PASSARAM! Lazy Propagation está funcionando corretamente!\n";
        
    } catch (const std::exception& e) {
        std::cout << "❌ ERRO: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}