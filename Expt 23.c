#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int P10[]={3,5,2,7,4,10,1,9,8,6};
int P8[]={6,3,7,4,8,5,10,9};
int IP[]={2,6,3,1,4,8,5,7};
int IPI[]={4,1,3,5,7,2,8,6};
int EP[]={4,1,2,3,2,3,4,1};
int P4[]={2,4,3,1};

int S0[4][4]={
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4]={
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

int permute(int v,int *t,int n,int bits)
{
    int r=0;
    for(int i=0;i<n;i++)
        r=(r<<1)|((v>>(bits-t[i]))&1);
    return r;
}

int shift(int v,int s,int bits)
{
    return ((v<<s)|(v>>(bits-s)))&((1<<bits)-1);
}

void generate_keys(int key,int *k1,int *k2)
{
    int p=permute(key,P10,10,10);
    int l=p>>5,r=p&31;

    l=shift(l,1,5);
    r=shift(r,1,5);
    *k1=permute((l<<5)|r,P8,8,10);

    l=shift(l,2,5);
    r=shift(r,2,5);
    *k2=permute((l<<5)|r,P8,8,10);
}

int fk(int v,int k)
{
    int l=v>>4,r=v&15;
    int e=permute(r,EP,8,4)^k;

    int a=e>>4,b=e&15;
    int row0=((a&8)>>2)|(a&1);
    int col0=(a>>1)&3;
    int row1=((b&8)>>2)|(b&1);
    int col1=(b>>1)&3;

    int s=(S0[row0][col0]<<2)|S1[row1][col1];

    return ((l^permute(s,P4,4,4))<<4)|r;
}

int encrypt(int p,int k1,int k2)
{
    int v=permute(p,IP,8,8);
    v=fk(v,k1);
    v=((v&15)<<4)|(v>>4);
    v=fk(v,k2);
    return permute(v,IPI,8,8);
}

int main()
{
    char plaintext[]="000000010000001000000100";
    char keystr[]="0111111101";

    int key=strtol(keystr,NULL,2);
    int k1,k2;

    generate_keys(key,&k1,&k2);

    int n=strlen(plaintext)/8;
    int pt[10],ct[10],dt[10];

    for(int i=0;i<n;i++)
    {
        char temp[9];
        strncpy(temp,plaintext+i*8,8);
        temp[8]='\0';
        pt[i]=strtol(temp,NULL,2);
    }

    printf("ENCRYPTION AND DECRYPTION USING CTR MODE\n");
    printf("Plaintext: %s\n",plaintext);
    printf("Key: %s\n",keystr);
    printf("Initial Counter: 00000000\n");

    for(int i=0;i<n;i++)
    {
        int counter=i;
        int keystream=encrypt(counter,k1,k2);
        ct[i]=pt[i]^keystream;
    }

    printf("\nEncrypted Ciphertext:\n");
    for(int i=0;i<n;i++)
        printf("%08d ",atoi("0")+ 
        ((ct[i]&128)?10000000:0) +
        ((ct[i]&64)?1000000:0) +
        ((ct[i]&32)?100000:0) +
        ((ct[i]&16)?10000:0) +
        ((ct[i]&8)?1000:0) +
        ((ct[i]&4)?100:0) +
        ((ct[i]&2)?10:0) +
        ((ct[i]&1)?1:0));

    printf("\n");

    for(int i=0;i<n;i++)
    {
        int counter=i;
        int keystream=encrypt(counter,k1,k2);
        dt[i]=ct[i]^keystream;
    }

    printf("\nDecrypted Plaintext:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=7;j>=0;j--)
            printf("%d",(dt[i]>>j)&1);
        printf(" ");
    }

    printf("\n\nProgram executed successfully.\n");

    return 0;
}
