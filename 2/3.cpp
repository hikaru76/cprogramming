#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char[32] word;

typedef struct {
    int size;  // 現在の配列の要素数
    int length;  // メモリが確保されている要素数
    word *data;  // 配列の本体
} array_list;

void array_list_init(array_list *list) {
    int init_size = 4;
    list->data = (word*)malloc(sizeof(word) * init_size);
    list->size = 0;
    list->length = init_size;
}

void array_list_add(array_list *list, word item) {
    if (list->size >= list->length) {
        // 2倍の大きさの配列を確保
        word *new_data = (word*)malloc(list->length * 2 * sizeof(word));
        // データを移行する
        memcpy(new_data, list->data, list->length * sizeof(word));
        // メモリの解放
        free(list->data);
        // ポインタの付け替え
        list->data = new_data;
        list->length *= 2;
    }

    // 文字列は = ではコピーできないことに注意する
    memcpy(list->data[list->size], item, sizeof(word));
    list->size += 1;
}

void array_list_free(array_list *list) {
    free(list->data);
    list->size = 0;
    list->length = 0;
}

int main() {
    array_list list;
    array_list_init(&list);

    word w;
    for (;;) {
        bool valid = true;
        printf("next word?\n");
        scanf("%s", w);

        if (strlen(w) == 0)
		{
			printf("Please input word\n");
			continue ;
		}

        // 単語が「n」で終わっていたら終了
        if (w[strlen(w) - 1] == 'n')
		{
			printf("your word \"%s\" ended with \"n\"", w);
			break ;
		}

        if (list.size > 0) {
            if (list.data[list.size][strlen(list.data[list.size] - 1)] != w[strlen(w) - 1])
			{
				printf("please input correct word\n");
				continue;
			} 
        }

        // 同じ単語がないか？
        for (int i = 0; i < list.size; i++)
		{
			if (strcmp(list.data[i], w) == 0)
			{
				printf("please input correct word\n");
				continue;
			}
		}

        // 単語を追加
        array_list_add(&list, w);        

        // しりとりが上手くいかなければループを抜ける
        if (!valid) {
            break;
        }
    }

    printf("WORDS: ");
    for (int i = 0; i < list.size; i++) {
        printf("%s", list.data[i]);
        if (i != list.size - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    // メモリ解放
    array_list_free(&list);
}