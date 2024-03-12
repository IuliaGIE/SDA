/*Giuroiu Iulia Elena 313CC*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct COLOR
{
    unsigned char red, green, blue;
} COLOR;
typedef struct QuadTreeNode
{
    unsigned int x, y, size;          // Coordonatele si dimensiunea cvadrantului
    unsigned char type;               // 0 - nod intern, 1 - nod frunza
    COLOR color;                      // Culorile cvadrantului
    struct QuadTreeNode *children[4]; // Copii
} QuadTreeNode;

// Aloca memorie pentru matrice
COLOR **aloca_matricea(int n)
{
    int i;
    COLOR **matrice = (COLOR **)malloc(n * sizeof(COLOR *));
    for (i = 0; i < n; i++)
    {
        matrice[i] = (COLOR *)malloc(n * sizeof(COLOR));
    }
    return matrice;
}

// Elibereaza memoria matricei de pixeli
void elibereaza_matricea(COLOR **matrice, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}

// Alcatuieste arborele cuaternal
QuadTreeNode *buildQuadTree(COLOR **image, unsigned int x, unsigned int y, unsigned int size, unsigned int factor)
{
    QuadTreeNode *node = (QuadTreeNode *)malloc(sizeof(QuadTreeNode));
    node->x = x;
    node->y = y;
    node->size = size;
    node->type = 0; // nod intern
    unsigned long long sred = 0, sgreen = 0, sblue = 0, i, j;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            sred += image[i][j].red;
            sgreen += image[i][j].green;
            sblue += image[i][j].blue;
        }

    // Culoarea medie
    unsigned long long red = 0, green = 0, blue = 0;
    red = sred / (size * size);
    green = sgreen / (size * size);
    blue = sblue / (size * size);

    // se calculeaza un scor al similaritatii pentru blocul respectiv
    unsigned long long smean = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            smean += (red - image[i][j].red) * (red - image[i][j].red)
             + (green - image[i][j].green) * (green - image[i][j].green) 
             + (blue - image[i][j].blue) * (blue - image[i][j].blue);
        }
    unsigned long long mean = 0;
    mean = smean / (3 * size * size);
    if (mean <= factor || size == 1 || mean == 0){
        // Blocul poate fi reprezentat ca un nod frunza
        node->type = 1;
        node->color.red = red;
        node->color.green = green;
        node->color.blue = blue;
        node->children[0] = NULL;
        node->children[1] = NULL;
        node->children[2] = NULL;
        node->children[3] = NULL;
    }
    else{
        // Blocul trebuie divizat în 4
        node->type = 0;
        node->color.red = 0;
        node->color.green = 0;
        node->color.blue = 0;
        node->children[0] = buildQuadTree(image, x, y, size / 2, factor);
        node->children[1] = buildQuadTree(image, x, y + size / 2, size / 2, factor);
        node->children[3] = buildQuadTree(image, x + size / 2, y, size / 2, factor);
        node->children[2] = buildQuadTree(image, x + size / 2, y + size / 2, size / 2, factor);
    }
    return node;
}

// Determinarea numarului de niveluri
int num_levels(QuadTreeNode *node)
{
    int i;
    if (node == NULL) {
        return 0;
    }

    if (node->type == 1) { // nod frunză
        return 1;
    }

    unsigned int maxChildLevel = 0;
    for ( i = 0; i < 4; i++) {
        unsigned int childLevel = num_levels(node->children[i]);
        if (childLevel > maxChildLevel) {
            maxChildLevel = childLevel;
        }
    }

    return maxChildLevel + 1;
}

// Determinarea numarului de frunze
int countLeaves(QuadTreeNode *node) {
    int i;
    // dacă nodul este frunza, returnam 1
    if (node->type == 1) {
        return 1;
    }
    
    // altfel, numaram frunzele copiilor
    int count = 0;
    for ( i = 0; i < 4; i++) {
        if (node->children[i] != NULL) {
            count += countLeaves(node->children[i]);
        }
    }
    
    return count;
}

// Cel mai mare size al unei frunze
unsigned int getMaxLeafSize(QuadTreeNode* node)
{
    int i;
    if (node == NULL) {
        return 0;
    }

    if (node->type == 1) { // nod frunză
        return node->size;
    }

    unsigned int maxLeafSize = 0;
    for (i = 0; i < 4; i++) {
        unsigned int leafSize = getMaxLeafSize(node->children[i]);
        if (leafSize > maxLeafSize) {
            maxLeafSize = leafSize;
        }
    }

    return maxLeafSize;
}

// Cerinta 1
void cerinta1(QuadTreeNode *node, int *nivel, int *nr_bloc, int *dim){
    *nivel = num_levels(node);
    *nr_bloc = countLeaves(node);
    *dim = getMaxLeafSize(node);
}

// Cerinta 2
// Afiseaza nivelul specificat de noduri dintr-un arbore.
void printLevelNodes(QuadTreeNode *node, int level, FILE *out) {
    if (node == NULL) {
        return;
    }
    if (level == 0) {
        if(node->type == 0) {
            fwrite(&node->type, sizeof(unsigned char), 1, out);
        }
        else {
            fwrite(&node->type, sizeof(unsigned char), 1, out);
            fwrite(&node->color, sizeof(COLOR), 1, out);
        }
    } else {
        // Daca nivelul nu este zero, functia apelaza recursiv 
        //functia printLevelNodes pentru fiecare dintre cei patru copii
        printLevelNodes(node->children[0], level-1, out);
        printLevelNodes(node->children[1], level-1, out);
        printLevelNodes(node->children[2], level-1, out);
        printLevelNodes(node->children[3], level-1, out);
    }
}

// Afiseaza întreg arborele prin apelarea functiei printLevelNodes
void printQuadTreeLevelOrder(QuadTreeNode *node, FILE* out) {
    int height = num_levels(node);
    int level;
    for (level = 0; level <= height; level++) {
        printLevelNodes(node, level, out);
    }

}
// Elibereaza memoria alocata arborelui
void freeQuadTree(QuadTreeNode* node)
{
    int i;
    if (node == NULL) {
        return;
    }
    for (i = 0; i < 4; i++) {
        freeQuadTree(node->children[i]);
    }
    free(node);
}

int main(int argc, char *argv[])
{
    // ./quadtree [-c1 factor | -c2 factor | -d] [fisier_intrare] [fisier_iesire]
    // Verificam optiunea specificata si prelucram în consecinta
    if (strcmp(argv[1], "-c1") == 0)
    {
        // Cerința 1
        unsigned int factor = atoi(argv[2]);
        // Citim din fisierul de intrare si scriem în fisierul de iesire
        FILE *in = fopen(argv[3], "rb");
        FILE *out = fopen(argv[4], "wb");
        char format[3];
        unsigned int width, height, max_color;
        if (in == NULL || out == NULL)
        {
            printf("Nu am putut deschide fisierele.\n");
            return 1;
        }

        fscanf(in, "%s", format);
        if (format[0] != 'P' || format[1] != '6')
        {
            printf("Fisierul nu este in formatul PPM.\n");
            return 1;
        }
        // Citeste dimensiunile imaginii
        fscanf(in, "%u %u", &width, &height);

        // Citeste valoarea maxima a culorilor
        fscanf(in, "%u", &max_color);

        // Declaram si alocam matricea
        COLOR **image = aloca_matricea(width);

        // Citeste si salveaza fiecare pixel din matrice
        int i, j;
        char c;
        fread(&c, sizeof(char), 1, in);
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                fread(&image[i][j], sizeof(COLOR), 1, in);
            }
        }
        QuadTreeNode *root = buildQuadTree(image, 0, 0, width, factor);
        int nivel, frunze, dimensiune;
        cerinta1(root, &nivel, &frunze, &dimensiune);
        fprintf(out ,"%d\n%d\n%d\n", nivel, frunze, dimensiune);
        elibereaza_matricea(image, width);
        fclose(in);
        fclose(out);
        freeQuadTree(root);
    }
    else if (strcmp(argv[1], "-c2") == 0)
    {
        // Cerinta 2
        int factor = atoi(argv[2]);
        // Citim din fisierul de intrare si scriem în fisierul de iesire
        FILE *in = fopen(argv[3], "rb");
        FILE *out = fopen(argv[4], "wb");
        char format[3];
        unsigned int width, height, max_color;
        if (in == NULL || out == NULL)
        {
            printf("Nu am putut deschide fisierele.\n");
            return 1;
        }

        fscanf(in, "%s", format);
        if (format[0] != 'P' || format[1] != '6')
        {
            printf("Fisierul nu este in formatul PPM.\n");
            return 1;
        }
        // Citeste dimensiunile imaginii
        fscanf(in, "%u %u", &width, &height);

        // Citeste valoarea maxima a culorilor
        fscanf(in, "%u", &max_color);

        // Declaram si alocam matricea
        COLOR **image = aloca_matricea(width);

        // Citeste si salveaza fiecare pixel din matrice
        int i, j;
        char c;
        fread(&c, sizeof(char), 1, in);
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                fread(&image[i][j], sizeof(COLOR), 1, in);
            }
        }
        QuadTreeNode *root = buildQuadTree(image, 0, 0, width, factor);

        // ... prelucrare ...
        fwrite(&width, sizeof(unsigned int), 1, out);
        printQuadTreeLevelOrder(root, out);
        elibereaza_matricea(image, width);
        fclose(in);
        fclose(out);
        freeQuadTree(root);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        // Cerinta 3
        // Citim din fisierul de intrare si scriem în fisierul de iesire
        FILE *in = fopen(argv[2], "rb");
        FILE *out = fopen(argv[3], "wb");

        // ... prelucrare ...

        fclose(in);
        fclose(out);
    }
    else
    {
        printf("Optiunea specificata nu este valida: %s\n", argv[1]);
        return 1;
    }

    return 0;
}