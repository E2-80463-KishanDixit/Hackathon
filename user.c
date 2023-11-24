#include "main.h"

void sign_up(void){
    signup_t user;

    signup_t temp;

    FILE * fptr = fopen("user.db","ab+");

    if(fptr == NULL){
        printf("Unable to open file\n");
    }

    if(u_id ==0){
        while(fread(&temp,sizeof(signup_t),1,fptr) != 0){
            u_id++;
        }
    }

    fclose(fptr);
    //Assigning unique id 
    user.userid = u_id+1; 

    printf("Enter your First Name: \n");
    scanf("%*c%[^\n]s",user.fname);

    printf("Enter your Last Name: \n");
    scanf("%*c%[^\n]s",user.lname);

    do{
        printf("Enter your email\n");
        scanf("%*c%[^\n]s",user.email);
    }while(!validate_email(user.email));

    do{
        printf("Enter your Mob.no.\n");
        scanf("%*c%[^\n]s",user.mobno);
    }while(!validate_mob(user.mobno));


    printf("Enter your DoB in dd/mm/yyyy Formate\n");
    scanf("%*c%[^\n]s",user.dob);

    printf("Enter your Password:\n");
    scanf("%*c%[^\n]s",user.pass);

    fptr = fopen("user.db","ab+");

    if(fptr == NULL){
        printf("Unable to open file\n");
    }

    fwrite(&user,sizeof(signup_t),1,fptr);
    fclose(fptr);

    printf("*******************************************************\n");
    printf("Welcome  %s !!!:) You are signed up successfully\n",user.fname);
    printf("*******************************************************\n");
}

//validate user email
int validate_email(char *email){

    FILE * fptr = fopen("user.db","ab+");
    signup_t temp;

    if(fptr == NULL){
        printf("Unable to open file\n");
    }
        while(fread(&temp,sizeof(signup_t),1,fptr) != 0){
            if(strcpy(temp.email,email)){
                printf("User Already Exist\n");
                return 0;
            }
        }
    fclose(fptr);

    if((strstr(email,"@gmail.com")== NULL) && (strstr(email,"@rediffmail.com")== NULL) && (strstr(email,"@yahoo.com")== NULL)){
        printf("Enetr a valid Email\n");
        return 0;
    }

    return 1;
}

// validate mob number
int validate_mob(char * no){
    if(strlen(no) != 10){
        printf("Enter a valid mob Number\n");
        return 0;
    }
        for(int i=0; i<strlen(no);i++){
            int temp = no[i]- '0';
            if(temp < 0 || temp > 9){
                printf("Enter a valid mob Number\n");
                return 0;
            }
        }
    return 1;
}



// SIGN IN OF USER 
void sign_in(void){
    char email[20];
    char pass[20];
    int signin_id;

    int signin_flag =0;

    printf("\nEnter your email\n");
    scanf("%*c%[^\n]s",email);

    printf("\nEnter your Password:\n");
    scanf("%*c%[^\n]s",pass);

    signup_t temp;

    FILE * fptr = fopen("user.db","rb+");

    if(fptr == NULL){
        printf("Unable to open file\n");
    }
    while(fread(&temp,sizeof(signup_t),1,fptr)!= 0){
        if((strcmp(temp.email,email) == 0) && (strcmp(temp.pass,pass) == 0)){
            printf("************* \n YOUR ARE LOGGED IN :)\n************************\n");
            signin_id = temp.userid;
            login_user(signin_id);
            signin_flag =1;
            break;
        }
    }
    fclose(fptr);
    if(signin_flag ==0){
    printf("Invalid Credential!! Please try Again\n");
    }
}

void login_user(int signin_id){
    int choice;
    do{
        printf("\n 0.Exit\n 1.Edit Profile\n 2.Change Password \n 3.View My Profile\n 4.Display all movies\n 5.Create Review\n 6.Display my reviews\n 7.Edit review\n 8.Display All Reviews\n 9.delete review\n 10.Share Review\n 11.Show shared Review\n 12.Shared with me\n");
        printf("Enter your choice : \n");
        scanf("%d",&choice);

        switch(choice)
        {
         case 1:
            edit_profile(signin_id);
                break;
         case 2:
            change_password(signin_id);
                break;
         case 3:
            view_profile(signin_id);
                break;
         case 4: 
            display_movies();
                 break;
         case 5:
            create_review(signin_id);
                break;
         case 6:
            display_my_reviews(signin_id);
                break;
         case 7: 
            edit_review(signin_id);
                break;
         case 8:
            display_all_reviews();
                break; 
         case 9:
            delete_review(signin_id);
                break;   
        case 10:
            share_review(signin_id);
                break; 
        case 11:
            show_shared_review(signin_id);
                break; 
        case 12:
            shared_with_me(signin_id);
                break;
        default:
            break;
        }
    }while(choice!=0);
}

void edit_profile(int signin_id){ 
    signup_t user;

    char efname[20];
    char elname[20];
    char eemail[20];
    char embno[20];
    char edob[20];

    printf("Edit your First Name:\n");
    scanf("%*c%[^\n]s",efname);
    strcpy(user.lname,efname);

    printf("Edit your Last Name\n");
    scanf("%*c%[^\n]s",elname);
    strcpy(user.lname,elname);

    printf("Edit your Email\n");
    scanf("%*c%[^\n]s",eemail);
    strcpy(user.email,eemail);

    printf("Edit your Mob No.\n");
    scanf("%*c%[^\n]s",embno);
    strcpy(user.mobno,embno);

    printf("Edit your DOB.\n");
    scanf("%*c%[^\n]s",edob);
    strcpy(user.dob,edob);

    signup_t e_temp = user;

    signup_t temp;

    FILE *fptr=fopen("user.db","rb+");

    if(fptr==NULL){
        printf("failed to open file\n");
        exit(1);
    }
    while(fread(&temp,sizeof(signup_t),1,fptr)!=0)
    {
        if(temp.userid == signin_id){
            e_temp.userid = signin_id;
            strcpy(e_temp.pass,temp.pass);
            fseek(fptr,-sizeof(signup_t),SEEK_CUR);
            fwrite(&e_temp,sizeof(signup_t),1,fptr);
        }
    }
    fclose(fptr);
    printf("\nYour profile edited successfully!! :)\n");
}


void change_password(int signin_id){
    char newpass[20];
    signup_t user;
    printf("Enter new Password\n");
    scanf("%*c%[^\n]s",newpass);
    strcpy(user.pass,newpass);

    signup_t e_temp = user;
    signup_t temp;

    FILE *fptr=fopen("user.db","rb+");
    if(fptr==NULL)
    {
        printf("failed to open file\n");
        exit(1);
    }

    while(fread(&temp,sizeof(signup_t),1,fptr)!=0)
    {
        if(temp.userid == signin_id){
            fseek(fptr,-sizeof(temp.pass),SEEK_CUR);
            fwrite(&e_temp.pass,sizeof(e_temp.pass),1,fptr);
        }
    }
    printf("Password edited successfully!!\n");
    fclose(fptr);
}

void view_profile(int signin_id){
    signup_t temp;
    FILE *fptr=fopen("user.db","rb+");
    if(fptr==NULL)
    {
        printf("failed to open file\n");
        exit(1);
    }
    printf("************ YOUR PROFILE *********************\n");
    while(fread(&temp,sizeof(signup_t),1,fptr)!=0)
    {
        if(temp.userid == signin_id){
            printf("First Name: %s\n",temp.fname);
            printf("Last Name: %s\n",temp.lname);
            printf("Email: %s\n",temp.email);
            printf("Mobile No.: %s\n",temp.mobno);
            printf("DoB: %s\n",temp.dob);
        }
    }
    fclose(fptr);
    printf("************************************************\n");
}


void display_movies(){
    for(int i=0;i<10;i++){
        printf("%s",arr[i]);
    }
}

void create_review(int signin_id){

    char str_review [20];
    reivew_t review;

    FILE * fptr;
    if(review_id == 0){
        fptr = fopen("review.db","ab+");
        if(fptr==NULL){
            printf("failed to open file\n");
            exit(1);
        }
        while(fread(&review,sizeof(reivew_t),1,fptr)!=0){   
            review_id++;
        }
        fclose(fptr);
    }

    review.review_id = review_id+1;
    
    review.user_id = signin_id;

    printf("Enter Movie Id: \n");
    scanf("%d",&review.move_id);

    printf("Enter a Riview: \n");
    scanf("%*c%[^\n]s",str_review);
    strcpy(review.myreview,str_review);

    do{
        printf("Enter rating (0 to 5): \n");
        scanf("%d",&review.rating);

        if(review.rating > 5 || review.rating < 0){
            printf("Kindly Enter a valid Rating\n");
        }
    }while((review.rating > 5 || review.rating < 0));

    // printf("Kindly Enter  Valid Rating\n");

    fptr = fopen("review.db","ab+");
    if(fptr == NULL){
        printf("Unable to open user file data\n");
        exit(1);
    }
    fwrite(&review,sizeof(reivew_t),1,fptr);
    fclose(fptr);
    printf("Your Rivew Addedd successfully!!\n");

    review_id++;
}

void display_my_reviews(int signin_id){
    reivew_t temp;

    FILE *fptr=fopen("review.db","ab+");
    if(fptr==NULL)
    {
        printf("failed to open file\n");
        exit(1);
    }
    while(fread(&temp,sizeof(reivew_t),1,fptr)!=0)
    {
        if(signin_id == temp.user_id){
            printf("\n************************************************\n");
            printf("MOVIE NAME: %s\n",arr[temp.move_id-1]);
            printf("YOUR MOVIE ID: %d\n",temp.move_id);
            printf("YOUR REVIEW ID: %d\n",temp.review_id);
            printf("YOUR REVIEW: %s\n",temp.myreview);
            printf("YOUR GIVEN RATING: %d\n",temp.rating);
            printf("\n************************************************\n");
        }
    }
    fclose(fptr);
}

void edit_review(int signin_id){
    int review_id;
    int move_id;
    reivew_t temp;

    printf("Enter Review Id: \n");
    scanf("%d",&review_id);

    printf("Enter Movie Id: \n");
    scanf("%d",&move_id);

    FILE *fptr=fopen("review.db","rb+");
    if(fptr==NULL)
    {
        printf("failed to open file\n");
        exit(1);
    }
    while(fread(&temp,sizeof(reivew_t),1,fptr)!=0)
    {
        if(signin_id == temp.user_id && move_id == temp.move_id && review_id == temp.review_id){
            char new_review[20];
            printf("\n************************************************\n");
            printf("Your Previous Review: %s",temp.myreview);
            printf("\n************************************************\n");
            printf("Enter New Review: \n");
            scanf("%*c%[^\n]s",new_review);
            printf("\n************************************************\n");
            fseek(fptr,-sizeof(temp.myreview),SEEK_CUR);
            fwrite(&new_review,sizeof(new_review),1,fptr);
            break;
        }
    }
    fclose(fptr);
    printf("Your Review Edited Successfully!!!!!\n");
}

void display_all_reviews(void){
    int user_temp_id=0;
    signup_t user_temp;
    reivew_t temp;

    FILE *fptr=fopen("review.db","ab+");
    if(fptr==NULL){
        printf("failed to open file\n");
        exit(1);
    }
    while(fread(&temp,sizeof(reivew_t),1,fptr)!=0){
        printf("\n************************************************\n");
        printf("MOVIE NAME: %s\n",arr[temp.move_id-1]);
        printf("YOUR MOVIE ID: %d\n",temp.move_id);
        printf("YOUR REVIEW ID: %d\n",temp.review_id);
        printf("YOUR REVIEW: %s\n",temp.myreview);
        printf("YOUR GIVEN RATING: %d\n",temp.rating);
        user_temp_id = temp.user_id;
        printf("Author Id: %d\n",temp.user_id);
        FILE *auth_fptr = fopen("user.db","rb+");
        while(fread(&user_temp,sizeof(signup_t),1,auth_fptr)!=0){
            if(user_temp.userid == user_temp_id){
                printf("AUTHOR: %s",user_temp.email);
                printf("\n************************************************\n");
            }
        }
        fclose(auth_fptr);
    }
    fclose(fptr);
}


void delete_review(int signin_id){
    int flag =0;
    int review_id;
    int move_id;

    reivew_t temp;
    FILE *new_fptr = NULL;

    printf("Enter Movie Id: \n");
    scanf("%d",&move_id);

    printf("Enter Review Id: \n");
    scanf("%d",&review_id);

    FILE *fptr=fopen("review.db","rb+");
    if(fptr==NULL)
    {
        printf("failed to open file\n");
        exit(1);
    }
    while(fread(&temp,sizeof(reivew_t),1,fptr)!=0){
        if((signin_id == temp.user_id) && (move_id == temp.move_id) && (review_id == temp.review_id)){
            flag =1;
            continue;
        }else{
            new_fptr = fopen("temp.db","ab+");
            fwrite(&temp,sizeof(reivew_t),1,new_fptr);
            fclose(new_fptr);
        }
    }
    fclose(fptr);
    if(flag == 0){
        printf("Review not found or Not access to delete\n");
    }else{
        printf("Your Review Deleted successfully!!\n");
    }

    remove("review.db");
    rename("temp.db","review.db");

}

void share_review(int signin_id){
    int flag =0;
    share_rvw_t shared_rvw;
    int rvw_id;
    reivew_t temp;
 
    shared_rvw.auth_id = signin_id;

    printf("Enter Review id\n");
    scanf("%d",&rvw_id);

    printf("Enter id with whome you want to share this review\n");
    scanf("%d",&shared_rvw.shred_with_id);

    FILE * fptr = fopen("review.db","ab+");

    while(fread(&temp,sizeof(reivew_t),1,fptr) !=0){
        if(signin_id == temp.user_id && rvw_id == temp.review_id){
            if(signin_id == shared_rvw.shred_with_id){
                printf("*******************************************\n");
                printf("You can't share your review with yourself\n");
                printf("*******************************************\n");
            }
            shared_rvw.review = temp;
            flag =1;
        }
    }
    fclose(fptr);

    if(flag == 1){
        fptr = fopen("sharedReview.db","ab+");
        fwrite(&shared_rvw,sizeof(share_rvw_t),1,fptr);
        fclose(fptr);
        printf("Review shared successfully\n");
    }else{
        printf("Wrong credentials.Try Again\n");
    }
}

void show_shared_review(int signin_id){
    share_rvw_t temp;
    FILE * fptr = fopen("sharedReview.db","ab+");

    while(fread(&temp,sizeof(share_rvw_t),1,fptr) !=0){
        if(signin_id == temp.auth_id){
            printf("Shared With: %d\n",temp.shred_with_id);
            printf("**************************************\n");
            printf("Review: %s\n",temp.review.myreview);
            printf("**************************************\n");
        }
    }
    fclose(fptr);
}

void shared_with_me(int signin_id){
    share_rvw_t temp;
    FILE * fptr = fopen("sharedReview.db","ab+");

    while(fread(&temp,sizeof(share_rvw_t),1,fptr) !=0){
        if(signin_id == temp.shred_with_id){
            printf("Author: %d\n",temp.auth_id);
            printf("**************************************\n");
            printf("Review: %s\n",temp.review.myreview);
            printf("**************************************\n");
        }
    }
    fclose(fptr);
}