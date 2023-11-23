//Malak Nassar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500
//struct for the date
typedef struct date {
    char day[MAX_SIZE];
    char month[MAX_SIZE];
    char year[MAX_SIZE];
} date;
//the node format first struct
typedef struct student_info {
    char ID[MAX_SIZE];
    char Student_Name[MAX_SIZE];
    char Address[MAX_SIZE];
    char Class_ID[MAX_SIZE];
    date *enrollment;

} student_info;
//the second node :to tidy the code calling
typedef struct student_info_node {
    student_info *data;
    struct student_info_node *right;
    struct student_info_node *left;
} student_info_node;
//****************************************************************************
//initializing the tree
typedef struct student_info_node *TREE;//creating the node pointer
TREE root = NULL;//creating an empty tree called root sorted based on the id
TREE NAME_SORTED_TREE = NULL;//creating an empty tree called NAME_SORTED_TREE to sort based on the names
//****************************************************************************
//global variable
//to take the input from the user
char user_input_ID[MAX_SIZE];//the id user input
char user_input_city[MAX_SIZE];//the address user input
char user_input_class_id[MAX_SIZE];// the class id user input
char deleteline[MAX_SIZE];


//****************************************************************************
//it will create an empty  node on the size of course info node
student_info_node *create_node(student_info *data) {
    student_info_node *node = (student_info_node *) malloc(
            sizeof(struct student_info_node)); // alocate in memory in size of course_info_node
    node->left = node->right = NULL;
    node->data = data;
    return node;
}

//****************************************************************************
// to find the smallest node in the tree
//the smallest value is always the max left
TREE FindMin(TREE t) {
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return FindMin(t->left);
}

//****************************************************************************
//to insert to the tree
TREE insert(TREE t, student_info *data) {

    // if it is an empty tree create a new node and it will be a leaf and irs height is 0
    if (t == NULL) {
        return create_node(data);// the same as make empty function
    }
        //if the new node is less than the parent go left
    else if (strcmp(data->ID, t->data->ID) < 0)
        t->left = insert(t->left, data);
        //if the new node is bigger than the parent  go right
    else if (strcmp(data->ID, t->data->ID) > 0)
        t->right = insert(t->right, data);
    return t;
}

//****************************************************************************
//insert for the new tree that is sorted based on the name
TREE insert_by_name(TREE t, student_info *data) {
    // if it is an empty tree create a new node and it will be a leaf and irs height is 0
    if (t == NULL) {
        return create_node(data);// the same as make empty function
    }
        //if the new node is less than the parent go left
    else if (strcmp(data->Student_Name, t->data->Student_Name) < 0)
        t->left = insert_by_name(t->left, data);
        //if the new node is bigger than the parent  go right
    else if (strcmp(data->Student_Name, t->data->Student_Name) > 0)
        t->right = insert_by_name(t->right, data);
    else if (strcmp(data->Student_Name, t->data->Student_Name) ==
             0)//if the names are the same then put the new name to the right of the parent
        t->right = insert_by_name(t->right, data);
    return t;
}

//****************************************************************************
//traversing through the tree in order and inserting the data to the tree
void inorder_insert_by_name(TREE t, TREE *tree_by_name) {
    if (t != NULL) {
        inorder_insert_by_name(t->left, tree_by_name);
        *tree_by_name = insert_by_name(*tree_by_name,
                                       t->data);//*tree_by_name pointer to the new tree that is sorted based on the names
        inorder_insert_by_name(t->right, tree_by_name);
    }
}

//****************************************************************************
//to print the code in lexicographic order
void PrintInOrder_by_name(TREE t) {
    if (t != NULL) {
        PrintInOrder_by_name(t->left);//traversing through the left subtree
        printf("[%s\t%s\t%s\t%s\t%s/%s/%s] ", t->data->ID, t->data->Student_Name, t->data->Address, t->data->Class_ID,
               t->data->enrollment->day, t->data->enrollment->month, t->data->enrollment->year);
        PrintInOrder_by_name(t->right);//traversing through the right subtree
    }
}

//****************************************************************************
//read from file if exits.
void Read_file() {
    char student_filebuff[MAX_SIZE];
    FILE *student_fptr;
    student_fptr = fopen("students.data", "r");//open the file and read
    if (student_fptr == NULL) {
        printf("\n****Error file is empty****\n");
        exit(1);
    }
//to split the file
    while (!feof(student_fptr)) {
        struct student_info *info = malloc(sizeof(struct student_info));
        info->enrollment = malloc(sizeof(date));
        char *eptr;
        fgets(student_filebuff, MAX_SIZE, student_fptr);

        char *token = strtok(student_filebuff, ",");
        strncpy(info->ID, token, MAX_SIZE);//the id value

        token = strtok(NULL, ",");
        strncpy(info->Student_Name, token, MAX_SIZE);//the name value

        token = strtok(NULL, ",");
        strncpy(info->Address, token, MAX_SIZE);//the address value

        token = strtok(NULL, ",");
        strncpy(info->Class_ID, token, MAX_SIZE);//the class id value

        token = strtok(NULL, "/");
        strncpy(info->enrollment->day, token, MAX_SIZE);//the enrollment day value
        token = strtok(NULL, "/");
        strncpy(info->enrollment->month, token, MAX_SIZE);//the enrollment month
        token = strtok(NULL, "");
        strncpy(info->enrollment->year, token, MAX_SIZE);//the enrollment year

        root = insert(root, info);//insert to the tree that is sorted based in the ID


    }

    fclose(student_fptr);

}

//****************************************************************************
//to print the tree according to ID
// to print the tree in order
void PrintInOrder(TREE t) {
    if (t != NULL) {
        PrintInOrder(t->left);
        printf("[%s\t%s\t%s\t%s\t%s/%s/%s] ", t->data->ID, t->data->Student_Name, t->data->Address, t->data->Class_ID,
               t->data->enrollment->day, t->data->enrollment->month, t->data->enrollment->year);
        PrintInOrder(t->right);
    }
}

//****************************************************************************
//FIND the id
TREE find_by_ID(char student_ID[MAX_SIZE], TREE t) {
    if (t == NULL) {
        printf("ID NOT FOUND!\n");
        return NULL;
    } else if (strcmp(student_ID, t->data->ID) < 0)//search the left subtree
        return find_by_ID(student_ID, t->left);

    else if (strcmp(student_ID, t->data->ID) > 0)//search the right subtree
        return find_by_ID(student_ID, t->right);
    else
        return t;
}

//****************************************************************************
//to insert a new student
void insert_new_student() {
    TREE unique;
    student_info *data = malloc(sizeof(struct student_info));
    data->enrollment = malloc(sizeof(date));

    printf("to insert a new student please enter\n");
    printf("enter the student ID\n");
    scanf("%s", &data->ID);
    unique = find_by_ID(data->ID, root);//if the tree (unique) is not empty that means that the id already exists
    while (unique != NULL) {//check if unique
        printf("the IS already exits enter a new ID\n");
        printf("enter the student ID\n");//ask for the id
        scanf("%s", &data->ID);
        unique = find_by_ID(data->ID, root);
    }
    printf("enter the student name\n");//student name for the id
    scanf("%s", &data->Student_Name);

    printf("enter the student address\n");//address for the id
    scanf("%s", &data->Address);

    printf("enter the student class ID\n");//class id for the id
    scanf("%s", &data->Class_ID);

    printf("enter the day of enrolment\n");//day enrollment for the id
    scanf("%s", &data->enrollment->day);

    printf("enter the month of enrolment\n");//month enrollment for the id
    scanf("%s", &data->enrollment->month);

    printf("enter the year of enrolment \n");//year enrollment  for the id
    scanf("%s", &data->enrollment->year);

    root = insert(root, data);//to insert the new node to the tree
    PrintInOrder(root);
}

//****************************************************************************
//FIND and print by address
TREE find_print_by_city(char student_address[MAX_SIZE], TREE t) {


    if (t != NULL) {//to iterate through the whole tree
        find_print_by_city(student_address, t->left);//search the left subtree
        if (strcmp(student_address, t->data->Address) == 0) {//if equal insert to the name sorted tree
            NAME_SORTED_TREE = insert_by_name(NAME_SORTED_TREE,
                                              t->data);//insert the new nodes that contain the address that you want to find to the tree based on names
        }
        find_print_by_city(student_address, t->right);//search the right subtree

    }

}

//****************************************************************************
//FIND and print by class id
TREE find_print_by_class_id(char student_class_ID[MAX_SIZE], TREE t) {

    if (t != NULL) {//to iterate through the whole tree
        find_print_by_class_id(student_class_ID, t->left);//search the left subtree
        if (strcmp(student_class_ID, t->data->Class_ID) == 0)//if equal insert to the name sorted tree
            NAME_SORTED_TREE = insert_by_name(NAME_SORTED_TREE,
                                              t->data);//insert the new nodes that contain the class id that you want to find to the tree based on names
        find_print_by_class_id(student_class_ID, t->right);//search the right subtree
    }
}

//****************************************************************************
//update
void update(TREE node) {
    int choice_update = 0;
    int choice_update_date = 0;

    student_info *data = malloc(sizeof(struct student_info));
    data->enrollment = malloc(sizeof(date));
    // asks the user
    printf("please choose from1-4\n");
    printf("1-if you want to change the ID\n"
           "2-if you want to change the the student Name\n"
           "3-if you want to change the Address\n"
           "4-if you want to change the class ID\n"
           "5-if you want to change enrollment date\n");
    scanf("%d", &choice_update);
    switch (choice_update) {
        case 1:
//            to change the id
            printf("please enter the new ID");
            gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
            gets(data->ID);
            TREE unique_update = find_by_ID(data->ID,
                                            root);//if the tree (unique) is not empty that means that the id already exists
            while (unique_update != NULL) {//check if unique
                //copies the new data to the old data
                printf("the IS already exits enter a new ID\n");
                printf("enter the new ID\n");//ask for the id
                gets(data->ID);
                unique_update = find_by_ID(data->ID, root);
            }
            strncpy(node->data->ID, data->ID, MAX_SIZE);
            break;
        case 2:
//            to change the student name
            printf("please enter the new name");
            gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
            gets(data->Student_Name);
            //copies the new data to the old data
            strncpy(node->data->Student_Name, data->Student_Name, MAX_SIZE);
            break;
        case 3:
//            to change to address
            printf("please enter the new Address");
            gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
            gets(data->Address);
            //copies the new data to the old data
            strncpy(node->data->Address, data->Address, MAX_SIZE);
            break;
        case 4:
//            to change the class id
            printf("please enter the new class ID");
            gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
            gets(data->Class_ID);
            //copies the new data to the old data
            strncpy(node->data->Class_ID, data->Class_ID, MAX_SIZE);
            break;
        case 5:
//            to change the enrollment date
            printf("please choose from 1-4\n");
            printf("1-if you want to change the day\n"
                   "2-if you want to change the month\n"
                   "3-if you want to change the year\n"
                   "4-if you want to change the whole date\n");
            scanf("%d", &choice_update_date);
            switch (choice_update_date) {
                case 1://to change the day only
                    printf("please enter the new day\n");
                    gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
                    gets(data->enrollment->day);
                    //copies the new data to the old data
                    strncpy(node->data->enrollment->day, data->enrollment->day, MAX_SIZE);
                    break;
                case 2://to change the month only
                    printf("please enter the new month\n");
                    gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
                    gets(data->enrollment->month);
                    //copies the new data to the old data
                    strncpy(node->data->enrollment->month, data->enrollment->month, MAX_SIZE);
                    break;
                case 3://to change the year only
                    printf("please enter the new year\n");
                    gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
                    gets(data->enrollment->year);
                    //copies the new data to the old data
                    strncpy(node->data->enrollment->year, data->enrollment->year, MAX_SIZE);
                    break;
                case 4://to change the whole enrollment date
//                to change the day
                    printf("please enter the new day\n");
                    gets(deleteline);//to remove the new line(it doesn't remove it reads it so it wont take the new data as anew line)
                    gets(data->enrollment->day);
                    //copies the new data to the old data
                    strncpy(node->data->enrollment->day, data->enrollment->day, MAX_SIZE);

//                to change the day
                    printf("please enter the new month\n");
                    gets(data->enrollment->month);
                    //copies the new data to the old data
                    strncpy(node->data->enrollment->month, data->enrollment->month, MAX_SIZE);

//                to change the day
                    printf("please enter the new year\n");
                    gets(data->enrollment->year);
                    //copies the new data to the old data
                    strncpy(node->data->enrollment->year, data->enrollment->year, MAX_SIZE);
                    break;

                default:
                    printf("error try again");
                    exit(1);
            }
            break;

        default:
            printf("error try again");
            exit(1);
    }
}

//****************************************************************************
//delete by id
TREE delete(char student_ID[MAX_SIZE], TREE t) {
    if (t == NULL) {
        printf("STUDENT ID NOT FOUND!!");
        return NULL;
//        search the right subtree
    } else if (strcmp(student_ID, t->data->ID) > 0)
        t->right = delete(student_ID, t->right);
//        search the left subtree
    else if (strcmp(student_ID, t->data->ID) < 0)
        t->left = delete(student_ID, t->left);
    else {//if it is the root the id wanted for delete
        if ((t->left != NULL) && (t->right != NULL)) {//if it has two children
            TREE temp = FindMin(root->right);//temp == the smallest node in the right sub tree
            // copys the data  from temp to root
            strncpy(t->data->ID, temp->data->ID, MAX_SIZE);
            strncpy(t->data->Student_Name, temp->data->Student_Name, MAX_SIZE);
            strncpy(t->data->Address, temp->data->Address, MAX_SIZE);
            strncpy(t->data->Class_ID, temp->data->Class_ID, MAX_SIZE);
            strncpy(t->data->enrollment->day, temp->data->enrollment->day, MAX_SIZE);
            strncpy(t->data->enrollment->month, temp->data->enrollment->month, MAX_SIZE);
            strncpy(t->data->enrollment->year, temp->data->enrollment->year, MAX_SIZE);

            t->right = delete(temp->data->ID, t->right);

        } else if ((t->left == NULL) || (t->right == NULL)) {//one child or zero

            TREE temp = t->left ? t->left
                                :// if the left doesnt equal null then temp equals t->left else if the right doesnt equal NULL then temp t->right
                        t->right;
            // No child case
            if (temp == NULL) {
                temp = t;
                t = NULL;
            } else // One child case
                *t = *temp;//copys the contents

            free(temp);//free the node
        }
    }
    return t;
}

//****************************************************************************
//SAVE TO FILE based on the id
void save_to_file(TREE t) {
    FILE *save_fptr;

    save_fptr = fopen("students.data", "a");//open file
    if (save_fptr == NULL) {
        printf("\n****Error couldn't open the file****\n");
        exit(1);
    }
    if (t != NULL) {
        save_to_file(t->left);
        fprintf(save_fptr, "\n%s,%s,%s,%s,%s/%s/%s", t->data->ID, t->data->Student_Name, t->data->Address,
                t->data->Class_ID, t->data->enrollment->day, t->data->enrollment->month,
                t->data->enrollment->year);//to print to the file
        save_to_file(t->right);

    }

    fclose(save_fptr);
}

//****************************************************************************
//MENU
int main(void) {
    FILE *student_fptr;

    int choice = 0;
    printf("*********MENU*********\n");
    printf("1-read from file\n"
           "2-insert a new student\n"
           "3-find student by ID and update student info\n"
           "4-list all students in Lexicographic order\n"
           "5-search students by city and list them in a lexicographic order\n"
           "6-list all students in the same class in lexicographic order\n"
           "7-delete student by ID\n"
           "8-save to file\n"
           "9-exit\n");
    printf("please enter a number\n", choice);
    scanf("%d", &choice);
    while (choice != 0) {
        switch (choice) {
            case 1:
//                checks if the file is empty if yes then insert to the tree using the function insert
                student_fptr = fopen("students.data", "r");//open the file and read
                if (student_fptr == NULL) {
                    printf("\n****Error file is empty****\n");
                    exit(1);
                }
                fseek(student_fptr, 0, SEEK_END); // Move the file position indicator to the end of the file
                long size = ftell(student_fptr); // Get the current position (size) of the file
                fclose(student_fptr);

                if (size == 0)
                    printf("file is empty insert to the tree ");
                else
//                    if not empty
                    Read_file();
                break;
            case 2:
//                insert student function
                insert_new_student();
                break;
            case 3:
                printf("please enter the student ID \n");
                scanf("%s", &user_input_ID);
                TREE tree = find_by_ID(user_input_ID, root);//store the tree that has the specific id
                if (tree != NULL) {
                    update(tree);//pass the tree that has the id
                    PrintInOrder(root);//print in order the whole tree
                }

                break;
            case 4:
//              print in lexicographic order
                NAME_SORTED_TREE = NULL;
                inorder_insert_by_name(root, &NAME_SORTED_TREE);
                PrintInOrder_by_name(NAME_SORTED_TREE);
                break;
            case 5:
//              print the student with the same address in lexicographic order
                printf("please enter the student Address \n");
                scanf("%s", &user_input_city);
                NAME_SORTED_TREE = NULL;
                TREE address_found = find_print_by_city(user_input_city,
                                                        root);//store the tree that has the specific address
                inorder_insert_by_name(address_found,
                                       &NAME_SORTED_TREE);//store it the new tree for it to be sorted in lexicographic order
                PrintInOrder_by_name(NAME_SORTED_TREE);
                break;
            case 6:
//              print the student with the same class id in lexicographic order
                NAME_SORTED_TREE = NULL;
                printf("please enter the student class ID \n");
                scanf("%s", &user_input_class_id);
                TREE Class_ID_found = find_print_by_class_id(user_input_class_id,
                                                             root);//store the tree that has the specific class id
                inorder_insert_by_name(Class_ID_found,
                                       &NAME_SORTED_TREE);//store it the new tree for it to be sorted in lexicographic order
                PrintInOrder_by_name(NAME_SORTED_TREE);//print in lexicographic order
                break;
            case 7:
//              delete
                printf("please enter the student ID \n");
                scanf("%s", &user_input_ID);
                delete(user_input_ID, root);

                break;
            case 8:
//              save to file
                save_to_file(root);
                break;
            case 9:
//              exit
                printf("***");
                exit(0);

            default:
                printf("error try again\n");


        }
        printf("\n*********MENU*********\n");
        printf("1-read from file\n"
               "2-insert a new student\n"
               "3-find student by ID and update student info\n"
               "4-list all students in Lexicographic order\n"
               "5-search students by city and list them in a lexicographic order\n"
               "6-list all students in the same class in lexicographic order\n"
               "7-delete student by ID\n"
               "8-save to file\n"
               "9-exit\n");
        printf("please enter a number\n", choice);
        scanf("%d", &choice);

    }

}