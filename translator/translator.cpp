#include "test_runner.h"
#include <string>
#include <set>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        auto srcIt = data.insert(string(source));
        auto trgIt = data.insert(string(target));
        srcToTarget[string_view(*srcIt.first)] = string_view(*trgIt.first);
        targetToSrc[string_view(*trgIt.first)] = string_view(*srcIt.first);
    }
    [[nodiscard]] string_view TranslateForward(string_view source) const {
        auto trgIt = srcToTarget.find(source);
        return trgIt == srcToTarget.end() ? "" : trgIt->second;
    }
    [[nodiscard]] string_view TranslateBackward(string_view target) const {
        auto srcIt = targetToSrc.find(target);
        return srcIt == targetToSrc.end() ? "" : srcIt->second;
    }

private:
    set<string> data;
    map<string_view, string_view> srcToTarget;
    map<string_view, string_view> targetToSrc;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}