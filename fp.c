#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void reverse(char arr[], int len){
    char temp[len];
    for(int i = 0; i < len; i++){
        temp[len - 1 - i] = arr[i];
    }
    for(int i = 0; i < len; i++){
        arr[i] = temp[i];
    }
}

int main(){
    
    printf("Enter operation: ");
    char soal[500];
    scanf("%[^\n]", soal);
    int len = strlen(soal);

    // remove spacing
    for(int i = 0; i < len; i++){
        if(soal[i] == ' '){
            for(int j = i; j < len; j++){
                soal[j] = soal[j+1];
            }
            len -= 1;
        }
    }

    // Expression Validator
    // checking if there is invalid component
    char all[] = "0123456789+-/*^()";
    int status;
    for(int i = 0; i < len; i++){
        for(int j = 0; j < strlen(all); j++){
            if(soal[i] == all[j]){
                status = 1;
                break;
            } else{
                status = 0;
            }
        }
        if(status == 0){
            printf("INVALID COMPONENT\n");
            return 0;
        }
    }
    // checking if there is invalid expression
    for(int i = 0; i < len; i++){
        if((soal[i] == '+') || (soal[i] == '-') || (soal[i] == '*') || (soal[i] == '/') || (soal[i] == '^')){
            if((soal[i+1] == '+') || (soal[i+1] == '-') || (soal[i+1] == '*') || (soal[i+1] == '/') || (soal[i+1] == '^')){
                printf("INVALID EXPRESSION\n");
                return 0;
            }
        } else if(soal[i] == '('){
            if((soal[i+1] == '+') || (soal[i+1] == '-') || (soal[i+1] == '*') || (soal[i+1] == '/') || (soal[i+1] == '^') || (soal[i+1] == ')')){
                printf("INVALID EXPRESSION\n");
                return 0;
            }
        } else if(soal[i] == ')'){
            if((soal[i+1] == '(') || ((soal[i+1] >= '0') && (soal[i+1] <= '9'))){
                printf("INVALID EXPRESSION\n");
                return 0;
            }

        }
    }

    // Declaration
    char operand_1[500];
    char operand_2[500];
    int idx_operand_1 = 0;
    int idx_operand_2 = 0;
    int int_operand_1, int_operand_2, int_result;
    char str_result[500];
    int i, j, k;
    int idx_bracket_1, idx_bracket_2, idx_operator_in_bracket, bracket_existence;
    int barrier_operand_1, barrier_operand_2;

    // bracket operation
    while(1){
        // reset
        memset(operand_1, 0, 500);
        memset(operand_2, 0, 500);
        memset(str_result, 0, 500);
        idx_operand_1 = 0;
        idx_operand_2 = 0;
        int_operand_1 = 0;
        int_operand_2 = 0;
        int_result = 0;
        idx_bracket_1 = 0;
        idx_bracket_2 = 0;
        idx_operator_in_bracket = 0;
        bracket_existence = 0;


        // find bracket location and operator inside
        for(i = 0; i < len; i++){
            if(soal[i] == '('){
                idx_bracket_1 = i;
            }
            if(soal[i] == ')'){
                idx_bracket_2 = i;
                bracket_existence = 1;
                break;
            }
        }
        if(bracket_existence == 0){
            break;
        }

        // pow operation
        for(i = idx_bracket_2-1; i > idx_bracket_1; i--){
            if(soal[i] == '^'){
                // reset
                memset(operand_1, 0, 500);
                memset(operand_2, 0, 500);
                memset(str_result, 0, 500);
                idx_operand_1 = 0;
                idx_operand_2 = 0;
                int_operand_1 = 0;
                int_operand_2 = 0;
                int_result = 0;
                barrier_operand_1 = 0;
                barrier_operand_2 = 0;

                // grab operand before operator
                for(j = i-1; j > idx_bracket_1; j--){
                    if((soal[j] == '+') || (soal[j] == '-') || (soal[j] == '*') || (soal[j] == '/') || (soal[j] == '^')){
                        break;
                    }
                    operand_1[idx_operand_1] = soal[j];
                    idx_operand_1++;
                    barrier_operand_1 = j;
                }
                reverse(operand_1, strlen(operand_1));
                int_operand_1 = atoi(operand_1);

                // grab operand after operator
                for(j = i+1; j < idx_bracket_2; j++){
                    if((soal[j] == '+') || (soal[j] == '-') || (soal[j] == '*') || (soal[j] == '/')){
                        break;
                    }
                    operand_2[idx_operand_2] = soal[j];
                    idx_operand_2++;
                    barrier_operand_2 = j;
                }
                int_operand_2 = atoi(operand_2);
                
                // operation
                int_result = pow(int_operand_1, int_operand_2);
                sprintf(str_result, "%d", int_result);
                
                // insert result
                len = len + strlen(str_result);
                for(j = len-1; j >= barrier_operand_1 + strlen(str_result); j--){
                    soal[j] = soal[j - strlen(str_result)];
                }
                int idx_str_result = 0;
                for(j = barrier_operand_1; j < barrier_operand_1 + strlen(str_result); j++){
                    soal[j] = str_result[idx_str_result];
                    idx_str_result++;
                }
            
                // remove finished operation
                idx_bracket_2 += strlen(str_result);
                barrier_operand_2 += strlen(str_result);
                barrier_operand_1 += strlen(str_result);
                for(j = barrier_operand_1; j < len; j++){
                    if(j <= barrier_operand_2){
                        for(k = j; k < len; k++){
                            soal[k] = soal[k+1];
                        }
                        len--;
                        barrier_operand_2--;
                        idx_bracket_2--;
                        j--;
                    } else{
                        break;
                    }
                }

                //
                i = idx_bracket_2-1;
            }
        }

        // mult div
        for(i = idx_bracket_1 + 1; i < idx_bracket_2; i++){
            if((soal[i] == '*') || (soal[i] == '/')){
                // reset    
                memset(operand_1, 0, 500);
                memset(operand_2, 0, 500);
                memset(str_result, 0, 500);
                idx_operand_1 = 0;
                idx_operand_2 = 0;
                int_operand_1 = 0;
                int_operand_2 = 0;
                int_result = 0;
                barrier_operand_1 = 0;
                barrier_operand_2 = 0;

                // grab operand before operator
                for(j = i-1; j > idx_bracket_1; j--){
                    if((soal[j] == '+') || (soal[j] == '-')){
                    break;
                    }
                    operand_1[idx_operand_1] = soal[j];
                    idx_operand_1++;
                    barrier_operand_1 = j;
                }
                reverse(operand_1, strlen(operand_1));
                int_operand_1 = atoi(operand_1);
            
                // grab operand after operator
                for(j = i+1; j < idx_bracket_2; j++){
                    if((soal[j] == '+') || (soal[j] == '-') || (soal[j] == '*') || (soal[j] == '/')){
                    break;
                    }
                    operand_2[idx_operand_2] = soal[j];
                    idx_operand_2++;
                    barrier_operand_2 = j;
                }
                int_operand_2 = atoi(operand_2);
           
                // operation
                switch(soal[i]){
                    case '*':
                        int_result = int_operand_1 * int_operand_2;
                        break;
                    case '/':
                        int_result = int_operand_1 / int_operand_2;
                        break;
                }
                sprintf(str_result, "%d", int_result);    
            
                // insert result
                len = len + strlen(str_result);
                for(j = len-1; j >= barrier_operand_1 + strlen(str_result); j--){
                soal[j] = soal[j - strlen(str_result)];
                }
                int idx_str_result = 0;
                for(j = barrier_operand_1; j < barrier_operand_1 + strlen(str_result); j++){
                    soal[j] = str_result[idx_str_result];
                    idx_str_result++;
                }     

                // remove finished operation
                idx_bracket_2 += strlen(str_result);
                barrier_operand_2 += strlen(str_result);
                barrier_operand_1 += strlen(str_result);
                for(j = barrier_operand_1; j < len; j++){
                    if(j <= barrier_operand_2){
                        for(k = j; k < len; k++){
                            soal[k] = soal[k+1];
                        }
                        len--;
                        barrier_operand_2--;
                        idx_bracket_2--;
                        j--;
                    } else{
                        break;
                    }
                }
     
                //
                i = idx_bracket_1 + 1;
            }
        }

        // add / minus operation
        for(i = idx_bracket_1 + 1; i < idx_bracket_2; i++){
            if((soal[i] == '+') || (soal[i] == '-')){
                // reset
                memset(operand_1, 0, 500);
                memset(operand_2, 0, 500);
                memset(str_result, 0, 500);
                idx_operand_1 = 0;
                idx_operand_2 = 0;
                int_operand_1 = 0;
                int_operand_2 = 0;
                int_result = 0;
                barrier_operand_1 = 0;
                barrier_operand_2 = 0;

                // grab operand before operator
                for(j = i-1; j > idx_bracket_1; j--){
                    operand_1[idx_operand_1] = soal[j];
                    idx_operand_1++;
                    barrier_operand_1 = j;
                }
                reverse(operand_1, strlen(operand_1));
                int_operand_1 = atoi(operand_1);
            
                // grab operand after operator
                for(j = i+1; j < idx_bracket_2; j++){
                    if((soal[j] == '+') || (soal[j] == '-')){
                    break;
                    }
                    operand_2[idx_operand_2] = soal[j];
                    idx_operand_2++;
                    barrier_operand_2 = j;
                }
                int_operand_2 = atoi(operand_2);
            
                // operation
                switch(soal[i]){
                    case '+':
                        int_result = int_operand_1 + int_operand_2;
                        break;
                    case '-':
                        int_result = int_operand_1 - int_operand_2;
                        break;
                }
                sprintf(str_result, "%d", int_result);
            
                // insert result
                len = len + strlen(str_result);
                for(j = len-1; j >= barrier_operand_1 + strlen(str_result); j--){
                soal[j] = soal[j - strlen(str_result)];
                }
                int idx_str_result = 0;
                for(j = barrier_operand_1; j < barrier_operand_1 + strlen(str_result); j++){
                    soal[j] = str_result[idx_str_result];
                    idx_str_result++;
                }

                // remove finished operation
                idx_bracket_2 += strlen(str_result);
                barrier_operand_2 += strlen(str_result);
                barrier_operand_1 += strlen(str_result);
                for(j = barrier_operand_1; j < len; j++){
                    if(j <= barrier_operand_2){
                        for(k = j; k < len; k++){
                            soal[k] = soal[k+1];
                        }
                        len--;
                        barrier_operand_2--;
                        idx_bracket_2--;
                        j--;
                    } else{
                        break;
                    }
                }

                //
                i = idx_bracket_1 + 1;
            }
        }

        // deleting the brackets
        for(i = 0; i < len; i++){
            if((i == idx_bracket_1) || (i == idx_bracket_2)){
                for(j = i; j < len; j++){
                    soal[j] = soal[j + 1];
                }
                len--;
                idx_bracket_2--;
            }
        }   
    }

    // pow operation
    for(i = len-1; i >= 0; i--){
        if(soal[i] == '^'){
            // reset
            memset(operand_1, 0, 500);
            memset(operand_2, 0, 500);
            memset(str_result, 0, 500);
            idx_operand_1 = 0;
            idx_operand_2 = 0;
            int_operand_1 = 0;
            int_operand_2 = 0;
            int_result = 0;
            barrier_operand_1 = 0;
            barrier_operand_2 = 0;

            // grab operand before operator
            for(j = i-1; j >=0; j--){
                if((soal[j] == '+') || (soal[j] == '-') || (soal[j] == '*') || (soal[j] == '/') || (soal[j] == '^')){
                    break;
                }
                operand_1[idx_operand_1] = soal[j];
                idx_operand_1++;
                barrier_operand_1 = j;
            }
            reverse(operand_1, strlen(operand_1));
            int_operand_1 = atoi(operand_1);

            // grab operand after operator
            for(j = i+1; j < len; j++){
                if((soal[j] == '+') || (soal[j] == '-') || (soal[j] == '*') || (soal[j] == '/')){
                    break;
                }
                operand_2[idx_operand_2] = soal[j];
                idx_operand_2++;
                barrier_operand_2 = j;
            }
            int_operand_2 = atoi(operand_2);

            // operation
            int_result = pow(int_operand_1, int_operand_2);
            sprintf(str_result, "%d", int_result);

            // insert result
            len = len + strlen(str_result);
            for(j = len-1; j >= barrier_operand_1 + strlen(str_result); j--){
                soal[j] = soal[j - strlen(str_result)];
            }
            int idx_str_result = 0;
            for(j = barrier_operand_1; j < barrier_operand_1 + strlen(str_result); j++){
                soal[j] = str_result[idx_str_result];
                idx_str_result++;
            }

            // remove finished operation
            barrier_operand_2 += strlen(str_result);
            barrier_operand_1 += strlen(str_result);
            for(j = barrier_operand_1; j < len; j++){
                if(j <= barrier_operand_2){
                    for(k = j; k < len; k++){
                        soal[k] = soal[k+1];
                    }
                    len--;
                    barrier_operand_2--;
                    j--;
                } else{
                    break;
                }
            }

            //
            i = len-1;
        }
    }

    // mult / div operation
    for(i = 0; i < len; i++){
        if((soal[i]) == '*' || (soal[i]) == '/'){
            // reset
            memset(operand_1, 0, 500);
            memset(operand_2, 0, 500);
            memset(str_result, 0, 500);
            idx_operand_1 = 0;
            idx_operand_2 = 0;
            int_operand_1 = 0;
            int_operand_2 = 0;
            int_result = 0;
            barrier_operand_1 = 0;
            barrier_operand_2 = 0;

            // grab operand before operator
            for(j = i-1; j >=0; j--){
                if((soal[j] == '+') || (soal[j] == '-')){
                    break;
                }
                operand_1[idx_operand_1] = soal[j];
                idx_operand_1++;
                barrier_operand_1 = j;
            }
            reverse(operand_1, strlen(operand_1));
            int_operand_1 = atoi(operand_1);

            // grab operand after operator
            for(j = i+1; j < len; j++){
                if((soal[j] == '+') || (soal[j] == '-') || (soal[j] == '*') || (soal[j] == '/')){
                    break;
                }
                operand_2[idx_operand_2] = soal[j];
                idx_operand_2++;
                barrier_operand_2 = j;
            }
            int_operand_2 = atoi(operand_2);

            // operation
            if(soal[i] == '*'){
                int_result = int_operand_1 * int_operand_2;
            } else if(soal[i] == '/'){
                int_result = int_operand_1 / int_operand_2;
            }
            sprintf(str_result, "%d", int_result);

            // insert result
            len = len + strlen(str_result);
            for(j = len-1; j >= barrier_operand_1 + strlen(str_result); j--){
                soal[j] = soal[j - strlen(str_result)];
            }
            int idx_str_result = 0;
            for(j = barrier_operand_1; j < barrier_operand_1 + strlen(str_result); j++){
                soal[j] = str_result[idx_str_result];
                idx_str_result++;
            }

            // remove finished operation
            barrier_operand_2 += strlen(str_result);
            barrier_operand_1 += strlen(str_result);
            for(j = barrier_operand_1; j < len; j++){
                if(j <= barrier_operand_2){
                    for(k = j; k < len; k++){
                        soal[k] = soal[k+1];
                    }
                    len--;
                    barrier_operand_2--;
                    j--;
                } else{
                    break;
                }
            }

            //
            i = 0;
        }
    }

    
    // add / minus operation
    for(i = 0; i < len; i++){
        if((soal[i] == '+') || (soal[i] == '-')){
            // reset
            memset(operand_1, 0, 500);
            memset(operand_2, 0, 500);
            memset(str_result, 0, 500);
            idx_operand_1 = 0;
            idx_operand_2 = 0;
            int_operand_1 = 0;
            int_operand_2 = 0;
            int_result = 0;
            barrier_operand_1 = 0;
            barrier_operand_2 = 0;
            
            // grab operand before operator
            for(j = i-1; j >= 0; j--){
                operand_1[idx_operand_1] = soal[j];
                idx_operand_1++;
                barrier_operand_1 = j;
            }
            reverse(operand_1, strlen(operand_1));
            int_operand_1 = atoi(operand_1);

            // grab operand after operator
            for(j = i+1; j < len; j++){
                if((soal[j] == '+') || (soal[j] == '-')){
                    break;
                }
                operand_2[idx_operand_2] = soal[j];
                idx_operand_2++;
                barrier_operand_2 = j;
            }
            int_operand_2 = atoi(operand_2);

            // operation
            if(soal[i] == '+'){
                int_result = int_operand_1 + int_operand_2;
            } else if(soal[i] == '-'){
                int_result = int_operand_1 - int_operand_2;
            }
            sprintf(str_result, "%d", int_result);
            
            // insert result
            len = len + strlen(str_result);
            for(j = len-1; j > barrier_operand_1 + strlen(str_result); j--){
                soal[j] = soal[j - strlen(str_result)];
            }
            int idx_str_result = 0;
            for(j = barrier_operand_1; j < barrier_operand_1 + strlen(str_result); j++){
                soal[j] = str_result[idx_str_result];
                idx_str_result++;
            }

            // remove finished operation
            barrier_operand_1 += strlen(str_result);
            barrier_operand_2 += strlen(str_result);
            for(j = barrier_operand_1; j < len; j++){
                if(j <= barrier_operand_2){
                    for(k = j; k < len; k++){
                        soal[k] = soal[k+1];
                    }
                    len--;
                    barrier_operand_2--;
                    j--;
                } else{
                    break;
                }
            }

            //
            i = 0;
        }
    }

    printf("Result: %s", soal);
    return 0;
}