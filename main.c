#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// -

#define MAXSTRLEN 200
#define MINHISTSTEP 1
#define ALPHLEN 33

void display_int(int arr[]) {
    for (int i = 0; i < 33; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void display_str(char* arr) {
    for (int i = 0; i < 33; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void copy(int arr1[], int arr2[]) {
    for (int i = 0; i < ALPHLEN; i++) {
        arr2[i] = arr1[i];
    }
}

void clear(char* str, int strlen) {
    for (int i = 0; i < strlen; i++) {
        str[i] = 0;
    }
}

void display_arr(int arr[], int sym_amt) {
    printf("Total amount of letters: %d\n", sym_amt);
    for (int i = 0; i < 32; i++) {
        printf("%d) %c - %d - %.3f\n", i, 'À'+i, arr[i], (float)arr[i]/(sym_amt));
    }
    printf("32) ¨ - %d - %.3f", arr[32], (float)arr[32]/(sym_amt));
}

void sort(int *arr, int size) {
    for (int d = size / 2; d > 0; d /= 2) {
        for (int i = d; i < size; i++) {
            for (int j = i - d; j >= 0 && arr[j] > arr[j + d]; j -= d) {
                int temp = arr[j];
                arr[j] = arr[j + d];
                arr[j + d] = temp;
            }
        }
    }
}

int max_n(int arr_sort[], int arr_ind[], int n) {
    int max_n = arr_sort[ALPHLEN - n];
    for (int i = 0; i < ALPHLEN; i++) {
        if (arr_ind[i] == max_n) {
            arr_ind[i] = 0;
            return i;
        }
    }
}

int str_set(char* str, char* set, int str_len) {
    int lenres = 0;
    for (int i = 0; i < str_len + 1; i++) {
        int flag = 1;
        for (int j = 0; j < lenres; j++) {
            if (str[i] == set[j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            set[lenres++] = str[i];
        }
    }

    return lenres;
}

void display_recomend(int freq_dict[], int alph_freq[], char* enc_str, int strlen) {

    int arr_sorted[ALPHLEN] = { 0 };
    copy(freq_dict, arr_sorted);
    sort(arr_sorted, ALPHLEN);
    int arr_ind[ALPHLEN] = { 0 };
    copy(freq_dict, arr_ind);

    int alph_arr_sorted[ALPHLEN] = { 0 };
    copy(alph_freq, alph_arr_sorted);
    sort(alph_arr_sorted, ALPHLEN);
    int alph_arr_ind[ALPHLEN] = { 0 };
    copy(alph_freq, alph_arr_ind);

    int positive_values = 0;
    for (int i = 0; i < ALPHLEN; i++) {
        if (freq_dict[i] != 0) {
            positive_values++;
        }
    }

    printf("Recomended changes: \n");
    for (int i = 1; i < positive_values; i++) {
        printf("%c - %c\n", 'À'+max_n(arr_sorted, arr_ind, i), 'à'+max_n(alph_arr_sorted, alph_arr_ind, i));
    }
}

int fill_dict(char* str, int freq_dict[]) {
    int sym_amt = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            continue;
        } else {
            if (str[i] == '¨') {
                freq_dict[ALPHLEN-1]++;
                sym_amt++;
                continue;
            } else {
                freq_dict[str[i] + 64]++;
                sym_amt++;
            }
        }
    }

    return sym_amt;
}

void show_encoded_string(char *str) {
    printf("Encrypted string: \n\n");
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
    printf("\n\n");
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); // alph À(64) > ÿ(-1)

    int freq_dict[ALPHLEN] = { 0 }; // À Á Â ... = i+64 (¨ = -88 = i=32)
    int alph_freq[ALPHLEN] = {31,13,25,15,21,32,9,14,30,11,23,24,\
                            22,29,33,20,26,27,28,19,3,10,6,12,\
                            8,5,2,17,16,4,7,18,1}; // alphabet letters frequency ranking
    int* history = (int*)malloc(MINHISTSTEP * sizeof(int));
    // char enc_str[MAXSTRLEN] = { 0 };

    // FILE* input_file = fopen("input.txt", "r");
    // if (input_file == NULL) {
    //     return 1;
    // }
    // fgets(enc_str, MAXSTRLEN, input_file);
    char enc_str[MAXSTRLEN] = "ÇÀÊÎÄÈÐÎÂÀÍÍÀßÑÒÐÎÊÀ";

    int sym_amt = fill_dict(enc_str, freq_dict);

    while (1) {
        show_encoded_string(enc_str);
        printf("Please, choose 1 option:\n\
        1. Frequency analysis\n\
        2. Group words by letters amount\n\
        3. Group words by uppercase letters left\n\
        4. Change letters in encrypted string\n\
        5. Revert action by id (show history)\n\
        'e'. Enter 'e' to exit the programm\n\
        >>> ");
        int user_option = getchar();
        fflush(stdin);
        switch (user_option) {
            case '1':
                //TODO freq analysis
                display_arr(freq_dict, sym_amt);
                printf("\n");
                display_recomend(freq_dict, alph_freq, enc_str, strlen(enc_str));
                break;
            case '2':
                //TODO words by letters_amt
                break;
            case '3':
                //TODO words by uppercase letters
                break;
            case '4':
                //TODO change letters 'À' - 'á'  
                break;
            case '5':
                //TODO revert action by id
                break;
            case 'e':
                printf("Shutting down...");
                return 0;
            default:
                printf("Error input detected!");
                break;
        }
    }
}