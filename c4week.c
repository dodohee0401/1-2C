#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LEN 50 // 상품명 최대 길이

void displayMenu() {
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 상품현황\n");
    printf("4. 상품명 입력\n");
    printf("5. 종료\n");
    printf("> 원하는 메뉴를 선택하세요: ");
}

void displayInventory(char names[][MAX_NAME_LEN], int inventory[], int sales[], int stock[]) {
    int totalSales = 0;
    float totalStock = 0;

    printf("\n[상품 현황]\n");
    printf("ID\t상품명\t\t재고\t판매량\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%d\t%-10s\t%d\t%d\n", i + 1, names[i], inventory[i], sales[i]);
        totalSales += sales[i];
        totalStock += stock[i];
    }

    float salesRate = (totalStock > 0) ? (totalSales / totalStock) * 100 : 0;
    printf("\n총 판매량: %d (판매율: %.2f%%)\n", totalSales, salesRate);

    // 부족 재고 경고
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (inventory[i] <= 2) {
            printf("상품 ID %d (%s): 재고 부족 (%d)\n", i + 1, names[i], inventory[i]);
        }
    }
}

int main() {
    char names[MAX_PRODUCTS][MAX_NAME_LEN] = {"미지정", "미지정", "미지정", "미지정", "미지정"}; // 상품명 초기화
    int stock[MAX_PRODUCTS] = {0};     // 입고 수량
    int sales[MAX_PRODUCTS] = {0};    // 판매 수량
    int inventory[MAX_PRODUCTS] = {0}; // 재고 수량

    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // 입고
                int subChoice;
                printf("\n입고수량 입력: 전체(1), 개별(2) 선택: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) { // 전체 상품 입고
                    printf("전체 상품 입고 수량 입력: ");
                    for (int i = 0; i < MAX_PRODUCTS; i++) {
                        scanf("%d", &stock[i]);
                        inventory[i] += stock[i];
                    }
                } else if (subChoice == 2) { // 개별 상품 입고
                    int id, qty;
                    printf("상품 ID 입력: ");
                    scanf("%d", &id);
                    if (id < 1 || id > MAX_PRODUCTS) {
                        printf("유효하지 않은 상품 ID입니다.\n");
                        break;
                    }
                    printf("입고 수량 입력: ");
                    scanf("%d", &qty);
                    stock[id - 1] += qty;
                    inventory[id - 1] += qty;
                } else {
                    printf("잘못된 선택입니다.\n");
                }
                break;
            }

            case 2: { // 판매
                int subChoice;
                printf("\n판매수량 입력: 전체(1), 개별(2) 선택: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) { // 전체 상품 판매
                    printf("전체 상품 판매 수량 입력: ");
                    for (int i = 0; i < MAX_PRODUCTS; i++) {
                        int qty;
                        scanf("%d", &qty);
                        if (qty > inventory[i]) {
                            printf("상품 ID %d (%s): 판매 수량이 재고를 초과합니다.\n", i + 1, names[i]);
                        } else {
                            sales[i] += qty;
                            inventory[i] -= qty;
                        }
                    }
                } else if (subChoice == 2) { // 개별 상품 판매
                    int id, qty;
                    printf("상품 ID 입력: ");
                    scanf("%d", &id);
                    if (id < 1 || id > MAX_PRODUCTS) {
                        printf("유효하지 않은 상품 ID입니다.\n");
                        break;
                    }
                    printf("판매 수량 입력: ");
                    scanf("%d", &qty);
                    if (qty > inventory[id - 1]) {
                        printf("상품 ID %d (%s): 판매 수량이 재고를 초과합니다.\n", id, names[id - 1]);
                    } else {
                        sales[id - 1] += qty;
                        inventory[id - 1] -= qty;
                    }
                } else {
                    printf("잘못된 선택입니다.\n");
                }
                break;
            }

            case 3: { // 상품 현황
                displayInventory(names, inventory, sales, stock);
                break;
            }

            case 4: { // 상품명 입력
                printf("\n[상품명 입력]\n");
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    printf("ID %d 상품명: ", i + 1);
                    scanf("%s", names[i]);
                }
                break;
            }

            case 5: { // 종료
                printf("프로그램을 종료합니다.\n");
                break;
            }

            default:
                printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    } while (choice != 5);

    return 0;
}

