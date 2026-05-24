#include "expense.h"

static void kmp_build_failure(const char *pattern, int m, int *fail) {
    fail[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i])
            k = fail[k - 1];
        if (pattern[k] == pattern[i]) k++;
        fail[i] = k;
    }
}

static int kmp_search(const char *text, const char *pattern) {
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    if (m == 0) return 0;

    int fail[MAX_KEYWORD];
    kmp_build_failure(pattern, m, fail);

    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i])
            q = fail[q - 1];
        if (pattern[q] == text[i]) q++;
        if (q == m) return 1; 
    }
    return 0;
}
