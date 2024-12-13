/**   前缀函数（KMP）
 *    2023-11-17: https://qoj.ac/submission/253754
 *    2024-04-09: https://qoj.ac/submission/384408 【模板】
 **/
std::vector<int> kmp(std::string pattern)
{
    int patternLength = pattern.size();
    std::vector<int> next(patternLength + 1);
    for (int i = 1, j = 0; i < patternLength; i++)
    {
        while (j && pattern[i] != pattern[j])
        {
            j = next[j];
        }
        j += (pattern[i] == pattern[j]);
        next[i + 1] = j;
    }
    return next;
}