#include <string>
#include "../test_runner.h"
#include <list>

using namespace std;

class Editor {
public:
    Editor() {
        cursor = text.begin();
    }

    void Left() {
        if (cursor != text.begin()) {
            cursor--;
        }
        debugPrint();
    }

    void Right() {
        if (cursor != text.end()) {
            cursor++;
        }
        debugPrint();
    }

    void Insert(char token) {
        text.insert(cursor, token);
        debugPrint();
    }

    void Cut(size_t tokens = 1) {
        buffer.clear();
        list<char>::const_iterator newCursor;
        if (distance(cursor, text.cend()) < tokens) {
            newCursor = text.end();
        } else {
            newCursor = next(cursor, tokens);
        }
        buffer.splice(buffer.begin(), text, cursor, newCursor);
        cursor = newCursor;
        debugPrint();
    }

    void Copy(size_t tokens = 1) {
        buffer.clear();
        list<char>::const_iterator rangeEnd;
        if (distance(cursor, text.cend()) < tokens) {
            rangeEnd = text.end();
        } else {
            rangeEnd = next(cursor, tokens);
        }
        const auto copyCursor = cursor;
        copy(copyCursor, rangeEnd, inserter(buffer, buffer.begin()));
        debugPrint();
    }

    void Paste() {
        for (char& it : buffer) {
            text.insert(cursor, it);
        }
        debugPrint();
    }

    [[nodiscard]] string GetText() const {
        stringstream ss;
        for (const auto &it : text) {
            ss << it;
        }
        return ss.str();
    }

private:
    list<char> text;
    list<char> buffer;
    list<char>::const_iterator cursor;

    void debugPrint() {
//        stringstream ss;
//        for (auto it = text.begin(); it != text.end(); it++) {
//            if (it == cursor) {
//                ss << "|";
//            }
//            ss << *it;
//        }
//        if (text.end() == cursor) {
//            ss << "|";
//        }
//        cout << ss.str() << endl;
    }
};

void TypeText(Editor &editor, const string &text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

void TestPaste() {
    Editor editor;
    TypeText(editor, "1234567");
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Paste();
    editor.Paste();
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "123456667");
}

void TestCopyPasteLastChars() {
    Editor editor;
    TypeText(editor, "happy birthday");
    editor.Left();
    editor.Left();
    editor.Copy(5);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "happy birthdayay");
}

int main() {
    TestRunner tr;

    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    RUN_TEST(tr, TestPaste);
    RUN_TEST(tr, TestCopyPasteLastChars);
    return 0;
}