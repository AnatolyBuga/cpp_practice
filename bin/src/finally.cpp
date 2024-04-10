template <class F>
struct Final_action {
explicit Final_action(F f) :act(f) {} // initialize
~Final_action() { act(); } // call action when going out of scope
F act; // our action, eg [&]{free(p);}
};

template <class F>
[[nodiscard]] auto finally(F f)
{
return Final_action{f};
}