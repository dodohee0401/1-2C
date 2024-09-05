#include <stdio.h>

#define MAX_ITEMS 100

int main() {
    int total_items;                  // 상품의 총 종류 수
    int stock[MAX_ITEMS] = {0};       // 각 상품의 입고 수량
    int sales[MAX_ITEMS] = {0};       // 각 상품의 판매 수량
    int inventory[MAX_ITEMS] = {0};   // 각 상품의 재고 수량
    int item_id;                      // 조회할 상품 ID

    // 상품의 종류 입력
    printf("상품의 종류를 입력하세요 (1-100): ");
    scanf("%d", &total_items);

    // 각 상품의 입고 수량 입력
    printf("\n각 상품의 입고 수량을 입력하세요:\n");
    for (int i = 0; i < total_items; i++) {
        printf("상품 ID %d의 입고 수량: ", i + 1);
        scanf("%d", &stock[i]);
        inventory[i] = stock[i];  // 초기 재고 수량 설정
    }

    // 각 상품의 판매 수량 입력
    printf("\n각 상품의 판매 수량을 입력하세요:\n");
    for (int i = 0; i < total_items; i++) {
        printf("상품 ID %d의 판매 수량: ", i + 1);
        scanf("%d", &sales[i]);
        inventory[i] -= sales[i];  // 판매된 만큼 재고에서 차감
    }

    // 조회할 상품의 재고 수량 출력
    printf("\n조회할 상품의 ID를 입력하세요 (1-%d): ", total_items);
    scanf("%d", &item_id);

    // 입력한 ID의 재고 수량 출력
    if (item_id >= 1 && item_id <= total_items) {
        printf("\n상품 ID %d의 재고 수량: %d\n", item_id, inventory[item_id - 1]);
    } else {
        printf("\n잘못된 상품 ID입니다.\n");
    }

    // 모든 상품의 각자 재고 수량 출력
    printf("\n모든 상품의 재고 수량:\n");
    for (int i = 0; i < total_items; i++) {
        printf("상품 ID %d의 재고 수량: %d\n", i + 1, inventory[i]);
    }

    // 전체 재고 수량 계산 및 출력
    int total_inventory = 0;
    for (int i = 0; i < total_items; i++) {
        total_inventory += inventory[i];
    }
    printf("\n전체 재고 수량: %d\n", total_inventory);

    return 0;
}
