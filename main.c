#include <stdio.h>
#include <time.h>

void menu();
void available();
void addRoom();
int findRoom(int roomNum,int checkAc);
void addPerson();
void rBill();
void UpdateRoom(int roomNum );
int checkRoom(int roomNum);
void bookingroomDetails();

struct hRooms{
    int roomNub;
    int available; //available=1 nonAvailable=0.1
    int condition; //ac=1 nonAc=0
};
struct addPerson{
    int date;
    int mount;
    int year;
    int roomNum;
    int phoneNum;
    int condition;
    int idNum;
    char name[20];
    char address[20];
};


int main() {
    int pword, check = 1;
    char uname[10];
    int password=2020;
    char username[10]="gRest";

    printf("Enter The Username:\n");
    scanf("%s",&uname);
    printf("Enter The Password:\n");
    scanf("%d",&pword);

    if(pword == password){
        for (int i = 0; i < 10; ++i) {
            if(uname[i]!=username[i]){
                check=0;
            }
        }
    } else{
        check =0;
    }

    if(check==1){
        menu();
    }else{
        printf("Invalid Password Or Username!\n");
    }


}

void menu(){
    int topic=0;
    printf("\n\t\t.......Welcome To The Golden Rest......\n");
    printf("=====================================================================\n");
    printf("1. Enter number 1 To Room Availability:\n");
    printf("2. Enter Number 2 To Add Personal Details:\n");
    printf("3. Enter Number 3 To Get The Bill:\n");
    printf("4. Enter number 4 To Add A Room:\n");
    printf("5. Enter Number 5 To Exit\n");
    printf("======================================================================\n");
    scanf("%d",&topic);

    switch (topic) {
        case 1:
            available();
            break;
        case 4:
            addRoom();
            break;
        case 2:
            addPerson();
            break;
        case 3:
            rBill();
            break;
        case 5:
            break;
        default:
            printf("========Invalid Input! Try Again=======\n\n");
            menu();
    }
}
void addRoom() {
    FILE *file;
    file= fopen("room.dat","a");
    struct hRooms data;
    int quantity;
    printf("Quantity Of Rooms:\n");
    scanf("%d",&quantity);
    for (int i = 0; i < quantity; ++i) {
        Loop: printf("Enter Room Number:\n");
        scanf("%d",&data.roomNub);
        int x= checkRoom(data.roomNub);
        if(x==0){
            printf("Enter 0 To NonAc & Enter 1 To Ac:");
            scanf("%d",&data.condition);
            data.available=0;
            fwrite(&data,sizeof (data),1,file);
        } else{
            printf("This Room number Already Used!!!\n");
            goto Loop;
        }

    }
    fclose(file);
    menu();
}

int checkRoom(int roomNum){
    int av=0;
    FILE *file;
    file= fopen("room.dat","r");
    struct hRooms data;

    while (fread(&data, sizeof(data),1,file)){
        if(roomNum==data.roomNub){
            av=1;
        }
    }
    return av;
};
void available(){
    struct hRooms data;
    FILE *file;
    int count=0;
    file= fopen("room.dat","r");
    printf("=========Rooms Are Available==========\n");
    while (fread(&data,sizeof (data),1,file)){
        if(data.available==0){
            count=count+1;
            printf("Room Number: %d\n",data.roomNub);
            if(data.condition==1) {
                printf("Ac Room\n");
            }else{
                printf("Non Ac Room\n");
            }
        }
    }
    printf("=====================================\n");
    printf("\tTotal Available Rooms: %d\n",count);
    printf("=====================================\n");
    fclose(file);
    menu();
}

void addPerson(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    struct addPerson data;
    printf("Per A Day  Rs.2000/=\n");
    Loop: printf("Enter The Room Number:\n");

    FILE *file;
    file= fopen("roomBooking.dat","a");

    scanf("%d",&data.roomNum);
    Loop1: printf("Enter 0 To NonAc & Enter 1 To Ac::\n");
    scanf("%d",&data.condition);
    if(data.condition!=1 && data.condition!=0){
        printf("====Invalid condition try Again!==== \n\n");
        goto Loop1;
    }
    int find= findRoom(data.roomNum, data.condition);
    if(find==1){
        printf("Enter The Phone Number:\n");
        scanf("%d",&data.phoneNum);
        printf("Enter The Id Number:\n");
        scanf("%d",&data.idNum);
        printf("Enter The Name:\n");
        scanf("%s",&data.name);
        printf("Enter The Address:\n");
        scanf("%s",&data.address);
        data.date = tm.tm_mday;
        data.mount = tm.tm_mon+1;
        data.year = tm.tm_year+1900;
        fwrite( &data,sizeof(data),1,file );
        printf("\n======Your Booking Is Successful=======\n");
    }else if(find==2){
        printf("====The Condition is Unavailable==== 1\n");
        printf("--------------------------------------------------\n");
        goto Loop;
    }else if (find == 3){
        printf("====Invalid Room number====\n");
        printf("--------------------------------------------------\n");
        goto Loop;
    } else{
        printf("=== Unavailable!! ===\n");
        printf("--------------------------------------------------\n");
        goto Loop;
    }
    fclose(file);
    menu();
}


int findRoom(int roomNum,int checkAc){
    struct hRooms data;
    int ret=3;
    FILE *file,*file1;
    file= fopen("room.dat","r");
    file1= fopen("tempRoom.dat","w");
    while (fread(&data,sizeof (data),1,file)){
        if(data.roomNub==roomNum){
            if(data.available==0) {
                if(data.condition==checkAc){
                    ret=1;
                    data.available=1;
                }else{
                    ret=2;
                }
            }else{
                ret = 0;
            }
        }
        fwrite( &data,sizeof(data),1,file1 );
    }
    fclose(file);
    fclose(file1);

    file= fopen("room.dat","w");
    file1= fopen("tempRoom.dat","r");


    while (fread(&data,sizeof (data),1,file1)){
        fwrite( &data,sizeof(data),1,file );
    }

    fclose(file);
    fclose(file1);

    return ret;

}

void bookingroomDetails(){
    struct hRooms data1;
    FILE *file1;
    file1= fopen("room.dat","r");
    printf("\n\n==Reserved Rooms==\n");
    printf("---------------------------------\n");
    while (fread(&data1,sizeof (data1),1,file1)){
        if(data1.available==1){
            printf("Book Room Number %d\n",data1.roomNub);
        }
    }
    printf("---------------------------------\n");
    fclose(file1);
}
void rBill(){
    bookingroomDetails();
    int Room_num;
    int total,check=0;
    struct addPerson data;
    FILE *file;
    file= fopen("roomBooking.dat","r");

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    time_t tmm;
    time(&tmm);



    printf("Enter The Room Number:\n");
    scanf("%d",&Room_num);

    if(file==NULL){
        printf("not found file\n");
    }
    while (fread(&data,sizeof (data),1,file)){
        if(Room_num==data.roomNum){

            int d =tm.tm_mday-data.date  ;
            int m = (tm.tm_mon+1) - data.mount ;
            int y = (tm.tm_year+1900)- data.year;

            int totalDate= d + (m*30)+ (y*365);

            if(totalDate== 0){
                total = 2000;
                totalDate=1;
            } else{
                total= totalDate*2000;
            }

            printf("\n\n=================================================================================\n");
            printf("=============================  The Golden Hotel =================================\n");
            printf("Person name: %s\n",data.name);
            printf("Person id %d\n",data.idNum);
            printf("%s", ctime(&tmm));
            printf("-----------------------------------------------------------------------------------\n");
            printf("Room Number\t\tPrice\t\tDays\t\tTotal Amount\n");
            printf("-----------------------------------------------------------------------------------\n");
            printf("%d\t\t\t%d\t\t%d\t\t%d",data.roomNum,2000,totalDate,total);
            printf("\n-----------------------------------------------------------------------------------\n");
            printf("\t\t\tThank You.. Come Again!\n");
            printf("=================================================================================\n\n\n");
            UpdateRoom(data.roomNum);
            fclose(file);
            check=1;
            break;
        }
    }
    if(check==0){
        printf("Wrong room number..! try again\n\n\n");
    }
    menu();

}

void UpdateRoom(int roomNum ){
    struct hRooms data;
    FILE *file,*file1;
    file= fopen("room.dat","r");
    file1= fopen("tempRoom.dat","w");
    while (fread(&data,sizeof (data),1,file)){
        if(data.roomNub==roomNum){
            if(data.available==1) {
                data.available=0;
            }
        }
        fwrite( &data,sizeof(data),1,file1 );
    }
    fclose(file);
    fclose(file1);

    file= fopen("room.dat","w");
    file1= fopen("tempRoom.dat","r");


    while (fread(&data,sizeof (data),1,file1)){
        fwrite( &data,sizeof(data),1,file );
    }

    fclose(file);
    fclose(file1);

}
