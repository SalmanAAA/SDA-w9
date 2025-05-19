#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "nbtrees.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader() {
    printf("============================================\n");
    printf("      PROGRAM NON BINARY TREE (NBT)\n");
    printf("          REPRESENTASI ARRAY\n");
    printf("============================================\n\n");
}

void createExampleTree(Isi_Tree tree) {
    for (int i = 0; i <= jml_maks; i++) {
        tree[i].info = ' ';
        tree[i].ps_fs = nil;
        tree[i].ps_nb = nil;
        tree[i].ps_pr = nil;
    }

    tree[1].info = 'A'; tree[1].ps_fs = 2;
    tree[2].info = 'B'; tree[2].ps_pr = 1; tree[2].ps_fs = 5; tree[2].ps_nb = 3;
    tree[3].info = 'C'; tree[3].ps_pr = 1; tree[3].ps_nb = 4;
    tree[4].info = 'D'; tree[4].ps_pr = 1; tree[4].ps_fs = 7;
    tree[5].info = 'E'; tree[5].ps_pr = 2; tree[5].ps_nb = 6;
    tree[6].info = 'F'; tree[6].ps_pr = 2;
    tree[7].info = 'G'; tree[7].ps_pr = 4; tree[7].ps_fs = 9; tree[7].ps_nb = 8;
    tree[8].info = 'H'; tree[8].ps_pr = 4;
    tree[9].info = 'I'; tree[9].ps_pr = 7; tree[9].ps_nb = 10;
    tree[10].info = 'J'; tree[10].ps_pr = 7;
}

void displayTreeInfo(Isi_Tree tree) {
    printf("======= INFORMASI TREE =======\n");
    printf("Jumlah Node : %d\n", nbElmt(tree));
    printf("Jumlah Daun : %d\n", nbDaun(tree));
    printf("Kedalaman   : %d\n\n", Depth(tree));
}

void displayInternalStructure(Isi_Tree tree, int jmlNode) {
    printf("======= STRUKTUR INTERNAL TREE =======\n");
    printf("IDX | INFO | PARENT | FIRST SON | NEXT BRO\n");
    printf("------------------------------------------\n");
    for (int i = 1; i <= jmlNode; i++) {
        if (tree[i].info != ' ') {
            printf("%3d |  %c   |   %2d   |     %2d     |    %2d\n",
                i, tree[i].info, tree[i].ps_pr, tree[i].ps_fs, tree[i].ps_nb);
        }
    }
    printf("\n");
}

int main() {
    Isi_Tree tree;
    int jmlNode, choice;
    infotype searchChar;
    boolean useExampleTree = false;
    boolean treeCreated = false;
    char option;

    clearScreen();
    printHeader();

    do {
        printf("Gunakan contoh tree? (Y/N): ");
        scanf(" %c", &option);
        option = toupper(option);
    } while (option != 'Y' && option != 'N');

    if (option == 'Y') {
        createExampleTree(tree);
        jmlNode = 10;
        treeCreated = true;
        useExampleTree = true;
        printf("Contoh tree berhasil dibuat!\n");
    } else {
        printf("Masukkan jumlah node (maks %d): ", jml_maks);
        scanf("%d", &jmlNode);

        if (jmlNode > jml_maks || jmlNode <= 0) {
            printf("Jumlah node tidak valid!\n");
            return 1;
        }

        Create_tree(tree, jmlNode);
        treeCreated = true;
    }

    do {
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
        if (getchar() == '\n') {
            clearScreen();
            printHeader();
        }

        if (treeCreated) {
            displayTreeInfo(tree);
        }

        printf("=========== MENU ===========\n");
        printf("1. Cetak Tree\n");
        printf("2. Traversal PreOrder\n");
        printf("3. Traversal InOrder\n");
        printf("4. Traversal PostOrder\n");
        printf("5. Traversal LevelOrder\n");
        printf("6. Cari Node\n");
        printf("7. Jumlah Node\n");
        printf("8. Jumlah Daun\n");
        printf("9. Level dari Node\n");
        printf("10. Kedalaman Tree\n");
        printf("11. Tampilkan Struktur Internal\n");
        printf("12. Buat Tree Baru\n");
        printf("0. Keluar\n");
        printf("============================\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Cetak Tree ---\n");
                PrintTree(tree);
                break;
            case 2:
                printf("\n--- Traversal PreOrder ---\n");
                PreOrder(tree);
                break;
            case 3:
                printf("\n--- Traversal InOrder ---\n");
                InOrder(tree);
                break;
            case 4:
                printf("\n--- Traversal PostOrder ---\n");
                PostOrder(tree);
                break;
            case 5:
                printf("\n--- Traversal LevelOrder ---\n");
                Level_order(tree, jmlNode);
                break;
            case 6:
                printf("\n--- Cari Node ---\n");
                printf("Masukkan karakter: ");
                scanf(" %c", &searchChar);
                if (Search(tree, searchChar)) {
                    printf("Node %c ditemukan.\n", searchChar);
                } else {
                    printf("Node %c tidak ditemukan.\n", searchChar);
                }
                break;
            case 7:
                printf("Jumlah node: %d\n", nbElmt(tree));
                break;
            case 8:
                printf("Jumlah daun: %d\n", nbDaun(tree));
                break;
            case 9:
                printf("Masukkan karakter node: ");
                scanf(" %c", &searchChar);
                int lvl = Level(tree, searchChar);
                if (lvl != -1) {
                    printf("Level node %c adalah: %d\n", searchChar, lvl);
                } else {
                    printf("Node %c tidak ditemukan.\n", searchChar);
                }
                break;
            case 10:
                printf("Kedalaman tree: %d\n", Depth(tree));
                break;
            case 11:
                displayInternalStructure(tree, jmlNode);
                break;
            case 12:
                do {
                    printf("Gunakan contoh tree? (Y/N): ");
                    scanf(" %c", &option);
                    option = toupper(option);
                } while (option != 'Y' && option != 'N');

                if (option == 'Y') {
                    createExampleTree(tree);
                    jmlNode = 10;
                    treeCreated = true;
                    useExampleTree = true;
                    printf("Contoh tree berhasil dibuat!\n");
                } else {
                    printf("Masukkan jumlah node (maks %d): ", jml_maks);
                    scanf("%d", &jmlNode);

                    if (jmlNode > jml_maks || jmlNode <= 0) {
                        printf("Jumlah node tidak valid!\n");
                        continue;
                    }

                    Create_tree(tree, jmlNode);
                    treeCreated = true;
                }
                break;
            case 0:
                printf("Terima kasih! Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 0);

    return 0;
}
