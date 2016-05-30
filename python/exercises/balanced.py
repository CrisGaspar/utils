class Parentheses:
    openParens = {
        '(' : '',
        '[': '',
        '{': ''
    }
    closeParens = {
        ')': '(',
        ']': '[',
        '}': '{'
    }

    def mismatch(self, s):
        unmatchedOpenParens = []

        for ch in s:
            if ch in self.openParens:
                unmatchedOpenParens.append(ch)
            elif ch in self.closeParens:
                if len(unmatchedOpenParens) == 0:
                    # found mismatch
                    return "NO"
                lastUnmatched = unmatchedOpenParens.pop()
                if lastUnmatched != self.closeParens[ch]:
                    # found mismatch
                    return "NO"

        if len(unmatchedOpenParens) == 0:
            return "YES"
        else:
            return "NO"


def braces(values):
    parens = Parentheses()
    res = []
    i = 0
    for v in values:
        res.insert(i, parens.mismatch(v))
        i += 1
    return res

if __name__ == "__main__":
    input = [
        "a(b[c(d[f][[g]])h]i)j[",
        "([]{()}())"
    ]
    output = braces(input)
    assert(output[0] == "NO")
    assert(output[1] == "YES")

