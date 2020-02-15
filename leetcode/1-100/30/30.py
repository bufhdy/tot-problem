class Solution:
    def findSubstring(self, s: str, words: [str]) -> [int]:
        ret = []
        unit = len(words[0])
        n, m = len(s), len(words)
        for i in range(n - unit*m + 1):
            words_crt = []
            count = 0
            word = s[i:i+unit]
            while word in words and count < m:
                words_crt.append(word)
                count += 1
                word = s[i+count*unit:i+count*unit+unit]
                
                if count == m: 
                    words_set = set(words_crt)
                    is_matched = True
                    for word in words_set:
                        if words_crt.count(word) != words.count(word):
                            is_matched = False
                            break
                    if is_matched: ret.append(i)
        return ret

s = Solution()
print(s.findSubstring("wordgoodgoodgoodbestword", ["word","good","best","word"]))
