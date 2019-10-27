#include <stdio.h>
#include <stdlib.h>

typedef struct list_s {
    char *name;
    char *creator;
    char *license;
    float rating;
    int value;
    struct list_s *next;
} list;

list *crtlst(char *name, char *creator, char *license, const float rating, const int value) {
    list *lst = malloc(sizeof(list));

    *lst = (list){ name, creator, license, rating, value, NULL };

    FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "w+");
    fprintf(fp, "[created]\t [0] %s, %s, %s, %.2f, %i\n", name, creator, license, rating, value);
    fclose(fp);

    return lst;
}

list *findlst(list *lst, const char *name) {
    list *cur = lst;

    int i = 0;
    while (cur != NULL) {
        if (cur->name == name) {
            FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
            fprintf(fp, "[finded]\t [%i] %s, %s, %s, %.2f, %i\n", i, cur->name, cur->creator, cur->license, cur->rating, cur->value);
            fclose(fp);
            return cur;
        }

        i++;
        cur = cur->next;
    }

    return cur;
}

void pushlst(list *lst, char *name, char *creator, char *license, float rating, int value) {
    list *cur = lst;
    int i = 0;
    while (cur->next != NULL) {
        i++;
        cur = cur->next;
    }

    cur->next = malloc(sizeof(list));
    *(cur->next) = (list){ name, creator, license, rating, value, NULL };

    FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
    fprintf(fp, "[added]\t\t [%i] %s, %s, %s, %.2f, %i\n", ++i, name, creator, license, rating, value);
    fclose(fp);
}

void printlst(list *lst) {
    list *cur = lst;
    int i = 0;
    while (cur != NULL) {
        FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
        printf("[%i] %s, %s, %s, %.2f, %i\n", i++, cur->name, cur->creator, cur->license, cur->rating, cur->value);
        fprintf(fp, "[print]\t\t [%i] %s, %s, %s, %.2f, %i\n", i - 1, cur->name, cur->creator, cur->license, cur->rating, cur->value);
        fclose(fp);
        cur = cur->next;
    }
}

void modifylst(list *lst, const int idx, char *name, char *creator, char *license, const float rating, const int value) {
    int i = 0;
    while (lst != NULL) {
        if (i++ == idx) {
            lst->name = name;
            lst->creator = creator;
            lst->license = license;
            lst->rating = rating;
            lst->value = value;

            FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
            fprintf(fp, "[modified]\t [%i] %s, %s, %s, %.2f, %i\n", i - 1, name, creator, license, rating, value);
            fclose(fp);
        }

        lst = lst->next;
    }
}

void deletelst(list **lst, int idx) {
    list *cur;
    if (idx == 0 && *lst != NULL && (*lst)->next != NULL) {
        cur = *lst;
        FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
        fprintf(fp, "[deleted]\t [%i] %s, %s, %s, %.2f, %i\n", idx, (*lst)->name, (*lst)->creator, (*lst)->license, (*lst)->rating, (*lst)->value);
        fclose(fp);
        *lst = (*lst)->next;
        free(cur);

        return;
    }

    int i = 0;
    while (*lst != NULL) {
        if (i == (idx - 1)) {
            cur = *lst;
            FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
            fprintf(fp, "[deleted]\t [%i] %s, %s, %s, %.2f, %i\n", idx, (*lst)->next->name, (*lst)->next->creator, (*lst)->next->license, (*lst)->next->rating, (*lst)->next->value);
            fclose(fp);
            free((*lst)->next);
            (*lst)->next = cur->next->next;
            free(cur->next);
            *lst = (*lst)->next;
        } else *lst = (*lst)->next;

        i++;
    }
}

void swaplst(list *lst, list *lst2) {
    list buf = *lst;
    lst->name = lst2->name;
    lst->creator = lst2->creator;
    lst->license = lst2->license;
    lst->rating = lst2->rating;
    lst->value = lst2->value;

    lst2->name = buf.name;
    lst2->creator = buf.creator;
    lst2->license = buf.license;
    lst2->rating = buf.rating;
    lst2->value = buf.value;
}

void sortlst(list *lst) {
    list *p1 = lst, *p2 = 0;
    for(p2 = lst; p2; p2 = p2->next)
        for(p1 = lst; p1->next; p1 = p1->next)
            if(p1->rating < p1->next->rating) swaplst(p1, p1->next);

    int i = 0;
    while (lst != NULL) {
        FILE *fp = fopen("C:\\Users\\Kolya\\Desktop\\test4.txt", "a+");
        fprintf(fp, "[sorted]\t [%i] %s, %s, %s, %.2f, %i\n", i++, lst->name, lst->creator, lst->license, lst->rating, lst->value);
        fclose(fp);
        lst = lst->next;
    }
}

int main(){
    list *fuck_you = crtlst("Visual Studio Code", "Microsoft", "GNU", 4.8, 14000);
    pushlst(fuck_you, "Atom", "GitHub", "MIT", 4.9, 0);
    pushlst(fuck_you, "Sublime Text 3", "I don't know", "GNU", 4.7, 3400);
    pushlst(fuck_you, "Random Name", "Test", "MIT", 4.8, 2550);
    pushlst(fuck_you, "Same Random", "Same test", "MIT", 4.8, 2830);

    findlst(fuck_you, "Same Random");
    deletelst(&fuck_you, 0);
    printlst(fuck_you);
    printf("\n");

    modifylst(fuck_you, 2, "badcode", "ya", "MIT", 0.0, 0);
    sortlst(fuck_you);
    printlst(fuck_you);

    return 0;
}
