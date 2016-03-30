#include <stdio.h>
#include <stdint.h>

/* get the i-th bit from A (the right bit is 0-th) */
#define BIT(A, i) ((((A)>>i)&1)==1)

/* do the cla */
uint64_t cla(uint64_t A, uint64_t B);

/* print bin for a 64-bit number */
void print_bin(uint64_t A);

int main(int argc, char *argv[]) {
    uint64_t A = 0, B = 0, S = 0;

    /* get input from stdin, using %lx */
    printf("Enter A (hex): ");
    scanf("%lx", &A);
    printf("Enter B (hex): ");
    scanf("%lx", &B);

    /* get the result */
    S = cla(A, B);

    /* print results */
    printf("\nA is %016lx or %lu\n", A, A);
    printf("B is %016lx or %lu\n\n", B, B);

    printf("Calculate sum, S:\n\n");
    printf("A (bin): ");
    print_bin(A);
    printf("B (bin): ");
    print_bin(B);
    printf("S (bin): ");
    print_bin(S);

    printf("\nS is %016lx or %lu\n\n", S, S);

    return 0;
}

uint64_t cla(uint64_t A, uint64_t B) {
    /* using int to store bits */
    int i = 0, j = 0, k = 0;

    /* get each bits of A and B, a[i] store the i-th bit */
    int a[64], b[64];
    for (i = 0; i < 64; i++) {
        a[i] = BIT(A, i);
        b[i] = BIT(B, i);
    }

    /* 1. Calculate gi and pi for all i(1 gate delay */
    int g[64], p[64];
    for (i = 0; i < 64; i++) {
        g[i] = a[i] & b[i];
        p[i] = a[i] | b[i];
    }

    /* 2. Calculate ggj and gpj for all j using gi and pi. (2 gate delays) */
    int gg[16], gp[16];
    for (j = 0; j < 16; j++) {
        i = j * 4;
        gg[j] = g[i+3] | (p[i+3] & g[i+2]) | (p[i+3] & p[i+2] & g[i+1])
            | (p[i+3] & p[i+2] & p[i+1] & g[i]);
        gp[j] = p[i+3] & p[i+2] & p[i+1] & p[i];
    }

    /* 3. Calculate sgk and spk for all k using ggj and gpj. (2 gate delays) */
    int sg[4], sp[4];
    for (k = 0; k < 4; k++) {
        j = k * 4;
        sg[k] = gg[j+3] | (gp[j+3] & gg[j+2]) | (gp[j+3] & g[j+2] & gg[j+1])
            | (gp[j+3] & gp[j+2] & gp[j+1] & gg[j]);
        sp[k] = gp[j+3] & gp[j+2] & gp[j+1] & gp[j];
    }

    /* 4. Calculate sck using sgk and spk for all k and 0 for sci−1. (2 gate delays) */
    int sc[4];
    for (k = 0; k < 4; k++) {
        if (k == 0) {
            sc[k] = sg[k];
        } else {
            sc[k] = sg[k] | (sp[k] & sc[k - 1]);
        }
    }

    /* 5. Calculate gcj using ggj, gpj and correct sck,k = (j div 4) as
     * sectional carry-in for all j. (2 gate delays) */ 
    int gc[16];
    for (j = 0; j < 16; j++) {
        k = j / 4;
        if (j % 4 == 0) {
            if (k == 0) {
                gc[j] = gg[j];
            } else {
                gc[j] = gg[j] | (gp[j] & sc[k - 1]);
            }
        } else {
            gc[j] = gg[j] | (gp[j] & gc[j - 1]);
        }
    }

    /* 6. Calculate ci using gi, pi and correct gcj, j = (i div 4) as
     * group carry-in for all i. (2 gate delays) */
    int c[64];
    for (i = 0; i < 64; i++) {
        j = i / 4;
        if (i % 4 == 0) {
            if (j == 0) {
                c[i] = g[i];
            } else {
                c[i] = g[i] | (p[i] & gc[j - 1]);
            }
        } else {
            c[i] = g[i] | (p[i] & c[i - 1]);
        }
    }
    
    /* 7. Calculate sumi using ai^bi^ci for all i. (2 gate delays) */
    int sum[64];
    for (i = 0; i < 64; i++) {
        if (i == 0) {
            sum[i] = a[i] ^ b[i];
        } else {
            sum[i] = a[i] ^ b[i] ^ c[i - 1];
        }
    }

    /* just for debug
    printf(" a: "); for (i = 0; i < 64; i++) { printf("%d", a[i]); if(i%4==3)printf(" ");} printf("\n");
    printf(" b: "); for (i = 0; i < 64; i++) { printf("%d", b[i]); if(i%4==3)printf(" ");} printf("\n");
    printf(" g: "); for (i = 0; i < 64; i++) { printf("%d", g[i]); if(i%4==3)printf(" ");} printf("\n");
    printf(" p: "); for (i = 0; i < 64; i++) { printf("%d", p[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("gg: "); for (i = 0; i < 16; i++) { printf("%d", gg[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("gp: "); for (i = 0; i < 16; i++) { printf("%d", gp[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("sg: "); for (i = 0; i < 4; i++) { printf("%d", sg[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("sp: "); for (i = 0; i < 4; i++) { printf("%d", sp[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("sc: "); for (i = 0; i < 4; i++) { printf("%d", sc[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("gc: "); for (i = 0; i < 16; i++) { printf("%d", gc[i]); if(i%4==3)printf(" ");} printf("\n");
    printf("c: "); for (i = 0; i < 64; i++) { printf("%d", c[i]); if(i%4==3)printf(" ");} printf("\n");
    */

    uint64_t S = 0;
    for (i = 0; i < 64; i++) {
        S |= (uint64_t)sum[i] << i;
    }
    return S;
}

void print_bin(uint64_t A) {
    /* print each bit */
    int i = 0;
    for (i = 63; i >= 0; i--) {
        printf("%d", BIT(A, i));
    }
    printf("\n");
}

