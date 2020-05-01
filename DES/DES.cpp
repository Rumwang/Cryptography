#include <iostream>
using namespace std;

const char convert[16][5]{
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000",
    "1001", "1010","1011","1100","1101","1110","1111"
};

const int key_change_rule[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

const int pc_2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

const int ip[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17, 9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

const int ip_1[64] = {
    40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,33,1,41, 9,49,17,57,25
};

const int E[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

const int P[32] = {
    16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
};

const int S[8][64] = {
// box 1
    14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
// box 2
    15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
// box 3
    10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
// box 4
    7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
// box 5
    2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
// box 6
    12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
// box 7
    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
// box 8
    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
};

const int shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void *get_new_key(char *key, char *C_key, char *D_key){
    char new_key[57];
    for(int i = 0; i < 56; i++){
        int tmp = key_change_rule[i] - 1;
        new_key[i] = key[tmp];
    }
    for(int i = 0; i < 28; i++){
        C_key[i] = new_key[i];
        D_key[i] = new_key[i+28];
    }
}

char **create_keys(char *key){
    char C_key[29], D_key[29]; // length 28
    char **K = new char *[16];
    get_new_key(key, C_key, D_key); // initialize C_0, D_0
    cout << "af get_new_key" << endl;
    for(int i = 0; i < 16; i++){
        char tmp_C[29];
        char tmp_D[29];
        char tmp_total[57];
        char *res_key = new char[49];
        res_key[48] = '\0';
        for(int k = 0, j = shift[i]; j < 28; j++, k++){
            tmp_C[k] = C_key[j];
            tmp_D[k] = D_key[j];
        }
        for(int j = 28 - shift[i], k = 0; j < 28; j++, k++){
            tmp_C[j] = C_key[k];
            tmp_D[j] = D_key[k];
        }
        // C_key + D_key
        for(int j = 0; j < 28; j++){
            tmp_total[j] = tmp_C[j];
            C_key[j] = tmp_C[j];
        }
        for(int j = 28; j < 56; j++){
            tmp_total[j] = tmp_D[j-28];
            D_key[j-28] = tmp_D[j-28];
        }
        //
        for(int j = 0; j < 48; j++)
            res_key[j] = tmp_total[pc_2[j] - 1];
        K[i] = res_key;
    }
    return K;
}

char *E_transform(char *s){
    char *res = new char[49];
    res[48] = '\0';
    for(int i = 0; i < 48; i++)
        res[i] = s[E[i] - 1];
    return res;
}

char *Xor(char *a, char *b, int len){
    char *res = new char[len+1];
    res[len] = '\0';
    for(int i = 0; i < len; i++)
        if(a[i] == b[i])
            res[i] = '0';
        else
            res[i] = '1';
    return res;
}

int calc_bin(char *bin, int len){
    int res;
    if(len == 2)
        res = (int)(bin[0] - '0') * 2 + (bin[1] - '0');
    else
        res = (int)(bin[0] - '0') * 8 + (bin[1] - '0') * 4 + (bin[2] - '0') * 2 + (bin[3] - '0');
    return res;
}

char *S_transform(char *s){
    char *res = new char[33];
    res[32] = '\0';
    int pointer = 0, start = 0, end = 6;
    for(int i = 0; i < 8; i++){
        char row_char[3], column_char[5];
        row_char[0] = s[start];
        row_char[1] = s[end-1];
        for(int j = 0; j < 4; j++)
            column_char[j] = s[start+1+j];
        int row = calc_bin(row_char, 2);
        int column = calc_bin(column_char, 4);
        int get_num = S[i][row * 16 + column];
        for(int j = 0; j < 4; j++)
            res[pointer++] = convert[get_num][j];
        start += 6;
        end += 6;
    }
    return res;
}

char *P_transform(char *s){
    char *res = new char[33];
    res[32] = '\0';
    for(int i = 0; i < 32; i++)
        res[i] = s[P[i] - 1];
    return res;
}

char *ip1_calc(char *s){
    char *res = new char[65];
    res[64] = '\0';
    for(int i = 0; i < 64; i++)
        res[i] = s[ip_1[i] - 1];
    return res;
}

void en_decrypt(char **K, char *input, bool op){
    char after_ip[65];
    // IP
    for(int i = 0; i < 64; i++)
        after_ip[i] = input[ip[i] - 1];
    // get L0 and R0
    char tmp_L[33];
    char tmp_R[33];
    for(int i = 0; i < 32; i++){
        tmp_L[i] = after_ip[i];
        tmp_R[i] = after_ip[i+32];
    }
    //
    for(int i = 0; i < 16; i++){
        char *afterE_R = E_transform(tmp_R);
        char *after_xor = Xor(afterE_R, (op ? K[i] : K[15-i]), 48);
        char *after_s = S_transform(after_xor);
        char *after_P = P_transform(after_s);
        char *tmp = Xor(tmp_L, after_P, 32);
        char last_R[33];
        for(int j = 0; j < 32; j++)
            last_R[j] = tmp_R[j];
        for(int j = 0; j < 32; j++){
            tmp_R[j] = tmp[j];
            tmp_L[j] = last_R[j];
        }
    }
    // ip_(-1)
    char before_ip1_calc[65];
    for(int i = 0; i < 32; i ++)
        before_ip1_calc[i] = tmp_R[i];
    for(int i = 32; i < 64; i++)
        before_ip1_calc[i] = tmp_L[i-32];
    char *res = ip1_calc(before_ip1_calc);
    if(op)
        cout << "encrypt result:" << res << endl;
    else
        cout << "decrypt result:" << res << endl;
}

int main(){
    char key[65] = "0001001100110100010101110111100110011011101111001101111111110001";
    char input[65] = "0000000100100011010001010110011110001001101010111100110111101111";
    char ciphertext[65] = "1000010111101000000100110101010000001111000010101011010000000101";
    char **K = create_keys(key);
    cout << "key:" << key << endl;
    cout << "plaintext:" << input << endl;
    en_decrypt(K, input, true);
    en_decrypt(K, ciphertext, false);
    return 0;
}