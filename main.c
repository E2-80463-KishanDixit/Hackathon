#include "user.c"

int main(void){
    int ch;
    do{
        printf("Enter your choice: \n 0.Exit\n 1.Sign Up\n 2.Sign In\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                sign_up();
                break;
            case 2:
                sign_in();
                break;
            default:
                if(ch !=0)
                    printf("Enter a valid choice\n");
        }
    }while(ch!=0);
    printf("Exit!!!!\n");
    return 0;
}