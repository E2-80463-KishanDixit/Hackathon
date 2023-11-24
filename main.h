#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user_signup {
    int userid;
    char fname[20];
    char lname[20];
    char email[20];
    char mobno[20];
    char dob[20];
    char pass[20];
}signup_t;


void sign_up(void);
int validate_email(char *);
int validate_mob(char * );
int u_id =0;

void sign_in(void);

void login_user(int);

void edit_profile(int);

void change_password(int);

void view_profile(int);

void display_movies();
char *arr[]={"[[id=1]\tAsur\t[release_date:10-01-2023]]\n","[[id=2]\tSardar Udham\t[release_date:10-01-2023]]\n","[[id=3]\tKaagaz\t[release_date:10-01-2023]]\n","[[id=4]\tOMG\t[release_date:27-01-2023]]\n","[[id=5]\tMission Mangal\t[release_date:05-01-2023]]\n","[[id=6]\tKesari\t[release_date:19-01-2023]]\n","[[id=7]\tJai Ho\t[release_date:14-01-2023]]\n","[[id=8]\tBorder\t[release_date:29-01-2023]]\n","[[id=9]\tBharat\t[release_date:25-01-2023]]\n","[[id=10] kashmir files\t[release_date:20-01-2023]]\n"};

typedef struct reivew{
    int user_id;
    int move_id;
    int review_id;
    int rating;
    char myreview[30];
}reivew_t;


int review_id =0;

void create_review(int);
void display_my_reviews(int);
void edit_review(int);
void display_all_reviews(void);
void delete_review(int);

typedef struct share_review{
    int auth_id;
    int shred_with_id;
    reivew_t review;
}share_rvw_t;

void share_review(int);
void show_shared_review(int);
void shared_with_me(int);