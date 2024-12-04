#include <stdio.h>

#define MAX_PRODUCTS 5

void displayMenu() {
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 상품현황\n");
    printf("4. 종료\n");
    printf("> 원하는 메뉴를 선택하세요: ");
}

void displayInventory(int inventory[], int sales[], int stock[]) {
    int totalSales = 0;
    float totalStock = 0;

    printf("\n[상품 현황]\n");
    printf("재고 수량: ");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("%d ", inventory[i]);
        totalSales += sales[i];
        totalStock += stock[i];
    }
    printf("\n");

    float salesRate = (totalStock > 0) ? (totalSales / totalStock) * 100 : 0;
    printf("총 판매량: %d (판매율: %.2f%%)\n", totalSales, salesRate);

    // 부족 재고 및 판매량 분석
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (inventory[i] <= 2) {
            printf("상품 ID %d: 재고 부족 (%d)\n", i + 1, inventory[i]);
        }
    }
}

int main() {
    int stock[MAX_PRODUCTS] = {0};     // 입고 수량
    int sales[MAX_PRODUCTS] = {0};    // 판매 수량
    int inventory[MAX_PRODUCTS] = {0}; // 재고 수량 (초기값 0)

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
                            printf("상품 ID %d: 판매 수량이 재고를 초과합니다.\n", i + 1);
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
                        printf("상품 ID %d: 판매 수량이 재고를 초과합니다.\n", id);
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
                displayInventory(inventory, sales, stock);
                break;
            }

            case 4: { // 종료
                printf("프로그램을 종료합니다.\n");
                break;
            }

            default:
                printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    } while (choice != 4);

    return 0;
}
