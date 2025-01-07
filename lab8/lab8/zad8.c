#include <stdio.h>
#include <stdlib.h>

typedef struct Stablo {
    int podatak;     
    struct Stablo* lijevi; 
    struct Stablo* desni; 
    struct Stablo* roditelj; 
} Stablo;


typedef struct Stablo* Cvor;


Cvor noviCvor(int podatak, Cvor roditelj) {
    Cvor novi = (Cvor)malloc(sizeof(Stablo));  
    if (novi == NULL) {
        printf("Pogreška pri alociranju memorije!\n");
        return NULL;
    }
    novi->podatak = podatak;
    novi->lijevi = NULL;
    novi->desni = NULL;
    novi->roditelj = roditelj; 
    return novi;
}


Cvor umetni(Cvor korijen, int podatak) {
    if (korijen == NULL) {
        return noviCvor(podatak, NULL);  
    }

    
    if (podatak < korijen->podatak) {
        korijen->lijevi = umetni(korijen->lijevi, podatak);
        korijen->lijevi->roditelj = korijen; 
    }
   
    else {
        korijen->desni = umetni(korijen->desni, podatak);
        korijen->desni->roditelj = korijen;  
    }
    return korijen;
}

// inorder (lijevo, korijen, desno)
void inorder(Cvor korijen) {
    if (korijen != NULL) {
        inorder(korijen->lijevi);  
        printf("%d ", korijen->podatak);  
        inorder(korijen->desni);  
    }
}

//preorder (korijen, lijevo, desno)
void preorder(Cvor korijen) {
    if (korijen != NULL) {
        printf("%d ", korijen->podatak);  
        preorder(korijen->lijevi);  
        preorder(korijen->desni);  
    }
}

//  postorder (lijevo, desno, korijen)
void postorder(Cvor korijen) {
    if (korijen != NULL) {
        postorder(korijen->lijevi); 
        postorder(korijen->desni);  
        printf("%d ", korijen->podatak);  
    }
}


void levelOrder(Cvor korijen) {
    if (korijen == NULL) return;

    Cvor red[100];  
    int pocetak = 0, kraj = 0;

    red[kraj++] = korijen;  

    while (pocetak < kraj) {
        Cvor trenutni = red[pocetak++]; 
        printf("%d ", trenutni->podatak);  

        if (trenutni->lijevi != NULL) {
            red[kraj++] = trenutni->lijevi;  
        }
        if (trenutni->desni != NULL) {
            red[kraj++] = trenutni->desni;  
        }
    }
}


Cvor pronadi(Cvor korijen, int podatak) {
    if (korijen == NULL || korijen->podatak == podatak) {
        return korijen; 
    }
    if (podatak < korijen->podatak) {
        return pronadi(korijen->lijevi, podatak);  
    }
    else {
        return pronadi(korijen->desni, podatak); 
    }
}


Cvor najmanji(Cvor korijen) {
    while (korijen != NULL && korijen->lijevi != NULL) {
        korijen = korijen->lijevi;  
    }
    return korijen;
}


Cvor obrisi(Cvor korijen, int podatak) {
    if (korijen == NULL) return korijen;  

    if (podatak < korijen->podatak) {
        korijen->lijevi = obrisi(korijen->lijevi, podatak);  
    }
    else if (podatak > korijen->podatak) {
        korijen->desni = obrisi(korijen->desni, podatak);  
    }
    else {
        
        if (korijen->lijevi == NULL) {
            Cvor temp = korijen->desni;  
            free(korijen);
            return temp;
        }
        else if (korijen->desni == NULL) {
            Cvor temp = korijen->lijevi;  
            free(korijen);
            return temp;
        }

        
        Cvor najmanjiCvor = najmanji(korijen->desni);
        korijen->podatak = najmanjiCvor->podatak;  
        korijen->desni = obrisi(korijen->desni, najmanjiCvor->podatak);  
    }
    return korijen;
}


int main() {
    Cvor stablo = NULL;  

   
    stablo = umetni(stablo, 50);
    stablo = umetni(stablo, 30);
    stablo = umetni(stablo, 70);
    stablo = umetni(stablo, 20);
    stablo = umetni(stablo, 40);
    stablo = umetni(stablo, 60);
    stablo = umetni(stablo, 80);

    
    printf("Inorder: ");
    inorder(stablo);
    printf("\n");

    printf("Preorder: ");
    preorder(stablo);
    printf("\n");

    printf("Postorder: ");
    postorder(stablo);
    printf("\n");

    printf("Level Order: ");
    levelOrder(stablo);
    printf("\n");

   
    int trazeni = 40;
    Cvor pronadeniCvor = pronadi(stablo, trazeni);
    if (pronadeniCvor != NULL) {
        printf("Element %d pronaden u stablu.\n", trazeni);
    }
    else {
        printf("Element %d nije pronaðen u stablu.\n", trazeni);
    }

    
    stablo = obrisi(stablo, 30);  
    printf("Inorder nakon brisanja 30: ");
    inorder(stablo);
    printf("\n");

    return 0;
}