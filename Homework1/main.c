#include <stdio.h>
#include <string.h>
#include <limits.h>

int minHoursForFinalRoute = INT_MAX;
int minRouteCities[100];
int citiesCostMatrix[100][100];

void swapValuesInArray(int *arr, int i, int j) {
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void calculateCostOfRouteAndCheckForMinCost(int *citiesRoute, int size) {
    int cost = 0;
    int i;
    printf("Route: ");
    for (i = 0; i < size; i++)
        printf("%d, ", citiesRoute[i]);
    printf("\n");

    for (i = 0; i < size - 1; i++) {
        cost += citiesCostMatrix[citiesRoute[i] - 1][citiesRoute[i + 1] - 1];
    }
    cost += citiesCostMatrix[citiesRoute[size - 1] - 1][0];
    printf("Total Cost for the route: %d\n", cost);
    printf("\n");
    if (cost < minHoursForFinalRoute) {
        for (i = 0; i < size; i++) {
            minRouteCities[i] = citiesRoute[i];
        }
        minHoursForFinalRoute = cost;
    } // checking for the minimum cost for particular route
}

void computeAllPossibleRoutes(int totalNumberOfCities) {

    int oArray[100];
    int cArray[100];
    int permutationArray[100];
    int i, j, q, s;

    // [P1:] Initialize: Cj ← 0 and Oj ← 1,for 1 ≤ j ≤n.
    for (i = 0; i < totalNumberOfCities; i++) {
        cArray[i] = 0;
        oArray[i] = 1;
        permutationArray[i] = i + 1;
    }

    while (1) {
        // [P2:] Visit permutation (a1, a2, · · · , an).
        calculateCostOfRouteAndCheckForMinCost(permutationArray, totalNumberOfCities);

        //[P3:] j ← n and s ← 0
        j = totalNumberOfCities - 1;
        s = 0;

        // [P4:] q ← Cj + Oj . If q < 0 go to P7; if q = j go to P6.
        q = cArray[j] + oArray[j];

        while (q < 0 || q == j) {
            if (q == j) {

                // [P6:] Terminate if j = 1; otherwise set s ← s + 1.
                if (j == 1) {
                    return;
                } else
                    s = s + 1;
            }

            // [P7:] Set oj ← −oj, j ← j − 1 and go back to P4.
            oArray[j] = -oArray[j];
            j = j - 1;
            q = cArray[j] + oArray[j];
        }

        // [P5:] Swap aj−cj+s with aj−q+s. Then set cj ← q and return to P2.
        swapValuesInArray(permutationArray, j - cArray[j] + s, j - q + s);

        cArray[j] = q;
    }
}

int main() {
    int totalNumberOfCities, i, j;
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");
    fscanf(inputFile, "%d", &totalNumberOfCities);
    printf("\n\n***********************************\n");
    printf("Travelling Salesman Problem\n");
    printf("***********************************\n\n");
    printf("Total no of cities from input file: %d\n\n", totalNumberOfCities);
    for (i = 0; i < totalNumberOfCities; i++) {
        for (j = 0; j < totalNumberOfCities; j++) {
            fscanf(inputFile, "%d", &citiesCostMatrix[i][j]);
        }
    }

    printf("Cost matrix: \n");
    for (i = 0; i < totalNumberOfCities; i++) {
        for (j = 0; j < totalNumberOfCities; j++) {
            printf("%d ", citiesCostMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");

    computeAllPossibleRoutes(totalNumberOfCities);
    printf("*********************************************************************************************\n");
    printf("Calculated minimum cost from all the options is %d for route: ", minHoursForFinalRoute);
    for (i = 0; i < totalNumberOfCities; i++) {
        printf("%d -> ", minRouteCities[i]);
    }
    printf("1\n");
    printf("*********************************************************************************************\n\n\n");
    return 0;
}