#include "udfs/vector.hpp"
#include <string>

enum class Error_action { ignore, throwing, terminating, logging }; // error-handling alternatives
constexpr Error_action default_Error_action = Error_action::throwing;

enum class Error_code { range_error, length_error }; // individual errors
std::string error_code_name[] { "range error", "length error" }; // names of individual errors

template<Error_action action = default_Error_action, class C>
constexpr void expect(C cond, Error_code x) // take "action" if the expected condition "cond" doesn’t hold
{
    if constexpr (action == Error_action::logging)
    if (!cond()) std::cerr << "expect() failure: " << int(x) << ' ' << error_code_name[int(x)] << '\n';
    if constexpr (action == Error_action::throwing)
    if (!cond()) throw x;
    if constexpr (action == Error_action::terminating)
    if (!cond()) std::terminate();
    // or no action
}

template<typename T>
class ChildVec : public MyVector<T>{
    auto operator[](int i) -> T&;
};

template<typename T>
T& ChildVec<T>::operator[](int i)
{
    expect([i,this]() { return 0<=i && i<ChildVec::size(); }, Error_code::range_error);
    return this->elem[i];
}