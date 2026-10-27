
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba {
    char ime[30];
    char prezime[30];
    int godina;
    struct osoba* sljedeci;
} Osoba;

/* Dodavanje na pocetak */
void dodajNaPocetak(Osoba** lista) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    printf("Unesi ime: ");
    scanf("%29s", nova->ime);

    printf("Unesi prezime: ");
    scanf("%29s", nova->prezime);

    printf("Unesi godinu rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = *lista;
    *lista = nova;
}

/* Ispis liste */
void ispisiListu(Osoba* lista) {
    if (lista == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (lista != NULL) {
        printf("%s %s, godina rodenja: %d\n",
            lista->ime, lista->prezime, lista->godina);

        lista = lista->sljedeci;
    }
}

/* Dodavanje na kraj */
void dodajNaKraj(Osoba** lista) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    printf("Unesi ime: ");
    scanf("%29s", nova->ime);

    printf("Unesi prezime: ");
    scanf("%29s", nova->prezime);

    printf("Unesi godinu rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = NULL;

    if (*lista == NULL) {
        *lista = nova;
        return;
    }

    Osoba* tekuca = *lista;

    while (tekuca->sljedeci != NULL) {
        tekuca = tekuca->sljedeci;
    }

    tekuca->sljedeci = nova;
}

/* Pretraga po prezimenu */
Osoba* pronadiOsobu(Osoba* lista, char prezime[]) {
    while (lista != NULL) {
        if (strcmp(lista->prezime, prezime) == 0) {
            return lista;
        }

        lista = lista->sljedeci;
    }

    return NULL;
}

/* Brisanje osobe po prezimenu */
void obrisiOsobu(Osoba** lista, char prezime[]) {
    Osoba* tekuca = *lista;
    Osoba* prethodna = NULL;

    while (tekuca != NULL &&
        strcmp(tekuca->prezime, prezime) != 0) {
        prethodna = tekuca;
        tekuca = tekuca->sljedeci;
    }

    if (tekuca == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    if (prethodna == NULL) {
        *lista = tekuca->sljedeci;
    }
    else {
        prethodna->sljedeci = tekuca->sljedeci;
    }

    free(tekuca);
    printf("Osoba je uspjesno obrisana.\n");
}

/* Pomocna funkcija za unos podataka nove osobe */
Osoba* unesiNovuOsobu(void) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    printf("Unesi ime: ");
    scanf("%29s", nova->ime);

    printf("Unesi prezime: ");
    scanf("%29s", nova->prezime);

    printf("Unesi godinu rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = NULL;

    return nova;
}

/* a) Dodavanje iza odredene osobe */
void dodajIza(Osoba** lista) {
    char prezime[30];

    printf("Iza koje osobe (prezime) zelis dodati novu osobu? ");
    scanf("%29s", prezime);

    Osoba* tekuca = pronadiOsobu(*lista, prezime);

    if (tekuca == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    Osoba* nova = unesiNovuOsobu();

    if (nova == NULL) {
        return;
    }

    nova->sljedeci = tekuca->sljedeci;
    tekuca->sljedeci = nova;

    printf("Osoba je dodana iza odabrane osobe.\n");
}

/* b) Dodavanje ispred odredene osobe */
void dodajIspred(Osoba** lista) {
    char prezime[30];

    printf("Ispred koje osobe (prezime) zelis dodati novu osobu? ");
    scanf("%29s", prezime);

    Osoba* tekuca = *lista;
    Osoba* prethodna = NULL;

    while (tekuca != NULL &&
        strcmp(tekuca->prezime, prezime) != 0) {
        prethodna = tekuca;
        tekuca = tekuca->sljedeci;
    }

    if (tekuca == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    Osoba* nova = unesiNovuOsobu();

    if (nova == NULL) {
        return;
    }

    nova->sljedeci = tekuca;

    if (prethodna == NULL) {
        *lista = nova;
    }
    else {
        prethodna->sljedeci = nova;
    }

    printf("Osoba je dodana ispred odabrane osobe.\n");
}

/* c) Sortiranje po prezimenima */
void sortirajListu(Osoba* lista) {
    if (lista == NULL || lista->sljedeci == NULL) {
        printf("Lista je sortirana.\n");
        return;
    }

    int zamjena;
    Osoba* tekuca;
    Osoba privremena;

    do {
        zamjena = 0;
        tekuca = lista;

        while (tekuca->sljedeci != NULL) {
            if (strcmp(tekuca->prezime,
                tekuca->sljedeci->prezime) > 0) {

                strcpy(privremena.ime, tekuca->ime);
                strcpy(privremena.prezime, tekuca->prezime);
                privremena.godina = tekuca->godina;

                strcpy(tekuca->ime, tekuca->sljedeci->ime);
                strcpy(tekuca->prezime, tekuca->sljedeci->prezime);
                tekuca->godina = tekuca->sljedeci->godina;

                strcpy(tekuca->sljedeci->ime, privremena.ime);
                strcpy(tekuca->sljedeci->prezime, privremena.prezime);
                tekuca->sljedeci->godina = privremena.godina;

                zamjena = 1;
            }

            tekuca = tekuca->sljedeci;
        }
    } while (zamjena);

    printf("Lista je sortirana po prezimenima.\n");
}

/* d) Upis liste u datoteku */
void upisiUDatoteku(Osoba* lista) {
    FILE* dat = fopen("osobe.txt", "w");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return;
    }

    while (lista != NULL) {
        fprintf(dat, "%s %s %d\n",
            lista->ime, lista->prezime, lista->godina);

        lista = lista->sljedeci;
    }

    fclose(dat);
    printf("Lista je spremljena u datoteku osobe.txt.\n");
}

/* e) Citanje liste iz datoteke */
void ucitajIzDatoteke(Osoba** lista) {
    FILE* dat = fopen("osobe.txt", "r");

    if (dat == NULL) {
        printf("Datoteka ne postoji ili se ne moze otvoriti.\n");
        return;
    }

    /* Brisemo staru listu da ne ostanu stari podaci */
    Osoba* tekuca;

    while (*lista != NULL) {
        tekuca = *lista;
        *lista = (*lista)->sljedeci;
        free(tekuca);
    }

    Osoba* zadnja = NULL;

    while (1) {
        Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

        if (nova == NULL) {
            printf("Greska pri alokaciji memorije!\n");
            break;
        }

        if (fscanf(dat, "%29s %29s %d",
            nova->ime, nova->prezime,
            &nova->godina) != 3) {
            free(nova);
            break;
        }

        nova->sljedeci = NULL;

        if (*lista == NULL) {
            *lista = nova;
        }
        else {
            zadnja->sljedeci = nova;
        }

        zadnja = nova;
    }

    fclose(dat);
    printf("Lista je ucitana iz datoteke osobe.txt.\n");
}

/* Glavni program */
int main(void) {
    Osoba* lista = NULL;
    Osoba* pronadena;
    char prezime[30];
    int izbor;

    do {
        printf("\n--- IZBORNIK ---\n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj osobu na kraj\n");
        printf("4. Pronadi osobu po prezimenu\n");
        printf("5. Obrisi osobu po prezimenu\n");
        printf("6. Dodaj osobu iza odredene osobe\n");
        printf("7. Dodaj osobu ispred odredene osobe\n");
        printf("8. Sortiraj listu po prezimenima\n");
        printf("9. Upisi listu u datoteku\n");
        printf("10. Ucitaj listu iz datoteke\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");

        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos!\n");
            break;
        }

        switch (izbor) {
        case 1:
            dodajNaPocetak(&lista);
            break;

        case 2:
            ispisiListu(lista);
            break;

        case 3:
            dodajNaKraj(&lista);
            break;

        case 4:
            printf("Unesi prezime za pretragu: ");
            scanf("%29s", prezime);

            pronadena = pronadiOsobu(lista, prezime);

            if (pronadena != NULL) {
                printf("Pronadena osoba: %s %s, godina rodenja: %d\n",
                    pronadena->ime,
                    pronadena->prezime,
                    pronadena->godina);
            }
            else {
                printf("Osoba nije pronadena.\n");
            }
            break;

        case 5:
            printf("Unesi prezime za brisanje: ");
            scanf("%29s", prezime);
            obrisiOsobu(&lista, prezime);
            break;

        case 6:
            dodajIza(&lista);
            break;

        case 7:
            dodajIspred(&lista);
            break;

        case 8:
            sortirajListu(lista);
            break;

        case 9:
            upisiUDatoteku(lista);
            break;

        case 10:
            ucitajIzDatoteke(&lista);
            break;

        case 0:
            printf("Kraj programa.\n");
            break;

        default:
            printf("Neispravan odabir!\n");
        }

    } while (izbor != 0);

    /* Oslobadanje memorije */
    while (lista != NULL) {
        Osoba* zaBrisanje = lista;
        lista = lista->sljedeci;
        free(zaBrisanje);
    }

    return 0;
}
