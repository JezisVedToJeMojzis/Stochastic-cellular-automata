#define _CRT_SECURE_NO_WARNINGS
#define LEN 50 
#define RULES_MAX_LEN 10 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randNumber(int a, int b)	//generate random number
{
    return rand() % (b - a + 1) + a;
}

void zaplnenie_pola(int(*p_pole)[], int dlzka_pola)// fill array with random 0 and 1 + visualization
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

int rules(int(*s_pole)[], int dlzka_pola_pravidiel)  // ask user what rules he wants
{
    int i;
    int a;
    for (i = 0; i < dlzka_pola_pravidiel; i++)
    {
        printf("Enter the success rate in percents %d . rule:", i);
        scanf("%d", &a);
        (*s_pole)[i] = a;
    }
}

int generateBit(int p) //propability of 0 and 1 in new state
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

void printState(int(*print_pole)[], int dlzka_pola) // print state of automat into one row
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

void printPravidla(int(*print_pole)[], int dlzka_pola) // print rules
{
    int i;
    printf("\n");
    for (i = 0; i < dlzka_pola; i++)
    {
        printf("\nRule %i : %d%%", i, (*print_pole)[i]);
    }
}

int sumInWindow(int(*plavajuce_pole)[], int dlzka_pola_pravidiel, int(*pociatocne_pole)[])  
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
        (*plavajuce_pole)[i] = jednotky;    
    }
}

void cellular_automation(int num) //whole process and generating next state
{
    int dlzka_pola_pravidiel;
    printf("Enter number of rules : ");
    scanf("%d", &dlzka_pola_pravidiel);
    int pole_pravidiel[dlzka_pola_pravidiel];   //array of rules
    rules(&pole_pravidiel, dlzka_pola_pravidiel);
    printf("\n\n\nLength of one state : %d", LEN);
    printPravidla(&pole_pravidiel, dlzka_pola_pravidiel);

    printf("\n\n\n");

    int pociatocne_pole[LEN]; //starting array
    zaplnenie_pola(&pociatocne_pole, LEN);
    printf(" Initial state\n");

    int t;
    int polko[dlzka_pola_pravidiel];
    for (t = 0; t < dlzka_pola_pravidiel; t++)
    {
        polko[t] = pole_pravidiel[t];   // to be able to check array of rules
    }

    int q, k, j, x, g, y;
    for (q = 0; q < num; q++) // generating next state
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
            pociatocne_pole[k] = novy_stav[k]; //initial state changing to new one
        }
        printState(&novy_stav, LEN);
        printf(" Interaction %d\n", q);
    }
}

int main()
{
    int num;     //number of interactions
    printf("Enter number of interactions: ");
    scanf("%d", &num);
    cellular_automation(num);
}