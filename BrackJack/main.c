#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int trump(void);
void poker(void);
void bingo(void);
void blackjack(void);
int blackt(void);

int money=100;
FILE *FP;
char fname[50];


int main()
{
    int money = 100;
    
    printf("あなたの所持金は%dです\n", money);
    
    blackjack();
    return 0;
}

//順番に並べたトランプをランダムにシャッフルする関数
int trump(void) {
    int trump[52] = { '\0' };
    int ans = 0;
    int i, j;
    int k = 1;
    int n = 1;
    int t;
    static int count = 0;
    srand(time(NULL));
    
    //trump[52]にトランプを用意
    for (i = 0;i < 52;i++) {
        j = k * 100 + n;
        trump[i] = j;
        n++;
        if (j % 100 == 13) {
            k++;
            n = 1;
        }
    }
    
    //シャッフル
    for (i = 0;i < 52;i++) {
        j = rand() % 52;
        t = trump[i];
        trump[i] = trump[j];
        trump[j] = t;
    }
    
    ans = trump[count];
    
    count++;
    if (count == 52) {
        count = 0;
    }
    return ans;
}

//J,Q,Kをブラックジャックのルールに従って10としてカウントするための関数
int blackt(void)
{
    int ans;
    ans = trump() % 100;
    if (ans > 10)
    {
        ans = 10;
    }
    return ans;
}

//ブラックジャックを行う関数
void blackjack(void)
{
    int ch;
    int n = 1;
    int win = 0;
    int ycs = 0;
    int dcs = 0;
    char hs[5] = { '\0' };
    int ok = 0;
    int tip;
    int temp;
    char dmy[5] = { '\0' };
    
    do
    {
        printf("ブラックジャックを開始します\n");
        win = 2;
        ycs = 0;
        dcs = 0;
        ok = 1;
        tip = 0;
        temp = 0;
        
        printf("**********************\n");
        printf("Game Start! #%d\n", n);
        n++;
        
        do
        {
            //掛け金の入力
            printf("掛け金を入力してください>");
            scanf("%d", &tip);
            fgets(dmy,5,stdin);
            if (tip <= money)ok = 0;
            else
            {
                printf("Please one more\n");
                ok = 1;
            }
        } while (ok != 0);
        money -= tip;
        ycs += blackt() + blackt();
        dcs += blackt() + blackt();
        printf("Dealer's Card%4d\n", dcs);
        printf("Your Card%4d\n", ycs);
        
        //自分のターン
        do
        {
            //HitかStandか
            printf("Hit or Stand?(h/s)>");
            fgets(hs, 5, stdin); // 入力："123456\n"
            
            char *ln = strchr(hs, '\n'); /* 改行文字を検索 */
            
            if (ln != NULL) { /* 改行が読み取られていたかどうか */
                *ln = '\0';    /* 改行文字を終端文字に置き換える */
            }
            else {            /* 入力ストリーム上に文字が残ってる場合 */
                while (1) {    /* 改行文字が読み取られるまで空読みする */
                    int c = getchar();
                    if (c == '\n' || c == EOF) break;
                }
            }
            
            if (strcmp(hs, "h") == 0)
            {
                ycs += blackt();
                ok = 1;
                printf("Your Card%4d\n", ycs);
                //21以上なら負け
                if (ycs > 21)
                {
                    printf("Your Card is Burst!\n");
                    ok = 0;
                }
                else if (ycs == 21)
                {
                    printf("Black Jack!\n");
                    win = 0;
                    ok = 0;
                }
            }
            else if (strcmp(hs, "s") == 0)
            {
                ok = 0;
            }
            else
            {
                ok = 1;
            }
        } while (ok == 1);
        
        //相手のターン(17以上になるまでHitし続ける)
        while (dcs<17)
        {
            dcs += blackt();
            printf("Dealer Hit\n");
            printf("Dealer's Card%4d\n", dcs);
            if (dcs > 21)
            {
                printf("Dealer's Card is Burst!\n");
            }
            else if (dcs >= 17)
            {
                printf("Dealer Stand\n");
            }
        }
        
        //勝利条件
        if (ycs <= 21 && dcs > 21)win = 0;
        else if (ycs > 21 && dcs <= 21)win = 1;
        else if (ycs > 21 && dcs > 21)win = 2;
        else if (ycs > dcs)win = 0;
        else if (ycs < dcs)win = 1;
        else win = 2;
        
        //結果表示
        if (win == 0)
        {
            printf("You win!\n");
            tip *= 2;
            printf("あなたは%d手に入れました\n", tip);
        }
        else if (win == 1)
        {
            printf("You lose!\n");
            tip = 0;
            printf("掛け金を失います\n");
        }
        else
        {
            printf("Draw!\n");
            printf("掛け金は返却されます\n");
        }
        money += tip;
        if (money == 0)
        {
            printf("所持金が0になりました\n終了します\n");
            break;
        }
        
        printf("あなたの所持金は%dです\n", money);
        printf("\n続ける場合はEnter\nやめる場合はそれ以外\n");
    } while ((ch = getchar()) == 10);
    
}
