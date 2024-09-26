#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// 상품 정보를 담는 구조체
typedef struct {
    int stock;  // 재고 수량
    int sold;   // 판매 수량
    int initial_stock; // 최초 입고 수량
} Product;

Product products[MAX_PRODUCTS];

// 상품의 입고 수량을 한 번에 입력하는 함수
void set_stock(int product_count) {
    printf("각 상품의 입고 수량을 공백으로 구분하여 입력하세요 (예: 8 5 3 4 9):\n");
    
    for (int i = 0; i < product_count; i++) {
        scanf("%d", &products[i].stock);
        products[i].initial_stock = products[i].stock;  // 최초 입고 수량 저장
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

// 전체 판매량을 계산하는 함수
void calculate_total_sales(int product_count) {
    int total_sales = 0;
    for (int i = 0; i < product_count; i++) {
        total_sales += products[i].sold;
    }
    printf("전체 판매량: %d\n", total_sales);
}

// 전체 판매율을 계산하는 함수
void calculate_total_sales_rate(int product_count) {
    int total_sold = 0;
    int total_stock = 0;
    
    for (int i = 0; i < product_count; i++) {
        total_sold += products[i].sold;
        total_stock += products[i].initial_stock;
    }

    if (total_stock > 0) {
        double sales_rate = ((double)total_sold / total_stock) * 100;
        printf("전체 판매율: %.2f%%\n", sales_rate);
    } else {
        printf("판매율을 계산할 수 없습니다 (입고 수량 없음).\n");
    }
}

// 최대 및 최소 판매량을 가진 상품을 출력하는 함수
void find_max_min_sales(int product_count) {
    int max_sales = products[0].sold;
    int min_sales = products[0].sold;
    int max_id = 1;
    int min_id = 1;

    for (int i = 1; i < product_count; i++) {
        if (products[i].sold > max_sales) {
            max_sales = products[i].sold;
            max_id = i + 1;
        }

        if (products[i].sold < min_sales) {
            min_sales = products[i].sold;
            min_id = i + 1;
        }
    }

    printf("최대 판매량 상품: ID %d, 판매량 %d\n", max_id, max_sales);
    printf("최소 판매량 상품: ID %d, 판매량 %d\n", min_id, min_sales);
}

// 재고 부족 경고를 출력하는 함수 (재고가 2 이하일 경우)
void check_low_stock_warning(int product_count) {
    for (int i = 0; i < product_count; i++) {
        if (products[i].stock <= 2) {
            printf("경고: 상품 ID %d의 재고가 %d개 남았습니다!\n", i + 1, products[i].stock);
        }
    }
}

// 각 상품의 재고 수량을 출력하는 함수
void print_each_stock(int product_count) {
    printf("각 상품의 재고 수량:\n");
    for (int i = 0; i < product_count; i++) {
        printf("상품 ID %d: %d개\n", i + 1, products[i].stock);
    }
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

    // 전체 판매량 계산
    calculate_total_sales(product_count);

    // 전체 판매율 계산
    calculate_total_sales_rate(product_count);

    // 최대 및 최소 판매량을 가진 상품 출력
    find_max_min_sales(product_count);

    // 재고 부족 경고 출력
    check_low_stock_warning(product_count);

    // 각 상품의 재고 수량 출력
    print_each_stock(product_count);

    return 0;
}

