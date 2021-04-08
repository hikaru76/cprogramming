int main() {
    array_list list;
    array_list_init(&list);

    word w;
    for (;;) {
        bool valid = true;
        printf("next word?\n");
        scanf("%s", w);

        // 単語が空なら単語入力からやり直す
        // ????

        // 単語が「n」で終わっていたら終了
        // ????

        // 最後の単語の最後の文字と新しい単語の最初の文字が一致するか？
        if (list.size > 0) {
            // ????
        }

        // 同じ単語がないか？
        // ????

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