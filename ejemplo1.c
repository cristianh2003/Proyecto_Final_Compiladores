/*
 * programa de ejemplo No. 1
 */
int scanf(char *fmt, ...);
int printf(char *fmt, ...);
int main(void)
{
    int i, j;
    i = scanf("%d");                /* lea i */
    j = 9 + i * 8;                  /* evalue j */
    printf("Resultado es %d\n", j); /* imprima j */
}