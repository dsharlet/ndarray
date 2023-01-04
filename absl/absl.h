#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "array.h"

// Adds Abseil Stringify support (https://abseil.io/blog/20221115-stringify).

namespace nda {

// interval -> string as the half-open interval [begin, end).
//
// Stringifies only the values, not whether they are static or dynamic.
template <typename Sink, index_t Min, index_t Extent>
void AbslStringify(Sink& sink, const interval<Min, Extent>& i) {
  absl::Format(&sink, "[%v, %v)", i.min(), i.min() + i.extent());
}

// dim -> string as "dim(min, extent, stride)".
//
// Stringifies only the values, not whether they are static or dynamic.
template <typename Sink, index_t Min, index_t Extent, index_t Stride>
void AbslStringify(Sink& sink, const dim<Min, Extent, Stride>& d) {
  absl::Format(&sink, "dim(%v, %v, %v)", d.min(), d.extent(), d.stride());
}

// shape -> string as "shape<`rank`>(dims...).
//
// Stringifies only the rank and each dim's values, not whether they are static
// or dynamic.
//
// While this can be implemented at compile-time, it is not worth the code size
// and reduced readability.
template <typename Sink, class... Dims>
void AbslStringify(Sink& sink, const shape<Dims...>& sh) {
  absl::Format(&sink, "shape<%d>(%v)", sh.rank(), absl::StrJoin(sh.dims(), ", "));
}

} // namespace nda
