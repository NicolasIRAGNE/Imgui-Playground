#include <greeter/greeter.h>
#include <greeter/version.h>
#include <gtest/gtest.h>


#include <string>

TEST(Greeter, Simple)
{
    using namespace greeter;

    Greeter greeter("Tests");

    EXPECT_EQ(greeter.greet(LanguageCode::EN), "Hello, Tests!");
    EXPECT_EQ(greeter.greet(LanguageCode::DE), "Hallo Tests!");
    EXPECT_EQ(greeter.greet(LanguageCode::ES), "¡Hola Tests!");
    EXPECT_EQ(greeter.greet(LanguageCode::FR), "Bonjour Tests!");
}

TEST(Greeter, Version)
{
    static_assert(std::string_view(GREETER_VERSION) == std::string_view("1.0"));
    EXPECT_EQ(std::string(GREETER_VERSION), std::string("1.0"));
}
