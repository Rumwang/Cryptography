key_change_rule = [57,49,41,33,25,17,9,
                    1,58,50,42,34,26,18,
                    10,2,59,51,43,35,27,
                    19,11,3,60,52,44,36,
                    63,55,47,39,31,23,15,
                    7,62,54,46,38,30,22,
                    14,6,61,53,45,37,29,
                    21,13,5,28,20,12,4 ]

pc_2 = [14,17,11,24,1,5,
        3,28,15,6,21,10,
        23,19,12,4,26,8,
        16,7,27,20,13,2,
        41,52,31,37,47,55,
        30,40,51,45,33,48,
        44,49,39,56,34,53,
        46,42,50,36,29,32]

ip = [58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17, 9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7,]

ip_1 = [40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,33,1,41, 9,49,17,57,25,]

E = [32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1]

P = [16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25,]

S = [[
14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
],
[15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
],
[10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
],
[7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
],
[2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
],
[12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
],
[4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
],
[13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11,
]
]


def calc_bin(binary):
    res = 0
    if len(binary) == 2:
        res = int(binary[0])*2 + int(binary[1])
    else:
        res = int(binary[0])*8 + int(binary[1])*4 + int(binary[2])*2 + int(binary[3])
    return res


def E_transform(s):
    res = ''
    for i in range(len(E)):
        res += s[E[i] - 1]
    return res


def S_transform(s):
    res = ''  # length 32
    start = 0
    end = 6
    for i in range(8):  # 6 -> 4 total 48 -> 32
        tmp = s[start:end]  # length 6
        row = calc_bin(tmp[0] + tmp[5])  # find S box's row
        column = calc_bin(tmp[1:5])  # find S box's column
        res += '{:04b}'.format(S[i][row * 16 + column])  # decimal to binary and add the result to 'res'
        start += 6
        end += 6
    return res


def P_transform(s):
    res = ''
    for i in range(len(P)):
        res += s[P[i] - 1]
    return res


def xor(a, b):
    res = ''
    for i in range(len(a)):
        if a[i] == b[i]:
            res += '0'
        else:
            res += '1'
    return res


def ip1_calc(s):
    res = ''
    for i in range(len(ip_1)):
        res += s[ip_1[i] - 1]
    return res


def create_keys(key):
    C = []
    D = []
    K = []  # 16
    new_key = ''  # length 56
    shift = [1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1]
    for i in range(len(key_change_rule)):
        new_key += key[key_change_rule[i] - 1]
    C_key = new_key[0:28]  # length 28
    D_key = new_key[28:56]  # length 28
    for i in range(len(shift)):
        C_key = C_key[shift[i]:28] + C_key[0:shift[i]]
        D_key = D_key[shift[i]:28] + D_key[0:shift[i]]
        C.append(C_key)
        D.append(D_key)
    for i in range(16):
        tmp = C[i] + D[i]
        get_key = ''
        for j in range(len(pc_2)):
            get_key += tmp[pc_2[j] - 1]
        K.append(get_key)
    return K


def en_decrypt(input_text, op):  # op == 1 -> encrypt || op == 0 -> decrypt
    after_ip = ''  # length 64
    #  IP
    for i in range(len(ip)):
        after_ip += input_text[ip[i] - 1]
    #  get L0 and R0
    L0 = after_ip[0:32]
    R0 = after_ip[32:64]

    #  calculate L16 and R16
    L = []
    R = []
    L.append(L0)
    R.append(R0)
    for i in range(16):
        tmp_R = E_transform(R[i])  # length 32 -> 48
        after_xor = xor(tmp_R, K[i]) if op == 1 else xor(tmp_R, K[15-i])
        after_x = S_transform(after_xor)  # length 32
        after_p = P_transform(after_x)
        R.append(xor(L[i], after_p))  # calc next R
        L.append(R[i])  # calc next L
    #  ip_-1
    res = ip1_calc(R[16]+L[16])
    if op == 1:
        print('encrypt result: ' + res)
    else:
        print('decrypt result: ' + res)


if __name__ == '__main__':
    K = create_keys('0001001100110100010101110111100110011011101111001101111111110001')
    print('key: ' + '0001001100110100010101110111100110011011101111001101111111110001')
    # input 0123456789ABCDEF, encrypt ans:85E813540F0AB405
    print('input_text :0000000100100011010001010110011110001001101010111100110111101111')
    en_decrypt('0000000100100011010001010110011110001001101010111100110111101111', 1)
    en_decrypt('1000010111101000000100110101010000001111000010101011010000000101', 0)
