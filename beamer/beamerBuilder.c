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

    snippetFile = fopen(token, "r");
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

    source=fopen("template.tex","r+");
    target=fopen("template_final.tex", "w");

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
    int status = system("cp assets/template.tex .");
    if (status == 0){
        printf("Template copy was made successfully \n");
    }else{
        printf("Something went wrong in copy of template");
    }
}


void compileBeamer(){
    system("pdflatex -output-directory tmpfiles/ template_final.tex");
}


