#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10 // ハッシュ表の大きさ

typedef char KEY; // キーの型

/* データ部（キー以外）のフィールド */
typedef struct data
{
    int value;
} DATA;

/* データ一つを表すレコード */
typedef struct record
{
    KEY key;
    DATA data;
    struct record *next;
} RECORD;

/* グローバル変数 */
RECORD *table[BUCKET_SIZE];

/*ハッシュ表の初期化*/
void init()
{
    int i;
    for (i = 0; i < BUCKET_SIZE; i++)
        table[i] = NULL;
}

/*ハッシュ関数*/
int hash(KEY key)
{
    return key % 10;
}

/*key1とkey2が等しいかどうか。等しいなら１, 等しくないなら０を返す*/
int keyequal(KEY key1, KEY key2)
{
    return key1 == key2;
}

DATA *search(KEY key)
{
    RECORD *p;
    int index;

    index = hash(key); // keyのハッシュ値を求める

    /*連結リストをたどる*/
    for (p = table[index]; p != NULL; p = p->next)
    {
        if (keyequal(key, p->key))
            return &p->data; // 発見=>DATAへのポインタを返す
    }
    return NULL; // 見つからない時にはNULLを返す
}

int add(RECORD record)
{
    RECORD *p;
    int index;

    if (search(record.key) != NULL)
    {
        return -1;
    }

    p = (RECORD *)malloc(sizeof(RECORD));
    if (p == NULL)
    {
        perror("out of memory.\n");
        exit(1); // プログラムを強制終了
    }

    /*ハッシュ関数でrecord.keyのハッシュ値を求める*/
    index = hash(record.key);

    p->key = record.key;
    p->data = record.data;

    /* table[index]に新しく作成したレコードを挿入する*/
    p->next = table[index];
    table[index] = p;

    return 0;
}

int del(KEY key)
{
    RECORD *current, *previous;
    int index;

    index = hash(key);

    // ハッシュ値が指すバケット
    current = table[index];

    previous = NULL;

    // ハッシュ値のバケットから伸びてる連結リストが尽きるまで
    while (current != NULL)
    {
        if (keyequal(key, current->key))
        {
            if (previous == NULL)
            {
                // キーが先頭でみつかったらtable[index]が次のやつにうつす
                table[index] = current->next;
            }
            else
            {
                // キーが先頭以外でみつかったら一つ前にずらす
                previous->next = current->next;
            }

            free(current);
            return 0; // 削除成功
        }
        previous = current;
        current = current->next;
    }
    return -1; // 削除対象のキーが見つからない場合
}

void createMap(char P[], int length)
{
    int i = 0;

    for (i = 0; i < length; i++)
    {
        if (search(P[i]) == NULL)
        {
            DATA data;
            data.value = length - i - 1;

            RECORD record;
            record.key = P[i];
            record.data = data;
            add(record);
        }
    }
}

int main()
{
    // テキスト
    char T[] = "she sells sea shells on the sea shore";
    // パターン
    char *P = "shell";
    char *P_k = "shel"; // 文字の種類

    int n = 38;          // テキストの文字数
    int m = 5;           // パターンの文字数
    int charKindNum = 9; // テキスト中の文字の種類数

    char S[charKindNum]; // スキップテーブル

    int i = 0; // テキストに対して照合を行う位置の先頭
    int j = 0; // パターンに対して照合を行う位置
    int times = 0;
    int charLength = 0;

    init();

    createMap(P, m);

    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        RECORD *p = table[i];
        while (p != NULL)
        {
            printf("Key: '%c', Value: %d\n", p->key, p->data.value);
            p = p->next;
        }
    }

    // テキスト中のすべての文字について配列Sの値をmに初期化する
    for (i = 0; i < charKindNum; i++)
    {
        S[i] = m;
    }

    // S[i] を探してsearch関数を呼び出す
    for (i = 0; i < m - 1; i++)
    {
        DATA *data = search(S[i]); // searchの結果を一時変数に保存
        if (data != NULL)
        { // NULLチェック
            printf("S[%c] = %d\n", i, data->value);
        }
        else
        {
            printf("S[%c] = Not Found\n", i);
        }
    }

    /* for (i = 0; i < m; i++)
       printf("S[%c] = %d\n", i, S[i]);*/

    while (i < n - m + 1)
    {
        j = m - 1;
        while (T[i + j] == P[j] && j >= 0)
            j--;
        if (j < 0)
        {
            printf("%d\n", i);
            i += m;
        }
        else
        {
            DATA *data = search(T[i + j]);
            if (data != NULL)
            { // NULLチェック
                i = i + data->value;
            }
            else
            {
                i++; // デフォルトのスキップ量
            }
        }
    }

    return 0;
}