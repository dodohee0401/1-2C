#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// 상품 정보를 담는 구조체
typedef struct {
    int stock;  // 재고 수량
    int sold;   // 판매 수량
} Product;

Product products[MAX_PRODUCTS];

// 상품의 입고 수량을 한 번에 입력하는 함수
void set_stock(int product_count) {
    printf("각 상품의 입고 수량을 공백으로 구분하여 입력하세요 (예: 8 5 3 4 9):\n");
    
    for (int i = 0; i < product_count; i++) {
        scanf("%d", &products[i].stock);
    }
}

// 판매 수량을 한 번에 입력받아 재고에서 차감하는 함수
void sell_products(int product_count) {
    printf("각 상품의 판매 수량을 공백으로 구분하여 입력하세요 (예: 2 1 0 4 3):\n");
    
    for (int i = 0; i < product_count; i++) {
        int sell_quantity;
        scanf("%d", &sell_quantity);

        if (products[i].stock >= sell_quantity) {
            products[i].stock -= sell_quantity;
            products[i].sold += sell_quantity;
        } else {
            printf("상품 ID %d의 재고가 부족합니다. 현재 재고: %d\n", i + 1, products[i].stock);
        }
    }
}

// 특정 상품의 재고 수량을 출력하는 함수
void get_product_stock(int product_id) {
    if (product_id >= 1 && product_id <= MAX_PRODUCTS) {
        printf("상품 ID %d의 현재 재고: %d\n", product_id, products[product_id - 1].stock);
    } else {
        printf("존재하지 않는 상품 ID입니다.\n");
    }
}

// 전체 재고 수량을 출력하는 함수
void get_total_stock(int product_count) {
    int total_stock = 0;
    for (int i = 0; i < product_count; i++) {
        total_stock += products[i].stock;
    }
    printf("전체 재고 수량: %d\n", total_stock);
}

int main() {
    int product_count;

    // 상품 종류 입력
    printf("상품 종류 개수 (1-100): ");
    scanf("%d", &product_count);

    if (product_count < 1 || product_count > 100) {
        printf("상품 종류는 1에서 100 사이여야 합니다.\n");
        return 1;
    }

    // 상품의 입고 수량 입력 (한 번에)
    set_stock(product_count);

    // 판매 수량 입력 (한 번에)
    sell_products(product_count);

    // 특정 상품의 재고 조회
    while (1) {
        int product_id;
        printf("재고를 확인할 상품 ID (종료: -1): ");
        scanf("%d", &product_id);

        if (product_id == -1) {
            break;
        }

        get_product_stock(product_id);
    }

    // 전체 재고 조회
    get_total_stock(product_count);

    return 0;
}

