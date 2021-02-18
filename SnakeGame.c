#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
/* Include other headers as needed */
#define N 25
char board[N][N];
int count=0;
char previousOption='L',newOption='L';

struct Node {
    char data;
    int x,y;
    struct Node* next;
};

struct Node* head = NULL;

struct Fruit {
    char value;
    int x,y;
};

struct Fruit* fruit = NULL;

int randomNumber(int lower,int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void createSnake() {
    struct Node* body1 = NULL;
    struct Node* body2 = NULL;
    struct Node* tail = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    body1 = (struct Node*)malloc(sizeof(struct Node));
    body2 = (struct Node*)malloc(sizeof(struct Node));
    tail = (struct Node*)malloc(sizeof(struct Node));

    head->data = 'H';
    head->next = body1;
    head->x = 10;
    head->y = 10;

    body1->data = 'o';
    body1->next = body2;
    body1->x = 10;
    body1->y = 11;

    body2->data = 'o';
    body2->next = tail;
    body2->x = 10;
    body2->y = 12;

    tail->data = 'T';
    tail->next = NULL;
    tail->x = 10;
    tail->y = 13;
}

void createFruit() {

    fruit = (struct Fruit*)malloc(sizeof(struct Fruit));

    int lower = 1, upper = N-2;

    srand(time(0));

    fruit->value = 'F';
    fruit->x = randomNumber(lower,upper);
    fruit->y = randomNumber(lower,upper);
}

void eatFruit() {
    struct Node* temp = head;
    head->data = 'o';
    head = fruit;
    head->data = 'H';
    head->next = temp;
    count++;
    createFruit();
}

void printBoard() {
    system("clear");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}

void updateBoard() {
    struct Node* temp = head;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i==0 || i==24 || j==0 || j==24)
            {
                board[i][j] = '*';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
    board[fruit->x][fruit->y] = fruit->value;
    while(temp != NULL)
    {
        int i = temp->x;
        int j = temp->y;
        board[i][j] = temp->data;
        temp = temp->next;
    }
    printBoard();
}

void init() {
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i==0 || i==N-1 || j==0 || j==N-1)
            {
                board[i][j] = '*';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
    createSnake();
    struct Node* temp = head;

    for(int i=0;i<4;i++)
    {
        board[temp->x][temp->y] = temp->data;
        temp = temp->next;
    }

    createFruit();

    board[fruit->x][fruit->y] = fruit->value;

    printBoard();
}

void moveLeft() {
    struct Node* temp = head;
    int oldX = temp->x;
    int oldY = temp->y;
    temp->y--;
    if(head->x == fruit->x && head->y == fruit->y)
    {
        temp->y++;
        eatFruit();
    }
    else
    {
        while(temp->next != NULL)
        {
            int newX,newY;
            newX = temp->next->x;
            newY = temp->next->y;
            temp->next->x = oldX;
            temp->next->y = oldY;
            oldX = newX;
            oldY = newY;
            temp = temp->next;
        }
    }
}

void moveRight() {
    struct Node* temp = head;
    int oldX = temp->x;
    int oldY = temp->y;
    temp->y++;
    if(head->x == fruit->x && head->y == fruit->y)
    {
        temp->y--;
        eatFruit();
    }
    else
    {
        while(temp->next != NULL)
        {
            int newX,newY;
            newX = temp->next->x;
            newY = temp->next->y;
            temp->next->x = oldX;
            temp->next->y = oldY;
            oldX = newX;
            oldY = newY;
            temp = temp->next;
        }
    }
}

void moveTop() {
    struct Node* temp = head;
    int oldX = temp->x;
    int oldY = temp->y;
    temp->x--;
    if(head->x == fruit->x && head->y == fruit->y)
    {
        temp->x++;
        eatFruit();
    }
    else
    {
        while(temp->next != NULL)
        {
            int newX,newY;
            newX = temp->next->x;
            newY = temp->next->y;
            temp->next->x = oldX;
            temp->next->y = oldY;
            oldX = newX;
            oldY = newY;
            temp = temp->next;
        }
    }
}

void moveBottom() {
    struct Node* temp = head;
    int oldX = temp->x;
    int oldY = temp->y;
    temp->x++;
    if(head->x == fruit->x && head->y == fruit->y)
    {
        temp->x--;
        eatFruit();
    }
    else
    {
        while(temp->next != NULL)
        {
            int newX,newY;
            newX = temp->next->x;
            newY = temp->next->y;
            temp->next->x = oldX;
            temp->next->y = oldY;
            oldX = newX;
            oldY = newY;
            temp = temp->next;
        }
    }
}

bool isCollisionWithWall() {
    if(head->x == 0 || head->x == N-1 || head->y == 0 || head->y == N-1)
    {
        return true;
    }
    return false;
}

bool isCollisionWithSnake() {
    struct Node* temp = head->next;
    int headX = head->x;
    int headY = head->y;
    while(temp != NULL)
    {
        if(headX == temp->x && headY == temp->y)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

struct Node* getCollisionPoint() {
    struct Node* temp = head->next;
    int headX = head->x;
    int headY = head->y;
    while(temp != NULL)
    {
        if(headX == temp->x && headY == temp->y)
        {
            return temp;
        }
        temp = temp->next;
    }
}

void reduceLength(struct Node* node) {
    struct Node* temp = head;
    while(temp->next != NULL)
    {
        if(temp->next == node)
        {
            temp->data = 'T';
            temp->next = NULL;
            break;
        }
        temp = temp->next;
    }
}

bool isValidMove(char c)
{
    if(newOption == 'L' && previousOption == 'R')
    {
        return false;
    }
    else if(newOption == 'R' && previousOption == 'L')
    {
        return false;
    }
    else if(newOption == 'T' && previousOption == 'B')
    {
        return false;
    }
    else if(newOption == 'B' && previousOption == 'T')
    {
        return false;
    }
    return true;
}

void movement() {
    printf("\n\n\nYour Score: %d",count);
    printf("\n\n\nL\tR\tT\tB\n\nEnter direction: ");
    char option;
    option = getchar();
    getchar();
    option = toupper(option);
    newOption = option;
    if(isValidMove(newOption))
    {
        previousOption = newOption;
        switch(option) {
            case 'L':
            {
                moveLeft();
                break;
            }
            case 'R':
            {
                moveRight();
                break;
            }
            case 'T':
            {
                moveTop();
                break;
            }
            case 'B':
            {
                moveBottom();
                break;
            }
            default:
            {
                printf("Default");
            }
        }
    }
    if(isCollisionWithSnake())
    {
        struct Node* collision_point = getCollisionPoint();
        reduceLength(collision_point);
    }
    updateBoard();
}

int main()
{
    init();
    while(!isCollisionWithWall())
    {
        movement();
    }
    system("clear");
    printf("GAME OVER!\n\n\nYour Score: %d\n\n\nReplay?? [Y/N]: ",count);
    char replay;
    replay = getchar();
    getchar();
    if(replay == 'Y')
    {
        main();
    }
    return 0;
}