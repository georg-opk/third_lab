#include <stdio.h>
#include "mycalc.h"

int main(int argc, char *argv[]) {
    Node *flight1 = NULL;
    TreeNode *flight2 = NULL;
    //read_file(argv[1], &flight1);
    read_file("flight_data14.bin", &flight1);
    Node *current = flight1;
    while (current != NULL) {
        flight2 = appendTree(flight2, current->timestamp_ms, current->lon_rad, current->lat_rad, current->alt_m);
        current = current->next;
    }
    printStatistics(flight1, flight2);

    writeStatistics("stat.txt", flight1, flight2);

    free(flight1);
    return 0;
    //123
}