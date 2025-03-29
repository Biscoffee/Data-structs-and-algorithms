bool backspaceCompare(string s, string t) {
    int i = s.length() - 1, j = t.length() - 1;
    int skipS = 0, skipT = 0;

    while (i >= 0 || j >= 0) {
        // 处理 s 的退格
        while (i >= 0) {
            if (s[i] == '#') {
                skipS++;
                i--;
            } else if (skipS > 0) {
                skipS--;
                i--;
            } else {
                break;
            }
        }
        // 处理 t 的退格
        while (j >= 0) {
            if (t[j] == '#') {
                skipT++;
                j--;
            } else if (skipT > 0) {
                skipT--;
                j--;
            } else {
                break;
            }
        }
        // 比较字符
        if (i >= 0 && j >= 0) {
            if (s[i] != t[j]) {
                return false;
            }
        } else if (i >= 0 || j >= 0) {
            return false;
        }
        i--;
        j--;
    }
    return true;
}