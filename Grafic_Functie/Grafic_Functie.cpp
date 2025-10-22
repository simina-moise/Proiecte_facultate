
#include <math.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <winbgim.h>
#include <windows.h>
#include <graphics.h>
#include <unistd.h>
#include <MMsystem.h>
#define infinit INT_MAX
#define epsi 0.0001
#define  MAX 300
#define MAX1 100
using namespace std;

int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);
int top1, top2;
const int max_stiva = 100;

double Opd[max_stiva]; // stiva operanzilor
char Op[max_stiva]; // stiva operatorilor


char projectpath[] = "D:\\FII\Semestrul I\\Introducere în programare\\Proiect_IP_Function_Graph\\src";

char Alfabet[200] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char OperatiiBinare[200] = "+-*/^";
char OperatiiUnare[200] = "sctbdfghnarel";
char Operatii[200] = "+-*/^sctbdfghnarel";
char Cifre[13] = "0123456789qx";
char Caractere_Nepermise[300] = "!@#$%&;'_[]{},~`\|""abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char limba = 'r';

char f_expresie_salvat[31] = "";
char a_salvat[5] = "";
char b_salvat[5] = "";

const float pi = 3.1415926; // se da sub forma literei q

int x, y;
//Variabile booleene care verifica daca se pot desena asimptotele
bool deseneazaAsimptote = false;
bool d_asy;

struct Functie
{
    char expresie[300];
    char vect[MAX][MAX1 + 1]; // vectorul cuprinzand “cuvintele”ce formeaza expresia}
    int lung; // lungimea efectiva a vectorului
    float a, b; // intervalul de evaluare a functiei
    int n; //numarul de puncte de evaluare
    int Tip[MAX];
};

struct Punct {
    double x;
    double y;
};

struct Grafic {
    float x1, x2;
    float y1, y2;
    float x1_ecran, x2_ecran;
    float y1_ecran, y2_ecran;
};

struct apasat
{
    bool citesteFunctie;
    bool minimGraf;
    bool maximGraf;
    bool salveaza;
};

struct coordonateButon
{
    int x1, y1;
    int x2, y2;
};

struct FunctionGraph
{
    Functie F;
    Punct minGraf, maxGraf;
};

coordonateButon functie, a_field, b_field, button_field, info_field, file_field, chenarBackButton, chenarGrafic, chenarReguli, about_field, chenarSetari, music_field, flag_field, chenarIesire;
bool func_pressed, a_pressed, b_pressed, info_pressed;



int Prioritate(char c)  // prioritate operatorilor
{
    if (c == '(' || c == ')')
        return 0;
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    if (c == '=' || c == '#' || c == '<' || c == '>')
        return 4;
    if (c == 'c' || c == 's' || c == 'l' || c == 'e' || c == 't' || c == 'a' || c == 'r')
        return 5;
}

int ok_i, ok_t, ok_c, ok_r, ok_l, ok_lz;
char a[100][100];///matrice de erori
int poz;

void read_file(char str[], char name[])
{
    FILE* fptr;

    char path_file[255] = "";
    strcpy(path_file, projectpath);
    strcat(path_file, "\\files\\");
    strcat(path_file, name);

    if ((fptr = fopen(path_file, "r")) != NULL)
    {
        fscanf(fptr, "%s", str);
        fclose(fptr);
    }
}

void write_file(char str[], char name[])
{
    FILE* fptr;

    char path_file[255] = "";
    strcpy(path_file, projectpath);
    strcat(path_file, "\\files\\");
    strcat(path_file, name);

    if ((fptr = fopen(path_file, "w")) != NULL)
    {
        fprintf(fptr, "%s", str);
        fclose(fptr);
    }
}

bool DifInf(float x)
{
    return fabs(infinit - fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
    if (x > epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}

float Exponential(float x)
{
    if (DifInf(x)) return exp(x);
    else return infinit;
}

float Inmultit(float x, float y)
{
    if (fabs(x < epsi) || fabs(y) < epsi) return 0;
    else if (DifInf(x) && DifInf(y)) return x * y;
    else return infinit;
}

float Putere(float x, float y)
{
    // float p;
    if (x == 0) return 0;
    else if (y == 0) return 1;
    else if (x == infinit || y == infinit) return infinit;
    else
        return pow(x, y);
}

float Egal(float x, float y)
{
    return x == y;
}

float Diferit(float x, float y)
{
    return x != y;
}

float MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x + y;
    else return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x - y;
    else return infinit;
}

float Impartit(float x, float y)
{
    if (fabs(y) > epsi) return x / y;
    else return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}

float Modul(float x)
{
    if (DifInf(x)) return fabs(x);
    else return infinit;
}

float Radical(float x)
{
    if (DifInf(x) && (x > epsi)) return sqrt(x);
    else return infinit;
}

float Tangenta(float x)
{
    return (sin(x) / cos(x));

}

float Cotangenta(float x)
{
    return (cos(x) / sin(x));
}

float arcsin(float x)
{
    if (DifInf(x))
        return asin(x);
    else return infinit;
}
float arccos(float x)
{
    if (DifInf(x))
        return acos(x);
    else return infinit;
}

float arctg(float x)
{
    if (DifInf(x))
        return atan(x);
    else return infinit;
}

float arcctg(float x)
{
    if (DifInf(x))
        return pi / 2 - atan(x);
    else return infinit;
}

bool EsteNumar(char sir[MAX1])
{
    return (atof(sir) != 0.0 &&
        strchr("0123456789", sir[0]));
}

void tokenize(Functie& F) {
    int n = strlen(F.expresie);
    strcpy(F.vect[0], "(");
    int i = 0, j = 1;

    while (i < n) {
        if (isdigit(F.expresie[i]) || F.expresie[i] == '.') {
            int k = 0;
            while (isdigit(F.expresie[i]) || F.expresie[i] == '.') {
                F.vect[j][k] = F.expresie[i];
                i++;
                k++;
            }
            F.vect[j][k] = '\0';
        }
        else if (isalpha(F.expresie[i])) {
            int k = 0;
            while (isalpha(F.expresie[i])) {
                F.vect[j][k] = F.expresie[i];
                i++;
                k++;
            }

            // Verificăm pentru funcțiile specifice și reducem dacă este cazul
            if (strncmp(F.vect[j], "sin", 3) == 0) {
                strcpy(F.vect[j], "s");
                i -= 2;  // Sărim înapoi peste "in"
            }
            else if (strncmp(F.vect[j], "cos", 3) == 0) {
                strcpy(F.vect[j], "c");
                i -= 2;  // Sărim înapoi peste "os"
            }
            else if (strncmp(F.vect[j], "ln", 2) == 0) {
                strcpy(F.vect[j], "l");
                i -= 1;  // Sărim înapoi peste "n"
            }
            else if (strncmp(F.vect[j], "abs", 3) == 0) {
                strcpy(F.vect[j], "a");
                i -= 2;  // Sărim înapoi peste "bs"
            }
            else if (strncmp(F.vect[j], "root", 4) == 0) {
                strcpy(F.vect[j], "r");
                i -= 3;  // Sărim înapoi peste "oot"
            }
            else if (strncmp(F.vect[j], "exp", 3) == 0) {
                strcpy(F.vect[j], "e");
                i -= 2;  // Sărim înapoi peste "xp"
            }

            F.vect[j][k] = '\0';
        }
        else {
            strncpy(F.vect[j], F.expresie + i, 1);
            F.vect[j][1] = '\0';
            i++;
        }

        j++;
    }

    strcpy(F.vect[j], ")");
}

/*void Cuvinte(char expr[], char OperatiiBinare[], char OperatiiUnare[], char Alfabet[], char Cifre[]) {
    char s[300];
    int k = 0, i = 0, ok = 0;

    while (i < strlen(expr)) {
        if (expr[i + 1] != NULL) {
            if ((expr[i] == '-' || expr[i] == '+') && strchr(Cifre, expr[i + 1]) && (i == 0 ||
                (strchr(Cifre, expr[i - 1]) == NULL || strchr(Alfabet, expr[i - 1]) != NULL) && strchr("xq", expr[i - 1]) == NULL) &&
                expr[i - 1] != ')') {
                s[k++] = expr[i++];
                s[k++] = '1';
                s[k++] = ' ';
                s[k++] = '*';
                s[k++] = ' ';

                if ((strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.') &&
                    strchr(OperatiiBinare, expr[i + 1]) == NULL && expr[i + 1] != ')' && expr[i + 1] != NULL) {
                    while ((strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.') &&
                        strchr(OperatiiBinare, expr[i + 1]) == NULL && expr[i + 1] != ')' && expr[i + 1] != NULL)
                        s[k++] = expr[i++];

                    s[k++] = expr[i++];
                    s[k++] = ' ';
                } else {
                    s[k++] = expr[i++];
                    s[k++] = ' ';
                }
            } else if (strchr(Cifre, expr[i]) != NULL &&
                (i == 0 || strchr(OperatiiBinare, expr[i - 1]) != NULL || expr[i - 1] == '(' || strchr(Alfabet, expr[i - 1]) != NULL)) {
                if (strchr(OperatiiBinare, expr[i + 1]) == NULL &&
                    strchr(Alfabet, expr[i + 1]) == NULL &&
                    expr[i + 1] != ')' &&
                    expr[i + 1] != '(' &&
                    expr[i + 1] != NULL &&
                    (strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.')) {
                    while (strchr(OperatiiBinare, expr[i + 1]) == NULL &&
                        strchr(Alfabet, expr[i + 1]) == NULL &&
                        expr[i + 1] != ')' &&
                        expr[i + 1] != '(' &&
                        expr[i + 1] != NULL &&
                        (strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.'))
                        s[k++] = expr[i++];

                    s[k++] = expr[i++];
                    s[k++] = ' ';
                } else {
                    s[k++] = expr[i++];
                    s[k++] = ' ';
                }
            } else if (strchr("xq", expr[i]) != NULL)
            {
                s[k++] = expr[i++];
                s[k++] = ' ';

            } else if ((expr[i] == '-' || expr[i] == '+') && (i == 0) && expr[i - 1] != ')' &&
                ((expr[i + 1] == 'l' && expr[i + 2] == 'n') ||
                    (expr[i + 1] == 's' && expr[i + 2] == 'i' && expr[i + 3] == 'n') ||
                    (expr[i + 1] == 'c' && expr[i + 2] == 'o' && expr[i + 3] == 's') ||
                    (expr[i + 1] == 't' && expr[i + 2] == 'g') ||
                    (expr[i + 1] == 'c' && expr[i + 2] == 't' && expr[i + 3] == 'g') ||
                    (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 's' && expr[i + 5] == 'i' && expr[i + 6] == 'n') ||
                    (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 'c' && expr[i + 5] == 'o' && expr[i + 6] == 's') ||
                    (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 't' && expr[i + 5] == 'g') ||
                    (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 'c' && expr[i + 5] == 't' && expr[i + 6] == 'g') ||
                    (expr[i + 1] == 'a' && expr[i + 2] == 'b' && expr[i + 3] == 's') ||
                    (expr[i + 1] == 'e' && expr[i + 2] == 'x' && expr[i + 3] == 'p') ||
                    (expr[i + 1] == 'r' && expr[i + 2] == 'a' && expr[i + 3] == 'd'))) {
                ok = 1;
                s[k++] = expr[i++];
                s[k++] = '1';
                s[k++] = ' ';
                s[k++] = '*';
                s[k++] = ' ';
            } else if (expr[i] == 'l' && expr[i + 1] == 'n' ||
                expr[i] == 't' && expr[i + 1] == 'g') {
                ok = 1;
                s[k++] = expr[i];
                s[k++] = expr[i + 1];
                s[k++] = ' ';
                i = i + 2;
            } else if ((expr[i] == 's' && expr[i + 1] == 'i' && expr[i + 2] == 'n') ||
                (expr[i] == 'c' && expr[i + 1] == 'o' && expr[i + 2] == 's') ||
                (expr[i] == 'a' && expr[i + 1] == 'b' && expr[i + 2] == 's') ||
                (expr[i] == 'e' && expr[i + 1] == 'x' && expr[i + 2] == 'p') ||
                (expr[i] == 'c' && expr[i + 1] == 't' && expr[i + 2] == 'g') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 's' && expr[i + 4] == 'i' && expr[i + 5] == 'n') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 'c' && expr[i + 4] == 'o' && expr[i + 5] == 's') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 't' && expr[i + 4] == 'g') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 'c' && expr[i + 4] == 't' && expr[i + 5] == 'g')) {
                ok = 1;
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = ' ';
            } else if ((expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 's' && expr[i + 4] == 'i' && expr[i + 5] == 'n') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 'c' && expr[i + 4] == 'o' && expr[i + 5] == 's') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 't' && expr[i + 4] == 'g') ||
                (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 'c' && expr[i + 4] == 't' && expr[i + 5] == 'g')) {
                ok = 1;
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = ' ';
            } else if (expr[i] == 'a' && expr[i + 1] == 'b' && expr[i + 2] == 's') {
                ok = 1;
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = ' ';
            } else if (expr[i] == 'r' && expr[i + 1] == 'o' && expr[i + 2] == 'o' && expr[i + 3] == 't') {
                ok = 1;
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = ' ';
            } else if (expr[i] == 'e' && expr[i + 1] == 'x' && expr[i + 2] == 'p') {
                ok = 1;
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = expr[i++];
                s[k++] = ' ';
            } else
                s[k++] = expr[i++];
        } else
            s[k++] = expr[i++];
    }

    s[k] = '\0';
    strcpy(expr, s);
}*/

void Cuvinte(char expr[MAX])
{
    char s[MAX];
    int k, i, ok;
    k = 0;
    i = 0;
    ok = 0;
    while (i < strlen(expr))
    {
        ///daca exista caracter
        if (expr[i + 1] != NULL)
        {
            /*numerele care incep cu '-' sau '+' sunt considerate operatii unare cand: 1) este primul caracter
                                                                                       2) in fata nu exista o cifra
                                                                                       3) in fata nu se afla ')'     */

            if ((expr[i] == '-' || expr[i] == '+') && strchr(Cifre, expr[i + 1]) && (i == 0 || (strchr(Cifre, expr[i - 1]) == NULL || strchr(Alfabet, expr[i - 1]) != NULL) && strchr("xq", expr[i - 1]) == NULL) && expr[i - 1] != ')')
            {
                s[k++] = expr[i++];
                s[k++] = '1';
                s[k++] = ' ';
                s[k++] = '*';
                s[k++] = ' ';
                if ((strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.') &&
                    strchr(OperatiiBinare, expr[i + 1]) == NULL && expr[i + 1] != ')' && expr[i + 1] != NULL)
                {
                    while ((strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.') &&
                        strchr(OperatiiBinare, expr[i + 1]) == NULL && expr[i + 1] != ')' && expr[i + 1] != NULL)
                        s[k++] = expr[i++];

                    s[k++] = expr[i++];
                    s[k++] = ' ';
                }
                else
                {
                    s[k++] = expr[i++];
                    s[k++] = ' ';
                }

            }

            else ///Cifre[13]="0123456789qx";
                 /*este cifra daca 1) in fata ei a fost '('
                                   2) este prima din sir
                                   3) in fata ei este un operator */ ///sin(2x)
                if (strchr(Cifre, expr[i]) != NULL &&
                    (i == 0 || strchr(OperatiiBinare, expr[i - 1]) != NULL || expr[i - 1] == '(' || strchr(Alfabet, expr[i - 1]) != NULL))
                {
                    if (strchr(OperatiiBinare, expr[i + 1]) == NULL &&
                        strchr(Alfabet, expr[i + 1]) == NULL &&
                        expr[i + 1] != ')' &&
                        expr[i + 1] != '(' &&
                        expr[i + 1] != NULL &&
                        (strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.'))
                    {
                        while (strchr(OperatiiBinare, expr[i + 1]) == NULL &&
                            strchr(Alfabet, expr[i + 1]) == NULL &&
                            expr[i + 1] != ')' &&
                            expr[i + 1] != '(' &&
                            expr[i + 1] != NULL &&
                            (strchr(Cifre, expr[i]) != NULL && strchr("xq", expr[i + 1]) == NULL || expr[i] == '.'))
                            s[k++] = expr[i++];

                        s[k++] = expr[i++];
                        s[k++] = ' ';
                    }
                    else
                    {
                        s[k++] = expr[i++];
                        s[k++] = ' ';
                    }
                }
                else

                    if (strchr("xq", expr[i]) != NULL)
                    {
                        s[k++] = expr[i++];
                        s[k++] = ' ';
                    }


                    else ///OperatiiUnare: ln/sin/cos/tg/ctg/arcsin/arccos/arctg/arcctg/abs/exp/rad care incep cu '-' sau '+'
                        if ((expr[i] == '-' || expr[i] == '+') && (i == 0) && expr[i - 1] != ')' &&
                            ((expr[i + 1] == 'l' && expr[i + 2] == 'n') ||
                                (expr[i + 1] == 's' && expr[i + 2] == 'i' && expr[i + 3] == 'n') ||
                                (expr[i + 1] == 'c' && expr[i + 2] == 'o' && expr[i + 3] == 's') ||
                                (expr[i + 1] == 't' && expr[i + 2] == 'g') ||
                                (expr[i + 1] == 'c' && expr[i + 2] == 't' && expr[i + 3] == 'g') ||
                                (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 's' && expr[i + 5] == 'i' && expr[i + 6] == 'n') ||
                                (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 'c' && expr[i + 5] == 'o' && expr[i + 6] == 's') ||
                                (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 't' && expr[i + 5] == 'g') ||
                                (expr[i + 1] == 'a' && expr[i + 2] == 'r' && expr[i + 3] == 'c' && expr[i + 4] == 'c' && expr[i + 5] == 't' && expr[i + 6] == 'g') ||
                                (expr[i + 1] == 'a' && expr[i + 2] == 'b' && expr[i + 3] == 's') ||
                                (expr[i + 1] == 'e' && expr[i + 2] == 'x' && expr[i + 3] == 'p') ||
                                (expr[i + 1] == 'r' && expr[i + 2] == 'a' && expr[i + 3] == 'd')))
                        {
                            ok = 1;
                            s[k++] = expr[i++];
                            s[k++] = '1';
                            s[k++] = ' ';
                            s[k++] = '*';
                            s[k++] = ' ';
                        }
                        else ///OperatiiUnare: ln/tg
                            if (expr[i] == 'l' && expr[i + 1] == 'n' ||
                                expr[i] == 't' && expr[i + 1] == 'g')
                            {
                                ok = 1;
                                s[k++] = expr[i];
                                s[k++] = expr[i + 1];
                                s[k++] = ' ';
                                i = i + 2;
                            }
                            else ///OperatiiUnare: sin/cos/ctg/abs/exp/rad
                                if ((expr[i] == 's' && expr[i + 1] == 'i' && expr[i + 2] == 'n') ||
                                    (expr[i] == 'c' && expr[i + 1] == 'o' && expr[i + 2] == 's') ||
                                    (expr[i] == 'c' && expr[i + 1] == 't' && expr[i + 2] == 'g') ||
                                    (expr[i] == 'a' && expr[i + 1] == 'b' && expr[i + 2] == 's') ||
                                    (expr[i] == 'e' && expr[i + 1] == 'x' && expr[i + 2] == 'p') ||
                                    (expr[i] == 'r' && expr[i + 1] == 'a' && expr[i + 2] == 'd'))

                                {
                                    ok = 1;
                                    s[k++] = expr[i];
                                    s[k++] = expr[i + 1];
                                    s[k++] = expr[i + 2];
                                    s[k++] = ' ';
                                    i = i + 3;
                                }
                                else///arctg
                                    if (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 't' && expr[i + 4] == 'g')
                                    {
                                        ok = 1;
                                        s[k++] = expr[i];
                                        s[k++] = expr[i + 1];
                                        s[k++] = expr[i + 2];
                                        s[k++] = expr[i + 3];
                                        s[k++] = expr[i + 4];
                                        s[k++] = ' ';
                                        i = i + 5;
                                    }
                                    else///arcsin/arccos/arcctg
                                        if ((expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 's' && expr[i + 4] == 'i' && expr[i + 5] == 'n') ||
                                            (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 'c' && expr[i + 4] == 'o' && expr[i + 5] == 's') ||
                                            (expr[i] == 'a' && expr[i + 1] == 'r' && expr[i + 2] == 'c' && expr[i + 3] == 'c' && expr[i + 4] == 't' && expr[i + 5] == 'g'))
                                        {
                                            ok = 1;
                                            s[k++] = expr[i];
                                            s[k++] = expr[i + 1];
                                            s[k++] = expr[i + 2];
                                            s[k++] = expr[i + 3];
                                            s[k++] = expr[i + 4];
                                            s[k++] = expr[i + 5];
                                            s[k++] = ' ';
                                            i = i + 6;
                                        }
                                        else
                                            ///pun in sir Operatiile Binare sau '(' , ')' urmate de spatiu
                                            if (expr[i] == '(' && strchr(Cifre, expr[i - 1]) && i != 0)
                                            {
                                                s[k++] = ' ';
                                                s[k++] = '*';
                                                s[k++] = ' ';
                                                s[k++] = expr[i++];
                                                s[k++] = ' ';
                                            }


                                            else
                                                if (strchr(OperatiiBinare, expr[i]) || expr[i] == '(' || expr[i] == ')')
                                                {
                                                    s[k++] = expr[i++];
                                                    s[k++] = ' ';
                                                }
                                                else
                                                    if (strchr("!@#$%&;'_[]{},~`\|""", expr[i]) || ok == 0 && strchr(Alfabet, expr[i]))
                                                    {

                                                        s[k++] = expr[i++];
                                                        s[k++] = ' ';

                                                    }
        }
        else
            ///daca nu exista caracter
            if (expr[i + 1] == NULL)
                s[k++] = expr[i++];
    }
    s[k] = NULL;
    strcpy(expr, s);
}


double ValoareFunctie(Functie F, double x)
{
    int i;
    ok_i = 1, ok_t = 1, ok_c = 1, ok_r = 1, ok_l = 1, ok_lz = 1;
    // returneaza valoarea functiei E in punctul x
    double valo, x_1, x_2;
    //calculul expresiei
    for (i = 1; i <= max_stiva; i++)
    {
        Opd[i] = 0;
        Op[i] = '@';
    }
    top1 = 0;
    top2 = 1;
    Op[top2] = '(';
    i = 0;
    while (i <= F.lung && top2 > 0)
    {
        i++;
        if (EsteNumar(F.vect[i]))
        {
            // printf("\nE.vect[%d]=%s\n",i,E.vect[i]);
            top1++;
            valo = atof(F.vect[i]);
            Opd[top1] = valo;
            // depanare();
        }
        else
            switch (F.vect[i][0]) {
                /* constanta pi=3.1415926 se da sub forma literei q */
            case 'q': top1++; Opd[top1] = pi; break;
            case 'x': /* variabila x */ top1++; Opd[top1] = x;
                /* printf("\n-->x=%f\n",x); */ break;
            case '(': /* inceput de bloc */ top2++; Op[top2] = '('; break;
            default:
                /* operatii binare si unare */
                while ((top2 > 0) && !(strchr("()", Op[top2])) &&
                    Prioritate(Op[top2]) >= Prioritate(F.vect[i][0]))
                {
                    if (top1 > 1) x_1 = Opd[top1 - 1];
                    x_2 = Opd[top1];
                    // depanare();
                    /* functii scrise in OPERATII */
                    switch (Op[top2]) {
                    case '=': valo = Egal(x_1, x_2); break;
                    case '#': valo = Diferit(x_1, x_2); break;
                    case '<': valo = MaiMic(x_1, x_2); break;
                    case '>': valo = MaiMare(x_1, x_2); break;
                    case '+': valo = Plus(x_1, x_2); break;
                    case '-': valo = Minus(x_1, x_2); break;
                    case '*': valo = Inmultit(x_1, x_2); break;
                    case '/': {
                        if (x_2 != 0)
                            valo = Impartit(x_1, x_2);
                        else
                            ok_i = 0;
                        break;
                    }
                    case '^': valo = Putere(x_1, x_2); break;
                    case 's': valo = Sinus(x_2); break;
                    case 'c': valo = Cosinus(x_2); break;
                    case 'l': {
                        if (x_2 == 0)
                            ok_lz = 0;
                        else
                            if (x_2 < 0)
                                ok_l = 0;
                            else
                                if (x_2 > 0)
                                    valo = Logaritm(x_2);

                        break;
                    }
                    case 'e': valo = Exponential(x_2); break;
                    case 'a': valo = Modul(x_2); break;
                    case 'r': {
                        if (x_2 == 0)
                            valo = 0;
                        else
                            if (x_2 > 0)
                                valo = Radical(x_2);
                            else
                                ok_r = 0;
                        break;
                    }
                    case 't': {

                        if (Cosinus(x_2) > epsi || Cosinus(x_2) < 0.0)
                            valo = Tangenta(x_2);
                        else
                            ok_t = 0;
                        break;
                    }
                    case 'b': {

                        if (Sinus(x_2) > epsi || Sinus(x_2) < 0.0)
                            valo = Cotangenta(x_2);
                        else
                            ok_c = 0;
                        break;
                    }
                    } //operator[top2]
                    if (strchr(OperatiiBinare, Op[top2])) top1--;
                    if (strchr(Operatii, Op[top2])) Opd[top1] = valo;
                    top2--;
                }
                // depanare();
                if (top2 > 0)
                    if ((Op[top2] != '(') || (strcmp(F.vect[i], ")")))
                    {
                        top2++; Op[top2] = F.vect[i][0];
                    }
                    else top2--;
            }
    }
    if (top2 == 0) return Opd[1];
    else return infinit;
}
void Tip(Functie& F)
{
    char tip_cifre[14] = "0123456789";
    char tip_litere[3] = "xq";
    for (int i = 0; i < F.lung; i++)
    {
        if (F.vect[i][0] == '(')
            F.Tip[i] = 1;

        else
            if (F.vect[i][0] == ')')
                F.Tip[i] = 2;

            else
                if (F.vect[i][0] == '+' || F.vect[i][0] == '-')
                    F.Tip[i] = 3;

                else

                    if (F.vect[i][0] == '*' || F.vect[i][0] == '/' || F.vect[i][0] == '^')
                        F.Tip[i] = 4;

                    else
                        if (strcmp(F.vect[i], "sin") == 0 ||
                            strcmp(F.vect[i], "cos") == 0 ||
                            strcmp(F.vect[i], "tg") == 0 ||
                            strcmp(F.vect[i], "btg") == 0 || ///ctg
                            strcmp(F.vect[i], "drcsin") == 0 || ///arcsin
                            strcmp(F.vect[i], "frccos") == 0 || ///arccos
                            strcmp(F.vect[i], "grctg") == 0 || ///arctg
                            strcmp(F.vect[i], "hrcctg") == 0 || ///arcctg
                            strcmp(F.vect[i], "abs") == 0 ||
                            strcmp(F.vect[i], "rad") == 0 ||
                            strcmp(F.vect[i], "exp") == 0 ||
                            strcmp(F.vect[i], "ln") == 0)
                            F.Tip[i] = 5;

                        else
                            if (strchr(tip_cifre, F.vect[i][0]))
                                F.Tip[i] = 6;
                            else
                                if (strchr(tip_litere, F.vect[i][0]))
                                    F.Tip[i] = 7;

                                else
                                    if (strchr(Caractere_Nepermise, F.vect[i][0]))
                                        F.Tip[i] = -1;
    }
}

void Adaugare_Vector(Functie& F)
{
    char s[MAX];
    strcpy(s, F.expresie);
    char* p;
    int k = 1;
    strcpy(F.vect[0], "(");
    p = strtok(s, " ");
    while (p)
    {
        strcpy(F.vect[k++], p);
        p = strtok(NULL, " ");
    }
    strcpy(F.vect[k++], ")");
    F.lung = k;
}


double maxVal(Functie F) {

    double maxValue = ValoareFunctie(F, F.a);

    for (int i = F.a; i <= F.b; i++) {
        double value = ValoareFunctie(F, i);

        if (value > maxValue) {
            maxValue = value;
        }
    }
    return maxValue;
}

double minVal(Functie F) {

    double minValue = ValoareFunctie(F, F.a);


    for (int i = F.a; i <= F.b; i++) {
        double value = ValoareFunctie(F, i);
        if (value < minValue) {
            minValue = value;
        }
    }
    return minValue;
}

Punct translate(Punct p, Grafic g)
{
    Punct res;
    res.x = (p.x - g.x1) / (g.x2 - g.x1) * (g.x2_ecran - g.x1_ecran) + g.x1_ecran;
    res.y = (p.y - g.y1) / (g.y2 - g.y1) * (g.y2_ecran - g.y1_ecran) + g.y1_ecran;
    return res;
};

Punct translateInapoi(Punct p, Grafic g)
{
    Punct res;
    res.x = (p.x - g.x1_ecran) / (g.x2_ecran - g.x1_ecran) * (g.x2 - g.x1) + g.x1;
    res.y = (p.y - g.y1_ecran) / (g.y2_ecran - g.y1_ecran) * (g.y2 - g.y1) + g.y1;
    return res;

}

void draw_axis(Grafic g)
{
    setlinestyle(0, USERBIT_LINE, 1);

    Punct origine;
    origine.x = 0;
    origine.y = 0;
    origine = translate(origine, g);

    if (origine.x > g.x1_ecran && origine.x < g.x2_ecran)
        line(origine.x, g.y2_ecran, origine.x, g.y1_ecran);

    if (origine.y > g.y1_ecran && origine.y < g.y2_ecran)
        line(g.x1_ecran, origine.y, g.x2_ecran, origine.y);

    Punct bare;
    setfillstyle(1, 0);
    settextjustify(1, 2);

    char str[20];

    if (origine.y > g.y1_ecran && origine.y < g.y2_ecran)
    {
        for (int i = g.x1; i < g.x2; ++i)
        {
            bare.x = i;
            bare.y = 0;
            if (bare.x != 0)
            {
                if ((abs(g.x1 - g.x2) < 30) || (abs(g.x1 - g.x2) >= 30 && abs(g.x1 - g.x2) < 100 && i % 5 == 0) || (abs(g.x1 - g.x2) >= 100 && i % 10 == 0))
                {

                    bare = translate(bare, g);
                    bar(bare.x - 1, origine.y + 3, bare.x + 1, origine.y - 3);

                    ltoa(i, str, 10);
                    outtextxy(bare.x, origine.y + 10, str);
                }
            }
        }
    }


    if (origine.x > g.x1_ecran && origine.x < g.x2_ecran)
    {
        for (int i = g.y2; i < g.y1; ++i)
        {
            bare.x = 0;
            bare.y = i;
            if (bare.y != 0)
            {
                if ((abs(g.x1 - g.x2) < 30) || (abs(g.x1 - g.x2) >= 30 && abs(g.x1 - g.x2) < 100 && i % 5 == 0) || (abs(g.x1 - g.x2) >= 100 && i % 10 == 0))
                {
                    bare = translate(bare, g);
                    bar(origine.x - 3, bare.y + 1, origine.x + 3, bare.y - 1);

                    ltoa(i, str, 10);
                    outtextxy(origine.x - 20, bare.y - 8, str);
                }
            }
        }
    }
}


void deseneazaGrafic(Grafic g, FunctionGraph& functionGraph)
{
    setbkcolor(COLOR(28, 33, 39));
    //cleardevice();

    settextstyle(0, HORIZ_DIR, 2);

    setcolor(COLOR(240, 236, 235));
    draw_axis(g);

    Punct p1, p2;
    p1.x = g.x1;
    p1.y = ValoareFunctie(functionGraph.F, p1.x);

    float diferentaPuncte = 0.05;


    d_asy = false;

    for (int i = 0; i < functionGraph.F.lung; ++i)
    {
        if (strcmp(functionGraph.F.vect[i], "btg") == 0 || strcmp(functionGraph.F.vect[i], "tg") == 0 || functionGraph.F.vect[i][0] == '/' || strcmp(functionGraph.F.vect[i], "ln") == 0)
        {
            d_asy = true;
            diferentaPuncte = 0.005;
        }
        if (strcmp(functionGraph.F.vect[i], "drcsin") == 0 || strcmp(functionGraph.F.vect[i], "frccos") == 0)
        {
            diferentaPuncte = 0.005;
        }
    }

    //min - max

    static bool alege_min = true, alege_max = true;

    if (functionGraph.minGraf.x < g.x1 || functionGraph.minGraf.x > g.x2 || (functionGraph.minGraf.y < g.y2 || functionGraph.minGraf.y > g.y1) || isnan(functionGraph.minGraf.y))
    {
        if (functionGraph.minGraf.y < g.y2 || functionGraph.minGraf.y > g.y1 || isnan(functionGraph.minGraf.y))
        {
            functionGraph.minGraf.x = g.x1;
            functionGraph.minGraf.y = ValoareFunctie(functionGraph.F, functionGraph.minGraf.x);
            while (functionGraph.minGraf.y < g.y2 || functionGraph.minGraf.y > g.y1 || isnan(functionGraph.minGraf.y))
            {
                functionGraph.minGraf.x += diferentaPuncte;
                functionGraph.minGraf.y = ValoareFunctie(functionGraph.F, functionGraph.minGraf.x);
                if (functionGraph.minGraf.x > g.x2)
                    break;
            }
        }
        if (functionGraph.minGraf.x < g.x1)
        {
            functionGraph.minGraf.x = g.x1;
            functionGraph.minGraf.y = ValoareFunctie(functionGraph.F, functionGraph.minGraf.x);
            alege_min = true;
        }
        if (functionGraph.minGraf.x > g.x2)
        {
            functionGraph.minGraf.x = g.x2;
            functionGraph.minGraf.y = ValoareFunctie(functionGraph.F, functionGraph.minGraf.x);
            alege_min = true;
        }
    }


    if (functionGraph.maxGraf.x < g.x1 || functionGraph.maxGraf.x > g.x2 || (functionGraph.maxGraf.y < g.y2 || functionGraph.maxGraf.y > g.y1) || isnan(functionGraph.maxGraf.y))
    {
        if (functionGraph.maxGraf.y < g.y2 || functionGraph.maxGraf.y > g.y1 || isnan(functionGraph.maxGraf.y))
        {
            functionGraph.maxGraf.x = g.x1;
            functionGraph.maxGraf.y = ValoareFunctie(functionGraph.F, functionGraph.maxGraf.x);
            while (functionGraph.maxGraf.y < g.y2 || functionGraph.maxGraf.y > g.y1 || isnan(functionGraph.maxGraf.y))
            {
                functionGraph.maxGraf.x += diferentaPuncte;
                functionGraph.maxGraf.y = ValoareFunctie(functionGraph.F, functionGraph.maxGraf.x);
                if (functionGraph.maxGraf.x > g.x2)
                    break;
            }
        }
        if (functionGraph.maxGraf.x < g.x1)
        {
            functionGraph.maxGraf.x = g.x1;
            functionGraph.maxGraf.y = ValoareFunctie(functionGraph.F, functionGraph.maxGraf.x);
            alege_max = true;
        }
        if (functionGraph.maxGraf.x > g.x2)
        {
            functionGraph.maxGraf.x = g.x2;
            functionGraph.maxGraf.y = ValoareFunctie(functionGraph.F, functionGraph.maxGraf.x);
            alege_max = true;
        }
    }

    Punct p1t, p2t;

    setlinestyle(0, USERBIT_LINE, 3);
    setcolor(COLOR(93, 142, 193));
    while (p1.x <= g.x2)
    {
        p2.x = p1.x;
        p2.y = p1.y;
        p1.x += diferentaPuncte;
        p1.y = ValoareFunctie(functionGraph.F, p1.x);

        p1t = translate(p1, g);
        p2t = translate(p2, g);

        if (p1.y > g.y2 && p1.y < g.y1)
        {
            if (functionGraph.minGraf.y > p1.y)
            {
                functionGraph.minGraf = p1;
            }
            else if (functionGraph.minGraf.y == p1.y && alege_min)
            {
                functionGraph.minGraf = p1;
                alege_min = false;
            }
            if (functionGraph.maxGraf.y < p1.y)
            {
                functionGraph.maxGraf = p1;
            }
            else if (functionGraph.maxGraf.y == p1.y && alege_max)
            {
                functionGraph.maxGraf = p1;
                alege_max = false;
            }
        }

        if (p1.y < g.y1 + 200 && p1.y > g.y2 - 200)
        {
            if (p1.y > g.y1)
            {
                p1.y = g.y1 + 10;
            }

            if (p1.y < g.y2)
            {
                p1.y = g.y2 - 10;
            }

            if (abs(p1.y - p2.y) < 200)
                line(int(p1t.x), int(p1t.y), int(p2t.x), int(p2t.y));
            else if (deseneazaAsimptote)
            {
                setcolor(COLOR(11, 56, 95));
                line(p1t.x - 2, g.y2_ecran, p1t.x - 2, g.y1_ecran);
                setcolor(COLOR(93, 142, 193));
            }
        }
    }

    setcolor(0);
    setbkcolor(COLOR(28, 33, 39));
    setlinestyle(0, USERBIT_LINE, 1);
    settextstyle(0, HORIZ_DIR, 2);
}

void deseneazaMinMax(const Grafic& g, Punct minGrafic, Punct maxGrafic, bool draw_min, bool draw_max)
{
    setlinestyle(0, USERBIT_LINE, 3);
    settextjustify(CENTER_TEXT, TOP_TEXT);

    if (abs(minGrafic.y) < 0.1)
        minGrafic.y = 0;

    if (abs(maxGrafic.y) < 0.1)
        maxGrafic.y = 0;


    char str[15] = { "" };

    // maxim
    char maxim[30];

    // desenare minim
    Punct minGraficEcran = translate(minGrafic, g);

    setcolor(4);
    if (draw_min && !isnan(minGraficEcran.y)) {
        //circle(minGraficEcran.x, minGraficEcran.y , 20);
        line(minGraficEcran.x, minGraficEcran.y, minGraficEcran.x, minGraficEcran.y + 10);
        char minPoint[] = "MIN(";
        gcvt(minGrafic.x, 2, str);
        strcat(minPoint, str);
        strcat(minPoint, ",");
        gcvt(minGrafic.y, 1, str);
        strcat(minPoint, str);
        strcat(minPoint, ")");
        outtextxy(minGraficEcran.x, minGraficEcran.y + 10, minPoint);
    }
    //desenare maxim
    Punct maxGraficEcran = translate(maxGrafic, g);
    setcolor(4);
    if (draw_max && !isnan(maxGraficEcran.y))
    {
        //circle(maxGrafic.x, maxGrafic.y, 20);
        line(maxGraficEcran.x, maxGraficEcran.y, maxGraficEcran.x, maxGraficEcran.y - 10);
        char maxPoint[] = "MAX(";
        gcvt(maxGrafic.x, 2, str);
        strcat(maxPoint, str);
        strcat(maxPoint, ",");
        gcvt(maxGrafic.y, 1, str);
        strcat(maxPoint, str);
        strcat(maxPoint, ")");
        outtextxy(maxGraficEcran.x, maxGraficEcran.y - 25, maxPoint);
    }
    setbkcolor(COLOR(28, 33, 39));
}



void deseneazaButoane(const Grafic& g, apasat& apasat, char projectpath[])
{
    char text[100] = " ";

    setfillstyle(SOLID_FILL, COLOR(3, 57, 108));
    setbkcolor(COLOR(3, 57, 108));
    settextstyle(3, HORIZ_DIR, 3);
    setcolor(15);
    settextjustify(1, 2);

    bar(g.x1_ecran + 17, g.y1_ecran + 20, g.x1_ecran + 100, g.y1_ecran + 60);
    outtextxy(g.x1_ecran + 60, g.y1_ecran + 25, "Inapoi");


    char backbutton[255] = "";
    strcpy(backbutton, projectpath);
    strcat(backbutton, "\\images\\backbutton.jpg");

    strcpy(text, "Inapoi");


    //readimagefile( backbutton, g.x1_ecran + 10, g.y1_ecran + 5, g.x2_ecran + 100, g.y1_ecran + 75);
    //bar(g.x1_ecran + 20, g.y1_ecran + 20, g.x1_ecran + 100, g.y1_ecran + 60);
    //outtextxy(g.x1_ecran + 65, 25, text);

    strcpy(text, "Salveaza");


    bar(g.x1_ecran + 200, g.y1_ecran + 20, g.x1_ecran + 300, g.y1_ecran + 60);
    outtextxy(g.x1_ecran + 250, 25, text);

    settextstyle(10, HORIZ_DIR, 5);
    bar(g.x2_ecran - 90, g.y1_ecran + 82, g.x2_ecran - 46, g.y1_ecran + 38);
    outtextxy(g.x2_ecran - 67, g.y1_ecran + 40, "+");


    bar(g.x2_ecran - 90, g.y1_ecran + 132, g.x2_ecran - 46, g.y1_ecran + 88);
    outtextxy(g.x2_ecran - 67, g.y1_ecran + 90, "-");

    settextstyle(10, HORIZ_DIR, 3);

    if (apasat.minimGraf)
    {
        setfillstyle(SOLID_FILL, COLOR(1, 3, 75));
        setbkcolor(COLOR(1, 3, 75));
    }
    else
    {
        setfillstyle(SOLID_FILL, COLOR(3, 57, 108));
        setbkcolor(COLOR(3, 57, 108));
    }

    bar(g.x1_ecran + 20, g.y2_ecran - 80, g.x1_ecran + 80, g.y2_ecran - 40);
    outtextxy(g.x1_ecran + 50, g.y2_ecran - 75, "MIN");

    if (apasat.maximGraf)
    {
        setfillstyle(SOLID_FILL, COLOR(1, 3, 75));
        setbkcolor(COLOR(1, 3, 75));
    }
    else
    {
        setfillstyle(SOLID_FILL, COLOR(3, 57, 108));
        setbkcolor(COLOR(3, 57, 108));
    }

    bar(g.x1_ecran + 100, g.y2_ecran - 80, g.x1_ecran + 160, g.y2_ecran - 40);
    outtextxy(g.x1_ecran + 130, g.y2_ecran - 75, "MAX");

    if (d_asy)
    {
        if (deseneazaAsimptote)
        {
            setfillstyle(SOLID_FILL, COLOR(1, 3, 75));
            setbkcolor(COLOR(1, 3, 75));
        }
        else
        {
            setfillstyle(SOLID_FILL, COLOR(3, 57, 108));
            setbkcolor(COLOR(3, 57, 108));
        }
    }
    else
    {
        setfillstyle(SOLID_FILL, COLOR(153, 153, 153));
        setbkcolor(COLOR(153, 153, 153));
    }

    if (limba == 'r')
        strcpy(text, "ASIMPTOTE");
    else if (limba == 'e')
        strcpy(text, "ASYMPTOTES");

    bar(g.x2_ecran - 206, g.y2_ecran - 80, g.x2_ecran - 46, g.y2_ecran - 40);
    outtextxy(g.x2_ecran - 126, g.y2_ecran - 75, text);
    setbkcolor(COLOR(28, 33, 39));

}

bool esteApasat(coordonateButon buton, int x, int y)
{
    if (x > buton.x1 && x < buton.x2 && y > buton.y1 && y < buton.y2)
        return true;
    return false;
}

bool apasaPeButton(Grafic& g, int x, int y, bool& d, apasat& apasat)
{
    static coordonateButon backToMenuButton = { g.x1_ecran + 17, g.y1_ecran + 25, g.x1_ecran + 165, g.y1_ecran + 60 };
    static coordonateButon salveaza = { g.x1_ecran + 200, g.y1_ecran + 20, g.x1_ecran + 300, g.y1_ecran + 60 };
    static coordonateButon minim = { g.x1_ecran + 20, g.y2_ecran - 80, g.x1_ecran + 80, g.y2_ecran - 40 };
    static coordonateButon maxim = { g.x1_ecran + 100, g.y2_ecran - 80, g.x1_ecran + 160, g.y2_ecran - 40 };
    static coordonateButon zoomOut = { g.x2_ecran - 90, g.y1_ecran + 88, g.x2_ecran - 46, g.y1_ecran + 132 };
    static coordonateButon zoomIn = { g.x2_ecran - 90, g.y1_ecran + 38, g.x2_ecran - 46, g.y1_ecran + 82 };
    static coordonateButon asimptote = { g.x2_ecran - 206, g.y2_ecran - 80, g.x2_ecran - 46, g.y2_ecran - 40 };

    if (esteApasat(backToMenuButton, x, y))
    {
        apasat.citesteFunctie = true;
        apasat.maximGraf = false;
        apasat.minimGraf = false;
        deseneazaAsimptote = false;
    }
    if (esteApasat(salveaza, x, y))
    {
        apasat.salveaza = true;
        d = true;
    }
    else if (esteApasat(zoomIn, x, y))
    {
        if (g.x1 + 3 < g.x2)
        {
            cleardevice();
            float n = ((g.x2 - g.x1) >= 30 ? ((g.x2 - g.x1) >= 60 ? 5 : 2) : 1);
            g.x1 += n;
            g.x2 -= n;

            g.y1 -= n / 2;
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
            d = true;
        }
        return true;
    }
    else if (esteApasat(zoomOut, x, y))
    {
        if ((g.x2 - g.x1) <= 250 && g.x2 <= 200 && g.x1 >= -200 && g.y1 <= 150 && g.y2 >= -150)
        {
            cleardevice();
            float n = ((g.x2 - g.x1) >= 30 ? ((g.x2 - g.x1) >= 60 ? 5 : 2) : 1);
            g.x1 -= n;
            g.x2 += n;

            g.y1 += n / 2;
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
            d = true;
        }
        return true;
    }
    else if (esteApasat(minim, x, y))
    {
        if (!apasat.minimGraf)
            apasat.minimGraf = true;
        else
            apasat.minimGraf = false;
        d = true;
        return true;
    }
    else if (esteApasat(maxim, x, y))
    {
        if (!apasat.maximGraf)
            apasat.maximGraf = true;
        else
            apasat.maximGraf = false;
        d = true;
        return true;
    }
    else if (esteApasat(asimptote, x, y))
    {
        if (!deseneazaAsimptote)
            deseneazaAsimptote = true;
        else
            deseneazaAsimptote = false;
        d = true;
        return true;
    }
}

void Verificare_Domeniu(Functie& F, float& x)
{
    ValoareFunctie(F, x);

    if (ok_i == 0)
    {
        if (limba == 'r')
        {
            strcpy(a[++poz], "EROARE: Nu se poate executa impartirea la 0!");
        }
        else if (limba == 'e')
        {
            strcpy(a[++poz], "ERROR: Unable to divide by Zero!");
        }
    }

    if (ok_t == 0)
    {
        if (limba == 'r')
        {
            strcpy(a[++poz], "EROARE: Tangenta nu este definita in punctele de forma (2k+1)*(pi/2)!");
        }
        else if (limba == 'e')
        {
            strcpy(a[++poz], "ERROR: The tangent is not defined in the points of the form (2k+1)*(pi/2)!");
        }
    }

    if (ok_c == 0)
    {
        if (limba == 'r')
        {
            strcpy(a[++poz], "EROARE: Cotangenta nu este definita in punctele de forma k*pi!");
        }
        else if (limba == 'e')
        {
            strcpy(a[++poz], "ERROR: The cotangent is not defined in the points of the form k*pi!");
        }
    }

    if (ok_r == 0)
    {
        if (limba == 'r')
        {
            strcpy(a[++poz], "EROARE: Nu se poate extrage radicalul dintr-un numar negativ!");
        }
        else if (limba == 'e')
        {
            strcpy(a[++poz], "ERROR: Unable to calculate the square root of a negative number!");
        }
    }

    if (ok_l == 0)
    {
        if (limba == 'r')
        {
            strcpy(a[++poz], "EROARE: Nu se poate calcula logaritmul natural dintr-un numar negativ!");
        }
        else if (limba == 'e')
        {
            strcpy(a[++poz], "ERROR: Unable to evaluate natural logarithm for a negative number!");
        }
    }

    if (ok_lz == 0)
    {
        if (limba == 'r')
        {
            strcpy(a[++poz], "EROARE: Logaritmul natural nu este definit in 0!");
        }
        else if (limba == 'e')
        {
            strcpy(a[++poz], "ERROR: Natural logarithm is not defined for 0!");
        }
    }
}

///cout<<"EROARE la pozitia "<<i<<": Dupa "<<v[i]<<" nu poate urma "<<v[i+1]<<endl;
void Eroare_Tip(int pozitia, char tip_1[], char tip_2[])
{
    if (limba == 'r')
    {
        char charValue[10] = "";
        char d[8] = ": Dupa ";
        char n[16] = " nu poate urma ";
        strcpy(a[++poz], "EROARE la pozitia ");
        itoa(pozitia, charValue, 10);
        for (int l = 0; l < strlen(charValue); l++)
            a[poz][strlen("EROARE la pozitia") + 1 + l] = charValue[l];

        for (int l = 0; l < strlen(d); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + 1 + l] = d[l];

        for (int l = 0; l < strlen(tip_1); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + strlen(d) + l + 1] = tip_1[l];

        for (int l = 0; l < strlen(n); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1] = n[l];

        for (int l = 0; l <= strlen(tip_2); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + strlen(d) + strlen(tip_1) + strlen(n) + l + 1] = tip_2[l];
    }
    else if (limba == 'e')
    {
        char charValue[10] = "";
        char d[8] = ": ";
        char n[] = " cannot be followed by ";
        strcpy(a[++poz], "ERROR at position ");
        itoa(pozitia, charValue, 10);
        for (int l = 0; l < strlen(charValue); l++)
            a[poz][strlen("ERROR at position") + 1 + l] = charValue[l];

        for (int l = 0; l < strlen(d); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + 1 + l] = d[l];

        for (int l = 0; l < strlen(tip_1); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + strlen(d) + l + 1] = tip_1[l];

        for (int l = 0; l < strlen(n); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1] = n[l];

        for (int l = 0; l <= strlen(tip_2); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + strlen(d) + strlen(tip_1) + strlen(n) + l + 1] = tip_2[l];
    }

}

void Codificare_Fct_Trigonometrice(Functie& F)
{
    for (int i = 0; i < F.lung; i++)
    {
        if (strcmp("ctg", F.vect[i]) == 0)
            F.vect[i][0] = 'b';
        else
            if (strcmp("arcsin", F.vect[i]) == 0)
                F.vect[i][0] = 'd';
            else
                if (strcmp("arccos", F.vect[i]) == 0)
                    F.vect[i][0] = 'f';
                else
                    if (strcmp("arctg", F.vect[i]) == 0)
                        F.vect[i][0] = 'g';
                    else
                        if (strcmp("arcctg", F.vect[i]) == 0)
                            F.vect[i][0] = 'h';
    }
}

void Elimin_Spatii(char* s)
{
    int lungime;
    lungime = strlen(s);
    for (int i = 0; i < lungime; i++)
    {
        while (s[i] == ' ')
            strcpy(s + i, s + i + 1);
    }
}

void Eroare_Brusc(int pozitia, char tip_1[])
{
    if (limba == 'r')
    {
        char charValue[10] = "";
        char d[8] = ": Dupa ";
        char n[30] = " expresia se termina brusc";
        strcpy(a[++poz], "EROARE la pozitia ");
        itoa(pozitia, charValue, 10);
        for (int l = 0; l < strlen(charValue); l++)
            a[poz][strlen("EROARE la pozitia") + 1 + l] = charValue[l];
        for (int l = 0; l < strlen(d); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + 1 + l] = d[l];

        for (int l = 0; l < strlen(tip_1); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + strlen(d) + l + 1] = tip_1[l];

        for (int l = 0; l <= strlen(n); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1] = n[l];
    }
    else if (limba == 'e')
    {
        char charValue[10] = "";
        char d[] = ": After ";
        char n[30] = " the expression ends abruptly";
        strcpy(a[++poz], "ERROR at position ");
        itoa(pozitia, charValue, 10);
        for (int l = 0; l < strlen(charValue); l++)
            a[poz][strlen("ERROR at position") + 1 + l] = charValue[l];
        for (int l = 0; l < strlen(d); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + 1 + l] = d[l];

        for (int l = 0; l < strlen(tip_1); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + strlen(d) + l + 1] = tip_1[l];

        for (int l = 0; l <= strlen(n); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1] = n[l];
    }
}

void Eroare_Nepermis(int pozitia, char tip_1[])
{
    if (limba == 'r')
    {
        char charValue[10] = "";
        char e[30] = " este un caracter nepermis";
        strcpy(a[++poz], "EROARE la pozitia ");

        itoa(pozitia, charValue, 10);

        for (int l = 0; l < strlen(charValue); l++)
            a[poz][strlen("EROARE la pozitia") + 1 + l] = charValue[l];

        a[poz][strlen("EROARE la pozitia") + strlen(charValue) + 1] = ':';
        a[poz][strlen("EROARE la pozitia") + strlen(charValue) + 2] = ' ';

        for (int l = 0; l < strlen(tip_1); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + 2 + l + 1] = tip_1[l];

        for (int l = 0; l <= strlen(e); l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + 2 + strlen(tip_1) + l + 1] = e[l];
    }
    else if (limba == 'e')
    {
        char charValue[10] = "";
        char e[30] = " is a forbidden character";
        strcpy(a[++poz], "ERROR at position ");

        itoa(pozitia, charValue, 10);

        for (int l = 0; l < strlen(charValue); l++)
            a[poz][strlen("ERROR at position") + 1 + l] = charValue[l];

        a[poz][strlen("ERROR at position") + strlen(charValue) + 1] = ':';
        a[poz][strlen("ERROR at position") + strlen(charValue) + 2] = ' ';

        for (int l = 0; l < strlen(tip_1); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + 2 + l + 1] = tip_1[l];

        for (int l = 0; l <= strlen(e); l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + 2 + strlen(tip_1) + l + 1] = e[l];
    }

}

void Verificare_Tipuri(char v[MAX][MAX1 + 1], int tip[MAX], int lungime)
{
    char charValue;
    for (int i = 1; i <= lungime - 2; i++)
    {
        if (i != lungime - 2)
        {
            if (tip[i] == 1 && (tip[i + 1] == 2 || tip[i + 1] == 4 || tip[i + 1] == -1)) /* '(' */
                Eroare_Tip(i, v[i], v[i + 1]);


            else

                if (tip[i] == 2 && (tip[i + 1] == 1 || tip[i + 1] == 5 || tip[i + 1] == 6 || tip[i + 1] == 7 || tip[i + 1] == -1)) /* ')' */
                    Eroare_Tip(i, v[i], v[i + 1]);

                else

                    if ((tip[i] == 3 && strlen(v[i]) == 1) && (tip[i + 1] == 2 || tip[i + 1] == 3 || tip[i + 1] == 4 || tip[i + 1] == -1))  /* '+-' binar */
                        Eroare_Tip(i, v[i], v[i + 1]);

                    else

                        if (tip[i] == 4 && (tip[i + 1] == 2 || (tip[i + 1] == 3 && strlen(v[i]) == 1) || tip[i + 1] == 4 || tip[i + 1] == -1)) /* '^/*' */
                            Eroare_Tip(i, v[i], v[i + 1]);

                        else
                            /* ln/sin/cos/tg/ctg/arcsin/arccos/arctg/arcctg/abs/exp/rad */
                            if (tip[i] == 5 && (tip[i + 1] == 2 || tip[i + 1] == 3 || tip[i + 1] == 5 || tip[i + 1] == -1)) ///daca nu urmeaza ( si nici un nr
                            {
                                if (strcmp("btg", v[i]) == 0)
                                    Eroare_Tip(i, "ctg", v[i + 1]);
                                else
                                    if (strcmp("drcsin", v[i]) == 0)
                                        Eroare_Tip(i, "arcsin", v[i + 1]);
                                    else
                                        if (strcmp("frccos", v[i]) == 0)
                                            Eroare_Tip(i, "arccos", v[i + 1]);
                                        else
                                            if (strcmp("grctg", v[i]) == 0)
                                                Eroare_Tip(i, "arctg", v[i + 1]);
                                            else
                                                if (strcmp("hrcctg", v[i]) == 0)
                                                    Eroare_Tip(i, "arcctg", v[i + 1]);
                                                else
                                                    Eroare_Tip(i, v[i], v[i + 1]);
                            }

                            else

                                if (tip[i] == 6 && (tip[i + 1] == 1 || tip[i + 1] == 5 || tip[i + 1] == 7 || tip[i + 1] == -1)) /*tip_cifre[14]="0123456789"*/
                                    Eroare_Tip(i, v[i], v[i + 1]);

                                else

                                    if (tip[i] == 7 && (tip[i + 1] == 1 || tip[i + 1] == 5 || tip[i + 1] == 7 || tip[i + 1] == -1)) /*char tip_litere[3]="xq" */
                                        Eroare_Tip(i, v[i], v[i + 1]);

                                    else

                                        if (tip[i] == -1)
                                            Eroare_Nepermis(i, v[i]);
        }

        else

            if (i == lungime - 2)
            {

                if (tip[i] == 1 || tip[i] == 3 || tip[i] == 4)
                    Eroare_Brusc(i, v[i]);

                else
                    if (tip[i] == 5)

                        if (strcmp("btg", v[i]) == 0)
                            Eroare_Brusc(i, "ctg");
                        else
                            if (strcmp("drcsin", v[i]) == 0)
                                Eroare_Brusc(i, "arcsin");
                            else
                                if (strcmp("frccos", v[i]) == 0)
                                    Eroare_Brusc(i, "arccos");
                                else
                                    if (strcmp("grctg", v[i]) == 0)
                                        Eroare_Brusc(i, "arctg");
                                    else
                                        if (strcmp("hrcctg", v[i]) == 0)
                                            Eroare_Brusc(i, "arcctg");
                                        else
                                            Eroare_Brusc(i, v[i]);

                    else

                        if (tip[i] == -1)
                            Eroare_Nepermis(i, v[i]);
            }
    }
}

int Verificare_Paranteze(char* s)
{
    int i, verif, k, j, lungime;
    lungime = strlen(s);
    k = 0;
    verif = 1;

    for (i = 0; i < lungime; i++)
    {
        if (s[i] == '(')
            k++;

        else
            if (s[i] == ')' && k == 0)
            {
                if (verif == 1)
                {
                    if (limba == 'r')
                        strcpy(a[++poz], "EROARE: Parantezele nu sunt inchise corect!");
                    else if (limba == 'e')
                        strcpy(a[++poz], "ERROR: The parentheses are not closed properly!");
                    verif = 0; ///pentru a afisa doar o data mesajul
                }
            }
            else
                if (s[i] == ')')
                    k--;
    }
    if (k != 0)
    {
        if (verif == 1)
        {
            if (limba == 'r')
                strcpy(a[++poz], "EROARE: Parantezele nu sunt inchise corect!");
            else if (limba == 'e')
                strcpy(a[++poz], "ERROR: The parentheses are not closed properly!");
            verif = 0; ///pentru a afisa doar o data mesajul
        }
    }
}


bool Expresie_Corecta(Functie& F, float x)
{
    bool corect;
    Verificare_Paranteze(F.expresie);
    Verificare_Tipuri(F.vect, F.Tip, F.lung);
    if (poz == 0)
    {
        Verificare_Domeniu(F, x);
        int p = poz;
        poz = 0;
        x = -201.1;
        Verificare_Domeniu(F, x);
        if (p != poz)
            poz = 0;
        else
        {
            if (p > poz)
                poz = p;
        }
    }

    if (poz == 0)
    {
        if (limba == 'r')
            strcpy(a[0], "Expresie corecta!");
        else if (limba == 'e')
            strcpy(a[0], "The expression is correct!");
        corect = true;
    }
    else
    {
        if (limba == 'r')
            strcpy(a[0], "Expresie gresita!");
        else if (limba == 'e')
            strcpy(a[0], "The expression is not correct!");
        corect = false;
    }

    for (int i = 0; i <= poz; i++)
        cout << a[i] << endl;

    return corect;
}

void backToMenu() {

    setcolor(12);
    settextstyle(1, 0, 1);
    rectangle(30, screen_height - 100, 230, screen_height - 75);
    outtextxy(40, screen_height - 95, "Inapoi la Menu");
}



void draw_pageII(int currentFunctionNumber)
{
    setbkcolor(COLOR(28, 33, 39));
    cleardevice();
    setcolor(COLOR(1, 3, 75));
    setlinestyle(0, USERBIT_LINE, 1);

    char text[100] = " ";

    //backgroud image
    char bk_image[255] = "";
    strcpy(bk_image, projectpath);
    strcat(bk_image, "\\images\\bk2.gif");

    //info sign image
    char info_sign_image[255] = "";
    strcpy(info_sign_image, projectpath);
    strcat(info_sign_image, "\\images\\info_sign.gif");

    //info box image
    char info_box[255] = "";
    strcpy(info_box, projectpath);
    strcat(info_box, "\\images\\info_box.gif");

    //backbutton image
    char backbutton_image[255] = "";
    strcpy(backbutton_image, projectpath);
    strcat(backbutton_image, "\\images\\backbutton.gif");


    //readimagefile( bk_image, -30, 0, screen_width + 60, screen_height);

    //backbutton
    setfillstyle(SOLID_FILL, COLOR(3, 57, 108));
    setbkcolor(COLOR(3, 57, 108));
    settextstyle(3, HORIZ_DIR, 3);
    settextjustify(1, 2);
    setcolor(0);

    if (limba == 'r')
        strcpy(text, "Inapoi");
    else if (limba == 'e')
        strcpy(text, "Back");

    //readimagefile( backbutton_image, 80, 110, 170, 180);
    outtextxy(135, 130, text);

    chenarBackButton = { 80, 110, 170, 180 };

    // info sign
    readimagefile(info_sign_image, screen_width - 120, 120, screen_width - 80, 160);
    info_field = { screen_width - 120, 120, screen_width - 80, 160 };

    if (info_pressed)
    {
        settextjustify(CENTER_TEXT, TOP_TEXT);

        readimagefile(info_box, screen_width - 300, 165, screen_width - 20, 530);

        setbkcolor(COLOR(28, 33, 39));
        setcolor(15);

        if (limba == 'r')
            strcpy(text, "Operatori");
        else if (limba == 'e')
            strcpy(text, "Operators");

        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 230, text);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 260, "+        -        *        /        ^");

        if (limba == 'r')
            strcpy(text, "Variabile");
        else if (limba == 'e')
            strcpy(text, "Variables");

        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 310, text);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 340, "x");

        if (limba == 'r')
            strcpy(text, "Functii");
        else if (limba == 'e')
            strcpy(text, "Functions");

        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 390, text);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 420, "sin    cos    arcsin    arccos");
        outtextxy(screen_width - 160, 450, "tg     ctg    arctg     arcctg");
        outtextxy(screen_width - 160, 480, "      rad    abs    ln        ");

    }

    setbkcolor(COLOR(28, 33, 39));
    setcolor(COLOR(3, 57, 108));

    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(10, HORIZ_DIR, 5);

    /*if(limba == 'r')
        strcpy(text, "Scrieti expresia functiei!");
    else if(limba == 'e')
        strcpy(text, "Write the function expression!");
*/
    if (limba == 'r')
        sprintf(text, "Introdu functia cu nr %d:", currentFunctionNumber + 1);
    else if (limba == 'e')
        sprintf(text, "Enter function with number %d:", currentFunctionNumber + 1);
    int width = textwidth(text);
    int height = textheight(text);
    outtextxy((screen_width - width) / 2, 120, text);

    // Partea pentru introducerea functiei
    setcolor(0);
    if (func_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    int width2 = textwidth("F(x)= ");
    outtextxy((screen_width - 500 - width2) / 2 - 200, 160 + height, "F(x)= ");
    rectangle((screen_width - 500) / 2 - 200 + width2 / 2, 150 + height, (screen_width + 500) / 2 + 200, 210 + height);

    functie = { (screen_width - 500) / 2 - 200 + width2 / 2, 150 + height, (screen_width + 500) / 2 + 200, 210 + height };

    height += textheight("F(x)= ");

    // Partea pentru afisarea mesajului despre interval
    settextstyle(10, HORIZ_DIR, 4);
    setcolor(COLOR(3, 57, 108));

    /*if(limba == 'r')
        strcpy(text, "Fixati intervalul de reprezentare: [a,b]");
    else if(limba == 'e')
        strcpy(text, "Set the representation range: [a,b]");
*/
    if (limba == 'r')
        sprintf(text, "Fixati intervalul de reprezentare pentru functia %d: [a, b]", currentFunctionNumber + 1);
    else if (limba == 'e')
        sprintf(text, "Set the representation range for function %d: [a, b]", currentFunctionNumber + 1);

    int width3 = textwidth(text);
    outtextxy((screen_width - width3) / 2, 210 + height, text);
    height += textheight(text);


    settextstyle(10, HORIZ_DIR, 5);

    //Partea cu introducerea valorii lui a
    setcolor(0);
    if (a_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    int width4 = textwidth("a= ");
    outtextxy((screen_width - width3) / 2 + 100, 250 + height, "a= ");
    rectangle((screen_width - width3) / 2 + width4 + 100, 240 + height, (screen_width - width3) / 2 + width4 + 220, 300 + height);

    a_field = { (screen_width - width3) / 2 + width4 + 100, 240 + height, (screen_width - width3) / 2 + width4 + 220, 300 + height };

    //Partea cu introducerea valorii lui b
    if (b_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    int width5 = textwidth("b= ");
    outtextxy((screen_width + width3) / 2 - 220 - width5, 250 + height, "b= ");
    rectangle((screen_width + width3) / 2 - 220, 240 + height, (screen_width + width3) / 2 - 100, 300 + height);

    b_field = { (screen_width + width3) / 2 - 220, 240 + height, (screen_width + width3) / 2 - 100, 300 + height };

    //Erori
    setcolor(COLOR(3, 57, 108));
    setlinestyle(0, USERBIT_LINE, 1);

    if (limba == 'r')
        strcpy(text, "Erori:");
    else if (limba == 'e')
        strcpy(text, "Errors:");

    int width6 = textwidth(text);
    int height6 = textheight(text);

    outtextxy((screen_width - width6) / 2, 330 + height, text);

    rectangle(screen_width / 2 - 435, 340 + height + height6, screen_width / 2 + 435, 515 + height);

    settextstyle(10, HORIZ_DIR, 1);
    setcolor(COLOR(3, 57, 108));
    settextjustify(0, 2);

    if (poz > 6)
        poz = 6;

    for (int i = 0; i <= poz; i++)
    {
        if (strcmp(a[0], "Expresie corecta!") && strcmp(a[0], "The expression is correct!"))
        {
            int h = textheight(a[i]);
            outtextxy(screen_width / 2 - 430, 345 + height + height6 + i * h, a[i]);
        }
    }


    setbkcolor(COLOR(3, 57, 108));
    setcolor(COLOR(28, 33, 39));
    settextstyle(10, 0, 3);
    setlinestyle(0, USERBIT_LINE, 1);
    setfillstyle(SOLID_FILL, COLOR(3, 57, 108));

    //Butonul de introducere din fisier

    /*bar((screen_width-310), 525+height, (screen_width-130), 575+height);
    outtextxy((screen_width-304), 538+height, "function.txt");
*/
    bar((screen_width - 310), 525 + height, (screen_width - 130), 575 + height);
    sprintf(text, "function%d.txt", currentFunctionNumber + 1);
    outtextxy((screen_width - 304), 538 + height, text);


    file_field = { (screen_width - 310), 525 + height, (screen_width - 140), 575 + height };

    //Butonul de desenare
    bar((screen_width - 150) / 2, 525 + height, (screen_width + 150) / 2, 575 + height);

    button_field = { (screen_width - 150) / 2, 525 + height, (screen_width + 150) / 2, 575 + height };

    /*if(limba == 'r')
        strcpy(text, "Deseneaza");
    else if(limba == 'e')
        strcpy(text, "Draw");
*/
    if (limba == 'r')
        sprintf(text, "Deseneaza functia %d", currentFunctionNumber + 1);
    else if (limba == 'e')
        sprintf(text, "Draw function %d", currentFunctionNumber + 1);

    int width7 = textwidth(text);
    outtextxy((screen_width - width7) / 2, 538 + height, text);

    setbkcolor(COLOR(28, 33, 39));
}




void read_pageII(Functie& f, bool& start_page, bool& f_ok, int currentFunctionNumber)
{
    //resetare f
    strcpy(f.expresie, " ");
    f.lung = 0;
    f.a = 0;
    f.b = 0;

    char c = ' ';
    char f_expresie[31] = "";
    char a[5] = "-10";
    char b[5] = "10";
    int i_func = 0;
    int i_a = strlen(a);
    int i_b = strlen(b);

    if (!f_ok)
    {
        strcpy(f_expresie, f_expresie_salvat);
        i_func = strlen(f_expresie);

        strcpy(a, a_salvat);
        i_a = strlen(a);

        strcpy(b, b_salvat);
        i_b = strlen(b);

        f_ok = true;
    }

    int x;
    int y;

    func_pressed = true;
    a_pressed = false;
    b_pressed = false;

    int page = 3;

    setactivepage(page);
    setvisualpage(page);
    page = (page == 3 ? 4 : 3);

    draw_pageII(currentFunctionNumber);

    setactivepage(page);
    setvisualpage(page == 3 ? 4 : 3);
    page = (page == 3 ? 4 : 3);

    bool d = true;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN) || c == 13)
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (esteApasat(functie, x, y))
            {
                func_pressed = true;
                a_pressed = false;
                b_pressed = false;
                d = true;
            }
            else if (esteApasat(file_field, x, y))
            {
                func_pressed = true;
                a_pressed = false;
                b_pressed = false;
                d = true;

                read_file(f_expresie, "function.txt");
                // read_file(f_expresie, ("function" + to_string(currentFunctionNumber + 1) + ".txt").c_str());
                f_expresie[30] = '\0';
                i_func = strlen(f_expresie);

            }
            else if (esteApasat(a_field, x, y))
            {
                func_pressed = false;
                a_pressed = true;
                b_pressed = false;
                d = true;
            }
            else if (esteApasat(b_field, x, y))
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = true;
                d = true;
            }
            else if (esteApasat(info_field, x, y))
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = false;

                if (info_pressed)
                    info_pressed = false;
                else
                    info_pressed = true;

                d = true;
            }
            else if (esteApasat(chenarBackButton, x, y))
            {
                start_page = true;
                poz = -1;
                return;
            }
            else if (esteApasat(button_field, x, y) || c == 13)
            {
                c = 0;
                if (strlen(f_expresie) == 0)
                {
                    d = true;
                    continue;
                }

                if (strlen(a) == 0)
                {
                    strcpy(a, "-10");
                    i_a = 3;
                }
                if (strlen(b) == 0)
                {
                    strcpy(b, "10");
                    i_b = 2;
                }

                if (a[0] == '-')
                {
                    char str[4];
                    strcpy(str, a + 1);
                    f.a = stoi(str);
                    f.a *= -1;
                }
                else
                {
                    f.a = stoi(a);
                }
                if (b[0] == '-')
                {
                    char str[4];
                    strcpy(str, b + 1);
                    f.b = stoi(str);
                    f.b *= -1;
                }
                else
                {
                    f.b = stoi(b);
                }

                if ((f.a + 3 > f.b) || ((f.b - f.a) >= 250) || f.a < -200 || f.b < -200 || f.a > 200 || f.b > 200)
                {
                    continue;
                }

                strcpy(f.expresie, f_expresie);
                f.lung = strlen(f.expresie);

                strcpy(f_expresie_salvat, f_expresie);
                strcpy(a_salvat, a);
                strcpy(b_salvat, b);

                // reset styles
                settextstyle(0, HORIZ_DIR, 2);
                break;
            }
            else
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = false;
                d = true;
            }
        }

        if (func_pressed)
        {
            if (kbhit())
            {
                c = getch();

                if (c == 8)
                {
                    if (i_func > 0)
                    {
                        f_expresie[i_func - 1] = '\0';
                        --i_func;
                        d = true;
                    }
                }
                else if (strchr("+-*/^x1234567890sincoartgdblq()<>.", c))
                {
                    if (!(f_expresie[i_func - 1] == '/' && c == '0') && !(f_expresie[i_func - 2] == '/' && f_expresie[i_func - 1] == '(' && c == '0'))
                    {
                        if (i_func < 30 && c != 13)
                        {
                            f_expresie[i_func] = c;
                            ++i_func;
                            d = true;
                        }
                    }
                }
            }
        }
        if (a_pressed)
        {
            if (kbhit())
            {
                c = getch();

                if (c == 8)
                {
                    if (i_a > 0)
                    {
                        a[i_a - 1] = '\0';
                        --i_a;
                        d = true;
                    }
                }
                else if (strchr("-1234567890", c))
                {
                    if ((i_a < 4 && c != '-') || (i_a < 1))
                    {
                        a[i_a] = c;
                        ++i_a;
                        d = true;

                    }
                }
            }
        }
        if (b_pressed)
        {
            if (kbhit())
            {
                c = getch();

                if (c == 8)
                {
                    if (i_b > 0)
                    {
                        b[i_b - 1] = '\0';
                        --i_b;
                        d = true;
                    }
                }
                else if (strchr("-1234567890", c))
                {
                    if ((i_b < 4 && c != '-') || (i_b < 1))
                    {
                        b[i_b] = c;
                        ++i_b;
                        d = true;

                    }
                }
            }
        }
        if (d)
        {
            setactivepage(page);
            setvisualpage(page == 3 ? 4 : 3);
            page = page == 3 ? 4 : 3;

            draw_pageII(currentFunctionNumber);

            setcolor(COLOR(3, 57, 108));
            settextstyle(3, 0, 5);
            outtextxy(functie.x1 + 5, functie.y1 + 10, f_expresie);
            outtextxy(a_field.x1 + 5, a_field.y1 + 10, a);
            outtextxy(b_field.x1 + 5, b_field.y1 + 10, b);

            setactivepage(page);
            setvisualpage(page == 3 ? 4 : 3);
            page = page == 3 ? 4 : 3;
            d = false;
        }
        if (!(func_pressed || a_pressed || b_pressed))
            if (kbhit())
                c = getch();
    }
}
void reguli() {
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy(screen_width / 2 - 100, 50, "Reguli");

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);

    // Coloana 1 - Functii disponibile
    int col1_x = 50;
    int current_y = 150;

    outtextxy(col1_x, current_y, "1. Functii disponibile:");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - sin(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - cos(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - exp(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - ln(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - abs(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - rad(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - tg(x)");
    current_y += 30;
    outtextxy(col1_x, current_y, "   - ctg(x)");
    // Adaugă alte funcții disponibile în această coloană după nevoie

    // Coloana 2 - Operatori disponibili
    int col2_x = screen_width / 3 + 50;
    current_y = 150;

    outtextxy(col2_x, current_y, "2. Operatori disponibili:");
    current_y += 30;
    outtextxy(col2_x, current_y, "   - +  (adunare)");
    current_y += 30;
    outtextxy(col2_x, current_y, "   - -  (scadere)");
    current_y += 30;
    outtextxy(col2_x, current_y, "   - *  (inmultire)");
    current_y += 30;
    outtextxy(col2_x, current_y, "   - /  (impartire)");
    current_y += 30;
    outtextxy(col2_x, current_y, "   - ^  (putere)");
    // Adaugă alți operatori disponibili în această coloană după nevoie

    // Coloana 3 - Exemple de functii
    int col3_x = 2 * screen_width / 3 + 50;
    current_y = 150;

    outtextxy(col3_x, current_y, "3. Exemple de functii:");
    current_y += 30;
    outtextxy(col3_x, current_y, "   - x^2 + 5*x, pentru x < n");
    current_y += 30;
    outtextxy(col3_x, current_y, "   - cos(x), pentru x > n");
    // Adaugă alte exemple de funcții în această coloană după nevoie

    backToMenu();
}


void read_reguli_page()
{

    int ac_page = getactivepage();
    int vs_page = getvisualpage();

    setactivepage(vs_page);
    setvisualpage(ac_page);

    reguli();

    setactivepage(ac_page);
    setvisualpage(vs_page);

    int x;
    int y;

    chenarBackButton = { 30, screen_height - 100, 230, screen_height - 75 };

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (esteApasat(chenarBackButton, x, y))
            {
                return;
            }
        }

    }
}

void drawSlider(int x, int y, int width, int height, int position) {

    setcolor(LIGHTGREEN);  // Change the color
    setfillstyle(SOLID_FILL, LIGHTGREEN);  // Change the fill color

    // Draw a rounded rectangle
    rectangle(x, y, x + width, y + height);
    floodfill(x + width / 2, y + height / 2, LIGHTGREEN);

    // Draw the filled part of the slider
    bar(x, y, x + position, y + height);
}

void setari(bool musicToggleButtonState, bool soundToggleButtonState, int volumeSliderPosition) {

    cleardevice();
    setcolor(WHITE);

    settextstyle(6, HORIZ_DIR, 2);
    outtextxy(320, 50, "Setari");

    settextstyle(1, HORIZ_DIR, 1);

    outtextxy(100, 150, "Muzica:");

    outtextxy(100, 180, "Sunet:");

    outtextxy(100, 300, "Volum:");

    // Draw music toggle button
    rectangle(475, 145, 530, 170);
    musicToggleButtonState ?
        outtextxy(480, 150, "ON") :
        outtextxy(480, 150, "OFF");

    // Draw sound toggle button
    rectangle(470, 175, 535, 200);
    soundToggleButtonState ?
        outtextxy(480, 180, "ON") :
        outtextxy(480, 180, "OFF");
    backToMenu();

    rectangle(460, 300, 485, 320);
    outtextxy(465, 302, "-");
    rectangle(715, 300, 740, 320);
    outtextxy(720, 302, "+");

    rectangle(500, 300, 700, 320);
    drawSlider(501, 301, 20, 20, volumeSliderPosition);

}

void read_setari_page()
{

    int ac_page = getactivepage();
    int vs_page = getvisualpage();

    setactivepage(vs_page);
    setvisualpage(ac_page);

    int volumeSliderPosition = 0;
    bool musicToggleButtonState = true;
    bool soundToggleButtonState = true;

    setari(musicToggleButtonState, soundToggleButtonState, volumeSliderPosition);

    setactivepage(ac_page);
    setvisualpage(vs_page);

    int x;
    int y;


    coordonateButon music, sunet, volumeUp, volumeDown;

    music = { 475, 145, 530, 170 };
    sunet = { 475, 175, 530, 200 };
    volumeUp = { 715, 300, 740, 320 };
    volumeDown = { 460, 300, 485, 320 };

    chenarBackButton = { 30, screen_height - 100, 230, screen_height - 75 };

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (esteApasat(chenarBackButton, x, y))
            {
                return;
            }
            else if (esteApasat(music, x, y))
            {
                musicToggleButtonState = !musicToggleButtonState;
            }
            else if (esteApasat(sunet, x, y))
            {
                soundToggleButtonState = !soundToggleButtonState;
            }
            else if (esteApasat(volumeUp, x, y))
            {
                if (volumeSliderPosition < 200)
                    volumeSliderPosition += 20;
            }
            else if (esteApasat(volumeDown, x, y))
            {
                if (volumeSliderPosition > 0)
                    volumeSliderPosition -= 20;
            }

            setari(musicToggleButtonState, soundToggleButtonState, volumeSliderPosition);
        }

    }
}


void deseneazaMenu() {
    // Load the image before setting the background color
    readimagefile("D:\\FII\\Semestrul I\\Introducere în programare\\Proiect_IP_Function_Graph\\src\\images\\background.gif", 0, 0, screen_width, screen_height);

    setbkcolor(COLOR(28, 33, 39));

    // Remove cleardevice() to keep the loaded image

    settextstyle(0, HORIZ_DIR, 5);

    setcolor(0);

    setfillstyle(SOLID_FILL, COLOR(28, 33, 39));
    bar(0, 0, getmaxx(), getmaxy());

    char background[255] = "";
    strcpy(background, projectpath);
    strcat(background, "\\images\\background.jpeg");

    setcolor(WHITE);

    // Desenăm titlul proiectului
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
    outtextxy(screen_width / 2 - 140, 100, "Grafic");

    settextstyle(1, 0, 3);

    // Desenăm optiunile din meniu
    int optionHeight = 250;  // Începe de la această înălțime

    rectangle(screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50);
    outtextxy(screen_width / 2 - 150, optionHeight + 10, "Graficul Functiei");
    chenarGrafic = { screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50 };

    optionHeight += 80;

    rectangle(screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50);
    outtextxy(screen_width / 2 - 150, optionHeight + 10, "Reguli");
    chenarReguli = { screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50 };

    optionHeight += 80;

    rectangle(screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50);
    outtextxy(screen_width / 2 - 150, optionHeight + 10, "Setari");
    chenarSetari = { screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50 };

    optionHeight += 80;

    rectangle(screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50);
    outtextxy(screen_width / 2 - 150, optionHeight + 10, "Iesire");
    chenarIesire = { screen_width / 2 - 160, optionHeight, screen_width / 2 + 140, optionHeight + 50 };
}




void read_start_page()
{
    //music
    char music_path[255] = "";
    strcpy(music_path, projectpath);
    strcat(music_path, "\\music\\music.wav");


    int ac_page = getactivepage();
    int vs_page = getvisualpage();

    setactivepage(vs_page);
    setvisualpage(ac_page);

    deseneazaMenu();

    setactivepage(ac_page);
    setvisualpage(vs_page);

    int x;
    int y;

    bool d = true;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (esteApasat(chenarGrafic, x, y))
            {
                return;
            }
            else if (esteApasat(chenarSetari, x, y))
            {
                read_setari_page();
                d = true;
            }
            else if (esteApasat(flag_field, x, y))
            {
                if (limba == 'r')
                {
                    limba = 'e';
                    char l[] = "e";
                    write_file(l, "language.txt");
                }
                else if (limba == 'e')
                {
                    limba = 'r';
                    char l[] = "r";
                    write_file(l, "language.txt");
                }
                d = true;
            }
            else if (esteApasat(chenarReguli, x, y))
            {
                read_reguli_page();
                d = true;
            }
            else if (esteApasat(chenarIesire, x, y))
            {
                closegraph();
                exit(0);
            }
        }
        if (d)
        {
            setactivepage(vs_page);
            setvisualpage(ac_page);

            deseneazaMenu();

            setactivepage(ac_page);
            setvisualpage(vs_page);
            d = false;
        }
    }
}


bool handle_key(char c, Grafic& g)
{
    switch (c)
    {
    case 'z':
        if (g.x1 + 3 < g.x2)
        {
            g.x1 += 0.5;
            g.x2 -= 0.5;
            g.y1 -= 0.25;
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
            return true;
        }
        return false;
    case 'u':
        if ((g.x2 - g.x1) <= 250 && g.x2 <= 200 && g.x1 >= -200 && g.y1 <= 150 && g.y2 >= -150)
        {
            g.x1 -= 0.5;
            g.x2 += 0.5;
            g.y1 += 0.25;
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
            return true;
        }
        return false;
    case 'd':
        if (g.x2 <= 200)
        {
            g.x1 += 0.5;
            g.x2 += 0.5;
            return true;
        }
        return false;
    case 'a':
        if (g.x1 >= -200)
        {
            g.x1 -= 0.5;
            g.x2 -= 0.5;
            return true;
        }
        return false;
    case 'w':
        if (g.y1 <= 150)
        {
            g.y1 += 0.5;
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
            return true;
        }
        return false;
    case 's':
        if (g.y2 >= -150)
        {
            g.y1 -= 0.5;
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
            return true;
        }
        return false;
    default:
        return false;
    }

}

void mouseClick(Grafic& g, bool& d, apasat& apasat)
{
    float precizie = 100;
    static int prevx, prevy, curx, cury;
    static bool isup = true, pressed = false;

    if (ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, prevx, prevy);
        isup = false;
        pressed = apasaPeButton(g, prevx, prevy, d, apasat); //din draw_graph_buttons
    }
    if (ismouseclick(WM_LBUTTONUP))
    {
        isup = true;
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONUP);
    }
    if (!isup && !pressed) // daca nu este nici un buton apasat si butonul din stanga nu este apasat
    {
        curx = mousex();
        cury = mousey();

        Punct current;
        current.x = curx * precizie; // imultim cu precizia, deoarece cand traduceam aveam probleme
        current.y = cury * precizie;
        current = translateInapoi(current, g);

        Punct precedent;
        precedent.x = prevx * precizie;
        precedent.y = prevy * precizie;
        precedent = translateInapoi(precedent, g);


        float diffx = current.x - precedent.x, diffy = current.y - precedent.y;

        if (diffx > 0 && g.x1 >= -200)
        {
            if (g.x1 - diffx / precizie < -200)
                diffx = (g.x1 + 200) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este -200
            d = true;
            g.x1 -= (diffx / precizie);
            g.x2 -= (diffx / precizie);
        }
        if (diffx < 0 && g.x2 <= 200)
        {
            if (g.x2 - diffx / precizie > 200)
                diffx = (g.x2 - 200) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este 200
            d = true;
            g.x1 -= (diffx / precizie);
            g.x2 -= (diffx / precizie);
        }
        if (diffy > 0 && g.y2 >= -150)
        {
            if (g.y2 - diffy / precizie < -150)
                diffy = (g.y2 + 150) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este -150
            d = true;
            g.y1 -= (diffy / precizie);
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
        }
        if (diffy < 0 && g.y1 <= 150)
        {
            if (g.y1 - diffy / precizie > 150)
                diffy = (g.y1 - 150) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este 150
            d = true;
            g.y1 -= (diffy / precizie);
            g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);
        }
        prevx = curx;
        prevy = cury;
    }
}
void read_numFunc(int numFunctions)
{
    char numFunctionsFilePath[100];
    strcat(numFunctionsFilePath, projectpath);
    strcat(numFunctionsFilePath, "\\files\\numFunctions.txt");
    ifstream numFunctionsFile(numFunctionsFilePath);

    if (numFunctionsFile.is_open()) {
        numFunctionsFile >> numFunctions;
        numFunctionsFile.close();
    }
    else {
        // Handle error when the file cannot be opened
        throw runtime_error("Error: Unable to open numFunctions.txt"); // Return an error code
    }
}

int main() {

    Grafic g;
    g.x1_ecran = 0;
    g.x2_ecran = screen_width;
    g.y1_ecran = 0;
    g.y2_ecran = screen_height;

    Punct minGraf, maxGraf;

    Functie F = { " " };

    int page = 0;

    getcwd(projectpath, sizeof(projectpath));

    initwindow(screen_width, screen_height, "Function Graph");
    const int numPoints = 800;
    const double initialXScale = screen_width;
    const double initialYScale = screen_height;

    double xScale = 1;
    double yScale = 1;


    //           citestefunc  min    max salveaza
    apasat apasat = { true, false, false, false };

    bool start_page = true;

    char c = ' ';

    bool d = true;

    bool f_ok = true;

    int numFunctions;
    char numFunctionsFilePath[100];
    strcat(numFunctionsFilePath, projectpath);
    strcat(numFunctionsFilePath, "\\files\\numFunctions.txt");
    ifstream numFunctionsFile(numFunctionsFilePath);

    if (numFunctionsFile.is_open()) {
        numFunctionsFile >> numFunctions;
        numFunctionsFile.close();
    }
    else {
        // Handle error when the file cannot be opened
        cerr << "Error: Unable to open numFunctions.txt" << endl;
        return 1; // Return an error code
    }
    FunctionGraph functionGraphs[numFunctions];

    int currentFunctionNumber = 0;
    while (true)
    {
        if (start_page)
        {
            read_start_page();
            start_page = false;
            apasat.citesteFunctie = true;
        }
        if (apasat.citesteFunctie)
        {
            apasat.citesteFunctie = false;

            for (int i = 0; i < numFunctions; ++i) {
                read_pageII(functionGraphs[i].F, start_page, f_ok, currentFunctionNumber);

                if (start_page)
                    continue;

                Elimin_Spatii(functionGraphs[i].F.expresie);

                Cuvinte(functionGraphs[i].F.expresie);
                Adaugare_Vector(functionGraphs[i].F);

                Codificare_Fct_Trigonometrice(functionGraphs[i].F);

                Tip(functionGraphs[i].F);

                poz = 0;

                float x = 201.1;

                if (!Expresie_Corecta(functionGraphs[i].F, x))
                {
                    apasat.citesteFunctie = true;
                    f_ok = false;
                    continue;
                }
                /*            std::string filename = "function" + std::to_string(currentFunctionNumber + 1) + ".txt";
            char* filenameCharArray = new char[filename.length() + 1];
            strcpy(filenameCharArray, filename.c_str());

            read_file(f_expresie, filenameCharArray);

            // Eliberarea memoriei alocate pentru filenameCharArray
            delete[] filenameCharArray;
            std::string filename = "function" + std::to_string(currentFunctionNumber + 1) + ".txt";
        char* filenameCharArray = (char*)malloc((filename.length() + 1) * sizeof(char));
        strcpy(filenameCharArray, filename.c_str());

        read_file(f_expresie, filenameCharArray);

        // Eliberarea memoriei alocate pentru filenameCharArray
        free(filenameCharArray);
*/
//pregatire coordonate grafic
                g.x1 = functionGraphs[i].F.a;
                g.x2 = functionGraphs[i].F.b;

                float dif = (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);

                g.y1 = dif / 2;
                g.y2 = g.y1 - (g.x2 - g.x1) * (g.y2_ecran - g.y1_ecran) / (g.x2_ecran - g.x1_ecran);


                functionGraphs[i].minGraf.x = functionGraphs[i].F.a;
                functionGraphs[i].minGraf.y = ValoareFunctie(functionGraphs[i].F, functionGraphs[i].minGraf.x);

                functionGraphs[i].maxGraf.x = functionGraphs[i].F.b;
                functionGraphs[i].maxGraf.y = ValoareFunctie(functionGraphs[i].F, functionGraphs[i].maxGraf.x);

                setcolor(WHITE);
            }

            setactivepage(page);
            setvisualpage(1 - page);
            page = 1 - page;

            setcolor(WHITE);
            cleardevice();
            currentFunctionNumber++;
            for (int i = 0; i < numFunctions; ++i) {
                deseneazaGrafic(g, functionGraphs[i]);
                deseneazaMinMax(g, functionGraphs[i].minGraf, functionGraphs[i].maxGraf, apasat.minimGraf, apasat.maximGraf);

                deseneazaButoane(g, apasat, projectpath);



                d = true;

            }

            setactivepage(page);
            setvisualpage(1 - page);
            page = 1 - page;
        }


        if (kbhit())
        {
            c = getch();
            if (handle_key(c, g))
                d = true;
        }

        mouseClick(g, d, apasat);

        if (d)
        {
            cleardevice();
            for (int i = 0; i < numFunctions; ++i) {

                deseneazaGrafic(g, functionGraphs[i]);
                deseneazaMinMax(g, functionGraphs[i].minGraf, functionGraphs[i].maxGraf, apasat.minimGraf, apasat.maximGraf);

                if (apasat.salveaza)
                {
                    writeimagefile();
                    apasat.salveaza = false;
                }

                deseneazaButoane(g, apasat, projectpath);

            }

            setactivepage(1 - page);
            setvisualpage(page);
            page = 1 - page;

            d = false;
        }
    }
    closegraph(); return 0;
}
