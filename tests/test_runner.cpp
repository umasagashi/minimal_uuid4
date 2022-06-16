#include <set>

#include "acutest.h"
#include "minimal_uuid4.h"

using namespace minimal_uuid4;

#define REPEAT for (int i = 0; i < 1000; i++)

#define REPEAT_TEST(name, cond) \
    void name() { \
        REPEAT { \
            Generator gen; \
            cond; \
        } \
    } \
    void name##_reuse() { \
        Generator gen; \
        REPEAT { cond; } \
    }

std::set<char> hex_chars() {
    const std::string t = "0123456789abcdef";
    return {t.begin(), t.end()};
}

std::set<char> variant_chars() {
    const std::string t = "8";
    return {t.begin(), t.end()};
}

void test_chars_used(const char &ch, const std::set<char> &candidates) {
    TEST_ASSERT(candidates.find(ch) != candidates.end());
}

void test_chars_used(const std::string &str, const std::set<char> &candidates) {
    for (const char &ch : str) {
        test_chars_used(ch, candidates);
    }
}

REPEAT_TEST(test_call, {
    const auto &uuid = gen.uuid4();
    TEST_ASSERT(!uuid.hex().empty());
    TEST_ASSERT(!uuid.str().empty());
})

REPEAT_TEST(test_hex_length, { TEST_ASSERT(gen.uuid4().hex().length() == 32); })

REPEAT_TEST(test_hex_chars_used, { test_chars_used(gen.uuid4().hex(), hex_chars()); })

REPEAT_TEST(test_hex_version, { TEST_CHECK(gen.uuid4().hex()[12] == '4'); })

REPEAT_TEST(test_hex_variant, { test_chars_used(gen.uuid4().hex()[16], variant_chars()); })

REPEAT_TEST(test_str_length, { TEST_ASSERT(gen.uuid4().str().length() == 32 + 4); })

REPEAT_TEST(test_str_chars_used, {
    const auto uuid = gen.uuid4().str();
    test_chars_used(uuid.substr(0, 8), hex_chars());
    test_chars_used(uuid.substr(8 + 1, 4), hex_chars());
    test_chars_used(uuid.substr(12 + 2, 4), hex_chars());
    test_chars_used(uuid.substr(16 + 3, 4), hex_chars());
    test_chars_used(uuid.substr(20 + 4, 12), hex_chars());
    TEST_CHECK(uuid[8] == '-');
    TEST_CHECK(uuid[12 + 1] == '-');
    TEST_CHECK(uuid[16 + 2] == '-');
    TEST_CHECK(uuid[20 + 3] == '-');
})

REPEAT_TEST(test_str_version, { TEST_CHECK(gen.uuid4().str()[12 + 2] == '4'); })

REPEAT_TEST(test_str_variant, { test_chars_used(gen.uuid4().str()[16 + 3], variant_chars()); })

#define DUPLICATION_TEST(name, map) \
    void name() { \
        std::set<std::string> history; \
        REPEAT { \
            Generator gen; \
            const auto &uuid = map(gen); \
            TEST_ASSERT(history.find(uuid) == history.end()); \
            history.insert(uuid); \
        } \
    } \
    void name##_reuse() { \
        std::set<std::string> history; \
        Generator gen; \
        REPEAT { \
            const auto &uuid = map(gen); \
            TEST_ASSERT(history.find(uuid) == history.end()); \
            history.insert(uuid); \
        } \
    }

DUPLICATION_TEST(test_hed_duplication, [](Generator &gen) { return gen.uuid4().hex(); })

DUPLICATION_TEST(test_str_duplication, [](Generator &gen) { return gen.uuid4().str(); })

#define TEST_FUNC(func) \
    { \
#func, func \
    }

#define TEST_FUNC_REPEAT(func) TEST_FUNC(func), TEST_FUNC(func##_reuse)

TEST_LIST = {
    TEST_FUNC_REPEAT(test_call),

    TEST_FUNC_REPEAT(test_hex_length),
    TEST_FUNC_REPEAT(test_hex_chars_used),
    TEST_FUNC_REPEAT(test_hex_version),
    TEST_FUNC_REPEAT(test_hex_variant),
    TEST_FUNC_REPEAT(test_hed_duplication),

    TEST_FUNC_REPEAT(test_str_length),
    TEST_FUNC_REPEAT(test_str_chars_used),
    TEST_FUNC_REPEAT(test_str_version),
    TEST_FUNC_REPEAT(test_str_variant),
    TEST_FUNC_REPEAT(test_str_duplication),

    {nullptr, nullptr},
};
