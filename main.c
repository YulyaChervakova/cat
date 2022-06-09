#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<regex.h>
#define S21_NULL ((void*)0)
typedef struct s_grep {
  int ePost[1024];
  int eNext[1024];
  int eP;
  int eN;
  int i;
  int v;
  int l;
  int c;
  int n;
  int f;
  int file[100];
  int template;
  int error;
} s21_flagGrep;
typedef struct s_coincidences {
  int strNumber[10000];
  int strMax;
  int strMin;
} s21_struct;
s21_flagGrep* s21_tab_null(s21_flagGrep* tab);
int s21_tab_No_Null(s21_flagGrep* tab);
s21_struct* s21_save_null(s21_struct* save );
s21_flagGrep* s21_flag_fillin(char** argv, int argc, s21_flagGrep* tab);
int s21_i (char c, char m, s21_flagGrep* tab);
int s21_coincidences(char** argv, s21_flagGrep* tab,FILE* file, s21_struct* save);
void s21_grep(char** argv, int argc, s21_flagGrep* tab);
int main(int argc, char *argv[]) {
    s21_flagGrep* tab = S21_NULL;
    tab = calloc(1, sizeof(s21_flagGrep));
    if (tab != S21_NULL && argc > 1) {
        s21_grep(argv, argc, tab);
    }
    free(tab);
return 0;
}
s21_flagGrep* s21_tab_null(s21_flagGrep* tab) {
    for (int i = 0; i < 100; i++) {
        tab->ePost[i] = 0;
        tab->file[i] = 1;
        tab->eNext[i] = 0;
    }

    tab->eP = 0;
    tab->eN = 0;
    tab->i = 0;
    tab->v = 0;
    tab->l = 0;
    tab->c = 0;
    tab->n = 0;
    tab->f = 0;
    tab->template = 0;
    tab->error = 0;
return tab;
}

int s21_tab_No_Null(s21_flagGrep* tab) {
int i = 0;
if ((tab->eN != 0 || tab->eP != 0 || tab->template != 0) && tab->f > 0 && tab->error == 0) {
    if (tab->i != 0 || tab->v != 0 || tab->l != 0 ||tab->c != 0 || tab->n != 0)
    i = 1;
}
return i;
}
s21_struct* s21_save_null(s21_struct* save ) {
    // for (int i = 0; i < 1000; i++){
    //     save->strNumber[i];
    // }
    save->strMax = 0;
    save->strMin = 0;
return save;
}

s21_flagGrep* s21_flag_fillin (char** argv, int argc, s21_flagGrep* tab) {
    size_t count = 0;
    int countArg = 0;
    for (int i = 1; i < argc; i++) {
        count = 0;
        countArg = 0;
        printf("i = = = %d, s =  = = %s\n", i, argv[i]);
            while (argv[i][count] && countArg != 2) {
                printf("Stroka = %s, argument i= %d count  =%ld \n", argv[i], i, count);
                if (argv[i][count] == '-' || countArg == 1) {
                    countArg = 1;
                    if (argv[i][count] == '-')
                    count++;
                    switch (argv[i][count]) {
                        case 'i':
                            tab->i = 1;
                            break;
                        case 'v':
                            tab->v = 1;
                            break;
                        case 'l':
                            tab->l = 1;
                            break;
                        case 'c':
                            tab->c = 1;
                            break;
                        case 'n':
                            tab->n = 1;
                            break;
                        case 'e':
                            if (count + 1 < strlen(argv[i])) {
                                tab->ePost[tab->eP] = i;
                                tab->eP = tab->eP +1;
                                countArg = 2;
                            } else {
                                if (i + 2 < argc || i + 1 < argc) {
                                    tab->eNext[tab->eN] = i+1;
                                    if (i+2 < argc) {
                                        tab->eNext[tab->eN] = i+1;
                                        i = i + 1;
                                    } else {
                                      i = i + 1;  
                                    }
                                    countArg =2;
                                    tab->eN = tab->eN + 1;
                                } else {
                                    tab->error = tab->error + 1;
                                }
                            }
                            break;
                        default:
                            tab->error = tab->error + 1;
                            break;
                    }
                } else {
                    
                    if (tab->eP == 0 && tab->eN == 0 && tab->template == 0) {
                        tab->template = i;
                    } else {
                        if ((tab->eP >= 1 || tab->eN >= 1 ) && tab->template != 0) {
                            tab->file[tab->f] = tab->template;
                            tab->f = tab->f + 1;
                            tab->template = 0;
                        } else {
                            tab->file[tab->f] = i;
                            tab->f = tab->f + 1;
                            countArg = 2;
                        }
                    }
                }
                count++;
            }
    }
printf(", tab->file[tab->f] = %d,  tab->f = = %d \n",  tab->file[tab->f], tab->f );
printf("Taberrror %d  ____\n",tab->error );
printf("f  ===%d\n", tab->f);
 //   printf("Taberrror %d",tab->error );
return tab;
}
int s21_i (char c, char m, s21_flagGrep* tab) {
    int flag = 0;
    if (tab->i == 1) {
        if (c > m) {
            if ( m+64 == c ) {
                flag = 1;
            }
        } else {
            if (c < m) {
                if(c+64 == m) {
                    flag = 1;
                }
            } else {
                flag = 1;
            }
        }
    } else {
        if (c == m ) {
            flag = 1;
        }
    }
return flag;
}
int s21_coincidences(char** argv, s21_flagGrep* tab, FILE* file, s21_struct* save) {
int flag = -1;
int number;
char* mas;
int i = 0;
// regex_t preg;
mas = calloc(1, sizeof(char));
            while ((number = fgetc(file))!= EOF) {
                if (number == '\n') {
                    save->strMax = save->strMax + 1;
                } else {
                    i = 0;
                    while ((number = fgetc(file))!= '\0') {
                        mas[i] = number;
                        i++;
                        mas = realloc(mas,(i+1)*sizeof(char));
                    }
                    if (tab->template > 0) {
                        //argv[tab->template];
                        // err = regcomp(&preg, argv[tab->template], REG_EXTENDED);
                        if (argv[tab->template] ==  0) {
                            
                        }
                    } else {
                        if ( tab->eP != 0 ) {
                            if ( tab->eN != 0 ) {
                            }
                        } else {
                            if ( tab->eN != 0 ) {
                            }
                        }
                    }
                }
            }

return flag;
}
//getline 
void s21_grep(char** argv, int argc, s21_flagGrep* tab) {
    s21_tab_null(tab);
    s21_flag_fillin(argv, argc, tab);
    for (int i = 0; i < tab->f; i++) {
       printf("i = = %d f =  %d\n", i, tab->file[i]);
    }
    s21_struct* save ; 
    // int numberStr = 0;
    // int next = 0;
    // int nextEmpty = 0;
    int number;
    save = calloc(1, sizeof(s21_struct));
    
    if (s21_tab_No_Null(tab)) {
        FILE *file;
        for (int i = 0; i < tab->f; i++) {
            if ((file = fopen(argv[tab->file[i]], "r")) != NULL) {
                // #if APPLE
                // numberStr = 1;
                // #endif  // APPLE
                s21_save_null(save);
                if (s21_coincidences(argv, tab, file, save)) {
                    fclose(file);
                    file = fopen(argv[tab->file[i]], "r");
                }
                fclose(file);
                while ((number = fgetc(file))!= EOF) {
                    }

                fclose(file);
            }
        }
    }
    free (save);
}
