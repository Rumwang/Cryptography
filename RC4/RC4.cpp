#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

uint8_t* convert(uint8_t s){
    const uint8_t map[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                            'b', 'c', 'd', 'e', 'f'};
    uint8_t *res = new uint8_t[2];
    res[0] = map[(s&0xf0) >> 4]; // high
    res[1] = map[(s&0xf)];
    return res;
}

void Swap(uint8_t *a, uint8_t *b){
    uint8_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void KSA(uint8_t *S, uint8_t *T){
    ofstream ofs;
    int j = 0;
    for(int i = 0; i < 256; i++){
        j = (j + S[i] + T[i]) % 256;
        Swap(&S[i], &S[j]);
    }
}

uint8_t *random_key(){
    uint8_t * key = new uint8_t[128]; // initial key 128 bytes
    srand((int)time(0));
    for(int i = 0; i < 128; i++)
        key[i] = rand() % 256;
    return key;
}

uint8_t *RC4(uint8_t *key){
    uint8_t S[256];
    uint8_t T[256];
    for(int r = 0; r < 256; r++){
        S[r] = r;
        T[r] = key[r%128];
    }
    KSA(S, T);
    //
    int len = 16 * 1024; // 16KB
    int i = 0, j = 0;
    uint8_t t;
    uint8_t *K = new uint8_t[len];
    for(int r = 0; r < len; r++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        Swap(&S[i], &S[j]);
        t = (S[i] + (S[j] % 256)) % 256;
        K[r] = S[t];
        printf("%d\n", r);
    }
    return K;
}

void file_w(uint8_t *K, int len, char* add){
    ofstream ofs;
    ofs.open(add, ios::out);
    for(int i = 0; i < len; i++){
        uint8_t *tmp = convert(K[i]);
        ofs << "0x" << tmp[0] << tmp[1] << "\n";
    }
    ofs.close();
}

int main(){
    uint8_t *key = random_key();
    file_w(key, 128, (char*)"initial_key.txt");
    uint8_t *K = RC4(key);
    file_w(K, 16*1024, (char*)"PRGA.txt");
    return 0;
}