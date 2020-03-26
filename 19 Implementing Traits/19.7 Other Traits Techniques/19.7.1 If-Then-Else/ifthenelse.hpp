

//primary template: yleld the second argument by default and rely on
//a partial specialization to yield the third argument if COND is false.
template<bool COND, typename TrueType, typename FlaseType>
struct IfThenElseT{
    using Type = TrueType;
};

//partial spcialization: false yields third argument
template<typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType>
{
    using Type = FlaseType;
};

template<bool COND, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<COND, TrueType, FalseType>::Type;