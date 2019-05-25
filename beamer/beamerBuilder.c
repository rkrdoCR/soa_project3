//
#include "beamerBuilder.h"


void removeNewLine(char *token, int tokenLength){
    for(int i=0; i<tokenLength;i++){
        if(token[i] == '\n'){
            //printf("new line was detected in token in position: %d \n", i);
            token[i]='\0';
        }
    }
}

void copySnippet(char *token, char *snippet){
    FILE *snippetFile;
    char snippetCh;
    int index=0;
    char full_path[100];

    //add path to token
    strcpy(full_path,"tmpfiles/");
    strcat(full_path,token);

    printf("This is full path in copySnippet: %s \n", full_path);

    snippetFile = fopen(full_path, "r");
    //snippetFile = fopen(token, "r");
    printf("copy Snippet i being reached");
    while ((snippetCh = fgetc(snippetFile)) != EOF){
        //strcat(snippet, &snippetCh);
        snippet[index]=snippetCh;
        index++;
    }
    printf("The snippet is: %s", snippet);
    fclose(snippetFile);
}

int readTemplate(){
    FILE *source, *target;
    char ch;
    char token[200] = "";
    char buffer[1000] = "";

    source=fopen("tmpfiles/template.tex","r+");
    target=fopen("tmpfiles/template_final.tex", "w");

    if(source==NULL || target==NULL)
    {
        printf("Some problem in opening the file");
        exit(0);
    } 
    else
    { 
        // while((ch=fgetc(fp))!='#');
        // fgets(token, 25, fp);

        // fprintf(fp, "%s", "\\This is a test");
        // printf("%s\n", token);

        // if(strcmp(token,"test_token_1") == 0){
        //     printf("token was detected");
        // }else{
        //     printf("Token was not detected");
        // }

        while ((ch = fgetc(source)) != EOF){
            if(ch == '#'){
                fgets(token, 25, source);
                
                removeNewLine(token,200);
                printf("Im about to get to copysnippet");
                copySnippet(token,buffer);
                fprintf(target, "%s", buffer);

            }else{
                fputc(ch, target);
            }

        }
    
    }

    

    fclose(source);
    fclose(target);

    return 0;
}


int copyTemplateToTempBash(){
    int status = system("cp assets/* tmpfiles");
    if (status == 0){
        printf("Template copy was made successfully \n");
    }else{
        printf("Something went wrong in copy of template");
    }
}


void compileBeamer(){
    system("pdflatex -interaction nonstopmode -output-directory tmpfiles/ tmpfiles/template_final.tex >/dev/null");
    system("evince tmpfiles/template_final.pdf &");
}


void createTabular(algo_results *ar, int tasks_count, int lcm, char *tabular_name){
    FILE *target;
    char full_path[100];
    strcpy(full_path,"tmpfiles/");
    strcat(full_path,tabular_name);

    target=fopen(full_path, "w");
    char buffer[1000]="";
    int i,j=0;
    char str_i[10];

    strcat(buffer, "\\begin{table}[]\n");
    strcat(buffer, "\\begin{tabular}");
    strcat(buffer, "{");
    for(i=0; i<lcm+1;i++){
        strcat(buffer,"|l");
    }
    strcat(buffer, "|}\n");
    strcat(buffer, "\\hline\n");

    for(i=0;i<lcm+1;i++){
        if(i==0){
            strcat(buffer," ");
        }else{
            sprintf(str_i,"%d",i);
            printf("stri_i %s", str_i);
            strcat(buffer, str_i);
        }
        strcat(buffer,"&"); 
    }
    strcat(buffer," \\hline\n"); 

    for(i=0; i<tasks_count;i++){
        for(j=0;j<lcm+1;j++){
            if(j==0){
                strcat(buffer,"Task : ");
                sprintf(str_i,"%d",i);
                strcat(buffer, str_i);
                strcat(buffer," &");
            }else{
                switch(ar->matrix[i][j-1]){
                    case 0:
                    strcat(buffer," &");  
                    break;
                    case 1:
                    strcat(buffer," \\cellcolor[HTML]{6434FC} &");
                    break;
                    case 2:
                    strcat(buffer," \\cellcolor[HTML]{F56B00} &");
                    break;
                    case 3:
                    strcat(buffer," \\cellcolor[HTML]{F8FF00} &");
                    break;
                    case 4:
                    strcat(buffer," \\cellcolor[HTML]{003532} &");
                    break;
                    case 5:
                    strcat(buffer," \\cellcolor[HTML]{94FF99} &");
                    break;
                    case 6:
                    strcat(buffer," \\cellcolor[HTML]{6434FC} &");
                    break;
                    case 7:
                    strcat(buffer," \\cellcolor[HTML]{FFCE93} &");
                    break;
                    case 13:
                    strcat(buffer," \\cellcolor[HTML]{CB0000} &");
                    break;                    
                }
                if(j== (lcm)){
                    strcat(buffer," \\hline\n");  
                }
            }
        }
    }

    //strcat(buffer, "\\hline\n");
    strcat(buffer, "\\end{tabular}\n");
    strcat(buffer, "\\end{table}");

    fprintf(target, "%s", buffer);
    fclose(target);

}

void createBeamer(algo_results *ar, int tasks_count, int lcm){
    char tabular_name[10];
    if(ar[0].selected==1){
        strcpy(tabular_name,"tabular1");
        createTabular(&ar[0], tasks_count, lcm, tabular_name);
    }
    
    if(ar[1].selected==1){
        strcpy(tabular_name,"tabular2");
        createTabular(&ar[1], tasks_count, lcm, tabular_name);
    }


    // if(ar[2].selected==1){
    //     strcpy(tabular_name,"tabular3");
    //     createTabular(&ar[2], tasks_count, lcm, tabular_name);
    // }

    
    copyTemplateToTempBash();

    readTemplate();

    compileBeamer();

    
};


