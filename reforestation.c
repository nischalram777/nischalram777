#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LAND_SIZE 10
#define NUM_TREES 10

typedef struct {
    char type[10];
    int age;
    int carbon_sequestration;
    int is_alive;
} Tree;

void initialize_land(Tree land[LAND_SIZE][LAND_SIZE]) {
    for (int i = 0; i < LAND_SIZE; i++) {
        for (int j = 0; j < LAND_SIZE; j++) {
            land[i][j].is_alive = 0;
        }
    }
}

void plant_tree(Tree land[LAND_SIZE][LAND_SIZE], const char* tree_type, int carbon_sequestration) {
    int x = rand() % LAND_SIZE;
    int y = rand() % LAND_SIZE;

    if (land[x][y].is_alive == 0) {
        land[x][y].is_alive = 1;
        land[x][y].age = 0;
        land[x][y].carbon_sequestration = carbon_sequestration;
        snprintf(land[x][y].type, 10, "%s", tree_type);
        printf("Planted a %s tree at (%d, %d).\n", tree_type, x, y);
    } else {
        plant_tree(land, tree_type, carbon_sequestration);
    }
}

void simulate_deforestation(Tree land[LAND_SIZE][LAND_SIZE]) {
    int deforested_trees = rand() % 5;
    for (int i = 0; i < deforested_trees; i++) {
        int x = rand() % LAND_SIZE;
        int y = rand() % LAND_SIZE;

        if (land[x][y].is_alive) {
            land[x][y].is_alive = 0;
            printf("Deforested a tree at (%d, %d).\n", x, y);
        }
    }
}

void simulate_growth(Tree land[LAND_SIZE][LAND_SIZE], int years) {
    for (int year = 1; year <= years; year++) {
        printf("\nYear %d:\n", year);
        int total_carbon = 0;

        for (int i = 0; i < LAND_SIZE; i++) {
            for (int j = 0; j < LAND_SIZE; j++) {
                if (land[i][j].is_alive) {
                    land[i][j].age++;
                    total_carbon += land[i][j].carbon_sequestration;
                    printf("Tree at (%d, %d) grew by 1 year. Age: %d, Carbon Sequestration: %d kg/year\n", i, j, land[i][j].age, land[i][j].carbon_sequestration);
                }
            }
        }

        printf("Total Carbon Sequestration this year: %d kg\n", total_carbon);
        simulate_deforestation(land);
    }
}

void display_land(Tree land[LAND_SIZE][LAND_SIZE]) {
    printf("\nFinal Land Status (T = Tree, D = Deforested):\n");
    for (int i = 0; i < LAND_SIZE; i++) {
        for (int j = 0; j < LAND_SIZE; j++) {
            if (land[i][j].is_alive) {
                printf("T ");
            } else {
                printf("D ");
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(0));

    Tree land[LAND_SIZE][LAND_SIZE];
    initialize_land(land);

    plant_tree(land, "Oak", 100);
    plant_tree(land, "Pine", 150);
    plant_tree(land, "Maple", 80);
    plant_tree(land, "Cedar", 120);
    plant_tree(land, "Birch", 90);
    plant_tree(land, "Spruce", 110);
    plant_tree(land, "Bamboo", 60);
    plant_tree(land, "Teak", 130);
    plant_tree(land, "Mahogany", 140);
    plant_tree(land, "Eucalyptus", 160);

    simulate_growth(land, 5);

    display_land(land);

    return 0;
}
