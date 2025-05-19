#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

/***************************/
/* IMPLEMENTASI NON BINARY TREE */
/***************************/

void Create_tree(Isi_Tree X, int Jml_Node) {
    /* Create Non Binary Tree sebanyak Jml_Node */
    /* Tujuan mengentrykan Non Binary Tree ke array Isi_Tree dengan pola Level Order */
    /* Jml Node adalah banyaknya elemen dalam Tree yang menjadi parameter input */
    
    int i;
    infotype info;
    address fs, nb;
    
    // Inisialisasi semua node
    for (i = 0; i <= jml_maks; i++) {
        X[i].info = ' ';
        X[i].ps_fs = nil;
        X[i].ps_nb = nil;
        X[i].ps_pr = nil;
    }
    
    printf("Masukkan data untuk %d node secara level order:\n", Jml_Node);
    
    // Input untuk root (node pertama)
    printf("Node ke-1 (Root): ");
    scanf(" %c", &info);
    X[1].info = info;
    X[1].ps_pr = nil; // Root tidak memiliki parent
    
    // Input untuk node-node selanjutnya
    for (i = 2; i <= Jml_Node; i++) {
        printf("Node ke-%d: ", i);
        scanf(" %c", &X[i].info);
        
        // Input parent dari node tersebut
        printf("Parent dari node %c (posisi): ", X[i].info);
        scanf("%d", &X[i].ps_pr);
        
        // Update struktur tree
        // Jika parent belum memiliki first son, maka node ini menjadi first son
        if (X[X[i].ps_pr].ps_fs == nil) {
            X[X[i].ps_pr].ps_fs = i;
        } else {
            // Jika parent sudah memiliki first son, maka cari next brother yang kosong
            int current = X[X[i].ps_pr].ps_fs;
            while (X[current].ps_nb != nil) {
                current = X[current].ps_nb;
            }
            X[current].ps_nb = i;
        }
    }
}

boolean IsEmpty(Isi_Tree P) {
    /* Mengirimkan true jika Isi_Tree KOSONG */
    return (P[1].info == ' ');
}

/***** Traversal *****/

void PreOrderUtil(Isi_Tree P, int root) {
    if (root != nil) {
        // Proses root
        printf("%c ", P[root].info);
        
        // Proses first son
        int fs = P[root].ps_fs;
        while (fs != nil) {
            PreOrderUtil(P, fs);
            fs = P[fs].ps_nb;
        }
    }
}

void PreOrder(Isi_Tree P) {
    /* Traversal PreOrder */
    /* IS : P terdefinisi */
    /* FS : Semua simpul P sudah ditampilkan secara PreOrder : Parent, fs, nb */
    
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    PreOrderUtil(P, 1);  // Mulai dari root (indeks 1)
    printf("\n");
}

void InOrderUtil(Isi_Tree P, int root) {
    if (root != nil) {
        // Proses first son (jika ada)
        if (P[root].ps_fs != nil) {
            InOrderUtil(P, P[root].ps_fs);
        }
        
        // Proses root
        printf("%c ", P[root].info);
        
        // Proses sisa anak (next brothers dari first son)
        if (P[root].ps_fs != nil) {
            int nb = P[P[root].ps_fs].ps_nb;
            while (nb != nil) {
                InOrderUtil(P, nb);
                nb = P[nb].ps_nb;
            }
        }
    }
}

void InOrder(Isi_Tree P) {
    /* Traversal InOrder */
    /* IS : P terdefinisi */
    /* FS : Semua simpul P sudah ditampilkan secara InOrder : fs, Parent, Sisa anak lain */
    
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    InOrderUtil(P, 1);  // Mulai dari root (indeks 1)
    printf("\n");
}

void PostOrderUtil(Isi_Tree P, int root) {
    if (root != nil) {
        // Proses semua anak
        int fs = P[root].ps_fs;
        while (fs != nil) {
            PostOrderUtil(P, fs);
            fs = P[fs].ps_nb;
        }
        
        // Proses root
        printf("%c ", P[root].info);
    }
}

void PostOrder(Isi_Tree P) {
    /* Traversal PostOrder */
    /* IS : P terdefinisi */
    /* FS : Semua simpul P sudah ditampilkan secara PostOrder : fs, nb, Parent */
    
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    PostOrderUtil(P, 1);  // Mulai dari root (indeks 1)
    printf("\n");
}

void Level_order(Isi_Tree X, int Maks_node) {
    /* Traversal LevelOrder */
    /* IS : P terdefinisi */
    /* FS : Semua simpul P sudah ditampilkan secara Level Order */
    
    if (IsEmpty(X)) {
        printf("Tree kosong\n");
        return;
    }
    
    int i;
    for (i = 1; i <= Maks_node; i++) {
        if (X[i].info != ' ') {
            printf("%c ", X[i].info);
        }
    }
    printf("\n");
}

void PrintTreeUtil(Isi_Tree P, int root, int level) {
    int i;
    
    if (root != nil) {
        // Print indentasi berdasarkan level
        for (i = 0; i < level; i++) {
            printf("  ");
        }
        
        // Print node
        printf("%c\n", P[root].info);
        
        // Print first son dan siblings
        int fs = P[root].ps_fs;
        while (fs != nil) {
            PrintTreeUtil(P, fs, level + 1);
            fs = P[fs].ps_nb;
        }
    }
}

void PrintTree(Isi_Tree P) {
    /* IS : P terdefinisi */
    /* FS : Semua simpul P sudah ditulis ke layar */
    
    if (IsEmpty(P)) {
        printf("Tree kosong\n");
        return;
    }
    
    PrintTreeUtil(P, 1, 0);  // Mulai dari root (indeks 1) dengan level 0
}

/***** Search *****/

boolean SearchUtil(Isi_Tree P, int root, infotype X) {
    if (root == nil) {
        return false;
    }
    
    // Cek node saat ini
    if (P[root].info == X) {
        return true;
    }
    
    // Cek first son
    if (SearchUtil(P, P[root].ps_fs, X)) {
        return true;
    }
    
    // Cek next brother
    return SearchUtil(P, P[root].ps_nb, X);
}

boolean Search(Isi_Tree P, infotype X) {
    /* Mengirimkan true jika ada node dari P yang bernilai X */
    
    if (IsEmpty(P)) {
        return false;
    }
    
    return SearchUtil(P, 1, X);  // Mulai dari root (indeks 1)
}

/***** Fungsi Lain *****/

int nbElmtUtil(Isi_Tree P, int root) {
    if (root == nil) {
        return 0;
    }
    
    int count = 1;  // Hitung node saat ini
    
    // Hitung semua anak
    int fs = P[root].ps_fs;
    while (fs != nil) {
        count += nbElmtUtil(P, fs);
        fs = P[fs].ps_nb;
    }
    
    return count;
}

int nbElmt(Isi_Tree P) {
    /* Mengirimkan banyak elemen (node) di pohon non biner P */
    
    if (IsEmpty(P)) {
        return 0;
    }
    
    return nbElmtUtil(P, 1);  // Mulai dari root (indeks 1)
}

int nbDaunUtil(Isi_Tree P, int root) {
    if (root == nil) {
        return 0;
    }
    
    // Jika node tidak memiliki anak (first son), maka node tersebut adalah daun
    if (P[root].ps_fs == nil) {
        return 1;
    }
    
    int count = 0;
    
    // Hitung daun dari semua anak
    int fs = P[root].ps_fs;
    while (fs != nil) {
        count += nbDaunUtil(P, fs);
        fs = P[fs].ps_nb;
    }
    
    return count;
}

int nbDaun(Isi_Tree P) {
    /* Mengirimkan banyak daun (node) pohon non biner P */
    
    if (IsEmpty(P)) {
        return 0;
    }
    
    return nbDaunUtil(P, 1);  // Mulai dari root (indeks 1)
}

int LevelUtil(Isi_Tree P, int root, infotype X, int currentLevel) {
    if (root == nil) {
        return -1;  // Node tidak ditemukan
    }
    
    // Jika node ditemukan
    if (P[root].info == X) {
        return currentLevel;
    }
    
    // Cari di first son
    int level = LevelUtil(P, P[root].ps_fs, X, currentLevel + 1);
    if (level != -1) {
        return level;
    }
    
    // Cari di next brother (dengan level yang sama)
    return LevelUtil(P, P[root].ps_nb, X, currentLevel);
}

int Level(Isi_Tree P, infotype X) {
    /* Mengirimkan level dari node X yang merupakan salah satu simpul */
    /* dr pohon P. Akar (P) levelnya adalah 0. Pohon tidak kosong */
    
    if (IsEmpty(P)) {
        return -1;
    }
    
    return LevelUtil(P, 1, X, 0);  // Mulai dari root (indeks 1) dengan level 0
}

int DepthUtil(Isi_Tree P, int root) {
    if (root == nil) {
        return -1;
    }
    
    int maxDepth = -1;
    
    // Cari kedalaman maksimum dari semua anak
    int fs = P[root].ps_fs;
    while (fs != nil) {
        int depth = DepthUtil(P, fs);
        if (depth > maxDepth) {
            maxDepth = depth;
        }
        fs = P[fs].ps_nb;
    }
    
    return maxDepth + 1;  // Tambahkan 1 untuk level node saat ini
}

int Depth(Isi_Tree P) {
    /* Pohon Biner mungkin Kosong, mengirimkan 'depth' yaitu tinggi dari Pohon */
    /* Basis : Pohon Kosong, tingginya Nol */
    
    if (IsEmpty(P)) {
        return 0;
    }
    
    return DepthUtil(P, 1);  // Mulai dari root (indeks 1)
}

int Max(infotype Data1, infotype Data2) {
    /* Mengirimkan Nilai terbesar dari dua data */
    
    return (Data1 > Data2) ? Data1 : Data2;
}