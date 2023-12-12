#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 100
#define INF 1000000

// Структура в которой содержится информация о городе
typedef struct City {
    char Name[50];
    int x;
    int y;
} City;

// Функция для сравнения двух городов по координате x
int compare(const void* a, const void* b) {
    const City* city1 = (const City*)a;
    const City* city2 = (const City*)b;
    return city1->x - city2->x;
}

// Функция для вычисления Евклидового расстояния между двумя городами
int rastoyanie(City city1, City city2) {
    int dx = city1.x - city2.x;
    int dy = city1.y - city2.y;
    return (int)sqrt(dx * dx + dy * dy);
}

// Рекурсивная функция для поиска самого короткого пути через все города
void Shorty(City cities[], int way[], bool visited[], int current, int waylength, int numсities, int dist[], int prev[]) {
    visited[current] = true;
    way[waylength] = current;

    // Eсли путь прошел через все города, вычисляем его длину и выводим
    if (waylength == numсities - 1) {
        int alldist = 0;
        for (int i = 0; i < numсities - 1; i++) {
            alldist += rastoyanie(cities[way[i]], cities[way[i + 1]]);
        }
        printf("Самый короткий путь, проходящий через все города:\n");
        for (int i = 0; i < numсities; i++) {
            printf("%s ", cities[way[i]].Name);
        }
        printf("\nДлина пути: %d\n", alldist);

        // Прерываем рекурсию, когда путь найден
        return;
    }

    // Ищем следующий город с большей координатой x
    int next_city = -1;
    for (int i = current + 1; i < numсities; i++) {
        if (!visited[i]) {
            next_city = i;
            break;
        }
    }

    if (next_city != -1) {
        int d = rastoyanie(cities[current], cities[next_city]);
        if (dist[current] + d < dist[next_city]) {
            dist[next_city] = dist[current] + d;
            prev[next_city] = current;
        }

        Shorty(cities, way, visited, next_city, waylength + 1, numсities, dist, prev);
    }

    // "Обнуление"
    visited[current] = false;
    way[waylength] = -1;
}

// Обертка для вызова рекурсивной функции Shorty
void Shortyk(City cities[], int numcities) {
    bool visited[MAX] = { false };
    int way[MAX];
    int dist[MAX];
    int prev[MAX];

    // Инициализация массивов 
    for (int i = 0; i < numcities; i++) {
        dist[i] = INF;
        prev[i] = (i == 0) ? 0 : -1;
    }

    // Начальное расстояние до первого города всегда равно 0
        dist[0] = 0;

    // Сортируем города по координате x
    qsort(cities, numcities, sizeof(City), compare);

    // Вызываем рекурсивную функцию Shorty, начиная с первого города
    Shorty(cities, way, visited, 0, 0, numcities, dist, prev);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Задаем информацию о городах
    City cities[] = { {"A", 10, 0}, {"B", 200, 1}, {"C", 6, 28}, {"D", 6, 333},  {"E", 8, 44}, {"F", 10, 57}, {"G", 12, 62},{"H", 14, 72},{"I", 146, 8},{"J", 18, 79} };

    int numcities = sizeof(cities) / sizeof(City);

    Shortyk(cities, numcities);

    return 0;
}