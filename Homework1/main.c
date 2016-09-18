#include <stdio.h>
#include <string.h>
#include <limits.h>

int minHrs = INT_MAX;
char minRouteCities[100];
int citiesCostMatrix[100][100];

void swapValuesInArray(char *x, char *y) {
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void computeAllPossibleRoutes(char *cities, int startingIndex, int endingIndex) {
    int i;
    if (startingIndex == endingIndex) {
        int cost = 0;
        printf("Staring new route of 1%s1\n", cities);
        cost = citiesCostMatrix[0][(cities[0] - 1) - '0']; // initial cost from city 0
        for (i = 0; i < strlen(cities) - 1; i++) {
            cost += citiesCostMatrix[(cities[i] - 1) - '0'][(cities[i + 1] - 1) - '0'];
        } // calculating the total cost of the travel before destination city 0
        cost += citiesCostMatrix[cities[(strlen(cities) - 1)] - '1'][0]; // add cost for going back to destination 0
        if (cost < minHrs) {
            strcpy(minRouteCities, cities);
            minHrs = cost;
        } // checking for the minimum cost for particular route
        printf("Total Cost for the route 1%s1: %d\n\n", cities, cost);
    } else {
        for (i = startingIndex; i <= endingIndex; i++) {
            swapValuesInArray((cities + startingIndex), (cities + i));
            computeAllPossibleRoutes(cities, startingIndex + 1, endingIndex);
            swapValuesInArray((cities + startingIndex), (cities + i));
        }
    }
}

int main() {
    int totalNumberOfCities, i, j;
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");
    fscanf(inputFile, "%d", &totalNumberOfCities);
    for (i = 0; i < totalNumberOfCities; i++) {
        for (j = 0; j < totalNumberOfCities; j++) {
            fscanf(inputFile, "%d", &citiesCostMatrix[i][j]);
        }
    }

    for (i = 0; i < totalNumberOfCities; i++) {
        for (j = 0; j < totalNumberOfCities; j++) {
            printf("%d ", citiesCostMatrix[i][j]);
        }
        printf("\n");
    }

    int counter;
    char cities[totalNumberOfCities];
    strcpy(cities, "2");
    char buffer[20];
    for (counter = 2; counter < totalNumberOfCities; counter++) {
        snprintf(buffer, 10, "%d", counter + 1);
        strcat(cities, buffer);
    }
    int n = (int) strlen(cities);
    computeAllPossibleRoutes(cities, 0, n - 1);
    printf("*********************************************************************************************\n");
    printf("Calculated minimum cost from all the options is %d for route 1%s1\n", minHrs, minRouteCities);
    printf("*********************************************************************************************\n");
    return 0;
}