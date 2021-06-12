#define _CRT_SECURE_NO_WARNINGS
#define LEN 50 
#define RULES_MAX_LEN 10 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNumber(int a, int b)	//funkcia na generovanie random cisla
{
    return rand() % (b - a + 1) + a;
}

void zaplnenie_pola(int(*p_pole)[], int dlzka_pola)// vyplnenie pola random 1 a 0 + vizualizacia
{
    int i;
    for (i = 0; i < dlzka_pola; i++)
    {
        (*p_pole)[i] = randNumber(0, 1);
        if ((*p_pole)[i] == 0)
        {
            printf(" ");
        }
        if ((*p_pole)[i] == 1)
        {
            printf("*");
        }
    }
}

int rules(int(*s_pole)[], int dlzka_pola_pravidiel)  // spyta sa ake chces pravidla a nasledne ich vlozi do pola
{
    int i;
    int a;
    for (i = 0; i < dlzka_pola_pravidiel; i++)
    {
        printf("Zadaj percento uspechu %d . pravidla:", i);
        scanf("%d", &a);
        (*s_pole)[i] = a;
    }
}

int generateBit(int p) //pravdepodobnost ci bude 0 alebo 1 v novom stave
{
    int c;
    c = randNumber(0, 100);
    if (c <= p)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printState(int(*print_pole)[], int dlzka_pola) // Funkcia, ktora do jedneho riadku vytlaci stav automatu + vizualizacia
{
    int i;
    printf("\n");
    for (i = 0; i < dlzka_pola; i++)
    {
        if ((*print_pole)[i] == 0)
        {
            printf(" ");

        }
        if ((*print_pole)[i] == 1)
        {
            printf("*");
        }
    }
}

void printPravidla(int(*print_pole)[], int dlzka_pola) //vypise pravidla
{
    int i;
    printf("\n");
    for (i = 0; i < dlzka_pola; i++)
    {
        printf("\nPravidlo %i : %d%%", i, (*print_pole)[i]);
    }
}

int sumInWindow(int(*plavajuce_pole)[], int dlzka_pola_pravidiel, int(*pociatocne_pole)[])  //plavajuce okno
{
    int  i, j, a, b, jednotky, plavajuce_okno;
    plavajuce_okno = (dlzka_pola_pravidiel - 2) / 2;
    for (i = 0; i < 80; i++)
    {
        for (j = 0; j < plavajuce_okno; j++)
        {
            jednotky = 0;
            a = i + (j - plavajuce_okno);
            b = i + (j + plavajuce_okno);

            if ((*pociatocne_pole)[a] == 1)
            {
                jednotky = jednotky + 1;
            }
            if ((*pociatocne_pole)[b] == 1)
            {
                jednotky = jednotky + 1;
            }
            if ((*pociatocne_pole)[i + j] == 1)
            {
                jednotky = jednotky + 1;
            }
        }
        (*plavajuce_pole)[i] = jednotky;    //kazdy prvok je pocet jednotiek daneho plavajuceho okna
    }
}

void cellular_automation(int num) //cely priebeh funkcie je tu (sucastou je GenerateNextStep)
{
    int dlzka_pola_pravidiel;
    printf("Zadaj pocet pravidiel : ");
    scanf("%d", &dlzka_pola_pravidiel);
    int pole_pravidiel[dlzka_pola_pravidiel];   //pole pravidiel
    rules(&pole_pravidiel, dlzka_pola_pravidiel);
    printf("\n\n\nDlzka jedneho stavu : %d", LEN);
    printPravidla(&pole_pravidiel, dlzka_pola_pravidiel);

    printf("\n\n\n");

    int pociatocne_pole[LEN]; //pociatocne pole
    zaplnenie_pola(&pociatocne_pole, LEN);
    printf(" Pociatocny stav\n");

    int t;
    int polko[dlzka_pola_pravidiel];
    for (t = 0; t < dlzka_pola_pravidiel; t++)
    {
        polko[t] = pole_pravidiel[t];   // Aby som vedel prehliadat pole s pravidlami
    }

    int q, k, j, x, g, y;
    for (q = 0; q < num; q++) //tu sa vytvara dalsi stav
    {
        int novy_stav[LEN];
        sumInWindow(&novy_stav, LEN, &pociatocne_pole);

        for (k = 0; k < LEN; k++)
        {
            for (j = 0; j < dlzka_pola_pravidiel; j++)
            {
                if (novy_stav[k] == j)
                {
                    x = generateBit(polko[j]);
                    novy_stav[k] = x;
                }
            }
            pociatocne_pole[k] = novy_stav[k]; //pociatocny stav sa zmení na nový 
        }
        printState(&novy_stav, LEN);
        printf(" Interakcia %d\n", q);
    }
}

int main()
{
    int num;     //pocet interakcii
    printf("Zadaj pocet interakcii : ");
    scanf("%d", &num);
    cellular_automation(num);
}