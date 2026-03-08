#include <stdio.h>
#include <stdlib.h>

#define D 4
#define N 3

int main(void) {
    int max_temp[D][N];
    int min_temp[D][N];
    float max_avg_temp[D];

    printf("Informe a previsão da temperatura máxima para os próximos %d dias em %d cidades (max min): \n", D, N);

    for(int day = 0; day < D; day++) {
        for(int city = 0; city < N; city++) {
            printf("Dia - %d, Cidade - %d: \n", day + 1, city + 1);
            printf("Max: ");
            scanf( "%d", &max_temp[day][city]);
            printf("Min: ");
            scanf( "%d", &min_temp[day][city]);
            max_avg_temp[day] += (float)max_temp[day][city] / N;
        }
    }

    float max_avg = 0;
    int max_avg_day = 0;
    for(int day = 0; day < D; day++) {
        if(max_avg < max_avg_temp[day]) {
            max_avg = max_avg_temp[day];
            max_avg_day = day;
        }
    }

    printf("O dia %d terá a maior média de temperatura máxima, com %.2f graus celsius.\n", max_avg_day + 1, max_avg);

    int max_delta_temp[N];
    for(int city = 0; city < N; city++) {
        int max_max = max_temp[0][city], min_min = min_temp[0][city];
        for(int day = 0; day < D; day++){
            if(max_temp[day][city] > max_max) max_max = max_temp[day][city];
            if(min_temp[day][city] < min_min) min_min = min_temp[day][city];
        }
        max_delta_temp[city] = max_max - min_min;
    }

    int max_delta_city = 0, max_delta_t = 0;
    for(int city = 0; city < N; city++){
        if (max_delta_temp[city] > max_delta_t) {
            max_delta_t = max_delta_temp[city];
            max_delta_city = city;
        }
    }

    printf("A cidade %d terá a maior variação de temperatura, com %d graus celsius.\n", max_delta_city + 1, max_delta_t);

    return EXIT_SUCCESS;
}
