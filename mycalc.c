#include "mycalc.h"
#include "string.h"

Node *createNodeArr(uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (!newNode) {
        exit(1);
    }
    newNode->timestamp_ms = timestamp_ms;
    newNode->lat_rad = lat_rad;
    newNode->lon_rad = lon_rad;
    newNode->alt_m = alt_m;
    newNode->next = NULL;
    return newNode;
}

void appendArr(Node **head, uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m) {
    Node *newNode = createNodeArr(timestamp_ms, lat_rad, lon_rad, alt_m);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printingArr(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%u %f %f %f\n", current->timestamp_ms, current->lat_rad, current->lon_rad, current->alt_m);
        current = current->next;
    }
    printf("NULL\n");
}

void freeArr(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

int countPoints(Node *head) {
    int count = 0;
    Node *current = head;
    while (current != NULL) {
        count += 1;
        current = current->next;
    }

    return count;
}

uint32_t durationFlight(Node *head) {
    uint32_t duration = 0;
    Node *current = head;
    while (current != NULL) {
        duration += current->timestamp_ms;
        current = current->next;
    }

    return duration;

}


TreeNode *createNodeTree(uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->timestamp_ms = timestamp_ms;
        newNode->lat_rad = lat_rad;
        newNode->lon_rad = lon_rad;
        newNode->alt_m = alt_m;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

TreeNode *appendTree(TreeNode *cursor, uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m) {
    if (cursor == NULL) return createNodeTree(timestamp_ms, lat_rad, lon_rad, alt_m);

    if (alt_m < cursor->alt_m) cursor->left = appendTree(cursor->left, timestamp_ms, lat_rad, lon_rad, alt_m);
    else if (alt_m > cursor->alt_m) cursor->right = appendTree(cursor->right, timestamp_ms, lat_rad, lon_rad, alt_m);

    return cursor;
}

void NLR(TreeNode *root) {
    if (root != NULL) {
        printf("%f\n", root->alt_m);
        NLR(root->left);
        NLR(root->right);
    }
}

void LNR(TreeNode *root) {
    if (root != NULL) {
        LNR(root->left);
        printf("%f\n", root->alt_m);
        LNR(root->right);
    }
}

void RNL(TreeNode *root) {
    if (root != NULL) {
        RNL(root->right);
        printf("%f\n", root->alt_m);
        RNL(root->left);
    }
}

void freeTree(TreeNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
    return;
}

float findMax(TreeNode *root) {
    if (root == NULL) return 0.0f;

    while (root->right != NULL)
        root = root->right;

    return root->alt_m;
}

float findMin(TreeNode *root) {
    if (root == NULL) return 0.0f;

    while (root->left != NULL)
        root = root->left;

    return root->alt_m;
}


int read_file(char *filename, Node **head) {
    FILE *file = fopen(filename, "rb");

    uint32_t timestamp_ms;
    float lat_rad, lon_rad, alt_m;

    while (fread(&timestamp_ms, sizeof(uint32_t), 1, file) == 1 &&
           fread(&lat_rad, sizeof(float), 1, file) == 1 &&
           fread(&lon_rad, sizeof(float), 1, file) == 1 &&
           fread(&alt_m, sizeof(float), 1, file) == 1) {
        appendArr(head, timestamp_ms, lat_rad, lon_rad, alt_m);
    }

    fclose(file);
    return 0;
}

void printStatistics(Node *head, TreeNode *root) {
    printf("Number of points: %i\n", countPoints(head));
    printf("Duration of flight: %u\n", durationFlight(head));
    printf("Max altitude: %f\n", findMax(root));
}

void writeStatistics(char *filename, Node *head, TreeNode *root) {
    FILE *file = fopen("Statistics", "w");

    int n = countPoints(head);
    uint32_t T = durationFlight(head);
    float alt_max = findMax(root);
    float alt_min = findMin(root);


    fprintf(file, "Количество точек                        : %i;\n", n);
    fprintf(file, "Продолжительность полёта                : %uч-%uм-%uс-%uмс;\n",
            T / 3600000, (T / 1000) % 3600 / 60, (T / 1000) % 60, T % 1000);
    fprintf(file, "Продолжительность полёта в миллисекундах: %uмс;\n", T);
    fprintf(file, "Максимальная высота полёта              : %f;\n", alt_max);
    fprintf(file, "Минимальная высота полёта               : %f;\n", alt_min);

}