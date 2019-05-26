//
#include "beamerBuilder.h"

int decoder_index=0;
char decoder_keys[100][100];
char decoder_values[100][100];


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
    if(snippetFile == NULL){
        printf("File for token does not exist\n");
    }else{
        printf("copy Snippet is being reached\n");
        while ((snippetCh = fgetc(snippetFile)) != EOF){
            //strcat(snippet, &snippetCh);
            snippet[index]=snippetCh;
            index++;
        }
        printf("The snippet is: \n%s", snippet);
        printf("The snippet end");
        fclose(snippetFile);
    }

    
}

void clean_buffer(char *buffer, int length){
    int i=0;
    for(i=0;i<length;i++){
        buffer[i]="\0";
    }
}

int readTemplate(){
    FILE *source, *target;
    char ch;
    char token[200] = "";
    char buffer[2000] = "";

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
                printf("Im about to get to copysnippet\n");
                StringDecoder(token,buffer);
                copySnippet(token,buffer);
                fseek(target,-1,SEEK_CUR);
                fprintf(target, "%s", buffer);
                //clean_buffer(buffer,2000);
                memset(buffer, 0, 2000);
            }else{
                fputc(ch, target);
            }

        }
    
    }

    

    fclose(source);
    fclose(target);

    return 0;
}


// int copyTemplateToTempBash(){
//     int status = system("cp assets/* tmpfiles");
//     if (status == 0){
//         printf("Template copy was made successfully \n");
//     }else{
//         printf("Something went wrong in copy of template");
//     }
// }

int copyTemplateToTempBash(char *file_to_copy){
   char full_command[150];
   printf("Im inside copy template and this is file to copy: \n%s",file_to_copy);
   strcpy(full_command,"cp assets/");
   strcat(full_command,file_to_copy);
   strcat(full_command," tmpfiles");
   printf("Im inside copy template and this is full_command: \n%s",full_command);

   int status = system(full_command);
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

void StringDecoder(char *input, char *output){
    int i=0;
    int c=100;
    for (i=0; i<decoder_index;i++){
        c=strcmp(decoder_keys[i],input);
        if(c==0){
            strcpy(output,decoder_values[i]);
        }
    }
}

void addKeyToDecoder(char *key, char *value){
    strcpy(decoder_keys[decoder_index],key);
    strcpy(decoder_values[decoder_index],value);
    decoder_index++;
}

void flushDecoder(){
    int i=0;
    for (i=0; i<100;i++){
        memset(decoder_keys[i],0,100);
    }
}



void createTabular(algo_results *ar, int tasks_count, int lcm, char *tabular_name){
    FILE *target;
    char full_path[100];
    strcpy(full_path,"tmpfiles/");
    strcat(full_path,tabular_name);

    target=fopen(full_path, "w");
    char buffer[1000]="";
    int i,j,k=0;
    char str_i[100];
    char title_name[100];

    printf("Creating this tabular: %s", tabular_name);

    strcat(buffer, "\\begin{table}[]\n");

    //table title
    //strcat(buffer,"\\caption {Table Title} \\label{tab:title}");
    strcat(buffer,"\\caption {");
    StringDecoder(tabular_name,title_name);
    strcat(buffer,title_name);
    strcat(buffer,"} \\label{tab:");
    strcat(buffer,tabular_name);
    strcat(buffer,"}\n");


    strcat(buffer, "\\small\\addtolength{\\tabcolsep}{-5pt}\n");
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
    printf("Done with table header");
    strcat(buffer," \\hline\n"); 

    for(i=0; i<tasks_count;i++){
        for(j=0;j<lcm+1;j++){
            if(j==0){
                strcat(buffer,"T: ");
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
    printf("Done with table body");

    //strcat(buffer, "\\hline\n");
    strcat(buffer, "\\end{tabular}\n");
    strcat(buffer, "\\end{table}\n");

    fprintf(target, "%s", buffer);
    fclose(target);
    printf("file closed successfully");
}


void createBeamer(algo_results *ar, int tasks_count, int lcm){
    char tabular_name[10];
    flushTempFiles();
    flushDecoder();
    copyTemplateToTempBash("template.tex");


    if(ar[0].selected==1){
        addKeyToDecoder("subsectionrm","\\subsection{Rate Monothonic}");
        addKeyToDecoder("tabular1","Resultados de simulacion de Rate Monothonic");
        addKeyToDecoder("beginrmd","\\begin{frame}{Descripcion de Rate Monothonic}\n");
        addKeyToDecoder("beginrmt","\\begin{frame}{Resultados test de Rate Monothonic}\n");
        addKeyToDecoder("beginrms","\\begin{frame}{Resultados sim de Rate Monothonic}\n");
        addKeyToDecoder("endrm","\\end{frame}\n");
        copyTemplateToTempBash("description11");
        copyTemplateToTempBash("description12");
        createTabular(&ar[0], tasks_count, lcm, "tabular1");
    }
    
    if(ar[1].selected==1){
        addKeyToDecoder("subsectionedf","\\subsection{Earliest deadline first}");
        addKeyToDecoder("tabular2","Resultados de simulacion de Earliest Deadline first");
        addKeyToDecoder("beginedfd","\\begin{frame}{Descripcion de Earliest Deadline first}\n");
        addKeyToDecoder("beginedft","\\begin{frame}{Resultados test de Earliest Deadline first}\n");
        addKeyToDecoder("beginedfs","\\begin{frame}{Resultados sim de Earliest Deadline first}\n");
        addKeyToDecoder("endedf","\\end{frame}\n");
        copyTemplateToTempBash("description21");
        copyTemplateToTempBash("description22");
        createTabular(&ar[1], tasks_count, lcm, "tabular2");
    }

    if(ar[2].selected==1){
        addKeyToDecoder("subsectionllf","\\subsection{Least Laxity first}");
        addKeyToDecoder("tabular3","Resultados de simulacion de Least Laxity first");
        addKeyToDecoder("beginllfd","\\begin{frame}{Descripcion de Least Laxity First}\n");
        addKeyToDecoder("beginllft","\\begin{frame}{Resultados test de Least Laxity First}\n");
        addKeyToDecoder("beginllfs","\\begin{frame}{Resultados sim de Least Laxity First}\n");
        addKeyToDecoder("endllf","\\end{frame}\n");
        copyTemplateToTempBash("description31");
        copyTemplateToTempBash("description32");
        createTabular(&ar[2], tasks_count, lcm, "tabular3");
    }

    readTemplate();

    compileBeamer();

    
};

void flushTempFiles(){
    int status = system("rm tmpfiles/*");
    if (status == 0){
        printf("tmpFiles cleared\n");
    }else{
       printf("Something went wrong clearing temp files");
    }
}




