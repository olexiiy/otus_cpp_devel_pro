#include "timer.h"

#include <chrono>
#include <iostream> //Для вывода
#include <string_view>

Timer::Timer()
    : m_beg(clock_t::now())
{
}
void Timer::reset()
{
    m_beg = clock_t::now();
}

double Timer::elapsed_ms() const
{
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count() * 1000;
}

double Timer::elapsed_ml() const
{
    return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count() * 1000 * 1000;
}

void Timer::print_sec()
{
    auto ii{ std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count() };
    std::cout << ii << " seconds\n";
}

void Timer::print_milli()
{
    auto ii{ std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count() * 1000 };
    std::cout << ii << " milliseconds\n";
}

void Timer::print_micro()
{
    auto ii{ std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count() * 1000 * 1000 };
    std::cout << ii << " microseconds\n";
}

void ignoreLine() // maybe #include <limits>
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string get_string(const std::string_view& sv = { "" })
{

    while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        std::cout << sv;
        std::string x;
        std::cin >> x;

        // Check for failed extraction
        if (!std::cin) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        else {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
}

bool playAgain()
{
    while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        std::cout << "Would you like to start again (y/n)?";
        char answer;
        std::cin >> answer;

        // Переменные типа char могут принимать любые символы из пользовательского ввода, поэтому нам не стоит беспокоиться по поводу возникновения неудачного извлечения

        // Check for failed extraction
        if (!std::cin) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        else {
            ignoreLine(); // remove any extraneous input
        }

        // Выполняем проверку пользовательского ввода
        if (answer == 'y') {
            std::cout << "\x1B[2J\x1B[H";
            return true;
        } // возвращаем обратно в caller
        else if (answer == 'n')
            return false; // возвращаем обратно в caller
        else // в противном случае, сообщаем пользователю что что-то пошло не так
            std::cout << "Oops, that input is invalid.  Please try again.\n";
    }
}

bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Перевіряємо числа на їх рівність один одному - це потрібно в випадках, коли числа, що порівнюються, є нульовими або "біля нуля"
    double diff = fabs(a - b);
    if (diff <= absEpsilon)
        return true;

    // В протилежному випадку повертаємося до алгоритму Кнута
    return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}
