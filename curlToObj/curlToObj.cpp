#include <string>
#include <algorithm>

std::string curlToObject(std::string s) {
    // 删除第一项
    for (int i = 1; i <= 2; i++) {
        int pos = s.find("\'");
        s.erase(0, pos + 1);
    }

    // 需要删除的部分
    std::string cut[] = {"curl", "\\", "-H", "--compressed", "\n"};
    for (int i = 0; i < cut -> length(); i++) {
        int pos = s.find(cut[i]);
        while (pos != std::string::npos) {
            s.erase(pos, cut[i].size());
            pos = s.find(cut[i]);
        }
    }

    // 兼容大多数语言里字符串的格式
    std::replace(s.begin(), s.end(), '\'', '\"');

    // 删尾连空格
    while (s[s.size() - 1] != '\"') {
        s.erase(s.size() - 1, 1);
    }

    // :两边加""和行尾加逗号
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ':') {
            if (s[i + 1] != ' ') continue;
            s.insert(i, "\"");
            s.insert(i + 3, "\"");
            int start = i + 4;
            while (start < s.size() - 1) {
                if (s[start] == '\"') {
                    s.insert(start + 1, ",");
                    break;
                }
                start++;
            }
            i++;
        }
    }


    // 大括号格式化
    s.insert(0, "{");
    s.append("\n");
    s.append("}");

    return s;
}

