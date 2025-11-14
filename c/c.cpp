#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

class VertexCoverSolver {
private:
    vector<pair<int, int>> edges;
    int vertex_count;
    
public:
    VertexCoverSolver(const vector<pair<int, int>>& input_edges, int n) 
        : edges(input_edges), vertex_count(n) {}
    
    set<int> greedyVertexCover() {
        set<int> cover;
        set<pair<int, int>> remaining_edges;
        
        // Нормализуем ребра (храним упорядоченные пары)
        for (auto& edge : edges) {
            int u = min(edge.first, edge.second);
            int v = max(edge.first, edge.second);
            remaining_edges.insert({u, v});
        }
        
        int iterations = 0;
        
        cout << "ШАГ 2: Основной цикл алгоритма" << endl;
        cout << "Начальное количество ребер: " << remaining_edges.size() << endl;
        
        while (!remaining_edges.empty()) {
            iterations++;
            
            // Выбираем первое ребро из множества
            auto it = remaining_edges.begin();
            int u = it->first;
            int v = it->second;
            
            cout << "Итерация " << iterations << ": выбрано ребро (" << u << ", " << v << ")" << endl;
            
            remaining_edges.erase(it);
            
            cover.insert(u);
            cover.insert(v);
            
            cout << "  Добавлены вершины: " << u << ", " << v << endl;
            cout << "  Текущий размер покрытия: " << cover.size() << endl;
            
            // Удаляем все ребра, инцидентные u или v
            auto edge_it = remaining_edges.begin();
            int removed_count = 0;
            
            while (edge_it != remaining_edges.end()) {
                if (edge_it->first == u || edge_it->first == v || 
                    edge_it->second == u || edge_it->second == v) {
                    edge_it = remaining_edges.erase(edge_it);
                    removed_count++;
                } else {
                    ++edge_it;
                }
            }
            
            cout << "  Удалено инцидентных ребер: " << removed_count << endl;
            cout << "  Осталось ребер: " << remaining_edges.size() << endl << endl;
        }
        
        cout << "Алгоритм завершен за " << iterations << " итераций" << endl;
        return cover;
    }
    
    bool verifyCover(const set<int>& cover) {
        cout << "ШАГ 3: Проверка корректности покрытия" << endl;
        
        for (auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            
            if (cover.find(u) == cover.end() && cover.find(v) == cover.end()) {
                cout << "  ОШИБКА: Ребро (" << u << ", " << v << ") не покрыто!" << endl;
                return false;
            }
        }
        
        cout << "  ✓ Все ребра покрыты корректно" << endl;
        return true;
    }
    
    void analyzeApproximation(const set<int>& cover) {
        cout << "ШАГ 4: Анализ качества аппроксимации" << endl;
        
        int cover_size = cover.size();
        cout << "  Размер найденного покрытия |C| = " << cover_size << endl;
        
        int optimal_estimate = 5;
        cout << "  Оценка оптимального покрытия |OPT| = " << optimal_estimate << endl;
        
        double approximation_ratio = static_cast<double>(cover_size) / optimal_estimate;
        cout << "  Коэффициент аппроксимации |C|/|OPT| = " << approximation_ratio << endl;
        
        if (approximation_ratio <= 2.0) {
            cout << "  ✓ Условие 2-аппроксимации выполняется: |C| ≤ 2×|OPT|" << endl;
        } else {
            cout << "  ✗ Условие 2-аппроксимации не выполняется" << endl;
        }
    }
    
    void solve() {
        cout << "==================================================" << endl;
        cout << "ЖАДНЫЙ АЛГОРИТМ ДЛЯ ВЕРШИННОГО ПОКРЫТИЯ" << endl;
        cout << "Граф: цикл C10 с вершинами 0-9" << endl;
        cout << "==================================================" << endl << endl;
        
        cout << "ШАГ 1: Инициализация структур данных" << endl;
        cout << "Количество вершин: " << vertex_count << endl;
        cout << "Количество ребер: " << edges.size() << endl;
        cout << "Ребра: ";
        for (auto& edge : edges) {
            cout << "(" << edge.first << "," << edge.second << ") ";
        }
        cout << endl << endl;
        
        set<int> cover = greedyVertexCover();
        
        cout << endl;
        
        bool is_valid = verifyCover(cover);
        
        cout << endl;
        
        if (is_valid) {
            cout << "ФИНАЛЬНЫЕ РЕЗУЛЬТАТЫ:" << endl;
            cout << "Вершинное покрытие: { ";
            for (int v : cover) {
                cout << v << " ";
            }
            cout << "}" << endl;
            cout << "Размер покрытия: " << cover.size() << endl;
            
            cout << endl;
            analyzeApproximation(cover);
        } else {
            cout << "Алгоритм нашел некорректное покрытие!" << endl;
        }
        
        cout << "==================================================" << endl;
    }
};

int main() {
    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, 
        {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 0}
    };
    
    VertexCoverSolver solver(edges, 10);
    solver.solve();
    
    return 0;
}
