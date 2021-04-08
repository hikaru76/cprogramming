#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef char word[32];

typedef struct list_node_ {
    word value;
    struct list_node_ *next;
} list_node;

typedef struct {
    int size;
    list_node *root;
} linked_list;

list_node *create_node(word w) {
    // メモリの確保
    list_node *node = (list_node*)malloc(sizeof(list_node));
    // 値をノードにコピーする
    memcpy(node->value, w, sizeof(word));
    // 次のノードへのポインタはまだない
    node->next = NULL;

    return node;
}

void linked_list_init(linked_list *list) {
    list->size = 0;
    list->root = NULL;
}

void linked_list_add(linked_list *list, word w) {
    // 新しい要素を作成して、値をコピーする
    list_node *new_node = create_node(w);
    
    // 終端の要素を探して、値を設定後、ポインタを付け替える
    if (list->root == NULL) {
        list->root = new_node;
    } else {
        list_node *node = list->root;
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = new_node;
    }
    list->size += 1;
}

void linked_list_remove(linked_list *list, word w) {
    if (list->root == NULL) {
        // 要素が存在しない
        return;
    }

    if (strcmp(list->root->value, w) == 0) {
        // 最初の要素を削除するならrootを置き換える
        list_node *rem = list->root;
        list->root = list->root->next;
        list->size = 0;
        free(rem);
        return;
    }

    list_node *node = list->root;    
    while (node->next != NULL) {
        // 次の要素が該当の値を持つかをチェック
        if (strcmp(node->next->value, w) == 0) {
            // ポインタを付け替える
            list_node *rem = node->next;
            node->next = node->next->next;
            free(rem);
            list->size -= 1;
            break;
        }
        node = node->next;
    }
}

void linked_list_free(linked_list *list) {
    list_node *node = list->root;
    while (node != NULL) {
        // 処理の順番に注意すること
        list_node *curr = node;
        node = node->next;
        free(curr);
    }
}

char *linked_list_last(linked_list *list) {
	int i;
	list_node *tmp;

	i = -1;
	tmp = list->root;
	while (++i < list->size - 1)
		tmp = tmp->next;
	return (tmp->value);
}

int	main(void)
{
	linked_list *list;
	list = (linked_list *)malloc(sizeof(linked_list));
	linked_list_init(list);

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
			printf("ERROR: your word \"%s\" ended with \"n\"\n", w);
			break ;
		}

        if (list->size > 0) {
            if (linked_list_last(list)[strlen(linked_list_last(list)) - 1] != w[0])
			{
				printf("wrong word\n");
				continue;
			} 
        }

        // 同じ単語がないか？
		list_node *tmp;
		tmp = list->root;
        for (int i = 0; i < list->size; i++)
		{
			if (strcmp(tmp->value, w) == 0)
				linked_list_remove(list, w);
			tmp = tmp->next;
		}

        // 単語を追加
        linked_list_add(list, w);

        // しりとりが上手くいかなければループを抜ける
        if (!valid) {
            break;
        }
    }

    printf("WORDS: ");
	list_node *tmp = list->root;
    for (int i = 0; i < list->size; i++) {
        printf("%s", tmp->value);
        if (i != list->size - 1) {
            printf(" -> ");
        }
		tmp = tmp->next;
    }
	printf(" -> %s", w);
    printf("\n");

    // メモリ解放
	linked_list_free(list);
}
