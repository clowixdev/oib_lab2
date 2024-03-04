#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

// -

#define MAXSTRLEN 200
#define HISTLEN 33
#define ALPHLEN 33

void display_int(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void display_str(char* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", arr[i]);
    }
    printf(" ");
}

void copy(int arr1[], int arr2[]) {
    for (int i = 0; i < ALPHLEN; i++) {
        arr2[i] = arr1[i];
    }
}

void clear(char* str, int strlen) {
    for (int i = 0; i < strlen; i++) {
        str[i] = '\0';
    }
}

void display_arr(int arr[], int sym_amt) {
    printf("Total amount of letters: %d\n", sym_amt);
    for (int i = 0; i < 32; i++) {
        if (arr[i] != 0) {
            printf("%d) %c - %d - %.3f\n", i, '¿'+i, arr[i], (float)arr[i]/(sym_amt));
        }
    }
    if (arr[32] != 0) {
        printf("32) ® - %d - %.3f", arr[32], (float)arr[32]/(sym_amt));
    }
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

    printf("Recomended changes: ");
    int set_upper[ALPHLEN] = { 0 };
    int set_lower[ALPHLEN] = { 0 };

    for (int i = 0; enc_str[i] != '\0'; i++) {
        if ((enc_str[i] >= -64 && enc_str[i] <= -32) && enc_str[i] != ' ') { //is_uppercase
            set_upper[enc_str[i] + 64]++;
        } else if (enc_str[i] == -88) { //is_upper_YO
            set_upper[32]++;
        } else if ((enc_str[i] >= -31 && enc_str[i] <= -1) && enc_str[i] != ' ') { //is_lowercase
            set_lower[enc_str[i] + 32]++;
        } else if (enc_str[i] == -72) { //is_lower_yo
            set_lower[32]++;
        }
    }

    for(int i = 0; i < 33; i++) {
        if (set_lower[i] == 0) {
            set_lower[i] = alph_freq[i];
        } else {
            set_lower[i] = 0;
        }
    }

    int arr_sorted[ALPHLEN] = { 0 };
    copy(set_upper, arr_sorted);
    sort(arr_sorted, ALPHLEN);
    int arr_ind[ALPHLEN] = { 0 };
    copy(set_upper, arr_ind);

    int alph_arr_sorted[ALPHLEN] = { 0 };
    copy(set_lower, alph_arr_sorted);
    sort(alph_arr_sorted, ALPHLEN);
    int alph_arr_ind[ALPHLEN] = { 0 };
    copy(set_lower, alph_arr_ind);

    int encrypted_amt = 0;
    for (int i = 0; i < ALPHLEN; i++) {
        if (set_upper[i] != 0) {
            encrypted_amt++;
        }
    }

    printf("Recomended changes: \n");
    for (int i = 1; i < encrypted_amt; i++) {
        printf("%c - %c\n", '¿'+max_n(arr_sorted, arr_ind, i), '‡'+max_n(alph_arr_sorted, alph_arr_ind, i));
    }
}

int fill_dict(char* str, int freq_dict[]) {
    int symbols = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n') {
            continue;
        } else {
            if (str[i] == '®') {
                freq_dict[ALPHLEN-1]++;
                symbols++;
                continue;
            } else {
                freq_dict[str[i] + 64]++;
                symbols++;
            }
        }
    }

    return symbols;
}

void show_encoded_string(char *str) {
    printf("Encrypted string: \n\n");
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
    printf("\n\n");
}

//  Ÿ–Õ—…ÿŸ’ƒ“ –¡”“÷œ‘ﬁ—Õ€ ÿ… ‹…À¡ Õ—…—“Õ—“Œ¡ÕƒŸÃŸ …ÿ…∆“À… —¡ƒÕ—… ÿŸ —Ÿ∆≈ƒŸ ¡Õ∆“ Ÿÿ –ŸÕ—…—ŸŒÿŸ –∆“ÿÿ»√
int count_words(char* str) {
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            count++;
        }
    }
    count++; //last word
    return count;
}

int def_max_len(char* str) {
    int curr_len = 0;
    int max_len = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            curr_len++;
        } else {
            max_len = (curr_len > max_len) ? curr_len : max_len;
            curr_len = 0;
        }
    }

    return max_len;
}

void get_n_word(char* str, int n, char* word) {
    int count_whitespace = 0;
    int j = 0;
    for(int i = 0; count_whitespace != n; i++) {
        if (str[i] == ' ') {
            count_whitespace++;
            i++;
        }
        if (count_whitespace == n-1) {
            word[j++] = str[i];
        }
    }
    word[j] = '\0';
}

int upper_amt(char* str) {
    int amt = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        if (((str[i] >= -64 && str[i] <= -32) || str[i] == -88) && str[i] != ' ') {
            amt++;
        }
    }

    return amt;
}

int change_letter(char* enc_str, char enc_letter, char dec_letter) {
    for (int i = 0; enc_str[i] != 0; i++) {
        if (enc_str[i] == enc_letter) {
            enc_str[i] = dec_letter;
        }
    }

    return 0;
}

void history_add(int history[], char enc_letter, char dec_letter) {
    int action = 0;
    int enc_code = -1 * (int)enc_letter;
    int dec_code = -1 * (int)dec_letter;
    action = enc_code * 100 + dec_code;

    int i;
    for(i = 0; i < HISTLEN; i++) {
        if (history[i] == 0) {
            break;
        }
    }
    history[i] = action;
}

void show_history(int history[]) {
    printf("History: \n");
    for (int i = 0; history[i] != 0; i++) {
        printf("%d) %c -> %c\n", i, -1 * (history[i]/100), -1 * (history[i]%100));
    }
}

void history_del(int history[], int action_id) {
    int i;
    if (action_id == 32) {
        history[32] = 0;
        return;
    }
    history[action_id] = 0;
    for(i = action_id; history[i+1] != 0; i++) {
        history[i] = history[i+1];
    }
    history[i] = 0;
}

void wait_accept() {
    printf("\ntype anything to continue >>> ");
    getchar();
    fflush(stdin);
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); // alph ¿(-64) > ˇ(-1)

    int freq_dict[ALPHLEN] = { 0 }; // ¿ ¡ ¬ ... = i+64 (® = -88 = i=32, ∏ = -72)
    int alph_freq[ALPHLEN] = {31,13,25,15,21,32,9,14,30,11,23,24,\
                            22,29,33,20,26,27,28,19,3,10,6,12,\
                            8,5,2,17,16,4,7,18,1}; // alphabet letters frequency ranking
    int history[HISTLEN] = { 0 };
    // char enc_str[MAXSTRLEN] = { 0 };

    // FILE* input_file = fopen("input.txt", "r");
    // if (input_file == NULL) {
    //     return 1;
    // }
    // fgets(enc_str, MAXSTRLEN, input_file);
    char enc_str[MAXSTRLEN] = "œ≈–¬€… ¬“Œ–Œ… “–≈“»… ◊≈“¬≈–“€… œﬂ“€… ÿ≈—“Œ…\0";

    int sym_amt = fill_dict(enc_str, freq_dict);

    int words_amt = count_words(enc_str);
    int max_word_len = def_max_len(enc_str) + 1;

    char **words = (char**) malloc(words_amt * max_word_len * sizeof(char));
    for (int i = 0; i < words_amt; i++) {
        char *word = (char*) malloc(sizeof(char) * max_word_len);
        clear(word, max_word_len);
        get_n_word(enc_str, i+1, word);
        words[i] = word;
    }

    while (1) {
        printf("\n");
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
                printf("What do you want to see: \n\t1.Frequency dictionary\n\t2.Recomended changed\n\t>>> ");
                char user_input = getchar();
                fflush(stdin);

                switch (user_input) {
                    case '1':
                        display_arr(freq_dict, sym_amt);
                        break;
                    case '2':
                        display_recomend(freq_dict, alph_freq, enc_str, strlen(enc_str));
                        break;
                    default:
                        printf("Incorrect option");
                        break;
                }
                wait_accept();
                break;
            case '2':
                //TODO words by letters_amt

                bool is_printed_len = false;

                printf("Words with len");
                for (int i = max_word_len; i != 1; i--) {
                    for (int j = 0; j != words_amt; j++) {
                        if (strlen(words[j]) != i) {
                            continue;
                        } else {
                            if (is_printed_len == false) {
                                if (i != max_word_len) {
                                    printf("\n");
                                }
                                printf("\t%d symbols: ", i);
                                is_printed_len = true;
                            }
                            printf("%s ", words[j]);
                        }
                    }
                    is_printed_len = false;
                }
                wait_accept();
                break;
            case '3':
                //TODO words by uppercase letters

                bool is_printed_upper = false;

                for (int i = 0; i < words_amt; i++) {
                    get_n_word(enc_str, i+1, words[i]);
                }

                printf("Words with encoded letters:");
                for (int i = max_word_len; i != 1; i--) {
                    for (int j = 0; j < words_amt; j++) {
                        if (upper_amt(words[j]) != i) {
                            continue;
                        } else {
                            if (is_printed_upper == false) {
                                if (i != max_word_len) {
                                    printf("\n");
                                }
                                printf("\t%d symbols: ", i);
                                is_printed_upper = true;
                            }
                            printf("%s ", words[j]);
                        }
                    }
                    is_printed_upper = false;
                }
                wait_accept();
                break;
            case '4':
                //TODO change letters 'A' - 'o'
                printf("Encrypted letter >>> ");
                char enc_letter = getchar();
                fflush(stdin);

                printf("Decrypted letter >>> ");
                char dec_letter = getchar();
                fflush(stdin);

                if (change_letter(enc_str, enc_letter, dec_letter) == -1) {
                    printf("Wrong encrypted/decrypted letter!");
                } else {
                    for (int i = 0; i < words_amt; i++) {
                        get_n_word(enc_str, i+1, words[i]);
                    }
                    history_add(history, enc_letter, dec_letter);
                }

                break;
            case '5':
                //TODO revert action by id
                show_history(history);
                if (history[0] == 0) {
                    printf("Empty :(");
                    break;
                }

                printf("What action you want to revert? (enter \"id)\" or \"b\" to back) >>> ");
                int action_id = getchar() - '0';
                fflush(stdin);

                if (action_id == 'b' - '0') { //! b == 98
                    break;
                }

                change_letter(enc_str, (char)(-1 * (history[action_id]%100)), (char)(-1 * (history[action_id]/100)));
                history_del(history, action_id);

                for (int i = 0; i < words_amt; i++) {
                    get_n_word(enc_str, i+1, words[i]);
                }

                wait_accept();
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