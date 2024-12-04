#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LEN 50
#define FILE_NAME "product_data.txt"

// 메뉴 출력 함수
void displayMenu() {
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("1. 상품 추가/수정\n");
    printf("2. 개별 상품 정보\n");
    printf("3. 전체 상품 정보\n");
    printf("4. 상품 정보 저장\n");
    printf("5. 상품 정보 불러오기\n");
    printf("6. 종료\n");
    printf("> 원하는 메뉴를 선택하세요: ");
}

// 개별 상품 정보 출력 함수
void displayProductInfo(int id, char names[][MAX_NAME_LEN], int inventory[], int sales[], int stock[], int price[]) {
    if (id < 1 || id > MAX_PRODUCTS) {
        printf("유효하지 않은 상품 ID입니다.\n");
        return;
    }
    int idx = id - 1; // 배열 인덱스는 0부터 시작
    int revenue = sales[idx] * price[idx]; // 총 판매 금액 계산

    printf("\n[상품 정보]\n");
    printf("상품 ID: %d\n", id);
    printf("상품명: %s\n", names[idx]);
    printf("상품 가격: %d\n", price[idx]);
    printf("입고량: %d\n", stock[idx]);
    printf("판매량: %d\n", sales[idx]);
    printf("재고량: %d\n", inventory[idx]);
    printf("총 판매 금액: %d\n", revenue);
}

// 전체 상품 정보 출력 함수
void displayAllProducts(char names[][MAX_NAME_LEN], int inventory[], int sales[], int stock[], int price[]) {
    int totalSales = 0;
    int totalRevenue = 0;
    float totalStock = 0;

    printf("\n[전체 상품 정보]\n");
    printf("ID\t상품명\t\t가격\t입고량\t판매량\t재고\t판매 금액\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        int revenue = sales[i] * price[i];
        totalSales += sales[i];
        totalRevenue += revenue;
        totalStock += stock[i];
        printf("%d\t%-10s\t%d\t%d\t%d\t%d\t%d\n", i + 1, names[i], price[i], stock[i], sales[i], inventory[i], revenue);
    }

    float salesRate = (totalStock > 0) ? (totalSales / totalStock) * 100 : 0;
    printf("\n총 판매량: %d\n", totalSales);
    printf("총 판매율: %.2f%%\n", salesRate);
    printf("총 판매 금액: %d\n", totalRevenue);
}

// 상품 정보를 파일에 저장
void saveToFile(char names[][MAX_NAME_LEN], int inventory[], int sales[], int stock[], int price[]) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        fprintf(file, "%s %d %d %d %d\n", names[i], price[i], stock[i], sales[i], inventory[i]);
    }
    fclose(file);
    printf("상품 정보가 '%s' 파일에 저장되었습니다.\n", FILE_NAME);
}

// 파일에서 상품 정보를 불러오기
void loadFromFile(char names[][MAX_NAME_LEN], int inventory[], int sales[], int stock[], int price[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다. 저장된 데이터가 없을 수 있습니다.\n");
        return;
    }

    for (int i = 0; i < MAX_PRODUCTS; i++) {
        fscanf(file, "%s %d %d %d %d", names[i], &price[i], &stock[i], &sales[i], &inventory[i]);
    }
    fclose(file);
    printf("상품 정보가 파일에서 불러와졌습니다.\n");
}

int main() {
    char names[MAX_PRODUCTS][MAX_NAME_LEN] = {"미지정", "미지정", "미지정", "미지정", "미지정"};
    int stock[MAX_PRODUCTS] = {0};     // 입고 수량
    int sales[MAX_PRODUCTS] = {0};    // 판매 수량
    int inventory[MAX_PRODUCTS] = {0}; // 재고 수량
    int price[MAX_PRODUCTS] = {0};    // 상품 가격

    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // 상품 추가/수정
                int id, qty, prc;
                char name[MAX_NAME_LEN];

                printf("\n상품 ID를 입력하세요 (1 ~ %d): ", MAX_PRODUCTS);
                scanf("%d", &id);
                if (id < 1 || id > MAX_PRODUCTS) {
                    printf("유효하지 않은 상품 ID입니다.\n");
                    break;
                }

                printf("상품명을 입력하세요: ");
                scanf("%s", name);
                printf("상품 가격을 입력하세요: ");
                scanf("%d", &prc);
                printf("입고 수량을 입력하세요: ");
                scanf("%d", &qty);

                // 상품 정보 업데이트
                strcpy(names[id - 1], name);
                price[id - 1] = prc;
                stock[id - 1] += qty;
                inventory[id - 1] += qty;
                break;
            }

            case 2: { // 개별 상품 정보
                int id;
                printf("\n상품 ID를 입력하세요 (1 ~ %d): ", MAX_PRODUCTS);
                scanf("%d", &id);
                displayProductInfo(id, names, inventory, sales, stock, price);
                break;
            }

            case 3: { // 전체 상품 정보
                displayAllProducts(names, inventory, sales, stock, price);
                break;
            }

            case 4: { // 상품 정보 저장
                saveToFile(names, inventory, sales, stock, price);
                break;
            }

            case 5: { // 상품 정보 불러오기
                loadFromFile(names, inventory, sales, stock, price);
                break;
            }

            case 6: { // 종료
                printf("프로그램을 종료합니다.\n");
                break;

            default:
                printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    } while (choice != 6);

    return 0;
}
