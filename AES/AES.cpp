#include <iostream>
using namespace std;

const uint8_t rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

const uint8_t shift[16] = {
    0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11
};

const uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

uint8_t *w_a(uint8_t *s){
    uint8_t *res = new uint8_t[5];
    for(int i = 0; i < 3; i++)
        res[i] = s[i+1];
    res[3] = s[0];
    return res;
}

uint8_t *w_b(uint8_t *s){
    uint8_t *res = new uint8_t[5];
    for(int i = 0; i < 4; i++){
        // printf("--------->%x\n", s[i]);
        uint8_t row = (s[i] & 0xf0) >> 4; // high 4
        // printf("--------->%x\n", row);
        uint8_t column = (s[i] & 0x0f); // low 4
        // printf("--------->%x\n", column);
        uint8_t index = row * 16 + column;
        res[i] = sbox[index];
    }
    return res;
}

uint8_t *w_c(uint8_t *s, uint8_t round){
    uint8_t *res = new uint8_t[5];
    res[0] = s[0] ^ rcon[round];
    for(int i = 1; i < 4; i++)
        res[i] = s[i];
    return res;
}

uint8_t **create_key(uint8_t *key){
    uint8_t **W = new uint8_t *[44];
    // initialize W_0, W_1, W_2, W_3
    for(int i = 0; i < 4; i++){
        W[i] = new uint8_t[5];
        for(int j = 0; j < 4; j++)
            W[i][j] = key[i*4+j];
    }
    // initialize W_4  ----  K_43
    uint8_t round = 1;
    for(int i = 4; i < 44; i++){
        W[i] = new uint8_t[5];
        if(i % 4 == 0){
            uint8_t *after_w_a = w_a(W[i-1]);
            // printf("--->%x %x %x %x\n", after_w_a[0], after_w_a[1], after_w_a[2], after_w_a[3]);
            uint8_t *after_w_b = w_b(after_w_a);
            // printf("--->%x %x %x %x\n", after_w_b[0], after_w_b[1], after_w_b[2], after_w_b[3]);
            uint8_t *after_w_c = w_c(after_w_b, round);
            // printf("--->%x %x %x %x\n", after_w_c[0], after_w_c[1], after_w_c[2], after_w_c[3]);
            for(int j = 0; j < 4; j++)
                W[i][j] = (after_w_c[j] ^ W[i-4][j]);
            round += 1;
        }
        else
            for(int j = 0; j < 4; j++){
                W[i][j] = W[i-4][j] ^ W[i-1][j];
            }
    }
    // for(int i = 0; i < 44; i++)
    //     printf("%x %x %x %x\n", W[i][0],W[i][1],W[i][2],W[i][3]);
    return W;
}

uint8_t *sbox_replace(uint8_t *s){
    uint8_t *res = new uint8_t[16];
    for(int i = 0; i < 16; i++){
        uint8_t row = (s[i] & 0xf0) >> 4; // high 4
        uint8_t column = (s[i] & 0x0f); // low 4
        uint8_t index = row * 16 + column;
        res[i] = sbox[index];
    }
    return res;
}

uint8_t *shift_op(uint8_t *s){
    uint8_t *res = new uint8_t[16];
    for(int i = 0; i < 16; i++)
        res[i] = s[shift[i]];
    return res;
}

uint8_t *confusion(uint8_t *s){
    uint8_t *res = new uint8_t[16];
    for(int i = 0; i < 4; i++){
        res[i*4] = (s[i*4]<0x80 ? s[i*4]<<1 : (s[i*4]<<1)^0x1b) ^ ((s[i*4+1]<0x80?s[i*4+1]<<1 : (s[i*4+1]<<1^0x1b)) ^s[i*4+1]) ^ s[i*4+2] ^ s[i*4+3];
        res[i*4+1] = s[i*4] ^ (s[i*4+1]<0x80 ? s[i*4+1]<<1 : (s[i*4+1]<<1)^0x1b) ^ ((s[i*4+2]<0x80?s[i*4+2]<<1 : (s[i*4+2]<<1^0x1b)) ^s[i*4+2]) ^ s[i*4+3];
        res[i*4+2] = s[i*4] ^ s[i*4+1] ^ (s[i*4+2]<0x80 ? s[i*4+2]<<1 : (s[i*4+2]<<1)^0x1b) ^ ((s[i*4+3]<0x80?s[i*4+3]<<1 : (s[i*4+3]<<1^0x1b)) ^s[i*4+3]);
        res[i*4+3] = ((s[i*4]<0x80?s[i*4]<<1 : (s[i*4]<<1^0x1b)) ^s[i*4]) ^ s[i*4+1] ^ s[i*4+2] ^ (s[i*4+3]<0x80 ? s[i*4+3]<<1 : (s[i*4+3]<<1)^0x1b);
    }
    return res;
}

uint8_t *merge_key(uint8_t **W, uint8_t round){
    uint8_t *res = new uint8_t[16];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            res[i*4+j] = W[round*4+i][j];
    return res;
}

uint8_t *add_round_key(uint8_t *s, uint8_t *k){
    uint8_t *res = new uint8_t[16];
    for(int i = 0; i < 16; i++)
        res[i] = s[i] ^ k[i];
    return res;
}

uint8_t *encrypt(uint8_t *plaintext, uint8_t **W){
    uint8_t *res = new uint8_t[16];
    // round_0
    uint8_t **S = new uint8_t*[11];
    uint8_t **K = new uint8_t*[11];
    // for(int i = 0; i < 11; i++)
    S[0] = new uint8_t[16];
    K[0] = merge_key(W, 0);
    for(int i = 0; i < 16; i++)
        S[0][i] = plaintext[i] ^ K[0][i];

    
    // round_1 --> round_10
    for(int i = 1; i < 11; i++){
        K[i] = merge_key(W, i);
        uint8_t *after_replace = sbox_replace(S[i-1]);
        uint8_t *after_shift = shift_op(after_replace);
        if(i != 10){
            uint8_t *after_confuse = confusion(after_shift);
            uint8_t *after_add_key = add_round_key(after_confuse, K[i]);
            S[i] = after_add_key;
        }
        else{
            res = add_round_key(after_shift, K[i]);
        }
    }
    for(int i = 0; i < 16; i++)
        printf("%x ", res[i]);
    printf("\n");
    return res;
}

int main(){
    uint8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t plaintext[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30,0x8d,
                            0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t **W = create_key(key);
    uint8_t *ciphertext = encrypt(plaintext, W);
    return 0;
}